#include <iostream>
#include "Road.h"
#include "Car.h"

using namespace std;
				//declares a car pointer
int numCars;

void Road::InitializeRoad(int n)
{
	numCars = n;
	//cars = new Car; // creates an array of car structures
	for (int i = 0; i < n; i++) {
		cars[i] = new Car(-(double)i*4.0, 0.0, 2.0, 0.7);
	} //(initial position, initial velocity, time gap, sensitivity)
	for (int i = 1; i < n; i++) {
		cars[i]->SetLeader(cars[i], cars[i-1]);
	} // sets the order of the cars
}

void Road::UpdateRoad(double deltaT)
{
	for (int i = 0; i < numCars; i++) {
		cars[i]->ComputeNS(deltaT);
	} // computes each car's next state
	for (int i = 0; i < numCars; i++) {
		cars[i]->UpdateCS();
	} // updates car's current state to the next state
}

void Road::PrintRoad()
{
	for (int i = 0; i < numCars; i++) {
		cout << cars[i]->GetPosition() << ", ";
	} // prints out each car's position to the console
	cout << endl;
}
