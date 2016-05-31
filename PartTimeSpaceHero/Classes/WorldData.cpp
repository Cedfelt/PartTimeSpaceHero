//
//  WorldData.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 30/05/16.
//
//

#include "WorldData.hpp"
#include "LevelData.hpp"

bool WorldData::init(){
  //////////////////////////////
  // 1. super init first
  if (!Node::init())
  {
    return false;
  }
}

void WorldData::loadWorldData() {
  // World 1
  LevelData* level1 = LevelData::create();
  level1->setupLevel("level1.tmx","world1");
  level1->loadDataFromMemory();
  world1.pushBack(level1);
  addChild(level1);

  LevelData* level2 = LevelData::create();
  level2->setupLevel("level2.tmx", "world1");
  level2->loadDataFromMemory();
  world1.pushBack(level2);
  addChild(level2);

  LevelData* level3 = LevelData::create();
  level3->setupLevel("level3.tmx", "world1");
  level3->loadDataFromMemory();
  world1.pushBack(level3);
  addChild(level3);

}