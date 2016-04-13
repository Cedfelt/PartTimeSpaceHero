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
  addChild(mapObject);

  auto go = GameObject::create();
  go->setupHitbox(32, 32, 32, 32, true);
  addChild(go);

  // This Sets the scale for all World Objects
  setScale(getScaleFactor());

  setViewPointCenter(Point(500, 0));
  return true;
}

void WorldObject::setViewPointCenter(cocos2d::Point position) {
  // NO PROBS HERE
  Size winSize = Director::getInstance()->getWinSize() / 1;//Scene Scale Factor
  const float tileSize = 8;
  const float mapsize = 200;
  const float mapHeight = 200;
  const float scale = 2;

  float x = fmaxf(position.x, winSize.width / 2);
  float y = fmaxf(position.y, winSize.height / 2);
  x = fminf(x, (scale*mapsize * tileSize) - winSize.width / 2);
  y = fminf(y, (scale*mapHeight * tileSize) - winSize.height / 2);
  Point actualPosition = Point(x, y);

  Point centerOfView = Point(winSize.width / (2), winSize.height / (2));
  centerOfView.subtract(actualPosition);// ccpSub(centerOfView, actualPosition);
    this->setPosition(centerOfView);
}

