/*
*  File: imageTileColorPicker.cpp
*  Implements the image tile color picker for CPSC 221 PA2.
*
*/

#include "imageTileColorPicker.h"

ImageTileColorPicker::ImageTileColorPicker(PNG& otherimage) {
  // complete your implementation below
  img_other = otherimage;
}

HSLAPixel ImageTileColorPicker::operator()(PixelPoint p) {
  // complete your implementation below
  double h, s, l, a;

  int width_other, height_other;
  width_other = img_other.width();
  height_other = img_other.height();

  h = img_other.getPixel(p.x % width_other, p.y % height_other)->h;
  s = img_other.getPixel(p.x % width_other, p.y % height_other)->s;
  l = img_other.getPixel(p.x % width_other, p.y % height_other)->l;
  a = img_other.getPixel(p.x % width_other, p.y % height_other)->a;
  
  return HSLAPixel(h, s, l, a); // REPLACE THIS STUB
}