//
//  SoundFx.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 21/05/16.
//
//

#include "SoundFx.hpp"
#include "SimpleAudioEngine.h"

SoundFx::SoundFx(const char* fileName) {
  this->fileName = fileName;
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->preloadEffect(fileName);
  loop = false;
  pitch = 1.0f;
  pan = 0.0f;
}

void SoundFx::play(float volume) {
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  sound_id = audio->playEffect(fileName, loop,pitch, pan, volume);
}
