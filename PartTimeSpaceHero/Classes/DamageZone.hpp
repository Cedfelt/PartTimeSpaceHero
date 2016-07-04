//
//  DamageZone.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 04/06/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class DamageZone : public GameObject {
public:
  virtual bool init();
  float xForce;
  float yForce;
  bool setupAnimation();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  bool hurt(const int dmg, const Vec2 force);
  CREATE_FUNC(DamageZone);
  SoundFx* pling;
private:
};
