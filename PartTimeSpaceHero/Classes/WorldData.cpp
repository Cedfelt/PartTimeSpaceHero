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
  return true;
}

void WorldData::loadWorldData() {
  // World 1
  LevelData* level1 = LevelData::create();
  level1->setupLevel("level1.tmx");
  level1->loadDataFromMemory();
  world1.pushBack(level1);
  addChild(level1);

  LevelData* level2 = LevelData::create();
  level2->setupLevel("level2.tmx");
  level2->loadDataFromMemory();
  world1.pushBack(level2);
  addChild(level2);

  LevelData* level3 = LevelData::create();
  level3->setupLevel("level3.tmx");
  level3->loadDataFromMemory();
  world1.pushBack(level3);
  addChild(level3);
}

std::string currentLevel = "CURRENT_LEVEL";

void WorldData::setCurrentLevel (E_LEVEL eLevel, E_WORLD eWorld) {
  auto userDef = cocos2d::UserDefault::getInstance();
  userDef->setIntegerForKey(currentLevel.c_str(),eLevel);
  userDef->flush();
}

LevelData* WorldData::getCurrentLevel() {
  auto userDef = cocos2d::UserDefault::getInstance();
  E_LEVEL eLevel = (E_LEVEL)userDef->getIntegerForKey(currentLevel.c_str());
  if (eLevel<world1.size()) {
    world1.at(eLevel)->loadDataFromMemory();
    return world1.at(eLevel);
  }
  return NULL;
}

size_t WorldData::levelCountForWorld(const E_WORLD eWorld) {
  if (eWorld == WORLD_1)
  {
    return world1.size();
  }
  else if (eWorld == WORLD_2)
  {
    return world2.size();
  }
  else if (eWorld == WORLD_3)
  {
    return world3.size();
  }
  else if (eWorld == WORLD_4)
  {
    return world4.size();
  }
  else if (eWorld == WORLD_5)
  {
    return world5.size();
  }
  else if (eWorld == WORLD_6)
  {
    return world6.size();
  }
  else if (eWorld == WORLD_7)
  {
    return world7.size();
  }
  else if (eWorld == WORLD_8)
  {
    return world8.size();
  }
  else if (eWorld == WORLD_9)
  {
    return world9.size();
  }
  else if (eWorld == WORLD_10)
  {
    return world10.size();
  }
  return 0;
}

void WorldData::setCurrentLevelStatus(const bool completed,const uint32_t score,const uint32_t bestTime) {
  LevelData* levelData = getCurrentLevel();
  levelData->completed = completed;
  levelData->highScore = score;
  levelData->bestTime = bestTime;
  levelData->saveDataToMemory();
}