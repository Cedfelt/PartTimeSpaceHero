//
//  WaterTiles.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 11/06/16.
//
//

#include "WaterTiles.hpp"
bool WaterTiles::init() {
  //////////////////////////////
  // 1. super init first
  if (!TMXLayer::init())
  {
    return false;
  }
  animationSpeed = 0.4f;
  this->schedule(schedule_selector(WaterTiles::update));
  return true;
}

void WaterTiles::update(const float delta) {
  timeCnt+=delta;
  if(timeCnt<animationSpeed/2.0){
    _tileSet->_originSourceImage = "water1.png";
  }
  else{
    _tileSet->_originSourceImage = "water2.png";
  }
}