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
    int depth_limit;
    bool subdivided;
    int el_limit;
    std::vector<Point> elements;


  public:

    Quadtree(int depth_, Box box_) {
      std::cout << "Created Quadtree with Depth: " << depth_ << std::endl;
      ne = nullptr;
      nw = nullptr;
      se = nullptr; 
      sw = nullptr; 

      // we will not have more than 3 elements within a quad
      this->depth = depth_;
      el_limit = 3;
      depth_limit = 4;
      subdivided = false;
    }

    void subdivide(Quadtree* qt) {
      //we want to manage the current memory of the elements in our vector and place them into the correct pointers
      Box ne_box;
      ne_box.position.x = qt->box.position.x + qt->box.width/4;
      ne_box.position.y = qt->box.position.y + qt->box.height/4;
      ne_box.width = qt->box.width/2;
      ne_box.height = qt->box.height/2;
      Quadtree ne_qt(qt->depth + 1, ne_box);
      qt->ne = &ne_qt;

      Box nw_box;
      nw_box.position.x = qt->box.position.x - qt->box.width/4;
      nw_box.position.y = qt->box.position.y + qt->box.height/4;
      nw_box.width = qt->box.width/2;
      nw_box.height = qt->box.height/2;

      qt->nw = new Quadtree(qt->depth + 1, nw_box);

      Box se_box;
      se_box.position.x = qt->box.position.x + qt->box.width/4;
      se_box.position.y = qt->box.position.y - qt->box.height/4;
      se_box.width = qt->box.width/2;
      se_box.height = qt->box.height/2;

      qt->se = new Quadtree(qt->depth + 1, se_box);

      Box sw_box;
      sw_box.position.x = qt->box.position.x - qt->box.width/4;
      sw_box.position.y = qt->box.position.y - qt->box.height/4;
      sw_box.width = qt->box.width/2;
      sw_box.height = qt->box.height/2;

      qt->sw = new Quadtree(qt->depth + 1, sw_box);

      for (auto n: qt->elements) {
        if(n.position.y > qt->box.position.y) {
          if (n.position.x > qt->box.position.x) {
            qt->ne->elements.push_back(n);
          } else {
            qt->nw->elements.push_back(n);
          }

        } else {
          if (n.position.x > qt->box.position.x) {
            qt->se->elements.push_back(n);
          } else {
            qt->sw->elements.push_back(n);
          }
        }

        
      }
      //make sure to empty out the elements of qt quadtree
      qt->elements.clear();
      qt->subdivided = true;
    }

    // There is a major issue with this recursive function
    // It is referencing only the root's information and not the quadtree it is iterating on
    void insert(Quadtree* qt, Point point) {

      if (!qt->subdivided) {
        if (qt->elements.size() < qt->el_limit) {
          // if we are not at the limit, simply add it to the quadtree's current element list
          qt->elements.push_back(point);
          
        } else if(qt->elements.size() == qt->el_limit) {

          // if we are not at the limit, subdivide (which should be where the current list should get managed) and then append this one appropriately 
          qt->elements.push_back(point);

          if(depth < depth_limit) {
            qt->subdivide(qt); 
          }
        }
      } else {
        std::cout << "Quadtree has already been subdivided!" << std::endl;
        // if already subdivided, we need to perform insert on the correct quadrant:
        if(point.position.y > qt->box.position.y) {
          if (point.position.x > qt->box.position.x) {
            qt->ne->insert(qt->ne, point);
          } else {
            qt->nw->insert(qt->nw, point);
          }

        } else {
          if (point.position.x > qt->box.position.x) {
            qt->se->insert(qt->se, point);
          } else {
            qt->sw->insert(qt->sw, point);
          }
        }
      }
    }
  
};
