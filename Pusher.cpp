#include "Pusher.h"
#include "InputReader.h"

using namespace std;

Pusher::Pusher(int x, int y, InputReader* &input)
{
  xID = x;
  yID = y;

  inputReader = input;
  position = xID*inputReader->d;
  velocity = inputReader->vPusher;
  dt =  inputReader->dt;
  kPusher = inputReader->kPusher;

}

void Pusher::movePusher()
{
  position += velocity*dt;
}

double Pusher::getPusherForce(double x)
{
  movePusher();
  return kPusher*(position-x);
}
