//
//  EffectZone.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 06/08/16.
//
//

//
//  SignObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 26/07/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class EffectZone : public GameObject {
public:
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(EffectZone);
  void config(std::string type);
  bool (EffectZone::*playerEnter)(float);
  bool (EffectZone::*playerLeave)(float);
  TMXLayer* layerToHide;
private:
  bool hideLayer(float delta);
  bool showLayer(float delta);
  void isPlayerInEffectZone(float delta);
};
