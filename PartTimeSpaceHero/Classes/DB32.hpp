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
  BLACK,// 0
  LIGHTBLACK,// 1
  PLUMBROWN,// 2
  DARKCHOCOBROWN,// 3
  LIGHTCHOCOBROWN,// 4
  ORANGE,// 5
  DARKSAND,// 6
  LIGHTSAND,// 7
  YELLOW,// 8
  LIGHTGRASSGREEN,// 9
  DARKGRASSGREEN,// 10
  FORRESTGREEN,// 11
  DARKFORRESTGREEN,// 12
  BROWNGREEN,// 13
  GREYGREEN,// 14
  DARKPURPLE,// 15
  PETROLBLUE,// 17
  DARKSKYBLUE,//18
  SKYBLUE,//19
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
