//
//  Collectables.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 05/08/17.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class Collectables : public GameObject {
public:
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(Collectables);
  bool setupAnimation();
  SoundFx* pling;
  void update(const float delta);
private:
};
