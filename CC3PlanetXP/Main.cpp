//  https://rpgmaps.profantasy.com/developing-add-ons-for-cc3-part-1-getting-started/

#include "math.h"
#include "stdio.h"
#include "resource.h"
#include "Main.h"
#include "Planet.h"
#include "Planets.h"

#undef IDD_DLGSOLARSYSTEMPARAMETERS

#define RANDOM ((float)rand() / (float)RAND_MAX)


char CList[] = "SOLARSYSTEM\0\0";
PCMDPROC PList[] = { About, SetupDialog };

XP MyXP = { 0, CList, PList, 0, 0, 0, XPID, 0, 620, 0, 0, 620 };

static unsigned int ClosestPlanetNumber = 1;
static unsigned int FarthestPlanetNumber = 5;
static unsigned int DayNumber = 1;
static unsigned int MapWidth = 1;
static unsigned int MapHeight = 1;
static float OrbitalRadius = 100;
static float PlanetScale = 2;
static bool DrawAsteroids = true;
static bool DrawLabels = true;
static bool DrawScale = true;


/////////////  DllMain - XP initialization & Unload code //////////////
BOOL WINAPI DllMain(const HINSTANCE hDLL, const DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		MyXP.ModHdl = hDLL;
		_XPRegCmd(&MyXP);
		break;
	case DLL_PROCESS_DETACH:
		_XPUnregCmd(&MyXP);
		break;
	default:
		break;
	}
	return TRUE;
}


void XPCALL About()
{
	FORMST(MyAPkt, "CC3+ Solar System Generator\nv0.0.1\n\n"
		"Solar System Generator for Solar Legends"
	)

	FormSt(&MyAPkt, RSC(FD_MsgBox));
	CmdEnd();
}

void XPCALL SetupDialog()
{
	int DialogHandle = DefDlg("IDD_DLGSOLARSYSTEMPARAMETERS", 0, 0, InitSetupDialog, NULL, NULL);
	EDCTL(DialogHandle, IDC_CLOSESTPLANETNUMBER, 0, FT_UDec4, 6, &ClosestPlanetNumber, PlanetCountChange);
	EDCTL(DialogHandle, IDC_FARTHESTPLANETNUMBER, 0, FT_UDec4, 6, &FarthestPlanetNumber, PlanetCountChange);
	EDCTL(DialogHandle, IDC_DAYNUMBER, 0, FT_UDec4, 6, &DayNumber, DayNumberChange);
	EDCTL(DialogHandle, IDC_ORBITALRADIUS, 0, FT_Dist4, 6, &OrbitalRadius, OrbitalRadiusChange);
	EDCTL(DialogHandle, IDC_PLANETSCALE, 0, FT_Dist4, 6, &PlanetScale, PlanetScaleChange);
	CHKCTL(DialogHandle, IDC_DRAWASTEROIDS, 0, FT_UDec1, &DrawAsteroids, 1, DrawAsteroidsChange);
	CHKCTL(DialogHandle, IDC_DRAWLABELS, 0, FT_UDec1, &DrawLabels, 1, DrawLabelsChange);
	CHKCTL(DialogHandle, IDC_DRAWSCALE, 0, FT_UDec1, &DrawScale, 1, DrawScaleChange);
	int DialogResult = XPDlog(DialogHandle, MyXP.ModHdl, 0);
	RelDlg(DialogHandle);

	if (DialogResult == IDOK)
	{
		RunCreation();
	}

	CmdEnd();
}

static int XPCALL InitSetupDialog(void)
{
	return 0;
}

static int XPCALL PlanetCountChange(void)
{
	return 0;
}

static int XPCALL DayNumberChange(void)
{
	return 0;
}

static int XPCALL OrbitalRadiusChange(void)
{
	return 0;
}

static int XPCALL PlanetScaleChange(void)
{
	return 0;
}

static int XPCALL DrawAsteroidsChange(void)
{
	return 0;
}

static int XPCALL DrawLabelsChange(void)
{
	return 0;
}

static int XPCALL DrawScaleChange(void)
{
	return 0;
}

void XPCALL RunCreation()
{
	GPOINT2 MapCenter;
	GPOINT2 Location;
	Planets* PlanetsToDraw;
	Planet* p;
	pENTREC EntRec;
	SYMTMAT Mat;
	char CommandSet[16384] = "";
	char Command[500];
	char Temp[30];
	float Scale;
	float FudgeFactor;


	//  Get the dimensions, etc.
	MapCenter.x = (float)0;
	MapCenter.y = (float)0;

	//  Load the symbols.
	sprintf_s(Command, "CATALOG;$Solar Legends Symbols.FSC;");
	ExecScriptCopy(Command);

	// Draw the sun.
	sprintf_s(Command, "SYMBOLC;$Solar Legends Symbols.FSC;Sun;%.4f;%.4f;%.4f;%.4f,%.4f;_;", PlanetScale, PlanetScale, 0.0f, MapCenter.x, MapCenter.y);
	ExecScriptCopy(Command);
	sprintf_s(Command, "SSET;Sun;");
	ExecScriptCopy(Command);

	//  Set up the planets.
	PlanetsToDraw = new Planets(ClosestPlanetNumber, FarthestPlanetNumber, DayNumber, OrbitalRadius);

	//  Draw the planets!
	for (Planet p : PlanetsToDraw->ListOfPlanets)
	{
		//  Calculate the position.
		Location.x = (p.RadiusOnMap * cosf(p.CurrentTheta)) + MapCenter.x;
		Location.y = (p.RadiusOnMap * sinf(p.CurrentTheta)) + MapCenter.y;
		Scale = PlanetScale * p.Diameter;

		//  Draw the orbit.
		sprintf_s(Command, "COLOR;15;LWIDTH;2;CIRR;%.4f;%.4f,%.4f;;", p.RadiusOnMap, MapCenter.x, MapCenter.y);
		ExecScriptCopy(Command);
		sprintf_s(Command, "SSET;Planet Orbits;");
		ExecScriptCopy(Command);

		//  Draw the planet.
		//INSSYM <Symbol name> <x scale> <y scale> <rotation angle> <Insertion point…>
		sprintf_s(Command, "SYMBOLC;$Solar Legends Symbols.FSC;%s;%.4f;%.4f;%.4f;%.4f,%.4f;_;", p.SymbolName, Scale, Scale, 0.0f, Location.x, Location.y);
		ExecScriptCopy(Command);
		sprintf_s(Command, "SSET;Planets;");
		ExecScriptCopy(Command);

		//  Draw the label.
		if (DrawLabels)
		{
			Location.y -= (15 * (p.Diameter + 1));
			sprintf_s(Command, "TSPECH;15;TSPECJ;4;COLOR;15;TEXM;%s;%.4f,%.4f;", p.Name, Location.x, Location.y);
			ExecScriptCopy(Command);
		}
	}

	//  Should we draw the asteroid belt?
	if (DrawAsteroids)
	{
		//  Draw the circle.
		sprintf_s(Command, "COLOR;147;LSTYLE;0;LWIDTH;53;FSTYLE;1;CIRR;%.4f;%.4f,%.4f;_;", 3*OrbitalRadius, MapCenter.x, MapCenter.y);
		ExecScriptCopy(Command);
		sprintf_s(Command, "SSET;Asteroid Orbit;");
		ExecScriptCopy(Command);

		//  Draw asteroids.
		Draw20Asteroids(OrbitalRadius, PlanetScale);
		Draw20Asteroids(OrbitalRadius, PlanetScale);
		Draw20Asteroids(OrbitalRadius, PlanetScale);
		Draw20Asteroids(OrbitalRadius, PlanetScale);
		Draw20Asteroids(OrbitalRadius, PlanetScale);
	}

	//  Should we draw a scale?
	if (DrawScale)
	{
		GPOINT2 ScaleStart;
		GPOINT2 ScaleEnd;
		float BigTickHeight;
		float SmallTickHeight;
		float DayDistance;
		float DayLineX;
		int DayNumber = 0;
		int DaysToLabel;


		ScaleStart.x = 100;
		ScaleStart.y = -400;
		ScaleEnd.x = 300;
		ScaleEnd.y = -400;
		BigTickHeight = 20;
		SmallTickHeight = 10;

		//  Draw base scale.
		strcat_s(CommandSet, "SSET;Scale;COLOR;15;LSTYLE;0;LWIDTH;2;FSTYLE;1;");
		sprintf_s(Command, "LINE;%.4f,%.4f;%.4f,%.4f;_;", ScaleStart.x, ScaleStart.y, ScaleEnd.x, ScaleEnd.y);
		strcat_s(CommandSet, Command);
		sprintf_s(Command, "LINE;%.4f,%.4f;%.4f,%.4f;_;", ScaleStart.x, ScaleStart.y - BigTickHeight, ScaleStart.x, ScaleStart.y + BigTickHeight);
		strcat_s(CommandSet, Command);
		sprintf_s(Command, "LINE;%.4f,%.4f;%.4f,%.4f;_;", ScaleEnd.x, ScaleEnd.y - BigTickHeight, ScaleEnd.x, ScaleEnd.y + BigTickHeight);
		strcat_s(CommandSet, Command);

		//  Draw the text.
		sprintf_s(Command, "TSPECH;30;TSPECJ;4;COLOR;15;TEXM;Days;%.4f,%.4f;", ScaleStart.x + 100, ScaleStart.y + 40);
		strcat_s(CommandSet, Command);

		//  Draw day lines.
		DayDistance = OrbitalRadius * 32 / 100;
		DaysToLabel = floor(64 / DayDistance);
		strcat_s(CommandSet, "LWIDTH;1;");

		for (int i = DayDistance; i <= 200; i += DayDistance)
		{
			DayNumber++;
			DayLineX = ScaleStart.x + i;
			sprintf_s(Command, "LINE;%.4f,%.4f;%.4f,%.4f;_;", DayLineX, ScaleStart.y - SmallTickHeight, DayLineX, ScaleStart.y + SmallTickHeight);
			strcat_s(CommandSet, Command);

			if (!(DayNumber % DaysToLabel))
			{
				sprintf_s(Command, "TSPECH;12;TSPECJ;4;COLOR;15;TEXM;%d;%.4f,%.4f;", DayNumber, DayLineX, ScaleStart.y - 40);
				strcat_s(CommandSet, Command);
			}
		}

		ExecScriptCopy(CommandSet);
	}

	delete PlanetsToDraw;
	Redraw();
	CmdEnd();
}

void XPCALL Draw20Asteroids(float BaseRadius, float BaseScale)
{
	char CommandSet[16384] = "";
	char Command[500];
	float Scale;
	float Rotation;
	float Theta;
	float Radius;
	float RadiusBandWidth;
	GPOINT2 Location;
	int AsteroidNumber;

	//  100 => 200
	//  50 => 100


	for (int i = 0; i < 20; i++)
	{
		AsteroidNumber = floor(RANDOM * 2) + 1;
		Scale = ((((RANDOM * 2000) - 1000) / 1000) + BaseScale) / 2;
		Rotation = (RANDOM * 35900) / 100;
		Theta = (RANDOM * 35900) / 100;
		RadiusBandWidth = BaseRadius;
		Radius = (RANDOM * RadiusBandWidth) + (BaseRadius * 3) - (RadiusBandWidth / 2);
		Location.x = Radius * cos(Theta);
		Location.y = Radius * sin(Theta);

		//sprintf_s(Command, "INSSYM CosA Asteroid %d;%.4f;%.4f;%.4f;%.4f,%.4f;", AsteroidNumber, Scale, Scale, Rotation, Location.x, Location.y);
		sprintf_s(Command, "SSET;Asteroids;");
		strcat_s(CommandSet, Command);
		sprintf_s(Command, "SYMBOLC;$Solar Legends Symbols.FSC;Asteroid %d;%.4f;%.4f;%.4f;%.4f,%.4f;_;", AsteroidNumber, Scale, Scale, Rotation, Location.x, Location.y);
		strcat_s(CommandSet, Command);
	}

	ExecScriptCopy(CommandSet);
	CmdEnd();
}
