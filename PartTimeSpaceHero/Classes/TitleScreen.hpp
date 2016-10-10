//
//  TitleScreen.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/10/16.
//
//

#pragma once

#include "cocos2d.h"
#include "SaveData.hpp"
using namespace cocos2d;

class TitleScreen : public cocos2d::Layer
{
  
public:
  // there's no 'id' in cpp, so we recommend returning the class instance pointer
  static cocos2d::Scene* createScene();
  
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(TitleScreen);
  
private:
  virtual void onTouchBegan(const std::vector<Touch*>&, Event*);
  virtual void onTouchEnded(const std::vector<Touch*>&, Event*);
  virtual void onTouchMoved(const std::vector<Touch*>&, Event*);
  virtual void onTouchCancelled(const std::vector<Touch*>&, Event*);
  float start_cnt = 2.5f;
  SaveData* gameSave;
};
