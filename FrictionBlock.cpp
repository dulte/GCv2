#include <cmath>

#include "FrictionBlock.h"
#include "InputReader.h"
#include "BottomBlock.h"
#include "Block.h"


using namespace std;

FrictionBlock::FrictionBlock(int xID_, int yID_, InputReader* &input)
: BottomBlock::BottomBlock(xID_,yID_,input)
{
  inputReader = input;
  staticFricCoeff = inputReader->staticCoeff;
  dynamicFricCoeff = inputReader->dynamicCoeff;

  connectorPosition = xPos;

  dt = inputReader->dt;
  solidificationTime = inputReader->stickTime;

}

int FrictionBlock::sign(double vx)
{
  if (vx < 0)
  {return -1;}
  else if(vx > 0)
  {return 1;}
  else{return 0;}
}

void FrictionBlock::calculateForces()
{
  BottomBlock::calculateForces();

  k = sqrt(39.2e9*normalForce);
  springForce = -k*(xPos-connectorPosition);
  dynamicFricForce = -sign(xVel)*dynamicFricCoeff*normalForce;

  if (state)
  {
    if (abs(springForce) < staticFricCoeff*normalForce)
    {
      xForce += springForce;
    }
    else
    {
      state = false;
      xForce += springForce;
    }
  }
  else
  {
    if (t<solidificationTime)
    {
      t += dt;
      xForce += dynamicFricForce;
    }
    else
    {
      t = 0;
      connectorPosition = xPos;
      state = true;
      xForce += dynamicFricForce;
    }
  }

}



int FrictionBlock::getState()
{
  return int(state);
}
