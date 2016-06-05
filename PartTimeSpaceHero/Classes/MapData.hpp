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
    BLOCKED,
    WATER,
    CLEAR,
    ONE_WAY_UP,
    DESTRUCTABLE
  };
#define TILES_COUNT_X 1000
#define TILES_COUNT_Y 1000
  int attributes[TILES_COUNT_X][TILES_COUNT_Y];
  CREATE_FUNC(MapData);
  virtual bool init();
};

