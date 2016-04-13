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
  
  map = TMXTiledMap::create(getMapUrl());
  addChild(map);
  return true;
}

