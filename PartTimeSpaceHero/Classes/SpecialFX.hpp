//
//  SpecialFX.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 15/01/17.
//
//

//
//  CaveMonsters.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 15/01/17.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"
typedef enum tFX_ID
{
  POOF_FX,
  BIG_EXPLOSION_FX
}FX_ID;

using namespace cocos2d;
class SpecialFX : public GameObject {
public:
  virtual bool init();
  bool setupAnimation(int fx_type);
  void update(const float delta);
  CREATE_FUNC(SpecialFX);
  SoundFx* plingSFX;
  FX_ID fx_id;
  void setupFXType(FX_ID id);
protected:
private:
  
};
