#include <cmath>
#include <iostream>

#include "InputReader.h"
#include "getVar.h"

using namespace std;

InputReader::InputReader()
{
  getVar* pGV = new getVar();
  blockWidth = pGV->get("width");
  blockHeight = pGV->get("height");
  numberOfBlocks = blockHeight*blockWidth;
  numberOfStripes = int(floor(double(blockWidth)/2.0) + 1);

  dt = pGV->get("dt");
  tStop = pGV->get("tStop");


  E = pGV->get("E");
  L = pGV->get("L");
  M = pGV->get("M");
  m = M/(numberOfBlocks);

  d = L/(blockWidth-1);
  B = pGV->get("B");

  k = (3./4.)*B*E;

  totalWidth = (blockWidth-1)*d;
  totalHeight = (blockHeight-1)*d;


  eta = sqrt(0.1*m*k);

  writeFrequency = pGV->get("writeFrequency");
  test = pGV->get("test");

  downPushForce = pGV->get("downPushForce");

  vPusher = pGV->get("vPusher");
  kPusher = pGV->get("kPusher");

  staticCoeff = pGV->get("staticCoeff");
  dynamicCoeff = pGV->get("dynamicCoeff");

  stickTime = pGV->get("stickTime");

  //groundSpringCoeff = pGV->get("groundSpringCoeff");
  groundSpringCoeff = double(k)/(2.);


  restBeforePushTime = pGV->get("restBeforePushTime");
  restBeforeConnectTime = pGV->get("restBeforeConnectTime");

  numberOfConnectors = pGV->get("numberOfConnectors");

  delete pGV;

}

void InputReader::dumpToFile(ofstream &file)
{
  file << "Nx " << blockWidth << endl;
  file << "Nz " << blockHeight << endl;

  file << "dt " << dt << endl;
  file << "tStop " << tStop << endl;

  file << "k " << k << endl;
  file << "normal force " << downPushForce << endl;

  file << "Connected at " << restBeforeConnectTime << endl;
  file << "Pushed at " << restBeforePushTime << endl;

  file << "Number of Connectors " << numberOfConnectors << endl;
  file << "Elastic foundation modulus " << groundSpringCoeff << endl;


}
