#ifndef STRUCTSCOMM_H
#define STRUCTSCOMM_H

#include "Vector3.h"
#include "Vector2.h"
#include "Rect.h"

using namespace std;

#define maxplayerCount 100
#define maxvehicleCount 100
#define maxitemsCount 100
#define maxGrenadeCount 100
#define maxconCount 100
#define maxwbCount 100
#define maxmzjCount 100
#define maxzddCount 100
#define maxdjCount 100
#define maxqtCount 100
#define maxqkCount 100
#define maxammoCount 100
#define maxwepCount 100
#define maxgrCount 100
#define maxpisCount 100
#define maxmiscCount 100
#define maxsnpCount 100
#define maxsmgCount 100
#define maxsgCount 100
#define maxarCount 100
#define maxarmCount 100

class Color {
public:
	float r;
	float g;
	float b;
	float a;

	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}

	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}

	static Color Black(){
		return Color(0, 0, 0);
	}

	static Color White(){
		return Color(255,255,255);
	}

	static Color Green(){
		return Color(0,255,0);
	}

	static Color Orange(){
		return Color(255, 138, 28);
	}

	static Color Red(){
		return Color(255, 0, 0);
	}

	static Color Yellow(){
		return Color(255, 234, 0);
	}

	static Color Gold(){
		return Color(227, 169, 10);
	}

	static Color Teal(){
		return Color(0, 255, 200);
	}

	static Color Blue(){
		return Color(0, 85, 255);
	}

	static Color Purple(){
		return Color(115, 0, 255);
	}

	static Color Pink(){
		return Color(255, 74, 243);
	}

	static Color Gray(){
		return Color(133, 133, 133);
	}
};

enum Mode {
	InitMode = 1,
	ESPMode = 2,
	HackMode = 3,
	StopMode = 4,
	Config = 5,
	OpenEvent = 6,
};

struct Request {
	int Mode;
	int ScreenWidth;
	int ScreenHeight;
	int Type;
	int Code;
	int Value;
	int EvPath;
};

struct PlayerData {
	wchar_t PlayerName[30];
	uint ActorID;
	int TeamID;
	float Health;
	float BotST;
	float Distance;
	Vector2 Body;
	Vector2 Root;
	Vector2 Head;
	Vector2 Neck;
	Vector2 Chest;
	Vector2 Pelvis;
	Vector2 LShoulder;
	Vector2 RShoulder;
	Vector2 LElbow;
	Vector2 RElbow;
	Vector2 LWrist;
	Vector2 RWrist;
	Vector2 LThigh;
	Vector2 RThigh;
	Vector2 LKnee;
	Vector2 RKnee;
	Vector2 LAnkle;
	Vector2 RAnkle;
};

struct VehicleData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct GrenadeData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct ItemData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct ARData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct SGData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct SMGData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct SNPData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct MISCData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct PISData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct GRData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct WEPData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct AMMOData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct QKData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct QTData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct DJData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct ZDDData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct MZJData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct WBData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct CONData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct ARMData {
	int Name;
	float Distance;
	Vector2 Location;
};

struct Response {
	bool Success;
	int PlayerCount;
	int MyTeamID;
	int MyFiring;
	int MyADS;
	int MyIdentified;
	int VehicleCount;
	int ItemsCount;
	int GrenadeCount;
	int ARMCount;
	int CONCount;
	int WBCount;
	int MZJCount;
	int ZDDCount;
	int DJCount;
	int QTCount;
	int QKCount;
	int AMMOCount;
	int WEPCount;
	int MISCCount;
	int SNPCount;
	int ARCount;
	int PISCount;
	int SMGCount;
	int SGCount;
	int GRCount;
	PlayerData Players[maxplayerCount];
	VehicleData Vehicles[maxvehicleCount];
	GrenadeData Grenade[maxGrenadeCount];
	ItemData Items[maxitemsCount];
	GRData GR[maxgrCount];
	SGData SG[maxsgCount];
	SMGData SMG[maxsmgCount];
	PISData PIS[maxpisCount];
	ARData AR[maxarCount];
	SNPData SNP[maxsnpCount];
	MISCData MISC[maxmiscCount];
	WEPData WEP[maxwepCount];
	AMMOData AMMO[maxammoCount];
	QKData QK[maxqkCount];
	QTData QT[maxqtCount];
	DJData DJ[maxdjCount];
	ZDDData ZDD[maxzddCount];
	MZJData MZJ[maxmzjCount];
	WBData WB[maxwbCount];
	CONData CON[maxconCount];
	ARMData ARM[maxarmCount];
};

#endif
