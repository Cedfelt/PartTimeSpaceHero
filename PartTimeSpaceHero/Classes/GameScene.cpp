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

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();

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
  

  //////////////////////////////
  // 1. super init first
  if (!Layer::init())
  {
    return false;
  }

  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  const size_t scale = getScaleFactor();

  // Debug Label -
  auto label = Label::createWithTTF("GameScene", "fonts/Marker Felt.ttf", 25 * scale);
  label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
  addChild(label);

  this->schedule(schedule_selector(GameScene::mainGameLoop));

  return true;
}


void GameScene::mainGameLoop(float delta) {
  counter += delta;
  if (counter > 3) {
    Director::getInstance()->popScene();
  }
}

