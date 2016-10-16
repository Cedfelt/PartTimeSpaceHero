//
//  PauseScene.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/10/16.
//
//

#include "PauseScene.hpp"
#include "GlobalPList.hpp"
#include "GameScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "DB32.hpp"
#include "ui/CocosGUI.h"
#include "MainMenu.hpp"
#include "TitleScreen.hpp"





USING_NS_CC;



using namespace cocostudio::timeline;

Scene* PauseScreen::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = PauseScreen::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}


extern bool go_to_title;

// on "init" you need to initialize your instance
bool PauseScreen::init()
{
  
  
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
  {
    return false;
  }
  
  
  
  
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  
  const size_t scale = getScaleFactor();
  
  
  // Add Touch
  auto touchListener = EventListenerTouchAllAtOnce::create();
  touchListener->onTouchesBegan = CC_CALLBACK_2(PauseScreen::onTouchBegan, this);
  touchListener->onTouchesEnded = CC_CALLBACK_2(PauseScreen::onTouchEnded, this);
  touchListener->onTouchesMoved = CC_CALLBACK_2(PauseScreen::onTouchMoved, this);
  touchListener->onTouchesCancelled = CC_CALLBACK_2(PauseScreen::onTouchCancelled, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
  
  
  
  // New Game Label -
  auto label = Label::createWithTTF("PTSH - PAUSED!", "fonts/PressStart2P.ttf", 15*scale);
  label->setPosition(Vec2(visibleSize.width/2 , visibleSize.height*0.90));
  addChild(label);
  
  
  // Go to Title Button
  auto title_button = cocos2d::ui::Button::create("transparent.png", "transparent.png", "transparent.png");
  auto titleLabel = Label::createWithTTF("Go to Title", "fonts/PressStart2P.ttf", 15*scale);
  int sWidth = Director::getInstance()->getWinSize().width;
  int sHeight = Director::getInstance()->getWinSize().height;
  titleLabel->setPosition(Point(title_button->getContentSize().width/2,title_button->getContentSize().height/2));
  
  title_button->setPosition(Point(visibleSize.width/2,sHeight * 0.7f));
  
  title_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
    switch (type)
    {
      case ui::Widget::TouchEventType::BEGAN:
        break;
      case ui::Widget::TouchEventType::ENDED:
        go_to_title = true;
        Director::getInstance()->popScene();
        //auto scene = PauseScreen::createScene();
        //Director::getInstance()->pushScene(scene);
        break;
        
    }
  });
  addChild(title_button);
  title_button->addChild(titleLabel,1);
  
  // Resume Button
  auto button = cocos2d::ui::Button::create("transparent.png", "transparent.png", "transparent.png");
  auto resumeLabel = Label::createWithTTF("Resume Game", "fonts/PressStart2P.ttf", 15*scale);
  resumeLabel->setPosition(Point(button->getContentSize().width/2,button->getContentSize().height/2));
  
  button->setPosition(Point(visibleSize.width/2,sHeight * 0.5f));
  
  button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
    switch (type)
    {
      case ui::Widget::TouchEventType::BEGAN:
        break;
      case ui::Widget::TouchEventType::ENDED:
        Director::getInstance()->popScene();
        //auto scene = PauseScreen::createScene();
        //Director::getInstance()->pushScene(scene);
        break;
        
    }
  });
  addChild(button);
  button->addChild(resumeLabel,1);
  
  // Pause Menu Music
  //audio->playBackgroundMusic("Hope.mp3", true);
  
  return true;
}

void PauseScreen::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch Began");
}

void PauseScreen::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
  
}

void PauseScreen::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch moved");
}

void PauseScreen::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
  cocos2d::log("touch cancelled");
}

