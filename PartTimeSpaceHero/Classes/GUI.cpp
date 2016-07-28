//
//  GoalObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "GUI.hpp"

float bar_length = 4;
bool GUI::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }

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
  objectSprite->setColor(Color3B::GREEN);
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

  moneyLabel = Label::createWithTTF("0", "fonts/PressStart2P.ttf", 28);
  moneyLabel->setAnchorPoint(Point(0.0f, 1.f));
  moneyLabel->setPositionX(48);
  moneyLabel->setPositionY(-134);
  addChild(moneyLabel, 103);


  

  return true;
}

// Updating Player GUI
bool first = true;
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
      if(dialog->dialogShowed){
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
  objectSprite->setColor(Color3B::GREEN);
  if(fule<0.5f){
    objectSprite->setColor(Color3B::YELLOW);
  }
  if(fule<0.3f){
    objectSprite->setColor(Color3B::RED);
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
}


void GUI::colideWith(GameObject* oterhObj) {
  colided = true;
}

void GUI::addDialog(DialogObject* addDialog){
  dialogObjects.pushBack(addDialog);
}