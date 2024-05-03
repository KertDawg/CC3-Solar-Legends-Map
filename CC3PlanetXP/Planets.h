#pragma once

#include <vector>
#include "Planet.h"


class Planets
{
public:
	Planets(int ClosestPlanet, int FarthestPlanet, int CurrentDay, float ReloativeSize);
	~Planets();

	std::vector<Planet> ListOfPlanets;
	int ClosestPlanetNumber;
	int FarthestPlanetNumber;
	int NumberOfPlanets;
	int CurrentDay;
	float ReloativeSize;
};

