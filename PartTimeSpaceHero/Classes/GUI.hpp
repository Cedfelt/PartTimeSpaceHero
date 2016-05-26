//
//  GoalObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//


#pragma once
#include "GameObject.hpp"
#include "PlayerObject.hpp"

using namespace cocos2d;
class GUI : public GameObject {
public:
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj);
  CREATE_FUNC(GUI);
  PlayerObject* player;
  void update(const float delta);
  Sprite* heartSprite[3];
private:
};