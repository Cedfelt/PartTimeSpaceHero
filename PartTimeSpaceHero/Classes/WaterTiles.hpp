//
//  WaterTiles.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 11/06/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class WaterTiles : public cocos2d::TMXLayer {
public:
  virtual bool init();
  CREATE_FUNC(WaterTiles);
  void update(const float delta);
  float timeCnt;
  float animationSpeed;
  
  
  
private:
};