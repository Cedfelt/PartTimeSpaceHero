//
//  EraseGameScene.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 11/10/16.
//
//

#include "EraseGameScene.hpp"
#include "GlobalPList.hpp"
#include "GameScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "DB32.hpp"
#include "ui/CocosGUI.h"
#include "MainMenu.hpp"
#include "TitleScreen.hpp"
#include "LoadScreenScene.hpp"
#include "SimpleAudioEngine.h"





USING_NS_CC;



using namespace cocostudio::timeline;

Scene* EraseGameScreen::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = EraseGameScreen::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}


extern bool go_to_title;

// on "init" you need to initialize your instance
bool EraseGameScreen::init()
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
  touchListener->onTouchesBegan = CC_CALLBACK_2(EraseGameScreen::onTouchBegan, this);
  touchListener->onTouchesEnded = CC_CALLBACK_2(EraseGameScreen::onTouchEnded, this);
  touchListener->onTouchesMoved = CC_CALLBACK_2(EraseGameScreen::onTouchMoved, this);
  touchListener->onTouchesCancelled = CC_CALLBACK_2(EraseGameScreen::onTouchCancelled, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
  
  
  
  // New Game Label -
  auto label = Label::createWithTTF("This will erase any progress\n you made so far", "fonts/PressStart2P.ttf", 15*scale);
  label->setPosition(Vec2(visibleSize.width/2 , visibleSize.height*0.50));
  addChild(label);
  
  
  // Go to Title Button
  auto title_button = cocos2d::ui::Button::create("transparent.png", "transparent.png", "transparent.png");
  auto titleLabel = Label::createWithTTF("YES", "fonts/PressStart2P.ttf", 15*scale);
  int sWidth = Director::getInstance()->getWinSize().width;
  int sHeight = Director::getInstance()->getWinSize().height;
  titleLabel->setPosition(Point(title_button->getContentSize().width/2,title_button->getContentSize().height/2));
  
  title_button->setPosition(Point(visibleSize.width*0.2,sHeight * 0.2f));
  
  title_button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
    switch (type)
    {
      case ui::Widget::TouchEventType::BEGAN:
        break;
      case ui::Widget::TouchEventType::ENDED:
        gameSave = SaveData::create();
        gameSave->loadWorldData();
        addChild(gameSave);
        gameSave->eraseMemorey();
        auto scene = LoadScreen::createScene();
        Director::getInstance()->pushScene(scene);
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->stopBackgroundMusic();
        audio->end();
        break;
        
    }
  });
  addChild(title_button);
  title_button->addChild(titleLabel,1);
  
  // Resume Button
  auto button = cocos2d::ui::Button::create("transparent.png", "transparent.png", "transparent.png");
  auto resumeLabel = Label::createWithTTF("NO", "fonts/PressStart2P.ttf", 15*scale);
  resumeLabel->setPosition(Point(button->getContentSize().width * 0.8,button->getContentSize().height*0.10f));
  
  button->setPosition(Point(visibleSize.width*0.8,sHeight * 0.2f));
  
  button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
    switch (type)
    {
      case ui::Widget::TouchEventType::BEGAN:
        break;
      case ui::Widget::TouchEventType::ENDED:
        auto scene = MainMenu::createScene();
        Director::getInstance()->pushScene(scene);
        break;
        
    }
  });
  addChild(button);
  button->addChild(resumeLabel,1);
  return true;
}

void EraseGameScreen::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch Began");
}

void EraseGameScreen::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
  
}

void EraseGameScreen::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch moved");
}

void EraseGameScreen::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
  cocos2d::log("touch cancelled");
}

