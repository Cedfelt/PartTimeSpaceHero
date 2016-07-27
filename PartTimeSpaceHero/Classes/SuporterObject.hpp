//
//  SuporterObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 27/07/16.
//
//

#pragma once
#include "EnemyObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class SuporterObject : public GameObject {
public:
  virtual bool init();
  bool setupAnimation();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(SuporterObject);
  SoundFx* plingSFX;
  bool isThisfirst = true;
  void update(const float delta);
  float xVar;
  float yVar;
  float xtick;
  float ytick;
  virtual void deadState();
private:
};
