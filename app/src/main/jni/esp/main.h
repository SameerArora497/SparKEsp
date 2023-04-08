#ifndef KMODS_H
#define KMODS_H

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <dirent.h>
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <jni.h>
#include <sys/mman.h>
#include "StructsCommon.h"
#include "Log.h"
//#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

extern int eventFile;

bool isESP = true;
//Aimbot

bool isDrawCrosshair,IgnoreBot;

bool isAimbot = false;
bool isDrawAimRadius = false;
bool isPredictAim = false;
bool isWhenADS = false;
bool isWhenFiring = false;
bool isDrawTouch = false;
bool isTrueAimbot = false;
bool isAlwaysONAimbot = false;
float AimbotRadius = 0.0f;
float recoilComp = 3.0f;
bool isPhone = false;
bool isPhoneRU = false;
bool isAimbotInitialized = false;
bool isReqMT = false;
bool isPhoneN = false;
int AimFor = 3;
int touchXMax = 0;
int touchYMax = 0;
int touchXMin = 0;
int touchYMin = 0;
int touchXS = 1540;
int touchYS = 254;
int touchSRadius = 80;
int touchPower = 0;
int typeTouch = 0;
int slotMin = 0;
int slotMax = 0;
int aimbotEventIDMin = 0;
int aimbotEventIDMax = 0;
int aimLatency = 0;
int evID;
std::string event_path = "/dev/input/event0";
//Max Displayed Items
int maxItemDisp = 50;
//Player
bool isPlayerName = false;
bool isPlayerDist = false;
bool isPlayerHealth = false;
bool isTeamMateShow = false;
bool isPlayerBox = true;
bool isPlayerLine = true;
bool isPlayer360 = false;
bool isPlayerBone = false;
bool isDrawCount = true;
float playerTextSize = 15;
int lineThickness = 2;
int boxThickness = 2;
int boneThickness = 2;
int lineAlpha = 125;
//Vehicle
bool isVehicleName = false;
bool isVehicleDist = false;
float vehicleTextSize = 17;
//LootBox
bool isLootBoxName = false;
bool isLootBoxDist = false;
float lootTextSize = 17;
//Grenamde
bool isGrenadeName = false;
bool isGrenadeDist = false;
float grenadeTextSize = 17;
//All lootable items
float itemsTextSize = 17;
//AR
bool isM762 = true;
bool isSCAR = false;
bool isM416 = false;
bool isM16A = false;
bool isMk47 = false;
bool isG36 = false;
bool isQBZ = false;
bool isAKM = false;
bool isGroza = false;
bool isAUG = false;
//SG
bool isS12K = false;
bool isS686 = false;
bool isS1897 = false;
bool isSawedOff = false;
bool isDBS = false;
//SMG
bool isBizon = false;
bool isTommyGun = false;
bool isMP5 = false;
bool isUMP9 = false;
bool isVector = false;
bool isUzi = false;
//Sniper
bool isAWM = false;
bool isQBU = false;
bool isSLR = false;
bool isSKS = false;
bool isMini14 = false;
bool isM24 = false;
bool isKar98K = false;
bool isVSS = false;
bool isWin94 = false;
bool isMk14 = false;
//Misc
bool isDP28 = false;
bool isM249 = false;
bool isCrossBow = false;
//Pistols
bool isR1895 = false;
bool isVz61 = false;
bool isP92 = false;
bool isP18C = false;
bool isR45 = false;
bool isP1911 = false;
bool isDeagle = false;
//Grenade
bool isFragGrenade = false;
bool isSmokeGrenade = false;
bool isMolotov = false;
//Melee
bool isSickle = false;
bool isMachete = false;
bool isCrowbar = false;
bool isPan = false;
//Ammo
bool is762 = false;
bool is45ACP = false;
bool is556 = false;
bool is9mm = false;
bool is300Mag = false;
bool is12G = false;
bool isBolt = false;
bool isFlare = false;
//AccQK
bool isSMGFlashHider = false;
bool isSMGSuppressor = false;
bool isSMGCompensator = false;
bool isARSuppressor = false;
bool isARFlashHider = false;
bool isARCompensator = false;
bool isSGChoke = false;
bool isSGDuckbill = false;
bool isSnipFlashHider = false;
bool isSnipCompensator = false;
bool isSnipSuppressor = false;
//AccQT
bool isTacStock = false;
bool isCheekpad = false;
bool isStock = false;
//AccDJ
bool isSnipExQuickdraw = false;
bool isSMGExtended = false;
bool isSMGQuickdraw = false;
bool isSnipExtended = false;
bool isSnipQuickdraw = false;
bool isARQuickdraw = false;
bool isARExQuickdraw = false;
bool isARExtended = false;
bool isSMGExQuickdraw = false;
//AccZDD
bool isCrossbowPad = false;
bool isBulletLoops = false;
//AccWB
bool isThumbGrip = false;
bool isLaserSight = false;
bool isAngledGrip = false;
bool isLightGrip = false;
bool isHalfGrip = false;
bool isVerticalGrip = false;
//AccMZJ
bool is8xScope = false;
bool is2xScope = false;
bool isRedDot = false;
bool is3xScope = false;
bool isHolo = false;
bool is6xScope = false;
bool is4xScope = false;
bool isCanted = false;
//CON
bool isPills = false;
bool isInjections = false;
bool isDrinks = false;
bool isFirstAid = false;
bool isBandage = false;
bool isMedKit = false;
//ARM
bool isLv3Bag = false;
bool isLv2Bag = false;
bool isLv1Bag = false;
bool isLv3Armor = false;
bool isLv2Armor = false;
bool isLv1Armor = false;
bool isLv3Helm = false;
bool isLv2Helm = false;
bool isLv1Helm = false;
bool isGhillie = false;

int startClient();
bool isConnected();
void stopClient();
bool initServer();
bool stopServer();

Response getData(int screenWidth, int screenHeight);
Response openEVPath(int eventID);

bool isContain(string str, const char* check) {
	size_t found = str.find(check);
	return (found != string::npos);
}

#endif
