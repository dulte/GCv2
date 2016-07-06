#include <vector>
#include <memory>
#include <cmath>

#include "Block.h"

using namespace std;

Block::Block(int xID_, int yID_, double x, double y){
  xID = xID_;
  yID = yID_;

  xPos = x;
  yPos = y;

};

void Block::fillNeighbors(vector<shared_ptr<Block>> &blocks)
{
  double dx;
  double dy;
  for (shared_ptr<Block> block : blocks)
  {
    dx = abs(block->xID - xID);
    dy = abs(block->yID - yID);
    if ((dx == 1 || dx == 0) && (dy == 1 || dy == 0))
    {
      if (!(dx == 0 && dy == 0)){
        neighbors.push_back(block);
      }
    }
  }
}
