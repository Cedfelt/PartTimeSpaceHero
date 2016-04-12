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
  map = TMXTiledMap::create("db.tmx");
  addChild(map);
  return 32;
}
