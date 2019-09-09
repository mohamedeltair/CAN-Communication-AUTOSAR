#include "Decision_Logic.h"

int EmergencyCheck(float acc, float vel, float dist)
{
	float a, d;

	//If acceleration is zero, no need for quadratic equation, time for collision equals distance over time
	if (acc == 0) {

		//If relative velocity is below 0, then no emergency
		if (vel <= 0)
			return 0;
		
		if ((dist / vel) <= 0.6)
			return 1;
		else
			return 0;
	}
	else {

		//quadratic equation logic
		a = 0.5 * acc;
		d = (vel*vel) - (4 * a * -dist);

		if (d < 0) {
			return 0;
		}
		
		float t = (-vel + sqrt(d)) / (2 * a);
		if (t <= 0.6 && t >= 0) {
			return 1;
		}

		return 0;
	}
}