//
//  MapObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "MapObject.hpp"
#include "GlobalPList.hpp"

MapObject::MapObject() {
  
}

void MapObject::loadMap(const char* name) {
  map = TMXTiledMap::create(name);
  addChild(map);
}