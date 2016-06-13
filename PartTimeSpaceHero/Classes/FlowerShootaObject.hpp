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

using namespace cocos2d;
class FlowerShootaObject : public GameObject {
public:
  virtual bool init();
  CREATE_FUNC(FlowerShootaObject);
  SoundFx* pling;
  float shoot_timer;

  void update(const float delta);
private:
};
