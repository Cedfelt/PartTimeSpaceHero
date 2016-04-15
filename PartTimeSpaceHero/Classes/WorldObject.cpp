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
#include <math.h>
bool WorldObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init()) { return false; }

  mapObject = MapObject::create();
    mapObject->setAnchorPoint(Point(0,0));
  addChild(mapObject);

  player = PlayerObject::create();
  player->setupHitbox(32, 32, 32, 32, true);
    setAnchorPoint(Point(0,0));
  addChild(player);
  player->setupPlayer(0, 32);
  gameObjects.pushBack(player);

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
    physic->moveGameObjects(getGameObjects(),delta);
    setViewPointCenter(player->getPosition());
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

