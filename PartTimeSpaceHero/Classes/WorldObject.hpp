//
//  WorldObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "MapObject.hpp"
#include "GameObject.hpp"
class WorldObject : public cocos2d::Node
{
public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();
  // implement the "static create()" method manually
  CREATE_FUNC(WorldObject);
private:
  MapObject* mapObject;
  void setViewPointCenter(cocos2d::Point position);


};

