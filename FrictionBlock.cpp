#include <cmath>


#include "FrictionBlock.h"
#include "InputReader.h"
#include "BottomBlock.h"
#include "Block.h"


using namespace std;


random_device FrictionBlock::rd;
mt19937 FrictionBlock::gen(FrictionBlock::rd());

FrictionBlock::FrictionBlock(int xID_, int yID_, InputReader* &input)
: BottomBlock::BottomBlock(xID_,yID_,input)
{
  inputReader = input;
  staticFricCoeff = inputReader->staticCoeff;
  dynamicFricCoeff = inputReader->dynamicCoeff;

  std::normal_distribution<double> normDist(5,2);

  cout << round(normDist(gen)) << endl;

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

  double nf = 1000;

  k = 10*sqrt(39.2e9*normalForce);
  springForce = -k*(this->xPos-connectorPosition);
  dynamicFricForce = -sign(xVel)*dynamicFricCoeff*normalForce;


  if (!resting){
  if (state)
  {
    if (abs(springForce) < staticFricCoeff*normalForce)
    {
      xForce += springForce;
      //cout << xID << " "  << xPos << " " << connectorPosition  << " " << springForce << endl;
    }
    else
    {
      state = false;
      //frictionSpringSolidificationTime = std::normal_dist<double>(solidificationTime, 0.3*solidificationTime)
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

}



int FrictionBlock::getState()
{
  return int(state);
}
