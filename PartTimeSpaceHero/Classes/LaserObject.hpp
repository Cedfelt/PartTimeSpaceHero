//
//  LaserObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#pragma once
#include <stdio.h>
#include "cocos2d.h"
#include "GameObject.hpp"


USING_NS_CC;
#define MAX_CAPACITY 25
class LaserObject : public GameObject{
public:
  void setup(float output_time, float input_time, uint32_t direction, uint32_t range, float delay);
  int range;
  CREATE_FUNC(LaserObject);
  void updateGameObject(float delta);
  void add_updateFunction(float delta);
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  bool hurt(const int dmg, const Vec2 force);
  void addPhysicBody(uint32_t direction);
  Sprite *laser_sprites[MAX_CAPACITY];
  int current;
  bool output;
  uint32_t laser_dir;
  float o_time;
  float i_time;
  float laser_delay;
  float ot_counter;
  float maxLaserRange;
  float pause_time = 0;
private:
  uint32_t autoRange(uint32_t direction);
};
