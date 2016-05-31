//
//  WorldData.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 30/05/16.
//
//

#ifndef WorldData_hpp
#define WorldData_hpp
#include "cocos2d.h"
#include "LevelData.hpp"
#include "GlobalPList.hpp"
#include <stdio.h>


enum E_WORLD {
  WORLD_1,
  WORLD_2,
  WORLD_3,
  WORLD_4,
  WORLD_5,
  WORLD_6,
  WORLD_7,
  WORLD_8,
  WORLD_9,
  WORLD_10
};

enum E_LEVEL {
  LEVEL_1,
  LEVEL_2,
  LEVEL_3,
  LEVEL_4,
  LEVEL_5,
  LEVEL_6,
  LEVEL_7,
  LEVEL_8,
  LEVEL_9,
  LEVEL_10
};

class WorldData : public cocos2d::Node {
public:
  virtual bool init();
  CREATE_FUNC(WorldData);
  void loadWorldData();
  cocos2d::Vector<LevelData*> world1;
  void setCurrentLevel(E_LEVEL eLevel, E_WORLD eWorld);
  LevelData* getCurrentLevel();
};

#endif /* WorldData_hpp */
