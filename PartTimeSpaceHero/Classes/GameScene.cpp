//
//  GameScene.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 10/04/16.
//
//

#include "GameScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GlobalPList.hpp"
#include "MainMenu.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::createWithPhysics();
  scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
  if(getDebuggDraw()){
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
  }
  scene->setAnchorPoint(Point(0, 0));
  // 'layer' is an autorelease object
  auto layer = GameScene::create();

  // add layer as a child to scene
  scene->addChild(layer);



  // return the scene
  return scene;
}



// on "init" you need to initialize your instance
bool GameScene::init()
{

//  int temp_col [3] = {75, 105, 47};
int temp_col [3] = {63, 63, 116};
//int temp_col [3] = {34, 32, 52};
 // int temp_col [3] = {91, 110, 225};
// int temp_col [3] = {0, 0, 0};
  //  int temp_col [3] = {118, 66, 138};
//int temp_col [3] = {95, 205, 220};
  //////////////////////////////
  // 1. super init first
  if (!LayerColor::initWithColor(Color4B(temp_col[0], temp_col[1], temp_col[2], 255)))
  {
    return false;
  }
  
  auto director = Director::getInstance();
  director->setProjection(Director::Projection::_2D);
  
  
  
  setAnchorPoint(Point(0, 0));
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  const size_t scale = getScaleFactor();

  // Debug Label -
  /*auto label = Label::createWithTTF("GameScene", "fonts/Marker Felt.ttf", 25 * scale);
  label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
  addChild(label);*/


  

  this->schedule(schedule_selector(GameScene::mainGameLoop));


  worldObject = worldObject->create();
  worldObject->setAnchorPoint(Point(0, 0));
  addChild(worldObject);
  
 
  
  ////////////////////////////////////
  // GUI and Dialog
  gui = GUI::create();
  dialogObjects = &gui->dialogObjects;
  worldObject->dialogObjects = dialogObjects;
  worldObject->setupWorld();
  
 
  addChild(gui,100);
  gui->player = worldObject->player; // Create interface
  gui->setGlobalZOrder(100);
  
  return true;
}



void GameScene::mainGameLoop(float delta) {
  if(gui->finishLevel){
    worldObject->finishLevel();
  }
  
  return;
  auto director = Director::getInstance();
  director->setProjection(Director::Projection::_2D);
  counter += delta;
  if (counter > 25) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
  }
  
}




