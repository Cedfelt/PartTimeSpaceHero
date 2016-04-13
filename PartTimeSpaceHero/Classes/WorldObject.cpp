//
//  WorldObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "WorldObject.hpp"
#include "GlobalPList.hpp"
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
  // This Sets the scale for all World Objects
  
  this->schedule(schedule_selector(WorldObject::updateWorld));
  setViewPointCenter(player->getPosition());
  return true;
}

void WorldObject::updateWorld(float delta) {
  setViewPointCenter(player->getPosition());
}

void WorldObject::setViewPointCenter(cocos2d::Point position) {
  // NO PROBS HERE
  Size winSize = Director::getInstance()->getWinSize() / 2;//Scene Scale Factor
  const float tileSize = 8;
  const float mapsize = 200;
  const float mapHeight = 200;
  const float scale = getScale();

  float x = fmaxf(position.x, winSize.width);
  float y = fmaxf(position.y, winSize.height);
  x = fminf(x, (scale*mapsize * tileSize) - winSize.width);
  y = fminf(y, (scale*mapHeight * tileSize) - winSize.height);
    
    Point actualPosition = Point((int)x, (int)y);

  Point centerOfView = Point(winSize.width, winSize.height);
  centerOfView.subtract(actualPosition);// ccpSub(centerOfView, actualPosition);
    this->setPosition(centerOfView);
}

