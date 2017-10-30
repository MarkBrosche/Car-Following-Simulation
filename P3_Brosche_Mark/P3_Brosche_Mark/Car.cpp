#include "Euler.h"
#include "Car.h"

Car::Car(double initialPosition, double initialVelocity, double timeGap, double sensitivity)
{
	positionCS = initialPosition;
	velocityCS = initialVelocity;
	accelerationCS = 0;
	leader = 0;
	timeGap = timeGap;
	sensitivity = sensitivity;
}

double Car::ControllerAcceleration()
{
	return(sensitivity*((leader->positionCS - positionCS) - velocityCS * timeGap));	// computes acceleration based on distance and time gap
}

void Car::SetLeader(Car *car, Car *myLeader)
{
	leader = myLeader;
	accelerationCS = ControllerAcceleration();
}

double Car::MPH2FPS(double mph)
{
	return(mph * 5280 / 3600);
}

double Car::FPS2MPH(double mph)
{
	return(mph * 3600 / 5280);
}

void Car::ComputeNS(double deltaT)
{
	static int leaderState = 0;
	static double leaderTimer = 0.0;

	if (leader == 0) {		//car is the leader
		switch (leaderState)
		{
		case 0:
			if (velocityCS < MPH2FPS(60.0)) {
				accelerationNS = 8.82;
			}			// leader accelerates to 60 mph
			else {
				accelerationNS = 0.0;
				leaderState = 1;
				leaderTimer = 0.0;
			}
			break;
		case 1:
			if (leaderTimer < 10.0) {
				accelerationNS = 0.0;
			}			// leader stays at 60 mph for 10 seconds
			else {
				accelerationNS = -8.82;
				leaderState = 2;
			}
			leaderTimer += deltaT;
			break;
		case 2:
			if (velocityCS > 0) {
				accelerationNS = -8.82;
			}			// leader decelerates to 0 mph after 10 seconds
			else {
				accelerationNS = 0.0;
				leaderState = 3;
			}
			break;
		case 3:
			accelerationNS = 0.0;					// leader stays at 0 mph
			break;
		default:
			break;
		}
		velocityNS = velocityCS + accelerationCS * deltaT;		// computes next state velocity
		positionNS = positionCS + velocityCS*deltaT;
	}			// computes next state position
	else {
		double distance = Car::leader->GetPosition() - positionCS;			// computes distance between leader and current car
		accelerationNS = ControllerAcceleration();						// computes next state acceleration
		velocityNS = Euler(velocityCS, accelerationCS, deltaT);	// computes next state velocity
		positionNS = Euler(positionCS, velocityCS, deltaT);
	}	// computes next state position
}

void Car::UpdateCS()															// updates all current states with computed next states
{
	accelerationCS = accelerationNS;
	velocityCS = velocityNS;
	positionCS = positionNS;
}

double Car::GetPosition()
{
	return positionCS;
}
