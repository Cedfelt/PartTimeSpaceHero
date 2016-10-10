#include "MainMenu.hpp"
#include "GlobalPList.hpp"
#include "GameScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "LoadScreenScene.hpp"
#include "SimpleAudioEngine.h"



USING_NS_CC;



using namespace cocostudio::timeline;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool MainMenu::init()
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
    touchListener->onTouchesBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(MainMenu::onTouchMoved, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(MainMenu::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // New Game Label -
    auto label = Label::createWithTTF("Start New Game", "fonts/PressStart2P.ttf", 15*scale);
    label->setPosition(Vec2(0 + label->getContentSize().width * 0.6f, 0 + label->getContentSize().height));
    addChild(label);
  
  auto label_continue = Label::createWithTTF("Continue", "fonts/PressStart2P.ttf", 15*scale);
  label_continue->setPosition(Vec2(visibleSize.width - label_continue->getContentSize().width * 1.f, 0 + label_continue->getContentSize().height));
  addChild(label_continue);
  
  // Sprite
  auto director = Director::getInstance();
  const float xPos = director->getWinSize().width *0.75;
  const float yPos = director->getWinSize().height / 4;
  Sprite* spaceShipSprite = Sprite::create("SpaceshipA.png");
  spaceShipSprite->getTexture()->setAliasTexParameters();
  spaceShipSprite->setScale(3);
  spaceShipSprite->setPositionX(xPos);
  spaceShipSprite->setPositionY(yPos);
  spaceShipSprite->setRotation(60);
  addChild(spaceShipSprite,0);
  
  
  const float xPosLogo = director->getWinSize().width / 2;
  const float yPosLogo = director->getWinSize().height*0.5;
  Sprite* logo = Sprite::create("logo.png");
  logo->getTexture()->setAliasTexParameters();
  logo->setScale(2);
  logo->setPositionX(xPosLogo);
  logo->setPositionY(yPosLogo);
  addChild(logo,1);
  
  gameSave = SaveData::create();
  gameSave->loadWorldData();
  addChild(gameSave);
  
    return true;
}
bool newGame;
void MainMenu::onTouchBegan(const std::vector<Touch*>& touch, Event* event)
{
    cocos2d::log("touch Began");
  newGame = true;
}

void MainMenu::onTouchEnded(const std::vector<Touch*>& touches, Event*)
{
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->stopBackgroundMusic();
  if(!newGame)
    return;
  newGame = false;
  CCSize winSize = CCDirector::sharedDirector()->getWinSize();
  for (int i = 0;i<touches.size();i++) {
    
    if ((touches.at(i)->getStartLocation().x) < winSize.width / 2) {
      // LEFT
      setDebuggDraw(false);
      gameSave->eraseMemorey();
    }
  }
  const bool unplayedLevels = gameSave->prepareNextLevel();
  if(unplayedLevels){
    LevelData* nextLevel = gameSave->getCurrentLevel();
    setMapUrl(nextLevel->getMapName());
    //setMapUrl("ptsh_template.tmx");
    //setMapUrl("djungel2.tmx");
    cocos2d::log(nextLevel->getMapName().c_str());
    auto scene = LoadScreen::createScene();
    Director::getInstance()->replaceScene(scene);
  }
  else{
    cocos2d::log("Game Cleared");
  }
}

void MainMenu::onTouchMoved(const std::vector<Touch*>& touch, Event* event)
{
    cocos2d::log("touch moved");
}

void MainMenu::onTouchCancelled(const std::vector<Touch*>&, Event*)
{
    cocos2d::log("touch cancelled");
}
