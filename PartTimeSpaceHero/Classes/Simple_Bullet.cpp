//
//  Hero_Bullet.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 12/06/16.
//
//

#include "Simple_Bullet.hpp"
bool SimpleBullet::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  
  this->schedule(schedule_selector(SimpleBullet::update));
  addGravityToObject(false);
  // SETUP ANIMATIONS
  objectSprite = cocos2d::Sprite::create("turfel_baby.png");
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setPosition(8, 8);// Aling sprite in Hitbox
  objectSprite->setScale(2);
  addChild(objectSprite);
  dmg = 1;
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("explosion.plist");
  addAnimation("explosion", "explosion", 1, 12, 0.1f);
  start_animation = false;
  HP = 3;
  bullet_update = &SimpleBullet::explosive_bullet;
  x_bounce = 1;
  return true;
}

void SimpleBullet::setup(BULLET_TYPE bt){
  if(bt == E_SIMPLE_BULLET){
    setElastic(0.f);
    HP = 1;
    bullet_update = &SimpleBullet::simple_bullet;
  }
  else if(bt == E_EXPLOSIVE_BULLET){
    addGravityToObject(true);
    setElastic(1.2f);
    setVelocityY(25.f);
    HP = 3;
    bullet_update = &SimpleBullet::explosive_bullet;
  }
}

void SimpleBullet::colideWith(GameObject* oterhObj,const uint32_t otherType){
  oterhObj->hurt(dmg, Vec2(0.5f*getVelocityX(), 0.5f*getVelocityY()));
  oterhObj->setColor(Color3B::BLACK);
  start_animation = true;
  obstacle_mask = GO_LEFT|GO_RIGHT;
  
}

void SimpleBullet::update(const float delta) {
  (*this.*bullet_update)(delta);
}

bool SimpleBullet::explosive_bullet(float delta){
  if((obstacle_mask&GO_RIGHT||obstacle_mask&GO_LEFT) &&(!start_animation)){
    x_bounce-=1;
    if(x_bounce >= 0){
      obstacle_mask = 0;
      //return true; wall bounce
    }
    start_animation = true;
    setVelocityX(0);
    setVelocityY(0);
    addGravityToObject(false);
    
  }
  if(start_animation){
    bWallCollisions = false;
    setElastic(0);
    setVelocityX(getVelocityX()*0.95f);
    setVelocityY(getVelocityY()*0.95f);
    if(setAnimationOnce("explosion")){
      remove_object = true;
    }
  }
  return true;
}

bool SimpleBullet::simple_bullet(float delta){
  if(!getVelocityX()){
    remove_object = true;
  }
  return true;
}

bool SimpleBullet::setupAnimation() {
  return true;
}

void SimpleBullet::deadState() {
  remove_object = true;
}
