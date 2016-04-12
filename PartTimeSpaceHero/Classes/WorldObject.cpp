//
//  WorldObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "WorldObject.hpp"


bool WorldObject::init() {
  mapObject = MapObject::create();
  addChild(mapObject);
  return true;
}

