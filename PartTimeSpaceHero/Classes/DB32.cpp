//
//  DB32.cpp
//  PartTimeSpaceHero
//
//  Created by Anders Svensson on 28/08/16.
//
//

#include "DB32.hpp"

#include <stdio.h>



DB32Color color_collection[32];
DB32Color color1 = {20, 12, 28};
DB32Color color2 = {48, 52, 109};
DB32Color color3 = {109, 194, 202};
DB32Color color4 = {89, 125, 206};
DB32Color color5 = {143, 86, 59};
DB32Color color6 = {223, 113, 38};
DB32Color color7 = {217, 160, 102};
DB32Color color8 = {238, 195, 154};
DB32Color color9 = {251, 242, 54};
DB32Color color10 = {153, 229, 80};
DB32Color color11 = {106, 190, 48};
DB32Color color12 = {55, 148, 110};
DB32Color color13 = {75, 105, 47};
DB32Color color14 = {82, 75, 36};
DB32Color color15 = {50, 60, 57};
DB32Color color16 = {63, 63, 116};
DB32Color color17 = {48, 96, 130};
DB32Color color18 = {91, 110, 225};
DB32Color color19 = {8, 85, 234};
DB32Color color20 = {95, 205, 228};
DB32Color color21 = {203, 219, 252};
DB32Color color22 = {255, 255, 255};
DB32Color color23 = {155, 173, 183};
DB32Color color24 = {132, 126, 135};
DB32Color color25 = {105, 106, 106};
DB32Color color26 = {89, 86, 82};
DB32Color color27 = {118, 66, 138};
DB32Color color28 = {172, 50, 50};
DB32Color color29 = {10, 152, 172};
DB32Color color30 = {106, 49, 202};
DB32Color color31 = {33, 32, 64};
DB32Color color32 = {0, 23, 125};

void setup_colorcollection(){
  color_collection[BLACK] = color1;
  color_collection[LIGHTBLACK] = color2;
  color_collection[PLUMBROWN] = color3;
  color_collection[DARKCHOCOBROWN] = color4;
  color_collection[LIGHTCHOCOBROWN] = color5;
  color_collection[ORANGE] = color6;
  color_collection[DARKSAND] = color7;
  color_collection[LIGHTSAND] = color8;
  color_collection[YELLOW] = color9;
  color_collection[LIGHTGRASSGREEN] = color10;
  color_collection[DARKGRASSGREEN] = color11;
  color_collection[FORRESTGREEN] = color12;
  color_collection[DARKFORRESTGREEN] = color13;
  color_collection[BROWNGREEN] = color14;
  color_collection[GREYGREEN] = color15;
  color_collection[DARKPURPLE] = color16;
  color_collection[PETROLBLUE] = color17;
  color_collection[DARKSKYBLUE] = color18;
  color_collection[SKYBLUE] = color19;
  color_collection[SEABLUE] = color20;
  color_collection[ICEBLUE] = color21;
  color_collection[WHITE] = color22;
  color_collection[STEELGREY] = color23;
  color_collection[DARKSTEELGREY] = color24;
  color_collection[GREY] = color25;
  color_collection[DARKGREY] = color26;
  color_collection[PLUMPURPLE] = color27;
  color_collection[APPLERED] = color28;
  color_collection[OLDROSE] = color29;
  color_collection[LIPSTICKPINK] = color30;
  color_collection[MILITARYGREEN] = color31;
  color_collection[MILITARYBROWN] = color32;
}

DB32Color getColorFromCollection(int color_type){
  return color_collection[color_type];
}


//int main() {
//  setup_colorcollection();
//  Color color = getColorFromCollection(OLDROSE);
//  printf("%u\n", color.red);
//  printf("%u\n", color.green);
//  printf("%u\n", color.blue);
//  return 0;
//}
