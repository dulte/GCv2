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
  double groundSpringForce = 1e6;
  double normalForce = 0;

  BottomBlock(int xID_, int yID_, InputReader* &input);
  void calculateForces();
  double returnNormalForce();
};
