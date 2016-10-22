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

void SaveData::addLevelToGame(std::string levelName){
  LevelData* newLevel = LevelData::create();
  newLevel->setupLevel(levelName);
  newLevel->loadDataFromMemory();
  levelDataList.pushBack(newLevel);
  addChild(newLevel);
}

void SaveData::loadWorldData() {
  // Tutorial
  addLevelToGame("tutorial.tmx");
  addLevelToGame("nes_test.tmx");
  
  
  // Intro
  addLevelToGame("level1.tmx");
  
  // Beta Levels
  addLevelToGame("level2.tmx");
  addLevelToGame("djungel2.tmx");
  addLevelToGame("level3.tmx");
  addLevelToGame("level4.tmx");
  
  
  }

void SaveData::eraseMemorey(){
  auto user = cocos2d::UserDefault::getInstance();
  user->destroyInstance();
  for(int i = 0;i<levelDataList.size();i++){
    levelDataList.at(i)->eraseDataFromMemory();
  }
  setPlayerGear(0);
  setPlayerMoney(0);
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
