#include <vector>
#include <memory>
#include <cmath>
# include <iostream>

#include "Block.h"
#include "InputReader.h"

using namespace std;

class ConstantForceBlock : public Block
{
public:
  double xConstForce;
  double yConstForce;

  ConstantForceBlock(int xID_, int yID_, InputReader* &input,double xFactor, double yFactor);
  void calculateForces();
};
