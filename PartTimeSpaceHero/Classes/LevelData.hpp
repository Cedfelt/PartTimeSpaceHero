//
//  LevelData.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 30/05/16.
//
//

#ifndef LevelData_hpp
#include "cocos2d.h"
#define LevelData_hpp


#include <stdio.h>
class LevelData : public cocos2d::Node{
  std::string worldlName;
  std::string levelName;
  uint32_t highScore;
  uint32_t bestTime;
  bool completed;
  
  void init(std::string levelName,std::string worldName);
  bool loadDataFromMemory();
  void saveDataToMemory();
  std::string getLevelName();
  uint32_t getHighScore();
  uint32_t getBestTime();
  bool getCompleted();
};

#endif /* LevelData_hpp */
