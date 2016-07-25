#ifndef BOTTOMBLOCK_H
#define BOTTOMBLOCK_H


#include <vector>
#include <memory>
#include <cmath>
# include <iostream>

#include "Block.h"
#include "InputReader.h"

using namespace std;

class BottomBlock : public Block
{
public:
  double groundSpringCoeff;
  double normalForce = 0;

  BottomBlock(int xID_, int yID_, InputReader* &input);
  void calculateForces();
  double returnNormalForce();
};

#endif
