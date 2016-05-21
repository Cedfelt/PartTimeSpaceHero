//
//  SoundFx.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class SoundFx : public Node{
public:
  SoundFx(const char* fileName);
  void play(float volume);
  
  const char* fileName;
  int sound_id;
  bool loop;
  float pitch;
  float pan;
};


