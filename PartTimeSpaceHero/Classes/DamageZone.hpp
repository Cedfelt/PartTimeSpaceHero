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
  virtual void colideWith(GameObject *otherGo);
  CREATE_FUNC(DamageZone);
  SoundFx* pling;
private:
};
