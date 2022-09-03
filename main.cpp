#include <iostream>
#include <vector>
#include <string>

struct Node {
  Node *tr;
  Node *tl;
  Node *br;
  Node *bl;

  
};


int main() {
  // this repo's purpose will be to start playing with quadtrees and octrees as a concept, before implementing it as a grid
  // It' plausible I'll do this and realize this is not what i need.
  

  //the premise would be that you have a dense grid, a finer grid, and one past that.
  //
  // if you were performing an A* around obstacles, we should be able to draw a grid to traverse it easily.
  
  //All right, so actually quadtrees are not my favorite data structure for this purpose. I tend to prefer a grid hierarchy, like a coarse grid for the world, a finer grid for a region, and an even finer grid for a sub-region (3 fixed levels of dense grids, and no trees involved), with row-based optimizations so that a row that has no entities in it will be deallocated and turned into a null pointer, and likewise completely empty regions or sub-regions turned into nulls. While this simple implementation of the quadtree running in one thread can handle 100k agents on my i7 at 60+ FPS, I've implemented grids that can handle a couple million agents bouncing off each other every frame on older hardware (an i3). Also I always liked how grids made it very easy to predict how much memory they'll require, since they don't subdivide cells. But I'll try to cover how to implement a reasonably efficient quadtree.
  //
  //
  //Grid Hierarchy is more dependent on making a matrix of linked lists
  //
  int32_t 


  





  return 0;
}
