//
//  LevelData.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 30/05/16.
//
//

#include "LevelData.hpp"
#include "GlobalPList.hpp"

void LevelData::init(std::string levelName,std::string worldName){
  this->levelName = levelName;
  this->worldlName = worldlName;
  loadDataFromMemory();
}


bool LevelData::loadDataFromMemory(){
  auto userDef = cocos2d::UserDefault::getInstance();//->setIntegerForKey("scale_factor", (int)scale);
  
  std::string hsString = worldlName + "_" + levelName + "_highScore";
  highScore = userDef->getIntegerForKey(hsString.c_str());
  
  std::string btString = worldlName + "_" + levelName + "_bestTime";
  bestTime = userDef->getIntegerForKey(btString.c_str());
  
  std::string compString = worldlName + "_" + levelName + "_completed";
  completed = userDef->getIntegerForKey(compString.c_str());
  return true;
}

void LevelData::saveDataToMemory(){
  auto userDef = cocos2d::UserDefault::getInstance();//->setIntegerForKey("scale_factor", (int)scale);
  
  std::string hsString = worldlName + "_" + levelName + "_highScore";
  userDef->setIntegerForKey(hsString.c_str(), highScore);
  
  std::string btString = worldlName + "_" + levelName + "_bestTime";
  userDef->setIntegerForKey(btString.c_str(), bestTime);
  
  std::string compString = worldlName + "_" + levelName + "_completed";
  completed = userDef->getIntegerForKey(compString.c_str());
}

std::string LevelData::getLevelName(){}

uint32_t LevelData::getHighScore(){}

uint32_t LevelData::getBestTime(){}

bool LevelData::getCompleted(){}