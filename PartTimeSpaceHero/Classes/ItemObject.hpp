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
class ItemObject : public GameObject {
public:
  DialogObject* dia;
  bool setupAnimation();
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(ItemObject);
  SoundFx* pling;
  
  uint32_t itemId;
  void update(const float delta);
  void generateItem(uint32_t itemType);
private:
  uint32_t random;
};
