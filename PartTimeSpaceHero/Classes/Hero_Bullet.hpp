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
class HeroBullet : public GameObject {
public:
  virtual bool init();
  CREATE_FUNC(HeroBullet);
  SoundFx* babyTurfelCrySFX;
  virtual void colideWith(GameObject *otherGo);
  
  void update(const float delta);
private:
};