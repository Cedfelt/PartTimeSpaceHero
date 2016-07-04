//
//  TurfelObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 27/05/16.
//
//

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
class TurfelObject : public GameObject {
public:
  virtual bool init();
  bool setupAnimation();
  virtual void interActWithPlayer(GameObject* player);
  CREATE_FUNC(TurfelObject);
  SoundFx* turtleCrySFX;
  
  void AIUpdate(const float delta);
private:
};
