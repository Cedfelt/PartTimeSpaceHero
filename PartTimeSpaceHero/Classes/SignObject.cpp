//
//  SignObject.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 26/07/16.
//
//

#include "SignObject.hpp"


bool SignObject::init() {
  //////////////////////////////
  // 1. super init first
  if (!GameObject::init())
  {
    return false;
  }
  signPop = SoundFx::create();
  signPop->loadEffect("sign_pop.aif", 0, 1, false);
  addChild(signPop);
  addGravityToObject(false);
  bWallCollisions = false;
  return true;
}

const float lineTime = 3;
void SignObject::colideWith(GameObject* otherGo,const uint32_t otherType){
  
    auto dialog = DialogObject::create();
  signPop->play(0.6f);
  dialog->presentation = DialogObject::E_LINE_BY_LINE;
    for(int i = 0;i<signText.size();i++){
      dialog->addLine(signText.at(i), lineTime);
    }
    dialogObjects->pushBack(dialog);
}

void SignObject::addTextToSign(std::string text){
  signText.push_back(text);
}

