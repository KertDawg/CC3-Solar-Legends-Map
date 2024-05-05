
#include <stdlib.h>

#include "Planet.h"
#include "Planets.h"

Planets::Planets(int ClosestPlanet, int FarthestPlanet, int SystemCurrentDay, float SystemReloativeSize)
{
	Planet *OnePlanet;


	if (ClosestPlanet < 1)
	{
		ClosestPlanet = 1;
	}

	if (FarthestPlanet > 8)
	{
		FarthestPlanet = 9;
	}

	if (ClosestPlanet > FarthestPlanet)
	{
		FarthestPlanet = ClosestPlanet;
	}

	ClosestPlanetNumber = ClosestPlanet;
	FarthestPlanetNumber = FarthestPlanet;
	NumberOfPlanets = 1 + FarthestPlanetNumber - ClosestPlanetNumber;
	CurrentDay = SystemCurrentDay;
	ReloativeSize = SystemReloativeSize;


	for (int i = ClosestPlanetNumber; i <= FarthestPlanetNumber; i++)
	{
		switch (i)
		{
		case 1:
			OnePlanet = new Planet();
			OnePlanet->Set("Mercury", 0.47f, 87.97f, 10, 0.4f, CurrentDay, ReloativeSize, "CosA Planet Alien 1", false);
			ListOfPlanets.push_back(*OnePlanet);
			break;
		case 2:
			OnePlanet = new Planet();
			OnePlanet->Set("Venus", 0.73f, 224.7f, 20, 0.9f, CurrentDay, ReloativeSize, "CosA Planet Life 3", false);
			ListOfPlanets.push_back(*OnePlanet);
			break;
		case 4:
			OnePlanet = new Planet();
			OnePlanet->Set("Mars", 1.67f, 686.98f, 30, 1, CurrentDay, ReloativeSize, "CosA Planet Dry 1", false);
			ListOfPlanets.push_back(*OnePlanet);
			break;
		case 5:
			OnePlanet = new Planet();
			OnePlanet->Set("Jupiter", 5.37f, 11.86f * 365.26f, 40, 4, CurrentDay, ReloativeSize, "CosA Gasgiant 1", true);
			ListOfPlanets.push_back(*OnePlanet);
			break;
		case 6:
			OnePlanet = new Planet();
			OnePlanet->Set("Saturn", 10.07f, 29.46f * 365.26f, 50, 1, CurrentDay, ReloativeSize, "CosA Gasgiant 1", true);
			ListOfPlanets.push_back(*OnePlanet);
			break;
		case 7:
			OnePlanet = new Planet();
			OnePlanet->Set("Uranus", 20.09f, 84.01f * 365.26f, 60, 1, CurrentDay, ReloativeSize, "CosA Planet Water 1", false);
			ListOfPlanets.push_back(*OnePlanet);
			break;
		case 8:
			OnePlanet = new Planet();
			OnePlanet->Set("Neptune", 164.79f * 365.26f, 30.32f, 70, 1, CurrentDay, ReloativeSize, "CosA Planet Water 2", false);
			ListOfPlanets.push_back(*OnePlanet);
			break;
		case 9:
			OnePlanet = new Planet();
			OnePlanet->Set("Pluto", 90650.0f, 48.823f, 80, 1, CurrentDay, ReloativeSize, "CosA Planet Ice 1", false);
			ListOfPlanets.push_back(*OnePlanet);
			break;

		default:
			OnePlanet = new Planet();
			OnePlanet->Set("Earth", 1.0f, 1.0f, 90, 1, CurrentDay, ReloativeSize, "CosA Planet Life 1", false);
			ListOfPlanets.push_back(*OnePlanet);
		}
	}
}

Planets::~Planets()
{
}
