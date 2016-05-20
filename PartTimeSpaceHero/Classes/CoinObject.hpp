//
//  Player.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include "GameObject.hpp"

using namespace cocos2d;
class CoinObject : public GameObject {
public:
  virtual bool init();
  CREATE_FUNC(CoinObject);
  void update(const float delta);
private:
};
