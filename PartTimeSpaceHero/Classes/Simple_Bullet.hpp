//
//  Hero_Bullet.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 12/06/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class SimpleBullet : public GameObject {
public:
  virtual bool init();
  bool setupAnimation();
  CREATE_FUNC(SimpleBullet);
  SoundFx* babyTurfelCrySFX;
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  bool start_animation;
  void update(const float delta);
private:
};
