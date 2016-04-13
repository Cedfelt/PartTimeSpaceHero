//
//  GameObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "cocos2d.h"
#include <stdio.h>
using namespace cocos2d;
class GameObject : public cocos2d::DrawNode {
public:
  virtual bool init();
  CREATE_FUNC(GameObject);
  void setupHitbox(const float x, const float y, const float w, const float h,const bool draw);
private:
};


