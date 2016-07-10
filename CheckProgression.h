#include <time.h>

class CheckProgression
{
public:
	time_t timer;
	int percent = 0;
	bool isTesting = inputReader->test;
	int testTime = 10;
	
	double timeStarted;
	
	bool cont = true;
	
	double tStop;
	
	
	CheckProgression(double stoptime, bool testing);
	void showProgression(double time);
	bool doneTesting();
	
private:
	int calculateProgression(double time);
	
};