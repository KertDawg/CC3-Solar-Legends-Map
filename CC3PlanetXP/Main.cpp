//  https://rpgmaps.profantasy.com/developing-add-ons-for-cc3-part-1-getting-started/

#include "math.h"
#include "stdio.h"
#include "resource.h"
#include "Main.h"
#include "Planet.h"
#include "Planets.h"

#undef IDD_DLGSOLARSYSTEMPARAMETERS


char CList[] = "SOLARSYSTEM\0\0";
PCMDPROC PList[] = { About, SetupDialog };

XP MyXP = { 0, CList, PList, 0, 0, 0, XPID, 0, 620, 0, 0, 620 };

static unsigned int ClosestPlanetNumber = 1;
static unsigned int FarthestPlanetNumber = 8;
static unsigned int DayNumber = 1;
static unsigned int MapWidth = 1;
static unsigned int MapHeight = 1;
static float OrbitalRadius = 100;


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

void XPCALL RunCreation()
{
	GPOINT2 MapCenter;
	GPOINT2 Location;
	Planets* PlanetsToDraw;
	Planet* p;
	pENTREC EntRec;
	SYMTMAT Mat;
	char Command[500];
	char Temp[30];
	float Scale;


	//  Get the dimensions, etc.
	MapCenter.x = (float)0;
	MapCenter.y = (float)0;

	// Draw the sun.
	sprintf_s(Command, "SYMBOLC;D:\\ProgramData\\Profantasy\\CC3Plus\\Symbols\\Cosmographer\\Cos Bitmap A\\CosA_Stars_Traveller.FSC;CosA G Star 1;%.4f;%.4f;%.4f;%.4f,%.4f;_;", 4.0f, 4.0f, 0.0f, MapCenter.x, MapCenter.y);
	ExecScriptCopy(Command);

	//  Set up the planets.
	PlanetsToDraw = new Planets(ClosestPlanetNumber, FarthestPlanetNumber, DayNumber, OrbitalRadius);

	//  Draw the planets!
	for (Planet p : PlanetsToDraw->ListOfPlanets)
	{
		//  Calculate the position.
		Location.x = (p.RadiusOnMap * cosf(p.CurrentTheta)) + MapCenter.x;
		Location.y = (p.RadiusOnMap * sinf(p.CurrentTheta)) + MapCenter.y;
		Scale = 4 * p.Diameter;

		//  Draw the planet.
		//INSSYM <Symbol name> <x scale> <y scale> <rotation angle> <Insertion point�>
		sprintf_s(Command, "SYMBOLC;D:\\ProgramData\\Profantasy\\CC3Plus\\Symbols\\Cosmographer\\Cos Bitmap A\\CosA_Planets_Traveller.FSC;%s;%.4f;%.4f;%.4f;%.4f,%.4f;_;", p.SymbolName, Scale, Scale, 0.0f, Location.x, Location.y);
		ExecScriptCopy(Command);

		//  Draw the orbit.
		sprintf_s(Command, "COLOR;15;LWIDTH;2;CIRR;%.4f;%.4f,%.4f;;", p.RadiusOnMap, MapCenter.x, MapCenter.y);
		ExecScriptCopy(Command);
	}

	delete PlanetsToDraw;
	Redraw();
	CmdEnd();
}
