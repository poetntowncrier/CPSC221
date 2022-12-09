/*
*  File: censorColorPicker.cpp
*  Implements the censor color picker for CPSC 221 PA2.
*
*/

#include "censorColorPicker.h"

#include <math.h> // gives access to sqrt function
#include "queue.h"
/*
*  Useful function for computing the Euclidean distance between two PixelPoints
*/
double PointDistance(PixelPoint a, PixelPoint b) {
  unsigned int diff_x, diff_y;
  if (a.x > b.x)
    diff_x = a.x - b.x;
  else
    diff_x = b.x - a.x;
  if (a.y > b.y)
    diff_y = a.y - b.y;
  else
    diff_y = b.y - a.y;
  return sqrt(diff_x * diff_x + diff_y * diff_y);
}

CensorColorPicker::CensorColorPicker(unsigned int b_width, PixelPoint ctr, unsigned int rad, PNG& inputimage)
{
  unsigned x, y, pos_x, pos_y;
  double pm_h, pm_l, pm_s, pm_a;
  Queue<double> queue_h;
  Queue<double> queue_l;
  Queue<double> queue_s;
  Queue<double> queue_a;
  

  blockwidth = b_width;
  center = ctr;
  radius = rad;
  img = inputimage;
  blockyimg = inputimage;
  
  for (pos_x = 0; pos_x < img.width(); pos_x += blockwidth)
    for (pos_y = 0; pos_y < img.height(); pos_y += blockwidth){ 
      int block_num = 0;
      double h = 0, l = 0, s = 0, a = 0;
      for(x = pos_x; x < min(pos_x + blockwidth, img.width()); x++)
        for(y = pos_y; y < min(pos_y + blockwidth, img.height()); y++){
          HSLAPixel px = *img.getPixel(x, y);
          h += px.h; l += px.l; s += px.s; a += px.a;
          block_num++;
        }
        
        queue_h.Enqueue(h / block_num);
        queue_l.Enqueue(l / block_num);
        queue_s.Enqueue(s / block_num);
        queue_a.Enqueue(a / block_num);
       
    }

  for (pos_x = 0; pos_x < img.width(); pos_x += blockwidth)
    for (pos_y = 0; pos_y < img.height(); pos_y += blockwidth){ 

        pm_h = queue_h.Dequeue();
        pm_l = queue_l.Dequeue();
        pm_s = queue_s.Dequeue();
        pm_a = queue_a.Dequeue();
    

      for (x = pos_x; x < min(pos_x + blockwidth, img.width()); x++)
        for (y = pos_y; y < min(pos_y + blockwidth, img.height()); y++){ 
          
          blockyimg.getPixel(x, y)->h = pm_h;
          blockyimg.getPixel(x, y)->l = pm_l;
          blockyimg.getPixel(x, y)->s = pm_s;
          blockyimg.getPixel(x, y)->a = pm_a;
       
        }

    }
}

HSLAPixel CensorColorPicker::operator()(PixelPoint p)
{
  if (PointDistance(center, p) > radius){
    return *img.getPixel(p.x, p.y);
  }

  else{

    return *blockyimg.getPixel(p.x, p.y); 
  }
  
}
