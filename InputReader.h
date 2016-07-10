#ifndef INPUTREADER_H
#define INPUTREADER_H

using namespace std;


class InputReader
{
public:
  int blockHeight;
  int blockWidth;
  int numberOfBlocks;

  double dt;
  double tStop;

  double L;
  double M;
  double m;
  double k;
  double d;
  double B;
  double totalHeight;
  double totalWidth;
  double E;

  double eta;

  int writeFrequency;
  int test;

  double downPushForce;

  double vPusher;
  double kPusher;

  double staticCoeff;
  double dynamicCoeff;

  double stickTime;

  InputReader();

};

#endif
