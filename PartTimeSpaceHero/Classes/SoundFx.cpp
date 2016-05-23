//
//  SoundFx.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "SoundFx.hpp"
#include "SimpleAudioEngine.h"

void SoundFx::loadEffect(const char* fileName, const float pan, const float pitch,const bool loop){
  this->fileName = fileName;
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->preloadEffect(fileName);
  this->loop = loop;
  this->pitch = pitch;
  this->pan = pan;
  playing = false;
}

void SoundFx::play(float volume) {
  if(playing){
    return;
  }
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  sound_id = audio->playEffect(fileName, loop,pitch, pan, volume);
  playing = true;
}

void SoundFx::play(const float volume,const float pitch) {
  if(playing){
    return;
  }
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  sound_id = audio->playEffect(fileName, loop,pitch, pan, volume);
  playing = true;
}

void SoundFx::stop(){
  if(!playing){
    return;
  }
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->stopEffect(sound_id);
  playing = false;
}
