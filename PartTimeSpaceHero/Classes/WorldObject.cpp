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
  setViewPointCenter(Point(std::round(player->getObjectPositionX()),std::round(player->getObjectPositionY())));
  
  ////////////////////////////////////
  // MUSIC SETUP - SPECIFIC
  auto mapGroup = mapObject->map->getProperties();
  std::string track_name = mapGroup["music_track"].asString();
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic(track_name.c_str(), true);

   
  
  cocos2d::Director::getInstance()->getTextureCache()->removeAllTextures();
  physic->platforms = &plattis;
  return true;
}

cocos2d::Vector<GameObject*>* WorldObject::getGameObjects() {
  return &gameObjects;
}

void WorldObject::updateWorld(float delta) {
  physic->moveGameObjects(getGameObjects(), mapObject, delta);
  physic->movePlatform(physic->platforms, mapObject, delta);
  Point playerPos = cocos2d::Point(player->getObjectPositionX(),player->getObjectPositionY());
  const uint32_t offset = 71;
  playerPos.x = playerPos.x + offset;
  setViewPointCenter(playerPos);
  mapObject->moveBackgroundLayers();
 


  
  
  // Check Goal
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
  
  // Check if player dead
  if(player->HP==0){
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    stopAllActions();
    cocos2d::Director::getInstance()->popScene();
  }
  
  // Iterate objects
  for (int i = 0; i < gameObjects.size();i++) {
    // Remove Objects
    if (gameObjects.at(i)->remove_object) {
      GameObject *removeObj = gameObjects.at(i);
      this->removeChild(gameObjects.at(i));
      gameObjects.eraseObject(removeObj);
      removeObj->release();
      continue;
    }
    // add new objects from other objects
    if(gameObjects.at(i)->addToGameObjects.size()>0){
      for(int j = 0;j < gameObjects.at(i)->addToGameObjects.size();j++){
        gameObjects.pushBack(gameObjects.at(i)->addToGameObjects.at(j));
        addChild(gameObjects.at(i)->addToGameObjects.at(j));
      }
      gameObjects.at(i)->addToGameObjects.clear();
    }
  }
}

void WorldObject::setViewPointCenter(const cocos2d::Point position) {
  // NO PROBS HERE
  Size winSize = Director::getInstance()->getWinSize() / 2;//Scene Scale Factor
  const size_t tileSize = mapObject->getMapTileSize();
  const size_t scale = getScale();
  const size_t mapWidth = mapObject->getMapWidthInTiles()*scale;
  const size_t mapHeight = mapObject->getMapHeightInTiles()*scale;
  const size_t tilesOutsideLow = 16;
  float x = fmaxf(scale*position.x, winSize.width);
  float y = fmaxf(scale*position.y, winSize.height + tileSize*tilesOutsideLow);
  x = fminf(x, (mapWidth * tileSize) - winSize.width);
  y = fminf(y, (mapHeight * tileSize) - winSize.height);
  const Point actualPosition = Point(x, y);
  Point centerOfView = Point(winSize.width, winSize.height);
  centerOfView.subtract(actualPosition);// ccpSub(centerOfView, actualPosition);
  this->setPosition(centerOfView);
}

bool WorldObject::onContactBegan(PhysicsContact &contact) {
  auto *nodeA = (GameObject *)contact.getShapeA()->getBody()->getNode();
  auto * nodeB = (GameObject *)contact.getShapeB()->getBody()->getNode();
  if(nodeA->platform||nodeB->platform){
    return true;
  }
  nodeA->colideWith(nodeB);
  nodeB->colideWith(nodeA);
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
      player->setupHitbox(0.1, 1, 16, 31, 15, 25, false);
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
      botty->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::PlayerPickups|(int)PhysicsCategory::Hazard);
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
    
    gameObjects->at(gameObjects->size() -1)->mapData = mapObject->mapData;
    
  }
  for (int i = 0;i < gameObjects->size();i++) {
    gameObjects->at(i)->target = player;
  }
  for (int i = 0;i < plattis.size();i++) {
    plattis.at(i)->target = player;
  }
}
