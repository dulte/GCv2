#include <vector>
#include <memory>
#include <cmath>
# include <iostream>

#include "Block.h"
#include "InputReader.h"

#include "ConstantForceBlock.h"

using namespace std;

ConstantForceBlock::ConstantForceBlock(int xID_, int yID_, InputReader* &input,double xFactor, double yFactor)
: Block(xID_,yID_,input)
{
  xConstForce = xFactor*inputReader->downPushForce/(inputReader->blockWidth);
  yConstForce = yFactor*inputReader->downPushForce/(inputReader->blockHeight);

}

void ConstantForceBlock::calculateForces()
{
  Block::calculateForces();
  xForce += xConstForce;
  yForce += yConstForce;
}
