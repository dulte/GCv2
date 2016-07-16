#include <cmath>
#include <vector>


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



  // connectorPosition = xPos;
  //
  dt = inputReader->dt;
  solTimeMean = inputReader->stickTime;

  std::normal_distribution<double> normDist(solTimeMean,solTimeMean/3);
  for (int i = 0; i < inputReader->numberOfConnectors;i++)
  {
    t.push_back(0);
    solidificationTime.push_back(normDist(gen));
    // cout << solidificationTime[i] << endl;
    state.push_back(false);
    connectorPosition.push_back(xPos);
  }

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
  std::normal_distribution<double> normDist(solTimeMean,solTimeMean/3);

  k = sqrt(39.2e9*normalForce/inputReader->numberOfConnectors);

  for (int i = 0; i < inputReader->numberOfConnectors;i++)
  {

    springForce = -k*(this->xPos-connectorPosition[i]);
    dynamicFricForce = -sign(xVel)*dynamicFricCoeff*normalForce/inputReader->numberOfConnectors;


    if (resting)//!resting)f
    {
      state[i] = true;
      xForce += springForce;
    }
    else
    {
      if (state[i])
      {
        if (abs(springForce) < staticFricCoeff*normalForce/inputReader->numberOfConnectors)
        {
          xForce += springForce;
          //cout << xID << " "  << xPos << " " << connectorPosition  << " " << springForce << endl;
        }
        else
        {
          state[i] = false;
          solidificationTime[i] = normDist(gen);
          //frictionSpringSolidificationTime = std::normal_dist<double>(solidificationTime, 0.3*solidificationTime)
          xForce += springForce;
        }
      }
      else
      {
        if (t[i]<solidificationTime[i])
        {
          t[i] += dt;
          xForce += dynamicFricForce;
        }
        else
        {
          t[i] = 0;
          connectorPosition[i] = xPos;
          state[i] = true;
          xForce += dynamicFricForce;
        }
      }
    }
  }
}



int FrictionBlock::getState()
{
  return int(state[0]);
}

void FrictionBlock::setResting(bool f)
{
  resting = f;
  for (int i = 0; i<inputReader->numberOfConnectors;i++)
  {
    connectorPosition[i] = xPos;
    state[i] = true;
  }
}

int FrictionBlock::getNumberSlipped()
{
  int k = 0;
  for (int i = 0; i<inputReader->numberOfConnectors;i++)
  {
    k += int(state[i]);
  }
  return (inputReader->numberOfConnectors - k);

}

double FrictionBlock::getPercentageSlipped()
{
  return double(getNumberSlipped())/inputReader->numberOfConnectors;
}
