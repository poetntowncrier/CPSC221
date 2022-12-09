/*
*  File:        filler.cpp
*  Description: Implementation of functions in the filler namespace.
*
*/
#include "queue.h"
#include "stack.h"
/*
*  Performs a flood fill using breadth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillBFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.

  return Fill<Queue>(config); // REPLACE THIS STUB
}

/*
*  Performs a flood fill using depth first search.
*
*  PARAM:  config - FillerConfig struct to setup the fill
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
animation filler::FillDFS(FillerConfig& config) {
  // complete your implementation below
  // You should replace the following line with a
  // correct call to fill.
  return Fill<Stack>(config); // REPLACE THIS STUB
}

/*
*  Run a flood fill on an image starting at the seed point
*
*  PARAM:  config - FillerConfig struct with data for flood fill of image
*  RETURN: animation object illustrating progression of flood fill algorithm
*/
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config)
{
  /*
  * You need to implement this function!
  *
  * This is the basic description of a flood-fill algorithm: Every fill
  * algorithm requires an ordering structure, which is passed to this
  * function via its template parameter. For a breadth-first-search
  * fill, that structure is a Queue, for a depth-first-search, that
  * structure is a Stack. To begin the algorithm, you simply place the
  * given point in the ordering structure, marking it processed
  * (the way you mark it is a design decision you'll make yourself).
  * We have a choice to either change the color, if appropriate, when we
  * add the point to the OS, or when we take it off. In our test cases,
  * we have assumed that you will change the color when a point is added
  * to the structure.
  * Until the structure is empty, you do the following:
  *
  * 1.     Remove a point from the ordering structure, and then...
  *
  *        1.    add its unprocessed neighbors (up/down/left/right) whose color values are
  *              within (or equal to) tolerance distance from the seed point,
  *              to the ordering structure, and
  *              mark them as processed.
  *        2.    if it is an appropriate frame, send the current PNG to the
  *              animation (as described below).
  *
  * 2.     When implementing your breadth-first-search and
  *        depth-first-search fills, you will need to explore neighboring
  *        pixels (up/down/left/right) in some order.
  *
  *        While the order in which you examine neighbors does not matter
  *        for a proper fill, you must use the same order as we do for
  *        your animations to come out like ours! The order you should put
  *        neighboring pixels **ONTO** the queue or stack is based on the
  *        following priority condition:
  *        ** MINIMUM COLOR DISTANCE FROM THE CURRENT PIXEL **
  *        Ties are broken first by minimum y-coordinate, then by minimum x-coordinate.
  *        The HSLAPixel.dist() function will be useful, and you should
  *        take advantage of the functionality in your PriorityNeighbours class.
  * 
  *        If you process the neighbours in a different order, your fill may
  *        still work correctly, but your animations will be different
  *        from the grading scripts!
  *
  * 3.     For every k pixels filled, **starting at the kth pixel**, you
  *        must add a frame to the animation, where k = frameFreq.
  *
  *        For example, if frameFreq is 4, then after the 4th pixel has
  *        been filled you should add a frame to the animation, then again
  *        after the 8th pixel, etc.  You must only add frames for the
  *        number of pixels that have been filled, not the number that
  *        have been checked. So if frameFreq is set to 1, a pixel should
  *        be filled every frame.
  *
  * 4.     Finally, as you leave the function, send one last frame to the
  *        animation. This frame will be the final result of the fill, and
  *        it will be the one we test against.
  *
  */
  
  int framecount = 0; // increment after processing one pixel; used for producing animation frames (step 3 above)
  animation anim;
  OrderingStructure<PixelPoint> os;

  // complete your implementation below
  // HINT: you will likely want to declare some kind of structure to track
  //       which pixels have already been visited
  os.Add(config.seedpoint);

  vector<vector<bool>> track(config.img.width(), vector<bool>(config.img.height()));
  
  track[config.seedpoint.x][config.seedpoint.y] = true;
  
  *config.img.getPixel(config.seedpoint.x,config.seedpoint.y) = (*(config.picker))(config.seedpoint);

  
  anim.addFrame(config.img);

  while(!os.IsEmpty()){
    PixelPoint curr = os.Remove();
    if (curr.y){
    PixelPoint curr_up = PixelPoint(curr.x, curr.y - 1, *config.img.getPixel(curr.x, curr.y - 1));
    if (curr_up.x < config.img.width() && curr_up.y < config.img.height() &&
     curr_up.x >= 0 && curr_up.y >=0 && !track[curr_up.x][curr_up.y] &&
      config.seedpoint.color.dist(*config.img.getPixel(curr.x, curr.y - 1)) <= config.tolerance){

      config.neighbourorder.Insert(curr_up);
      os.Add(curr_up);
			track[curr_up.x][curr_up.y] = true;
			*config.img.getPixel(curr_up.x,curr_up.y) = (*(config.picker))(curr_up);
			framecount++;
			if(framecount%config.frameFreq == 0){
				anim.addFrame(config.img);
			}
    }
  }

    if (curr.x != config.img.width() - 1){
    PixelPoint curr_right = PixelPoint(curr.x + 1, curr.y, *config.img.getPixel(curr.x + 1, curr.y));
    if (curr_right.x < config.img.width() && curr_right.y < config.img.height() &&
     !track[curr_right.x][curr_right.y] && curr_right.x >= 0 && curr_right.y >=0 &&
      config.seedpoint.color.dist(*config.img.getPixel(curr.x + 1, curr.y)) <= config.tolerance){
      config.neighbourorder.Insert(curr_right);
      os.Add(curr_right);
			track[curr_right.x][curr_right.y] = true;
			*config.img.getPixel(curr_right.x,curr_right.y) = (*(config.picker))(curr_right);
			framecount++;
			if(framecount%config.frameFreq == 0){
				anim.addFrame(config.img);
			}
    }
    }

    if (curr.y != config.img.height() - 1){
    PixelPoint curr_down = PixelPoint(curr.x, curr.y + 1, *config.img.getPixel(curr.x, curr.y + 1));
    if (curr_down.x < config.img.width() && curr_down.y < config.img.height() &&
     curr_down.x >= 0 && curr_down.y >=0 && !track[curr_down.x][curr_down.y] &&
      config.seedpoint.color.dist(*config.img.getPixel(curr.x, curr.y + 1)) <= config.tolerance){
      config.neighbourorder.Insert(curr_down);
      os.Add(curr_down);
			track[curr_down.x][curr_down.y] = true;
			*config.img.getPixel(curr_down.x,curr_down.y) = (*(config.picker))(curr_down);
			framecount++;
			if(framecount%config.frameFreq == 0){
				anim.addFrame(config.img);
			}
    }
    }

    if (curr.x){
    PixelPoint curr_left = PixelPoint(curr.x - 1, curr.y, *config.img.getPixel(curr.x - 1, curr.y));
    if (curr_left.x < config.img.width() && curr_left.y < config.img.height() &&
    curr_left.x >= 0 && curr_left.y >=0 && !track[curr_left.x][curr_left.y] &&
     config.seedpoint.color.dist(*config.img.getPixel(curr.x - 1, curr.y)) <= config.tolerance){
      config.neighbourorder.Insert(curr_left);
      os.Add(curr_left);
			track[curr_left.x][curr_left.y] = true;
			*config.img.getPixel(curr_left.x,curr_left.y) = (*(config.picker))(curr_left);
			framecount++;
			if(framecount%config.frameFreq==0){
				anim.addFrame(config.img);
			}
    }
    }
		}
	anim.addFrame(config.img);
  return anim;
}