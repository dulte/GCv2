#ifndef PUSHER_H
#define PUSHER_H
#include "InputReader.h"

using namespace std;

class Pusher
{
public:
  int xID;
  int yID;
  double position = 0;
  double velocity;
  double force;
  double dt;
  double kPusher;

  InputReader* inputReader;



  Pusher(int x, int y, InputReader* &input);

  void movePusher();
  double getPusherForce(double x);

};

#endif
