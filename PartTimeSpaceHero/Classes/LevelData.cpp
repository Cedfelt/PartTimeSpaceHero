//
//  LevelData.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 30/05/16.
//
//

#include "LevelData.hpp"
#include "GlobalPList.hpp"

bool LevelData::init() {
  //////////////////////////////
  // 1. super init first
  if (!Node::init())
  {
    return false;
  }
  return true;
}

void LevelData::setupLevel(std::string mapName){
  this->mapName = mapName;
  description = "Into the Yonder";
}

bool LevelData::loadDataFromMemory(){
  auto userDef = cocos2d::UserDefault::getInstance();//->setIntegerForKey("scale_factor", (int)scale);
  
  std::string hsString = mapName + "_highScore";
  highScore = userDef->getIntegerForKey(hsString.c_str());
  
  std::string btString = mapName + "_bestTime";
  bestTime = userDef->getIntegerForKey(btString.c_str());
  
  std::string compString = mapName + "_completed";
  completed = userDef->getIntegerForKey(compString.c_str());

  userDef->flush();
  return true;
}

void LevelData::saveDataToMemory(){
  auto userDef = cocos2d::UserDefault::getInstance();//->setIntegerForKey("scale_factor", (int)scale);
  
  std::string hsString =   mapName + "_highScore";
  userDef->setIntegerForKey(hsString.c_str(), highScore);
  
  std::string btString = mapName + "_bestTime";
  userDef->setIntegerForKey(btString.c_str(), bestTime);
  
  std::string compString = mapName + "_completed";
  completed = userDef->getIntegerForKey(compString.c_str());
  userDef->flush();

}

std::string LevelData::getMapName() { return mapName; }

uint32_t LevelData::getHighScore() { return highScore; }

uint32_t LevelData::getBestTime() { return bestTime; }

bool LevelData::getCompleted() { return completed; }