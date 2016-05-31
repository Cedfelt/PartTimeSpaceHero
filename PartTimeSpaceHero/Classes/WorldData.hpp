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

class WorldData : public cocos2d::Node {
public:
  virtual bool init();
  CREATE_FUNC(WorldData);
  void loadWorldData();
  cocos2d::Vector<LevelData*> world1;
};

#endif /* WorldData_hpp */
