//
//  MapData.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 03/06/16.
//
//


#pragma once
#include "cocos2d.h"


#include <stdio.h>
class MapData : public cocos2d::Node{
  
  
  
public:
  void setupAttributes(cocos2d::TMXTiledMap* map);
  enum{
    CLEAR, // NO_TILE
    LEFT_RAMP, // TILE 1
    RIGHT_RAMP,// TILE 2
    ONE_WAY_UP,// TILE 3
    DESTRUCTABLE,// TILE 4
    BLOCKED,// TILE 5 AND ABOVE
  };
#define TILES_COUNT_X 1000
#define TILES_COUNT_Y 1000
  int attributes[TILES_COUNT_X][TILES_COUNT_Y];
  CREATE_FUNC(MapData);
  virtual bool init();
};

