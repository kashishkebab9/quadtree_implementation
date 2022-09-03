#include <__nullptr>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

struct Vector2 {
  float x;
  float y;

};


struct Box {
  Vector2 position;
  float width;
  float height;
};

struct Point {
  Vector2 position;
};

class Quadtree {

  private:

    Quadtree* ne;
    Quadtree* nw;
    Quadtree* se;
    Quadtree* sw;

    Box box;
    int depth;
    bool subdivided;
    int el_limit;
    std::vector<Point> elements;


  public:

    Quadtree(int depth_, Box box_) {
      ne = nullptr;
      nw = nullptr;
      se = nullptr; 
      sw = nullptr; 

      // we will not have more than 3 elements within a quad
      el_limit = 3;
      subdivided = false;
    }

    void subdivide() {
      //we want to manage the current memory of the elements in our vector and place them into the correct pointers
      Box ne_box;
      ne_box.position.x = this->box.position.x + this->box.width/4;
      ne_box.position.y = this->box.position.y + this->box.height/4;
      ne_box.width = this->box.width/2;
      ne_box.height = this->box.height/2;

      this->ne = new Quadtree(this->depth + 1, ne_box);

      Box nw_box;
      nw_box.position.x = this->box.position.x - this->box.width/4;
      nw_box.position.y = this->box.position.y + this->box.height/4;
      nw_box.width = this->box.width/2;
      nw_box.height = this->box.height/2;

      this->nw = new Quadtree(this->depth + 1, nw_box);

      Box se_box;
      se_box.position.x = this->box.position.x + this->box.width/4;
      se_box.position.y = this->box.position.y - this->box.height/4;
      se_box.width = this->box.width/2;
      se_box.height = this->box.height/2;

      this->se = new Quadtree(this->depth + 1, se_box);

      Box sw_box;
      sw_box.position.x = this->box.position.x - this->box.width/4;
      sw_box.position.y = this->box.position.y - this->box.height/4;
      sw_box.width = this->box.width/2;
      sw_box.height = this->box.height/2;

      this->sw = new Quadtree(this->depth + 1, sw_box);

      for (auto n: elements) {
        if(n.position.y > this->box.position.y) {
          if (n.position.x > this->box.position.x) {
            this->ne->elements.push_back(n);
          } else {
            this->nw->elements.push_back(n);
          }

        } else {
          if (n.position.x > this->box.position.x) {
            this->se->elements.push_back(n);
          } else {
            this->sw->elements.push_back(n);
          }
        }

        
      }
      //make sure to empty out the elements of this quadtree
      this->elements.clear();
      this->subdivided = true;
    }

    void insert(Point point) {

      if (!subdivided) {
        if (elements.size() < this->el_limit) {
          // if we are not at the limit, simply add it to the quadtree's current element list
          this->elements.push_back(point);
          
        } else if(elements.size() == this->el_limit) {

          // if we are not at the limit, subdivide (which should be where the current list should get managed) and then append this one appropriately 
          this->elements.push_back(point);
          this->subdivide(); 

        }



      } else {
          this->elements.push_back(point);

      }


    }



  
};
