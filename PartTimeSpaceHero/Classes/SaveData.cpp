//
//  WorldData.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 30/05/16.
//
//

#include "SaveData.hpp"
#include "LevelData.hpp"

LevelData* currentLevelData;
cocos2d::Vector<LevelData*> levelDataList;

bool SaveData::init(){
  //////////////////////////////
  // 1. super init first
  if (!Node::init())
  {
    return false;
  }
  return true;
}

void SaveData::loadWorldData() {
  // World 1
  LevelData* level1 = LevelData::create();
  level1->setupLevel("level1.tmx");
  level1->loadDataFromMemory();
  levelDataList.pushBack(level1);
  addChild(level1);

  LevelData* level2 = LevelData::create();
  level2->setupLevel("level2.tmx");
  level2->loadDataFromMemory();
  levelDataList.pushBack(level2);
  addChild(level2);

  LevelData* level3 = LevelData::create();
  level3->setupLevel("level3.tmx");
  level3->loadDataFromMemory();
  levelDataList.pushBack(level3);
  addChild(level3);
  
  LevelData* level4 = LevelData::create();
  level4->setupLevel("level4.tmx");
  level4->loadDataFromMemory();
  levelDataList.pushBack(level4);
  addChild(level4);
}

void SaveData::eraseMemorey(){
  auto user = cocos2d::UserDefault::getInstance();
  user->destroyInstance();
  for(int i = 0;i<levelDataList.size();i++){
    levelDataList.at(i)->eraseDataFromMemory();
  }
}

 LevelData* SaveData::getCurrentLevel() {
  return currentLevelData;
}

void SaveData::setCurrentLevelStatus(const bool completed,const uint32_t score,const uint32_t bestTime) {
  LevelData* levelData = getCurrentLevel();
  levelData->completed = completed;
  levelData->highScore = score;
  levelData->bestTime = bestTime;
  levelData->saveDataToMemory();
}

bool SaveData::prepareNextLevel(){
  for(int i = 0;i<levelDataList.size();i++){
    levelDataList.at(i)->loadDataFromMemory();
    if(!levelDataList.at(i)->getCompleted()){
      currentLevelData = levelDataList.at(i);
      return true;
    }
  }
  return false;
}