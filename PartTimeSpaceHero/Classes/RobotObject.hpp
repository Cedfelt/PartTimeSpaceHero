//
//  RobotObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 22/12/16.
//
//

#pragma once
#include "EnemyObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class RobotObject : public EnemyObject {
public:
  virtual bool init();
  bool setupAnimation();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(RobotObject);
  SoundFx* plingSFX;
  void AIUpdate(const float delta);
  void ShootXDir(const float delta);
  virtual void deadState();
protected:
  enum {
    PATROL,
    AIM,
    SHOOT,
    AIM_DOWN,
    DEAD
  };
  float AI_TIMER;
private:
};
