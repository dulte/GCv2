#include "InputReader.h"
#include "BottomBlock.h"
#include "Block.h"

class FrictionBlock : public BottomBlock
{
public:

  InputReader* inputReader;
  double k;
  double connectorPosition;
  bool state = true;

  double staticFricCoeff;
  double dynamicFricCoeff;
  double springForce = 0;
  double dynamicFricForce = 0;

  double t = 0;
  double dt;
  double solidificationTime;



  FrictionBlock(int xID_, int yID_, InputReader* &input);
  void calculateForces();
  int sign(double vx);

  int getState();

};
