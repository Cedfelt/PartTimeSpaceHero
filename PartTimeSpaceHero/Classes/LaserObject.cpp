//
//  LaserObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "LaserObject.hpp"
#include "cocos2d.h"

enum LASER_DIR {
  LASER_LEFT,
  LASER_RIGHT,
  LASER_UP,
  LASER_DOWN
};

void LaserObject::setup(float output_time, float input_time, uint32_t direction, uint32_t range, float delay) {
  CCASSERT(range < MAX_CAPACITY, "LASER BUGG TO SMALL");
  objectSprite = cocos2d::Sprite::create();
  setAnchorPoint(Point(0.5, 0));
  this->addChild(objectSprite);
  objectSprite->setAnchorPoint(Point(0.5, 0));
  //hitBoxWidth =  ;
  maxLaserRange = 8 * 2 * range + 8 * 4;
  //this->setRotation(180);
  addGravityToObject(false);
  spriteFrameCache = spriteFrameCache->getInstance();
  animationCache = animationCache->getInstance();
  spriteFrameCache->addSpriteFramesWithFile("laser_trap.plist");
  addAnimation("laser_trap", "laser_trap_base", 5, 5, 2.f);
  addAnimation("laser_trap", "laser_mid", 3, 4, 6.0 / 60.0);
  addAnimation("laser_trap", "laser_top_down", 1, 2, 6.0 / 60.0);
  setAnimation("laser_trap_base");
  o_time = output_time;
  i_time = input_time;
  ot_counter = o_time;
  setScale(2);
  setAnchorPoint(Point(0.5, 0));
  //moveWhenOutsideOfScreen = true;
  laser_delay = delay;
  bool b = true;
  this->range = range;
  //updateHitBox(1);
  for (int i = 1;i <= range;i++) {
    laser_sprites[i - 1] = Sprite::create("laser_trap.png");
    laser_sprites[i - 1]->setAnchorPoint(Point(0.5, 0));
    addChild(laser_sprites[i - 1]);
    laser_sprites[i - 1]->setPosition(0, i * 8);
    laser_sprites[i - 1]->runAction(RepeatForever::create(Animate::create(animationCache->getAnimation("laser_mid"))));
    laser_sprites[i - 1]->setOpacity(0);
    addChild(laser_sprites[i - 1]);
  }
  laser_sprites[range - 1]->stopAllActions();
  laser_sprites[range - 1]->runAction(RepeatForever::create(Animate::create(animationCache->getAnimation("laser_top_down"))));
  current = 0;
  
  
  output = true;
  ot_counter = o_time;
  ot_counter = 0;
  laser_dir = direction;
  addPhysicBody(laser_dir);
  add_updateFunction(delay);
  
}

void LaserObject::colideWith(GameObject *otherGo) {
  const float currentRange = (float)(current) / (float)(range);
  const float ra = (abs(getPositionY() - otherGo->getPositionY()));
  bool inRange = (maxLaserRange > ra);
  
  if (!output && inRange) {
    otherGo->hurt(1, Vec2(0,0));
  }
}

void LaserObject::add_updateFunction(float delta) {
  this->schedule(CC_SCHEDULE_SELECTOR(LaserObject::updateGameObject));
}

void LaserObject::updateGameObject(float delta) {
  if (ot_counter > 0) {
    ot_counter -= delta;
    return;
  }
  if (output) {
    laser_sprites[current]->setOpacity(0xFF);
    laser_sprites[current]->setScaleX(0.1f);
    laser_sprites[current]->setColor(Color3B::BLUE);
    current++;
    if(pause_time < 1.0){
      if(current>=range)
        current = range-1;
      pause_time += delta;
      return;
    }
    if (current == range) {
      output = false;
      solid = true;
      current = range - 1;
      ot_counter = o_time;
      pause_time = 0;
      getPhysicsBody()->setEnabled(true);
      for(int i = 0;i<range;i++){
        laser_sprites[i]->setScaleX(1.0f);
        laser_sprites[i]->setColor(Color3B::WHITE);
      }
    }
  }
  else {
    laser_sprites[current]->setOpacity(0x00);
    current--;
    if (current < 0) {
      output = true;
      current = 0;
      ot_counter = i_time;
      solid = false;
      getPhysicsBody()->setEnabled(false);
    }
  }
}

void LaserObject::addPhysicBody(uint32_t direction){
  auto physicsBody = PhysicsBody::createBox(Size(8, 8*range), PhysicsMaterial(0.1, 1, 0.0f));
  physicsBody->setDynamic(true);
  if(direction == GO_UP){
    physicsBody->setPositionOffset(Vec2(0, 8 * 2 * range + 8 * 4));
    setRotation(0);
  }
  if(direction == GO_DOWN){
    physicsBody->setPositionOffset(Vec2(0, (-(int)range*8*2- 8 * 4)));
    setRotation(180);
  }
  
  physicsBody->setCategoryBitmask((int)PhysicsCategory::Hazard);
  physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
  physicsBody->setContactTestBitmask((int)PhysicsCategory::All);
  physicsBody->setEnabled(false);
  setPhysicsBody(physicsBody);
}


//void Laser_Trap::updateAI(float delta) {}




