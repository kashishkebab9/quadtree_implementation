#include <iostream>
#include <vector>
#include <string>
#include "include/QuadtreeRetry.h"

struct Node {
  Node *tr;
  Node *tl;
  Node *br;
  Node *bl;

  
};


int main() {
  Box box;
  box.position.x = 0;
  box.position.y = 0;
  box.height = 500;
  box.width = 500;
  QuadtreeNode* root = new QuadtreeNode(0, box); 
  Quadtree qt(root);
  
  for (int i = 0; i < 20; i++) {
    Point point;
    point.position.x = rand() % 250 + (-250);
    point.position.y = rand() % 250 + (-250);
    std::cout << "Inserting Point at position (" << point.position.x << ", " << point.position.y << ")" << std::endl;
    
    qt.Insert(point);

  }

  return 0;
}
