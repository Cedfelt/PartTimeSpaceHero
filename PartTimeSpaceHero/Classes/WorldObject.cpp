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
#include <math.h>

enum class PhysicsCategory {
  None = 0,
  Monster = (1 << 0),    // 1
  Projectile = (1 << 1), // 2
  All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
};

bool WorldObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init()) { return false; }

  mapObject = MapObject::create();
  mapObject->setAnchorPoint(Point(0, 0));
  addChild(mapObject);

  // PLAYER
  player = PlayerObject::create();
  player->setupHitbox(256, 256, 16, 31, 15, 25, false);
  //setAnchorPoint(Point(0,0));
  player->setupPlayer(90, 80);
  gameObjects.pushBack(player);
  player->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Monster);
  player->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
  player->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Projectile);
  addChild(player);

  // COIN
  auto coin = CoinObject::create();
  coin->setupHitbox(256, 256, 16, 16, 16, 16, false);
  gameObjects.pushBack(coin);
  coin->setObjectPositionX(100);
  coin->setObjectPositionY(200);
  coin->getPhysicsBody()->setCategoryBitmask((int)PhysicsCategory::Projectile);
  coin->getPhysicsBody()->setCollisionBitmask((int)PhysicsCategory::None);
  coin->getPhysicsBody()->setContactTestBitmask((int)PhysicsCategory::Monster);
  addChild(coin);
  
  auto contactListener = EventListenerPhysicsContact::create();
  contactListener->onContactBegin = CC_CALLBACK_1(WorldObject::onContactBegan, this);
  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

  physic = Physic::create();

  // This Sets the scale for all World Objects
  const size_t scale = getScaleFactor();
  setScale(scale);
  this->schedule(schedule_selector(WorldObject::updateWorld));
  setViewPointCenter(player->getPosition());
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
  GameObject *nodeA = (GameObject *)contact.getShapeA()->getBody()->getNode();
  GameObject * nodeB = (GameObject *)contact.getShapeB()->getBody()->getNode();
  const Vec2 repA = Vec2(nodeB->getVelocityX(), nodeB->getVelocityY());
  const Vec2 repB = Vec2(nodeA->getVelocityX(), nodeA->getVelocityY());
  
  nodeA->setVelocityX(repA.x);
  nodeA->setVelocityY(repA.y);
  nodeB->setVelocityX(repB.x);
  nodeB->setVelocityY(repB.y);
  


  //nodeA->removeFromParent();
  //nodeB->removeFromParent();
  return true;
}

