//
//  ProximityZone.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 07/11/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"


using namespace cocos2d;
class ProximityZone : public GameObject {
public:
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(ProximityZone);
  bool setupAnimation();
  SoundFx* pling;
  void update(const float delta);
  
private:
};
