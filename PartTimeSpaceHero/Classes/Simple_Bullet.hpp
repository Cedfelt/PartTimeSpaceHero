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

typedef enum tBULLET_TYPE{
  E_SIMPLE_BULLET,
  E_EXPLOSIVE_BULLET
}BULLET_TYPE;

using namespace cocos2d;
class SimpleBullet : public GameObject {
public:
  virtual bool init();
  virtual void deadState();
  bool setupAnimation();
  CREATE_FUNC(SimpleBullet);
  SoundFx* babyTurfelCrySFX;
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  bool start_animation;
  void update(const float delta);
  bool explosive_bullet(float delta);
  bool simple_bullet(float delta);
  bool (SimpleBullet::*bullet_update)(float);
  void setup(BULLET_TYPE bt);
  int x_bounce;
private:
};
