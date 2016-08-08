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
  
  // Comon
  bool (EffectZone::*playerEnter)(float);
  bool (EffectZone::*playerLeave)(float);
  bool doNothing(float delta);
  
  // Hide/Show layer
  TMXLayer* layerToHide;
  bool hideLayer(float delta);
  bool showLayer(float delta);
  // Hurl
  bool hurlPlayer(float delta);
  int hurlDirection;
  int hurlDirectionReverse;
  int hurlType;
  void stepTowards(float delta);
  void realHurl(float delta);
  virtual bool hurt(const int dmg, const Vec2 force);
  int step = 0;
  float stepSizeX;
  float stepSizeY;
  
  enum E_HURL_TYPES{
    HURL_TYPE_NONE,
    HURL_TYPE_START,
    HURL_TYPE_STOP,
    HURL_TYPE_TRANSFER
  };
  
  void addHurlSpeed(GameObject* obj,uint32_t hurlDirection);
  
private:
  
  void isPlayerInEffectZone(float delta);
};
