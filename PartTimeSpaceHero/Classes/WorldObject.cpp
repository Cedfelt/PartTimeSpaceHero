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
#include "GoalObject.hpp"
#include <math.h>
#include "SimpleAudioEngine.h"

enum class PhysicsCategory {
  None = 0,
  Player = (1 << 0),    // 1
  Bouncer = (1 << 1), // 2
  Goal = (1 << 2),
  All = 0xff // 3
};

bool WorldObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init()) { return false; }

  mapObject = MapObject::create();
  mapObject->setAnchorPoint(Point(0, 0));
  addChild(mapObject);

  spawnObjects(&gameObjects);

  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(WorldObject::onContactBegan, this);
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

  physic = Physic::create();

  // This Sets the scale for all World Objects
  const size_t scale = getScaleFactor();
  setScale(scale);
  this->schedule(schedule_selector(WorldObject::updateWorld));
  setViewPointCenter(player->getPosition());
  
  ////////////////////////////////////
  // MUSIC SETUP - SPECIFIC
  auto mapGroup = mapObject->map->getProperties();
  std::string track_name = mapGroup["music_track"].asString();
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic(track_name.c_str(), true);
  
  cocos2d::Director::getInstance()->getTextureCache()->removeAllTextures();
  return true;
}

cocos2d::Vector<GameObject*>* WorldObject::getGameObjects() {
  return &gameObjects;
}

void WorldObject::updateWorld(float delta) {
  physic->moveGameObjects(getGameObjects(), mapObject, delta);
  Point playerPos = player->getPosition();
  const uint32_t offset = 71;
  playerPos.x = playerPos.x + offset;
  setViewPointCenter(playerPos);
  mapObject->moveBackgroundLayers();
  
  // Check Goal
  if(obj->colided){
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    stopAllActions();
    cocos2d::Director::getInstance()->popScene();
    
  }
}

void WorldObject::setViewPointCenter(const cocos2d::Point position) {
  // NO PROBS HERE
  Size winSize = Director::getInstance()->getWinSize() / 2;//Scene Scale Factor
  const size_t tileSize = mapObject->getMapTileSize();
  const size_t scale = getScale();
  const size_t mapWidth = mapObject->getMapWidthInTiles()*scale;
  const size_t mapHeight = mapObject->getMapHeightInTiles()*scale;
  float x = fmaxf(scale*position.x, winSize.width);
  float y = fmaxf(scale*position.y, winSize.height);
  x = fminf(x, (mapWidth * tileSize) - winSize.width);
  y = fminf(y, (mapHeight * tileSize) - winSize.height);
  const Point actualPosition = Point((int)x, (int)y);
  Point centerOfView = Point(winSize.width, winSize.height);
  centerOfView.subtract(actualPosition);// ccpSub(centerOfView, actualPosition);
  this->setPosition(centerOfView);
}

bool WorldObject::onContactBegan(PhysicsContact &contact) {
  auto *nodeA = (GameObject *)contact.getShapeA()->getBody()->getNode();
  auto * nodeB = (GameObject *)contact.getShapeB()->getBody()->getNode();
  physic->gameObjectCollision(nodeA, nodeB);
  nodeA->colideWith(nodeB);
  nodeB->colideWith(nodeA);
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
    }
    
    else if(name == "CoinObject"){
      // COIN
      auto coin = CoinObject::create();
      coin->setupHitbox(0.1f, 1.0f, 19, 17, 19, 17, false);
      gameObjects->pushBack(coin);
      coin->setObjectPositionX(x);
      coin->setObjectPositionY(y);
      coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Bouncer);
      coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player|(int)PhysicsCategory::Bouncer);
      addChild(coin);
    }
    
    else if(name == "GoalObject"){
      // COIN
      this->obj = GoalObject::create();
      this->obj->setupHitbox(1, 1, 64, 64, 64, 64, false);
      gameObjects->pushBack(this->obj);
      this->obj->setObjectPositionX(x);
      this->obj->setObjectPositionY(y);
      this->obj->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Goal);
      this->obj->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
      this->obj->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Player);
      addChild(this->obj);
    }
  }
}
