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
  CREATE_FUNC(SoundFx);
  void play(float volume);
  void play(const float volume,const float pitch);
  void stop();
  void loadEffect(const char* fileName, const float pan, const float pitch,const bool loop);
  const char* fileName;
  int sound_id;
  bool loop;
  float pitch;
  float pan;
  bool playing;
};


