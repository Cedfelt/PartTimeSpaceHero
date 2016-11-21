//
//  GoalObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//


#pragma once
#include "GameObject.hpp"

using namespace cocos2d;
class GoalObject : public GameObject {
public:
  bool setupAnimation();
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj, const uint32_t otherType);
  CREATE_FUNC(GoalObject);
  void ai_setup();
  int ai_state;
  void update(const float delta);
private:
  typedef enum tAi_states{
    NO_AI_STATE,
    AI_ENABLE,
    SHUTDOWN_AI,
    DRAIN_AI,
  }ai_states;
};
