#pragma once
#include <windows.h>
#include <XT_Entities.h>
#include "XP.H"

#define XPID 0x2456

void XPCALL About(void);
void XPCALL SetupDialog(void);

extern char CList[];
extern PCMDPROC PList[];
extern XP MyXP;
void XPCALL RunCreation();
static int XPCALL InitSetupDialog(void);
static int XPCALL PlanetCountChange(void);
static int XPCALL DayNumberChange(void);
static int XPCALL OrbitalRadiusChange(void);
static int XPCALL PlanetScaleChange(void);
static int XPCALL DrawAsteroidsChange(void);
static int XPCALL DrawLabelsChange(void);
static int XPCALL DrawScaleChange(void);
static void XPCALL Draw20Asteroids(float BaseRadius, float BaseScale);
