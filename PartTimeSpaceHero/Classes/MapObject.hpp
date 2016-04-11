//
//  MapObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class MapObject : public cocos2d::Node
{
public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  MapObject();
  void loadMap(const char* name);
  // implement the "static create()" method manually
  TMXTiledMap* map;
private:
  
};