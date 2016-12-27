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

void SaveData::addLevelToGame(std::string levelName,std::string description){
  LevelData* newLevel = LevelData::create();
  newLevel->setupLevel(levelName);
  newLevel->description = description;
  newLevel->loadDataFromMemory();
  levelDataList.pushBack(newLevel);
  addChild(newLevel);
}

void SaveData::loadWorldData() {
  // Tutorial
  // Intro
  //addLevelToGame("tutorial2.tmx");
  //addLevelToGame("level1.tmx");
  addLevelToGame("design_test.tmx", "Dev Level");
  addLevelToGame("happy space.tmx", "Welcome to Scarp Yard 0x41A3");
  addLevelToGame("level2.tmx","Brace for Impact");
  addLevelToGame("the_second_step.tmx", "Down below");
  addLevelToGame("metroid_cave.tmx");
  
  addLevelToGame("djungel2.tmx","Up like a pancake");
  addLevelToGame("tutorial.tmx","Into The Yonder");
  addLevelToGame("nes_test.tmx","It should be here somewhere..");
  
  addLevelToGame("forest_dungeon.tmx","You Want it Darker");
  addLevelToGame("bellas_house.tmx","Something for the handy... ");
  
  
  addLevelToGame("level3.tmx");
  addLevelToGame("knock_knock.tmx");
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
