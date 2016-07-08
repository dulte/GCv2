#include <cmath>

#include "InputReader.h"
#include "getVar.h"

using namespace std;

InputReader::InputReader()
{
  getVar* pGV = new getVar();
  blockWidth = pGV->get("width");
  blockHeight = pGV->get("height");
  numberOfBlocks = blockHeight*blockWidth;

  dt = pGV->get("dt");
  tStop = pGV->get("tStop");

  k = pGV->get("k");
  L = pGV->get("L");
  M = pGV->get("M");
  m = M/numberOfBlocks;
  d = L/blockWidth;
  B = pGV->get("B");

  totalWidth = (blockWidth-1)*d;
  totalHeight = (blockHeight-1)*d;


  eta = sqrt(0.1*m*k);

  writeFrequency = pGV->get("writeFrequency");
  test = pGV->get("test");

  downPushForce = pGV->get("downPushForce");

  delete pGV;

}
