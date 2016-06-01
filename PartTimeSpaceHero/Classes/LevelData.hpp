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
  
public:
  std::string mapName;
  std::string description;
  uint32_t highScore;
  uint32_t bestTime;
  bool completed;
  
  CREATE_FUNC(LevelData);
  virtual bool init();
  void setupLevel(std::string levelName);
  bool loadDataFromMemory();
  void saveDataToMemory();
  std::string getMapName();
  uint32_t getHighScore();
  uint32_t getBestTime();
  bool getCompleted();
};

#endif /* LevelData_hpp */
