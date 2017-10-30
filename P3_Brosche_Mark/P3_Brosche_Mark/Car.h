#pragma once
#include "Road.h"
//enum Leader { leader, follower };

class Car
{
public:
	Car(double initialPostion, double initialVelocity, double timeGap, double sensitivity);
	double GetPosition();
	double GetVelocity();
	double GetTimeGap();
	double GetSensitivity();
	void SetLeader(Car *car, Car *leader);
	double MPH2FPS(double mph);
	double FPS2MPH(double mph);
	//Leader GetLeader();
	void ComputeNS(double deltaT);
	void UpdateCS();

private:
	Car* leader;
	double positionCS;
	double positionNS;
	double velocityCS;
	double velocityNS;
	double accelerationCS;
	double accelerationNS;
	double sensitivity;
	double ControllerAcceleration();
	double mph;
	double timeGap;

};


