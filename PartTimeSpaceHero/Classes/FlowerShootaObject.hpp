#pragma once

//
//  Player.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"
#include "EnemyObject.hpp"

using namespace cocos2d;
class FlowerShootaObject : public EnemyObject {
public:
  bool setupAnimation();
  virtual bool init();
  CREATE_FUNC(FlowerShootaObject);
  SoundFx* pling;
  float shoot_timer;
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  void update(const float delta);
private:
};
