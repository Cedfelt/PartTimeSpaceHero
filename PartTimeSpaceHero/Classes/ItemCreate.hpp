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
class ItemCreate : public GameObject {
public:
  bool setupAnimation();
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(ItemCreate);
  SoundFx* pling;
  bool isBlocked(Rect* playerRect);
  void update(const float delta);
  uint32_t random;
  bool landed;
  float goalY;
private:
};
