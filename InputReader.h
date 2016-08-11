#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <iostream>

using namespace std;


class InputReader
{
public:
  int blockHeight;
  int blockWidth;
  int numberOfBlocks;
  int numberOfStripes;

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
  int savestate;
  int loadstate;

  double downPushForce;

  double vPusher;
  double kPusher;
  int pusherHeight;

  double staticCoeff;
  double dynamicCoeff;

  double stickTime;

  double groundSpringCoeff;

  double restBeforePushTime;
  double restBeforeConnectTime;

  int numberOfConnectors;

  InputReader();

  void dumpToFile(ofstream &file);

};

#endif
