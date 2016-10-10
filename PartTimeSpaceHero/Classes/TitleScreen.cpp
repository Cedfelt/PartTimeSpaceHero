//
//  TitleScreen.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/10/16.
//
//

#include "TitleScreen.hpp"
#include "GlobalPList.hpp"
#include "MainMenu.hpp"
#include "cocostudio/CocoStudio.h"
#include "DB32.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;



using namespace cocostudio::timeline;

Scene* TitleScreen::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = TitleScreen::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}



// on "init" you need to initialize your instance
bool TitleScreen::init()
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
  touchListener->onTouchesBegan = CC_CALLBACK_2(TitleScreen::onTouchBegan, this);
  touchListener->onTouchesEnded = CC_CALLBACK_2(TitleScreen::onTouchEnded, this);
  touchListener->onTouchesMoved = CC_CALLBACK_2(TitleScreen::onTouchMoved, this);
  touchListener->onTouchesCancelled = CC_CALLBACK_2(TitleScreen::onTouchCancelled, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
  
  
  // New Game Label -
  auto label = Label::createWithTTF("P.T.S.H", "fonts/PressStart2P.ttf", 20*scale);
  label->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));
  addChild(label);
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->stopBackgroundMusic();
  audio->playBackgroundMusic("alone in space.mp3", true);
  return true;
}

void TitleScreen::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch Began");
}

void TitleScreen::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
    auto scene = MainMenu::createScene();
    // Transition Fade
    auto col = getColorFromCollection(BLACK);
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene, Color3B(col.red,col.green,col.blue)));
}

void TitleScreen::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch moved");
}

void TitleScreen::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
  cocos2d::log("touch cancelled");
}
