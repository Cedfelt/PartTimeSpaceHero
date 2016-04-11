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

class WorldObject : public cocos2d::Node
{
public:
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  WorldObject();
  void setupWorld();
  // implement the "static create()" method manually
 

private:

};

