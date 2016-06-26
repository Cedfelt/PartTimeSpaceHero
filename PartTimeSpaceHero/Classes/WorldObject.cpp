//
//  WorldObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "WorldObject.hpp"
#include "GlobalPList.hpp"
#include "Physic.hpp"
#include "CoinObject.hpp"
#include "TurfelObject.hpp"
#include "BottyObject.hpp"
#include "GoalObject.hpp"
#include "LaserObject.hpp"
#include "UfoObject.hpp"
#include <math.h>
#include "SimpleAudioEngine.h"
#include "DamageZone.hpp"
#include "PlatformObject.hpp"
#include "FlowerShootaObject.hpp"
#include "ItemCreate.hpp"



bool WorldObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init()) { return false; }

  mapObject = MapObject::create();
  mapObject->setAnchorPoint(Point(0, 0));
  addChild(mapObject);
  physic = Physic::create();
  addChild(physic);
  spawnObjects(&gameObjects);

  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(WorldObject::onContactBegan, this);
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

  

  // This Sets the scale for all World Objects
  const size_t scale = getScaleFactor();
  setScale(scale);
  this->schedule(schedule_selector(WorldObject::updateWorld));
  setViewPointCenter(Point((player->getObjectPositionX()),(player->getObjectPositionY())));
  
  ////////////////////////////////////
  // MUSIC SETUP - SPECIFIC
  auto mapGroup = mapObject->map->getProperties();
  std::string track_name = mapGroup["music_track"].asString();
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic(track_name.c_str(), true);

   
  
  cocos2d::Director::getInstance()->getTextureCache()->removeAllTextures();
  physic->platforms = &plattis;
  
  
  // Water Test
  cocos2d::TMXTilesetInfo *tilesetInfo;
  cocos2d::TMXLayerInfo *layerInfo;
  cocos2d::TMXMapInfo *mapInfo;
  //TMXLayer* water = TMXLayer::create(tilesetInfo, layerInfo, mapInfo);
  TMXLayer* water = mapObject->map->getLayer("water");
  return true;
}

cocos2d::Vector<GameObject*>* WorldObject::getGameObjects() {
  return &gameObjects;
}
float int_delta = 0;
uint32_t delta_cnt = 0;
const float delta_max = 120;
float new_delta = 1.0 / 60.0;
float lastX;
float lastY;
bool createSpawned = false;
void WorldObject::updateWorld(float delta) {
  if(delta_cnt ==delta_max){
    delta_cnt = 0;
    //new_delta = int_delta / (delta_max-1);
    int_delta = 0;
  }
  int_delta += delta;
  physic->moveGameObjects(getGameObjects(), mapObject, new_delta);
  physic->movePlatform(physic->platforms, mapObject, new_delta);
  Vec2 playerPos = Vec2(player->getObjectPositionX(),player->getObjectPositionY());
  const float offset = player->playerLookAhead;
  playerPos.x = playerPos.x + offset;
  mapObject->moveBackgroundLayers();
  setViewPointCenter(Vec2((playerPos.x + lastX)/2,(playerPos.y + lastY)/2));
  mapObject->updateLiquids(new_delta);
  lastX = playerPos.x;
  lastY = playerPos.y;

  // Check Goal
  if(obj!=NULL){
    if(obj->colided){
      // setCurrentCompleted
      auto sd = SaveData::create();
      sd->setCurrentLevelStatus(true,30,100);
      auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
      audio->stopBackgroundMusic();
      audio->pauseAllEffects();
      stopAllActions();
      cocos2d::Director::getInstance()->popScene();
    }
  }
  
  // Check if player dead
  if(player->HP==0){
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    stopAllActions();
    cocos2d::Director::getInstance()->popScene();
  }
  
  // Iterate objects
  for (int i = 0; i < gameObjects.size();i++) {
    // add new objects from other objects
    if(gameObjects.at(i)->addToGameObjects.size()>0){
      for(int j = 0;j < gameObjects.at(i)->addToGameObjects.size();j++){
        gameObjects.pushBack(gameObjects.at(i)->addToGameObjects.at(j));
        addChild(gameObjects.at(i)->addToGameObjects.at(j));
      }
      gameObjects.at(i)->addToGameObjects.clear();
    }
    // Remove Objects
    if (gameObjects.at(i)->remove_object) {
      GameObject *removeObj = gameObjects.at(i);
      /*removeObj->release();*/
      this->removeChild(gameObjects.at(i));
      gameObjects.eraseObject(removeObj);
      
      continue;
    }
    
  }

  // Spawn
  if ((player->getCoins() % 2 == 0) && (player->getCoins()>0)) {
    if (!createSpawned) {
      createSpawned = true;
      auto coin = ItemCreate::create();
      coin->setupHitbox(0.1f, 1.0f, 32, 32, 32, 32, false);
      coin->target = player;
      gameObjects.pushBack(coin);
      coin->setObjectPositionX(player->getObjectPositionX());
      coin->setObjectPositionY(player->getObjectPositionY()+128);
      coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerPickups);
      coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player | (int)PhysicsCategory::PlayerProjectile | (int)PhysicsCategory::Hazard);
      addChild(coin);

    }
  }
  else {
    createSpawned = false;
  }

  delta_cnt += 1;
}

void WorldObject::setViewPointCenter(const cocos2d::Point position) {
  // NO PROBS HERE
  Size winSize = Director::getInstance()->getWinSize() / 2.0;//Scene Scale Factor
  const float tileSize = mapObject->getMapTileSize();
  const float scale = getScale();
  const float mapWidth = mapObject->getMapWidthInTiles()*scale;
  const float mapHeight = mapObject->getMapHeightInTiles()*scale;
  const float tilesOutsideLow = 16;
  float x = fmaxf(scale*position.x, winSize.width);
  float y = fmaxf(scale*position.y, winSize.height + tileSize*tilesOutsideLow);
  x = fminf(x, (mapWidth * tileSize) - winSize.width);
  y = fminf(y, (mapHeight * tileSize) - winSize.height);
  const cocos2d::Point actualPosition = cocos2d::Point(int(x), int(y));
  cocos2d::Point centerOfView = cocos2d::Point(winSize.width, winSize.height);
  centerOfView.subtract(actualPosition);// ccpSub(centerOfView, actualPosition);
  this->setPosition(centerOfView);
}

bool WorldObject::onContactBegan(PhysicsContact &contact) {
  auto *nodeA = (GameObject *)contact.getShapeA()->getBody()->getNode();
  auto * nodeB = (GameObject *)contact.getShapeB()->getBody()->getNode();
  const uint32_t aType = nodeA->getObjectType();
  const uint32_t bType = nodeB->getObjectType();
  
  if(nodeA->platform||nodeB->platform){
    return true;
  }
  //  Player = (1 << 0),    // 1
  //  PlayerPickups = (1 << 1), // 2
  //  Goal = (1 << 2),
  //  Hazard = (1 << 3),
  //  Enemy = (1 << 4),
  nodeA->colideWith(nodeB,bType);
  nodeB->colideWith(nodeA,aType);
  physic->gameObjectCollision(nodeA, nodeB);
  return true;
}

void WorldObject::spawnObjects(cocos2d::Vector<GameObject*>* gameObjects) {
  
  const std::string objectName = "GameObjects";
  auto objectGroup = mapObject->map->getObjectGroup(objectName);
  ValueVector obj = objectGroup->getObjects();
  for (int i = 0;i < obj.size();i++) {
    ValueMap vm = obj.at(i).asValueMap();
    int x = vm["x"].asInt();
    int y = vm["y"].asInt();
    float w = vm["width"].asInt();
    float h = vm["height"].asInt();
    //x *= level->getScale();
    //y *= level->getScale();;
    //w *= level->getScale();;
    //h *= level->getScale();;
    std::string name = vm["name"].asString();
    std::string type = vm["type"].asString();
    
    if (name == "PlayerObject") {
      player = PlayerObject::create();
      player->setupHitbox(0.1, 1, 10, 25, 10, 25, false);
      //setAnchorPoint(Point(0,0));
      player->setupPlayer(x, y);
      gameObjects->pushBack(player);
      player->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Player);
      player->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      player->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::All);
      addChild(player);
      addChild(player->objectSprite);
      player->objectSprite->autorelease();
    }
    
    else if(name == "CoinObject"){
      // COIN
      auto coin = CoinObject::create();
      coin->setupHitbox(0.1f, 1.0f, 19, 17, 19, 17, false);
      gameObjects->pushBack(coin);
      coin->setObjectPositionX(x);
      coin->setObjectPositionY(y);
      coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerPickups);
      coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::PlayerPickups|(int)PhysicsCategory::Hazard);
      addChild(coin);
    }

    else if (name == "ItemCreate") {
      // COIN
      auto coin = ItemCreate::create();
      coin->setupHitbox(0.1f, 1.0f, 32, 32, 32, 32, false);
      gameObjects->pushBack(coin);
      coin->setObjectPositionX(x);
      coin->setObjectPositionY(y);
      coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::PlayerPickups);
      coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player | (int)PhysicsCategory::PlayerProjectile | (int)PhysicsCategory::Hazard);
      addChild(coin);
    }
    
    else if(name == "GoalObject"){
      // COIN
      this->obj = GoalObject::create();
      this->obj->setupHitbox(1, 1, 32, 32, 32, 32, false);
      gameObjects->pushBack(this->obj);
      this->obj->setObjectPositionX(x);
      this->obj->setObjectPositionY(y);
      this->obj->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Goal);
      this->obj->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      this->obj->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player);
      addChild(this->obj);
    }
    
    else if(name == "LaserObject"){
      // LaserObject
      uint32_t direction = vm["direction"].asInt();
      uint32_t range = vm["range"].asInt();
      float delay = vm["delay"].asFloat();
      float duration = vm["duration"].asFloat();
      float off_time = vm["off_time"].asFloat();
      auto obj = LaserObject::create();
      
      //obj->setupHitbox(1, 1, 64, 64, 64, 64, false);
      obj->setup(duration,off_time,direction, range, delay);
      gameObjects->pushBack(this->obj);
      obj->setObjectPositionX(x);
      obj->setObjectPositionY(y);
      //obj->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Bouncer);
      //obj->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      //obj->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player);
      addChild(obj);
    }
    
    else if(name == "TurfelObject"){
      // COIN
      auto turfel = TurfelObject::create();
      const float turfelScale = 2;
      turfel->setupHitbox(0.1f, 1.0f, 32, 32, 32, 32, false);
      gameObjects->pushBack(turfel);
      turfel->setObjectPositionX(x);
      turfel->setObjectPositionY(y);
      turfel->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      turfel->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      turfel->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::PlayerPickups|(int)PhysicsCategory::Hazard);
      turfel->target = player;
      addChild(turfel);
    }
    
    else if(name == "UfoObject"){
      // COIN
      auto patrolUfo = UfoObject::create();
      const float ufoScale = 4;
      patrolUfo->setupHitbox(0.1f, 1.0f, 16*ufoScale, 16*ufoScale, 16*ufoScale, 16*ufoScale, false);
      gameObjects->pushBack(patrolUfo);
      patrolUfo->setObjectPositionX(x);
      patrolUfo->setObjectPositionY(y);
      patrolUfo->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      patrolUfo->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      patrolUfo->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::PlayerPickups|(int)PhysicsCategory::Hazard);
      patrolUfo->target = player;
      patrolUfo->softXMax = x+w;
      patrolUfo->softXMin = x;
      addChild(patrolUfo);
    }
    
    else if(name == "BottyObject"){
      // COIN
      auto botty = BottyObject::create();
      botty->setupHitbox(0.1, 1, 24, 48, 24, 44, false);
      gameObjects->pushBack(botty);
      botty->setObjectPositionX(x);
      botty->setObjectPositionY(y);
      botty->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      botty->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      botty->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::PlayerProjectile|(int)PhysicsCategory::Hazard);
      botty->target = player;
      addChild(botty);
    }
    else if(name == "DamageZone"){
      // COIN
      auto botty = DamageZone::create();
      botty->setupHitbox(0.1, 1, w, h, w, h, false);
      gameObjects->pushBack(botty);
      botty->setObjectPositionX(x);
      botty->setObjectPositionY(y);
      botty->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      botty->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      botty->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::All);
      botty->dmg = vm["dmg"].asInt();
      botty->target = player;
      addChild(botty);
    }
    else if(name == "PlatformObject"){
      // COIN
      auto botty = PlatformObject::create();
      botty->setupHitbox(0.1, 1, 64, 32, 64, 32, false);
      //gameObjects->pushBack(botty);
      botty->setObjectPositionX(x);
      botty->setObjectPositionY(y);
      botty->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      botty->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      botty->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::None);
      botty->dmg = vm["dmg"].asInt();
      botty->target = player;
      plattis.pushBack(botty);
      addChild(botty,3);
    }
    else if (name == "FlowerShootaObject") {
      // COIN
      auto patrolUfo = FlowerShootaObject::create();
      const float ufoScale = 1;
      patrolUfo->setupHitbox(0.1f, 1.0f, 16 * ufoScale, 16 * ufoScale, 16 * ufoScale, 16 * ufoScale, false);
      gameObjects->pushBack(patrolUfo);
      patrolUfo->setObjectPositionX(x);
      patrolUfo->setObjectPositionY(y);
      patrolUfo->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Enemy);
      patrolUfo->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      patrolUfo->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player | (int)PhysicsCategory::PlayerPickups | (int)PhysicsCategory::Hazard);
      patrolUfo->target = player;
      addChild(patrolUfo);
    }
    
    else if (name == "LabelObject") {
      // LABEL
      auto label = Label::createWithTTF(vm["msg"].asString(), "fonts/Marker Felt.ttf", 25);
      label->setPosition(Vec2((int)x,(int)y));
      
      addChild(label,-1);
    }
    
    gameObjects->at(gameObjects->size() -1)->mapData = mapObject->mapData;
    
  }
  for (int i = 0;i < gameObjects->size();i++) {
    gameObjects->at(i)->target = player;
  }
  for (int i = 0;i < plattis.size();i++) {
    plattis.at(i)->target = player;
  }
}
