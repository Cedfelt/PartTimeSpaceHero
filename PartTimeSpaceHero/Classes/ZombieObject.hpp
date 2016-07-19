//
//  ZombieObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 19/07/16.
//
//

#pragma once
#include "EnemyObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class ZombieObject : public EnemyObject {
public:
  virtual bool init();
  bool setupAnimation();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(ZombieObject);
  SoundFx* plingSFX;
  void AIUpdate(const float delta);
  virtual void deadState();
private:
};
