//
//  MudMonsterObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 09/10/16.
//
//

#pragma once
#include "EnemyObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class MudMonsterObject : public EnemyObject {
public:
  virtual bool init();
  bool setupAnimation();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(MudMonsterObject);
  SoundFx* plingSFX;
  void AIUpdate(const float delta);
  virtual void deadState();
private:
};
