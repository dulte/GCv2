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

  int writeFrequency;
  int test;

  InputReader();

};

#endif
