#include <vector>
#include <memory>
#include <cmath>
# include <iostream>

#include "Block.h"
#include "InputReader.h"

using namespace std;

Block::Block(int xID_, int yID_, InputReader* &input){

  inputReader = input;

  xID = xID_;
  yID = yID_;

  xPos = xID*inputReader->d;
  yPos = yID*inputReader->d;


};

Block::~Block()
{
}

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
        if (dx == dy)
        {
          springConstModifier.push_back(0.5);
          eqDistModifier.push_back(sqrt(2));
        }
        else
        {
          springConstModifier.push_back(1);
          eqDistModifier.push_back(1);
        }
      }
    }
  }
}


void Block::calculateForces()
{
  xForce = 0;
  yForce = 0;

  for (int i = 0; i < neighbors.size();i++)
  {
    double deltaX = neighbors[i]->xPos - this->xPos;
    double deltaY = neighbors[i]->yPos - this->yPos;
    double length = sqrt(pow(deltaX,2) + pow(deltaY,2));

    xForce += inputReader->k*springConstModifier[i]*(length - inputReader->d*eqDistModifier[i])*deltaX/length;
    yForce += inputReader->k*springConstModifier[i]*(length - inputReader->d*eqDistModifier[i])*deltaY/length;

    xForce += -inputReader->eta*springConstModifier[i]*(this->xVel - neighbors[i]->xVel);
    yForce += -inputReader->eta*springConstModifier[i]*(this->yVel - neighbors[i]->yVel);

  }

}
