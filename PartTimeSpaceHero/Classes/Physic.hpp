//
//  GameObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "cocos2d.h"
#include "GameObject.hpp"
#include <stdio.h>
using namespace cocos2d;
class Physic : public cocos2d::Node {
public:
  virtual bool init();
  CREATE_FUNC(Physic);
  void moveGameObjects(cocos2d::Vector<GameObject*>* gameObjects,float delta);
  void colideGameObjects(cocos2d::Vector<GameObject*>* gameObjects);
    
    
private:
  const float gravity = 0;
};


