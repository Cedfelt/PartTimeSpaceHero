//
//  SignObject.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 26/07/16.
//
//

#pragma once
#include "GameObject.hpp"
#include "SoundFx.hpp"

using namespace cocos2d;
class SignObject : public GameObject {
public:
  virtual bool init();
  virtual void colideWith(GameObject* oterhObj,const uint32_t otherType);
  CREATE_FUNC(SignObject);
  void addTextToSign(std::string text);
  std::vector<std::string> signText;
  SoundFx* signPop;
private:
};