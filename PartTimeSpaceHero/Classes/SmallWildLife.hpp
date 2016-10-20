//
//  SmallWildLife.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 20/10/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"
#include "EnemyObject.hpp"

using namespace cocos2d;
class SmallWildLife : public EnemyObject {
public:
  virtual bool init();
  bool setupAnimation();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(SmallWildLife);
  SoundFx* turtleCrySFX;
  
  void AIUpdate(const float delta);
private:
};
