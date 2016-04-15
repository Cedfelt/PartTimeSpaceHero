//
//  MapObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "MapObject.hpp"
#include "GlobalPList.hpp"

bool MapObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init()){return false;}
  setAnchorPoint(Point(0,0));
  map = TMXTiledMap::create(getMapUrl());
    //map->setScale(3);
    map->setAnchorPoint(Point(0,0));
  addChild(map);
  return true;
}

void MapObject::setupBlocked() {

}

bool MapObject::isBlocked(const uint32_t x, const uint32_t y) {
  if (x < BLOCK_SIZE&&y < BLOCK_SIZE) {
    return blocked[x][y];
  }
}

