#include "Block.h"
#include "InputReader.h"
#include "BottomBlock.h"

using namespace std;

BottomBlock::BottomBlock(int xID_, int yID_, InputReader* &input)
: Block::Block(xID_, yID_,input)
{
}

void BottomBlock::calculateForces()
{
  Block::calculateForces();
  if (yPos < 0){
    normalForce = -groundSpringForce*yPos;
    yForce += normalForce;
  }
}

double BottomBlock::returnNormalForce()
{
  return normalForce;
}
