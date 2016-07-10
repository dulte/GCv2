#ifndef CHECKPROGRESSION_H
#define  CHECKPROGRESSION_H


#include <time.h>

class CheckProgression
{
public:
	time_t timer;
	int percent = 0;
	int testTime = 10;

	double timeStarted;

	bool cont = true;

	double tStop;

  bool isTesting;


	CheckProgression(double stoptime, bool testing);
	void showProgression(double t);
	bool doneTesting(double t);

private:
	int calculateProgression(double t, int p);

};

#endif
