#include <random>

#include "InputReader.h"
#include "BottomBlock.h"
#include "Block.h"

class FrictionBlock : public BottomBlock
{
public:

  static std::random_device rd;
  static std::mt19937 gen;



  InputReader* inputReader;
  double k;
  double connectorPosition;
  bool state = false;

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
