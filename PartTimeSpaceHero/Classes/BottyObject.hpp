//
//  UfoObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 29/05/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class BottyObject : public GameObject {
public:
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(BottyObject);
  SoundFx* turtleCrySFX;
  void AIUpdate(const float delta);
  virtual void deadState();
private:
};
