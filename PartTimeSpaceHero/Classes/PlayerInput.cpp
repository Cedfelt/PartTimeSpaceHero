//
//  PlayerInput.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "PlayerInput.hpp"
#include "ui/CocosGUI.h"

bool PlayerInput::init() {
  if (!Node::init()){return false;}
  auto touchListener = EventListenerTouchAllAtOnce::create();
  touchListener->onTouchesBegan = CC_CALLBACK_2(PlayerInput::onTouchBegan, this);
  touchListener->onTouchesEnded = CC_CALLBACK_2(PlayerInput::onTouchEnded, this);
  touchListener->onTouchesMoved = CC_CALLBACK_2(PlayerInput::onTouchMoved, this);
  touchListener->onTouchesCancelled = CC_CALLBACK_2(PlayerInput::onTouchCancelled, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
  swipeAmountL = 0;
  swipeAmountR = 0;
  tapChecks = 0;
  taps = 15;
  
  softWareResetR = false;
  fSWDistR = 0;
  softWareResetL = false;
  fSWDistL = 0;
  return true;
}


void PlayerInput::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  for (int i = 0;i < touch.size();i++) {
    if (touch.at(i)->getLocation().x < winSize.width / 2) {
      left = true;

      if (rightCounter < 2)// Dont want double tap on both
        leftCounter++;
    }
    else {
      right = true;
      if (leftCounter < 2)
        rightCounter++;
    }
  }
  tapChecks = 0;
  unschedule(schedule_selector(PlayerInput::tapCounter));
  this->schedule(schedule_selector(PlayerInput::tapCounter), 1.0 / 60.0, taps, 0);

}

void PlayerInput::tapCounter(float delta) {
  tapChecks++;
  if (rightCounter > 1) {
    cocos2d::log("DOUBLE RIGHT\n");
    unschedule(schedule_selector(PlayerInput::tapCounter));
    tapChecks = taps;
    doubleRight = true;
  }
  else if (leftCounter > 1) {
    cocos2d::log("DOUBLE LEFT\n");
    unschedule(schedule_selector(PlayerInput::tapCounter));
    tapChecks = taps;
    doubleLeft = true;
  }

  if (tapChecks == taps) {
    leftCounter = 0;
    rightCounter = 0;
    tapChecks = 0;
  }
}

bool PlayerInput::isDoubleRight(){
  const bool ret_val = doubleRight;
  doubleRight = false;
  return ret_val;
}

bool PlayerInput::isDoubleLeft(){
  const bool ret_val = doubleLeft;
  doubleLeft = false;
  return ret_val;
}

void PlayerInput::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
  bResetAnalog = false;
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  for (int i = 0;i<touches.size();i++) {
    if ((touches.at(i)->getStartLocation().x) < winSize.width / 2) {
      // LEFT
      left = false;
      swipeAmountL = 0;
      softWareResetL = false;
      fSWDistL = 0;
    }
    else {
      // RIGHT
      right = false;
      swipeAmountR = 0;
      softWareResetR = false;
      fSWDistR = 0;
    }
  }
}

void PlayerInput::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  
  
    for (int i = 0;i < touch.size();i++) {
      const float current_touch = touch.at(0)->getLocation().y;
      const float swipe_distance = current_touch - touch.at(0)->getStartLocation().y;
      float swipeThreshold = 40;
      if(bResetAnalog){
        
      }
      if (swipe_distance > swipeThreshold) {
        if ((touch.at(i)->getStartLocation().x) < winSize.width / 2) {
          // LEFT
          if(softWareResetL){
            softWareResetL = false;
            fSWDistL = swipe_distance;
          }
          swipeAmountL = (swipe_distance - fSWDistL)/ swipeThreshold;
        }
        else {
          // RIGHT
          if(softWareResetR){
            softWareResetR = false;
            fSWDistR = swipe_distance;
          }
          swipeAmountR = (swipe_distance - fSWDistR) / swipeThreshold;
    
        }
        
      }
    }
  
  if(softWareResetL){
    softWareResetL = false;
  }
  if(softWareResetR){
    softWareResetR = false;
  }
}

void PlayerInput::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
  cocos2d::log("touch cancelled");
}

bool PlayerInput::isLeft() {
  return left;
}

bool PlayerInput::isRight() {
  return right;
}

float PlayerInput::getSwipeR(){
  return swipeAmountR;
}

float PlayerInput::getSwipeL(){
  return swipeAmountL;
}

void PlayerInput::resetAnalog(){
  swipeAmountL = 0;
  swipeAmountR = 0;
  bResetAnalog = true;
}

void PlayerInput::setSWR(){
  softWareResetR = true;
  softWareResetL = true;
}

