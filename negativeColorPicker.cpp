/*
*  File: negativeColorPicker.cpp
*  Implements the negative color picker for CPSC 221 PA2.
*
*/

#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg)
{
  // complete your implementation below
  img = inputimg;
}

HSLAPixel NegativeColorPicker::operator()(PixelPoint p)
{
  // complete your implementation below
  double h, l, s, a;
  h = img.getPixel(p.x, p.y)->h;
  if (h <= 180){
    h += 180;
  }
  else{
    h -= 180;
  }
  
  l = 1.0 - img.getPixel(p.x, p.y)->l;
  s = img.getPixel(p.x, p.y)->s;
  a = img.getPixel(p.x, p.y)->a;
  return HSLAPixel(h, s, l, a); // REPLACE THIS STUB
}
