//
//  WorldObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "WorldObject.hpp"
#include "MapObject.hpp"

WorldObject::WorldObject() {

}

void WorldObject::setupWorld() {
  MapObject* mapObject = new MapObject();
  auto tmx = new TMXTiledMap();
  FileUtils::getInstance()->addSearchPath("res");
  tmx = TMXTiledMap::create("alpha.tmx");
  addChild(mapObject);
}