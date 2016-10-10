//
//  GoalObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "GUI.hpp"
#include "ui/CocosGUI.h"
#include "PauseScene.hpp"

float bar_length = 4;
Color3B green;
Color3B yellow;
Color3B red;

bool GUI::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  green = Color3B(106, 190, 49);
  yellow = Color3B(251, 242, 54);
  red = Color3B(172, 50, 50);
  this->schedule(schedule_selector(GUI::update));
  setAnchorPoint(Point(0, 5.1f));
  
  finishLevel = false;
  
  
  //addGravityToObject(false);
  setElastic(0);
  // SETUP ANIMATIONS
  auto director = Director::getInstance();
  const float xPos = director->getWinSize().width / 10;
  const float yPos = director->getWinSize().height*0.95f;
  setObjectPositionX(xPos);
  setObjectPositionY(yPos);
  setPosition(getPositionX() - 32 * bar_length / 2, getPositionY());
  addGravityToObject(false);

  leftIcon = Sprite::create("leftIcon.png");
  leftIcon->setAnchorPoint(Point(0.5f,0.5f));
  const float xLeft = leftIcon->getContentSize().width / 2;
  const float yLeft = director->getWinSize().height - leftIcon->getContentSize().height;
  leftIcon->setPosition(xLeft,-yLeft);
  addChild(leftIcon, 101);
  
  rightIcon = Sprite::create("rightIcon.png");
  rightIcon->setAnchorPoint(Point(0.5f,0.5f));
  const float xRight = director->getWinSize().width - 1.5*rightIcon->getContentSize().width;
  const float yRight = director->getWinSize().height - rightIcon->getContentSize().height;
  rightIcon->setPosition(xRight,-yRight);
  addChild(rightIcon, 101);
  
  Sprite* barBack = Sprite::create("fule_bar.png");
  barBack->setScaleX(bar_length);
  barBack->setAnchorPoint(Point(0.0f, 1.f));
  barBack->getTexture()->setAliasTexParameters();
  barBack->setColor(Color3B(0, 0, 0));
  addChild(barBack, 101);
  
  

  objectSprite = cocos2d::Sprite::create("fule_bar.png");
  objectSprite->setScaleX(bar_length);
  objectSprite->setAnchorPoint(Point(0.0f, 1.f));
  objectSprite->getTexture()->setAliasTexParameters();
  objectSprite->setColor(green);
  addChild(objectSprite, 102);

  Label* fuelLabel = Label::createWithTTF("POWER", "fonts/PressStart2P.ttf", 20);
  fuelLabel->setAnchorPoint(Point(0.0f, 1.f));
  fuelLabel->setPositionX(9 * bar_length / 2.0f);
  fuelLabel->setPositionY(-8);
  addChild(fuelLabel, 103);

  // Hearts
  for (int i = 0;i < 3;i++) {
    heartSprite[i] = Sprite::create("heart.png");
    heartSprite[i]->setPositionY((-64));
    heartSprite[i]->setPositionX((43*i));
    heartSprite[i]->setAnchorPoint(Point(0.0f, 1.f));
    heartSprite[i]->getTexture()->setAliasTexParameters();
    heartSprite[i]->setScale(getScale() * 2);
    //heartSprite->setColor(Color3B(0, 0, 0));
    addChild(heartSprite[i], 101);
  }

  // Money
  auto coin = cocos2d::Sprite::create("coin.png");
  coin->getTexture()->setAliasTexParameters();
  coin->setScale(2);
  coin->setAnchorPoint(Point(0.0f, 1.f));
  coin->setPositionY((-128));
  addChild(coin, 102);
  

  
  auto button = cocos2d::ui::Button::create("pause_button.png", "pause_button.png", "pause_button.png");
  
  button->setPosition(Point(director->getWinSize().width * 0.90f,0));
  
  button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
    switch (type)
    {
      case ui::Widget::TouchEventType::BEGAN:
        break;
      case ui::Widget::TouchEventType::ENDED:
        auto scene = PauseScreen::createScene();
        Director::getInstance()->pushScene(scene);
        break;
      
    }
  });
  
  this->addChild(button);

  moneyLabel = Label::createWithTTF("0", "fonts/PressStart2P.ttf", 28);
  moneyLabel->setAnchorPoint(Point(0.0f, 1.f));
  moneyLabel->setPositionX(48);
  moneyLabel->setPositionY(-134);
  addChild(moneyLabel, 103);


  

  return true;
}

// Updating Player GUI
void GUI::update(const float delta) {
  if(dialogObjects.size()>0){
    dialog = dialogObjects.at(0);
    if(!dialog->dialogShowed){
      if(first){
        first = false;
        dialog->setPositionY(-cocos2d::Director::getInstance()->getWinSize().height);
        addChild(dialog,3003);
      }
      dialog->playDialog();
    }
    else{
      if(dialog->dialogShowed||dialogObjects.size()>1){// Remove if queeing dialogs
        if(dialog->endLevelWhenDone){
          finishLevel = true;
        }
        
        this->removeChild(dialog);
        first = true;
        dialogObjects.erase(0);
      
      }
    }
  }
  
  
  const float fule = player->getFuel();
  objectSprite->setScaleX(bar_length*player->getFuel());
  objectSprite->setColor(green);
  if(fule<0.5f){
    objectSprite->setColor(yellow);
  }
  if(fule<0.3f){
    objectSprite->setColor(red);
  }
  
  const std::string moneyString = std::to_string(player->getCoins());
  moneyLabel->setString(moneyString);
  
  for (int i = 0;i < 3;i++) {
    if(i+1<=player->HP){
      heartSprite[i]->setVisible(true);
    }
    else{
      heartSprite[i]->setVisible(false);
    }
  }
  
  // BUTTONS
  leftIcon->setColor(Color3B::WHITE);
  rightIcon->setColor(Color3B::WHITE);
  if(player->getVelocityX()>7){
    rightIcon->setColor(green);
  }
  if(player->getVelocityX()<-7){
    leftIcon->setColor(green);
  }
  
}


void GUI::colideWith(GameObject* oterhObj) {
  colided = true;
}

void GUI::addDialog(DialogObject* addDialog){
  dialogObjects.pushBack(addDialog);
}
