//
//  DB32.hpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 28/08/16.
//
//

#ifndef DB32_hpp
#define DB32_hpp

#include <stdio.h>
typedef struct tColor{
  int red;
  int green;
  int blue;
}DB32Color;

enum db32_colors{
  BLACK,
  LIGHTBLACK,
  PLUMBROWN,
  DARKCHOCOBROWN,
  LIGHTCHOCOBROWN,
  ORANGE,
  DARKSAND,
  LIGHTSAND,
  YELLOW,
  LIGHTGRASSGREEN,
  DARKGRASSGREEN,
  FORRESTGREEN,
  DARKFORRESTGREEN,
  BROWNGREEN,
  GREYGREEN,
  DARKPURPLE,
  PETROLBLUE,
  DARKSKYBLUE,
  SKYBLUE,
  SEABLUE,
  ICEBLUE,
  WHITE,
  STEELGREY,
  DARKSTEELGREY,
  GREY,
  DARKGREY,
  PLUMPURPLE,
  APPLERED,
  OLDROSE,
  LIPSTICKPINK,
  MILITARYGREEN,
  MILITARYBROWN,
};

void setup_colorcollection();

DB32Color getColorFromCollection(int color_type);

#endif /* DB32_hpp */
