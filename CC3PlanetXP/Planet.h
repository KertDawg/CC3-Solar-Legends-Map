#pragma once

class Planet
{
public:
	Planet();
	void Set(char* PlanetName, float PlanetOrbitalRadius, float AngularSpeed, float StartingTheta, float PlanetDiameter, int CurrentDay, float RelativeSize, char *PlanetSymbolName);
	void SetDayAndSize(int DayNumber, float RelativeSize);

	char Name[200];
	float RadiusOnMap;
	float CurrentTheta;
	float Diameter;
	char SymbolName[100];

private:
	float OrbitalRadius;
	float AngularSpeed;
	float StartingTheta;
};
