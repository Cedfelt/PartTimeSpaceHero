//
//  LoadScreenScene.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/10/16.
//
//

#include "LoadScreenScene.hpp"
#include "GlobalPList.hpp"
#include "GameScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "DB32.hpp"

USING_NS_CC;



using namespace cocostudio::timeline;

Scene* LoadScreen::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  
  // 'layer' is an autorelease object
  auto layer = LoadScreen::create();
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}


bool first_time = true;
// on "init" you need to initialize your instance
bool LoadScreen::init()
{
  
  
  //////////////////////////////
  // 1. super init first
  if ( !Layer::init() )
  {
    return false;
  }
  
  
  
  Director::getInstance()->getTextureCache()->removeUnusedTextures();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  
  const size_t scale = getScaleFactor();
  
  
  // Add Touch
  auto touchListener = EventListenerTouchAllAtOnce::create();
  touchListener->onTouchesBegan = CC_CALLBACK_2(LoadScreen::onTouchBegan, this);
  touchListener->onTouchesEnded = CC_CALLBACK_2(LoadScreen::onTouchEnded, this);
  touchListener->onTouchesMoved = CC_CALLBACK_2(LoadScreen::onTouchMoved, this);
  touchListener->onTouchesCancelled = CC_CALLBACK_2(LoadScreen::onTouchCancelled, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
  
  gameSave = SaveData::create();
  if(first_time){
    first_time = false;
    gameSave->loadWorldData();
  }
  unplayedLevels = gameSave->prepareNextLevel();
  LevelData* nextLevel = gameSave->getCurrentLevel();
  std::string description= "";
  addChild(gameSave);
  
  if(nextLevel!=nullptr){
    description = nextLevel->description;
  }
  
  // New Game Label -
  auto label = Label::createWithTTF(description, "fonts/PressStart2P.ttf", 15*scale);
  label->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));
  addChild(label);
  
  
  
  
  
  
  return true;
}
bool newGame2;
void LoadScreen::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch Began");
  newGame2 = true;
}

void LoadScreen::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
  if(!newGame2)
    return;
  newGame2 = false;
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  if(unplayedLevels){
    LevelData* nextLevel = gameSave->getCurrentLevel();
    setMapUrl(nextLevel->getMapName());
    //setMapUrl("ptsh_template.tmx");
    //setMapUrl("djungel2.tmx");
    cocos2d::log(nextLevel->getMapName().c_str());
    auto scene = GameScene::createScene();
    // Transition Fade
    auto col = getColorFromCollection(BLACK);
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene, Color3B(col.red,col.green,col.blue)));
  }
  else{
    cocos2d::log("Game Cleared");
  }
}

void LoadScreen::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
  cocos2d::log("touch moved");
}

void LoadScreen::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
  cocos2d::log("touch cancelled");
}

