
#define _USE_MATH_DEFINES
#include <math.h>
#include "string.h"
#include "Planet.h"

Planet::Planet()
{
	strcpy_s(Name, "");
	strcpy_s(SymbolName, "");
	OrbitalRadius = 0;
	AngularSpeed = 0;
	StartingTheta = 0;
	RadiusOnMap = 1;
	CurrentTheta = 0;
	Diameter = 0;
}

void Planet::Set(char* PlanetName, float PlanetOrbitalRadius, float PlanetPeriodInDays, float PlanetStartingTheta, float PlanetDiameter, int CurrentDay, float RelativeSize, char *PlanetSymbolName, float SymbolPositionFudgeFactor)
{
	strcpy_s(Name, PlanetName);
	strcpy_s(SymbolName, PlanetSymbolName);
	OrbitalRadius = PlanetOrbitalRadius;
	AngularSpeed = (365.26  * M_2_PI)/ PlanetPeriodInDays;  //  radians/day
	StartingTheta = (PlanetStartingTheta * M_PI) / 180;  //  Convert degrees to radians
	RadiusOnMap = 1.0f;
	CurrentTheta = 0.0f;
	Diameter = PlanetDiameter;
	PositionFudgeFactor = SymbolPositionFudgeFactor;

	SetDayAndSize(CurrentDay, RelativeSize);
}

void Planet::SetDayAndSize(int DayNumber, float RelativeSize)
{
	//  Set theta.
	//  theta = starting_theta + (earth_days_passed x (radians/earth_day))
	CurrentTheta = StartingTheta + (DayNumber * AngularSpeed);

	//  Set the real orbital radius on the map.
	RadiusOnMap = OrbitalRadius * RelativeSize;

	//  Fix the position fudge factor.
	//  0.145
	//  100 -> 0.1425 * 4 * 100/100 = 0.57
	//  80 -> 0.475
	//  60 -> 0.3
	//  50 -> 0.15
	//  y = 0.6034 * ln(x) - 2.1897
	//PositionFudgeFactor = (PositionFudgeFactor == 0) ? 1 : 0.475;// (PositionFudgeFactor * Diameter * RelativeSize / 100);
	PositionFudgeFactor = (PositionFudgeFactor == 0) ? 1 : (0.6034 * logf(RelativeSize) - 2.1897);
}
