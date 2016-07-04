//
//  GoalObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//


#pragma once
#include "GameObject.hpp"

using namespace cocos2d;
class GoalObject : public GameObject {
public:
  bool setupAnimation();
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj);
  CREATE_FUNC(GoalObject);
  void update(const float delta);
private:
};
