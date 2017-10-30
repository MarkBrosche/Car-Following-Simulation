#pragma once
#include "Car.h"
//enum Leader { leader, follower };

class Road
{
public:
	Road(); //constructor

	~Road(); //destructor

	void InitializeRoad(int n);
		/*
		Functionality: Initializes road with n cars.
		Parameters: n
		Return value: none
		*/
	void UpdateRoad(double deltaT);
	/*
	Functionality: update cars on road
	*/
	void PrintRoad();
	/*
	Functionality print the road and car statuses at the current time.
	*/

private:
	Car *cars[];
};

