#include <iostream>
#include "Road.h"

using namespace std;

const double deltaT = 0.01;
const double endTime = 40.0;

Road *myRoad;

void main()
{
	myRoad = new Road();
		myRoad->InitializeRoad(4); // creates cars and positions them on the road

	for (double t = 0.0; t <= endTime; t += deltaT) {
		myRoad->UpdateRoad(deltaT);
		cout << t << ", ";
		myRoad->PrintRoad();
	}

	cout << "<enter> to terminate: ";
	cin.get();
}
