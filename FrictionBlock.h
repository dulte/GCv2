#include <random>
#include <vector>

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


  double staticFricCoeff;
  double dynamicFricCoeff;
  double springForce = 0;
  double dynamicFricForce = 0;

  // double t = 0;
  double dt;

  double solTimeMean;

  vector<double> solidificationTime;
  vector<double> connectorPosition;
  vector<bool> state;
  vector<double> t;






  FrictionBlock(int xID_, int yID_, InputReader* &input);
  void calculateForces();
  int sign(double vx);


  void setResting(bool f);
  int getState();

};
