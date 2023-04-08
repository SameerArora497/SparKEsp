#ifndef DESI_ESP_IMPORTANT_IMPORT_H
#define DESI_ESP_IMPORTANT_IMPORT_H

#include <jni.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cerrno>
#include <sys/un.h>
#include <cstring>
#include <string>
#include <cmath>
#include "struct.h"

bool Health = false;
bool Name = false;
bool Team_ID = false;
bool Distance = false;
bool Red_dots = false;
bool Skeletons = false;
bool Weapon = false;
bool Enemy_count = false;
bool Radar_line = false;
bool Edge_warning = false;
bool Grenade_alert = false;
bool Teammates = false;
bool itemImage = false;

int boxStyle = 0;
int lineStyle = 0;
bool fovScreen = false;
bool AdjustCamera = false;
bool RecoilADS = false;
bool AimToBot = false;
bool reverseTouch = false;
bool lockAimpost = false;
bool setAimForGlobal = false;
int fovrange = false;
int scale = 0;
int vertical = 0;
int aimObj = 0;

std::string Dirpatch;
std::string Patchmd5;
std::string Patchsh1;
std::string Patchsh256;

int aimmode;
int aimstate;
int aimprior;
int aimposx;
int aimposy;
float aimspeed;
int touchspeed;

int AutoShootTime;
int shootLoopType;
int shootLoopRecoil;
bool AutoShootPos = false;
int AutoShootPosX;
int AutoShootPosY;
bool AutoShoot = false;
int AutoShoots = 0;

int fpsCount = 60;

bool AquaRail = false;
bool BRDM = false;
bool Boat = false;
bool Buggy = false;
bool Bus = false;
bool Coupe = false;
bool Dacia = false;
bool Glider = false;
bool LadaNiva = false;
bool Mirado = false;
bool Motorbike = false;
bool Pickup = false;
bool Rony = false;
bool Scooter = false;
bool Snowbike = false;
bool Snowmobile = false;
bool Tuk = false;
bool Uaz = false;
bool Utv = false;
bool MonsterTruck = false;
bool ATV = false;

bool ammo300 = false;
bool ammo45 = false;
bool ammo12G = false;
bool ammo556 = false;
bool ammo762 = false;
bool ammo9mm = false;

bool x2 = false;
bool x3 = false;
bool x4 = false;
bool x6 = false;
bool x8 = false;
bool k98 = false;
bool AKM = false;
bool AUG = false;
bool AWM = false;
bool Crossbow = false;
bool DP12 = false;
bool DP28 = false;
bool Deagle = false;
bool Dot = false;
bool Flare = false;
bool G36 = false;
bool Grenade = false;
bool Groza = false;
bool Holo = false;
bool M1014 = false;
bool M16 = false;
bool M24 = false;
bool M249 = false;
bool M4 = false;
bool M762 = false;
bool MK14 = false;
bool MK47 = false;
bool MP5K = false;
bool Mini14 = false;
bool Molotov = false;
bool PP19 = false;
bool Pan = false;
bool QBU = false;
bool QBZ = false;
bool S12K = false;
bool S1897 = false;
bool S686 = false;
bool SCAR = false;
bool SKS = false;
bool SLR = false;
bool Stun = false;
bool Tommy = false;
bool UMP = false;
bool Uzi = false;
bool VSS = false;
bool Vector = false;
bool Win94 = false;
bool Armor2 = false;
bool Armor3 = false;
bool Helmet2 = false;
bool Helmet3 = false;

bool Bandage = false;
bool Drink = false;
bool FirstAid = false;
bool Injection = false;
bool Pills = false;

bool Aircraft = false;
bool Airdrop = false;
bool Angled = false;
bool Backpack2 = false;
bool Backpack3 = false;
bool CompensatorAR = false;
bool CompensatorSMG = false;
bool CompensatorSNP = false;
bool EQMAR = false;
bool EQMSMG = false;
bool EQMSNP = false;
bool FlashHiderAR = false;
bool FlashHiderSMG = false;
bool FlashHiderSNP = false;
bool Half = false;
bool Light = false;
bool Loot = false;
bool StockARSMG = false;
bool StockSNP = false;
bool SuppressorAR = false;
bool SuppressorSMG = false;
bool SuppressorSNP = false;
bool Thumb = false;
bool Vertical = false;
bool ShopToken = false;
bool GasCan = false;
bool ShowAllItem = false;
bool EspView = false;

std::string aimxx = "8AC8239FEDF5AE16682A840CACF48046";
std::string aimyy = "FE47CC7D1A84B1B7A80CF4A717D56A6709A30C9D";
std::string aimzz = "8C252F7D746739C0D1C7A5D4668B23858AA46A0034AB2FFF97B3D88C971409C7";

std::string OR = "https://ninjaskillzcheat-default-rtdb.firebaseio.com/CheatNinja.json";
std::string EDit = "https://ninjaskillzcheat-default-rtdb.firebaseio.com/CheatNinja/Key/";

const char *FlagsNames[239] = {
        "AD",
        "AE",
        "AF",
        "AG",
        "AI",
        "AL",
        "AM",
        "AO",
        "AR",
        "AS",
        "AT",
        "AU",
        "AW",
        "AX",
        "AZ",
        "BA",
        "BB",
        "BD",
        "BE",
        "BF",
        "BG",
        "BH",
        "BI",
        "BJ",
        "BM",
        "BN",
        "BO",
        "BQ",
        "BR",
        "BS",
        "BT",
        "BW",
        "BY",
        "BZ",
        "BZBZ",
        "CA",
        "CC",
        "CE",
        "CF",
        "CG",
        "CH",
        "CI",
        "CK",
        "CL",
        "CM",
        "CN",
        "CO",
        "CORSICA",
        "CR",
        "CU",
        "CV",
        "CW",
        "CX",
        "CY",
        "CZ",
        "DE",
        "DHSH",
        "DJ",
        "DK",
        "DM",
        "DZ",
        "EA",
        "EC",
        "EE",
        "EG",
        "EH",
        "EN",
        "ER",
        "ES",
        "ET",
        "FJ",
        "FK",
        "FL",
        "FM",
        "FO",
        "FR",
        "G1",
        "GA",
        "GB",
        "GD",
        "GE",
        "GG",
        "GH",
        "GI",
        "GL",
        "GM",
        "GN",
        "GQ",
        "GR",
        "GT",
        "GU",
        "GW",
        "GY",
        "HAWAII",
        "HK",
        "HN",
        "HR",
        "HT",
        "HU",
        "ID",
        "IE",
        "IL",
        "IM",
        "IN",
        "IO",
        "IQ",
        "IR",
        "IS",
        "IT",
        "JE",
        "JM",
        "JO",
        "JP",
        "KE",
        "KG",
        "KH",
        "KI",
        "KM",
        "KN",
        "KP",
        "KR",
        "KW",
        "KY",
        "KZ",
        "LA",
        "LB",
        "LI",
        "LK",
        "LR",
        "LS",
        "LT",
        "LU",
        "LV",
        "LY",
        "MA",
        "MADEIRA",
        "MC",
        "MD",
        "ME",
        "MG",
        "MH",
        "MK",
        "ML",
        "MM",
        "MN",
        "MO",
        "MP",
        "MQ",
        "MR",
        "MS",
        "MT",
        "MU",
        "MV",
        "MW",
        "MX",
        "MY",
        "MZ",
        "NA",
        "NATO",
        "NE",
        "NF",
        "NG",
        "NI",
        "NL",
        "NO",
        "NP",
        "NR",
        "NU",
        "NZ",
        "OM",
        "OSSETIA",
        "PA",
        "PE",
        "PF",
        "PG",
        "PH",
        "PK",
        "PL",
        "PN",
        "PR",
        "PS",
        "PT",
        "PW",
        "PY",
        "QA",
        "RO",
        "RS",
        "RU",
        "RW",
        "SA",
        "SB",
        "SC",
        "SD",
        "SE",
        "SG",
        "SI",
        "SK",
        "SL",
        "SN",
        "SO",
        "SR",
        "SS",
        "ST",
        "SV",
        "SY",
        "SZ",
        "TC",
        "TD",
        "TG",
        "TH",
        "TJ",
        "TK",
        "TL",
        "TM",
        "TN",
        "TO",
        "TR",
        "TT",
        "TV",
        "TW",
        "TZ",
        "UA",
        "UG",
        "US",
        "UY",
        "UZ",
        "VA",
        "VE",
        "VG",
        "VI",
        "VN",
        "VU",
        "WALES",
        "WS",
        "XK",
        "YE",
        "ZA",
        "ZM",
        "ZW"
};
const char* fakeName = "";
const char* realNM;

#endif //DESI_ESP_IMPORTANT_IMPORT_H
