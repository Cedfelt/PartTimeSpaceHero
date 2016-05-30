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
class BabyTurfelObject : public GameObject {
public:
  virtual bool init();
  virtual void interActWithPlayer(GameObject* player);
  CREATE_FUNC(BabyTurfelObject);
  SoundFx* babyTurfelCrySFX;
  
  void update(const float delta);
private:
};
