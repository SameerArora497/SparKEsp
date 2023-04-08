#ifndef RESOURCE1_INITIAL_FUNCTION_H
#define RESOURCE1_INITIAL_FUNCTION_H

//espGeneric
bool espGeneric[13] = {
        Health, Name, Team_ID,
        Distance, Red_dots, Skeletons,
        Weapon, Enemy_count, Radar_line,
        Edge_warning, Grenade_alert, Teammates,
        itemImage
};

const char *espGenerics[12] = {
        "Health", "Name", "Team_ID",
        "Distance", "Red_dots", "Skeletons",
        "Weapon", "Enemy_count", "Radar_line",
        "Edge_warning", "Grenade_alert", "Teammates"
};

//vehicle
bool vehicle[21] = {
        AquaRail, BRDM, Boat, Buggy, Bus,
        Coupe, Dacia, Glider, LadaNiva, Mirado,
        Motorbike, Pickup, Rony, Scooter, Snowbike,
        Snowmobile, Tuk, Uaz, Utv, MonsterTruck, ATV
};
const char *vehicleequals[21] = {
        "AquaRail","BRDM","PG117","Buggy","MiniBus","Coupe","Dacia","Motorglider",
        "LadaNiva","Mirado","Motorcycle","PickUp","Rony","Scooter",
        "Snowbike","Snowmobile","Tuk","UAZ", "UTV", "Bigfoot", "ATV1"
};
const char *vehiclereturn[21] = {
        "AquaRail", "BRDM", "Boat", "Buggy", "Bus",
        "Coupe", "Dacia", "Glider", "LadaNiva", "Mirado",
        "Motorbike", "Pickup", "Rony", "Scooter", "Snowbike",
        "Snowmobile", "Tuk", "Uaz", "Utv", "MonsterTruck", "Quad"
};
Color vehicleColor[18];

//ommo
bool ammo[6] = {
        ammo300, ammo45, ammo12G,
        ammo556, ammo762, ammo9mm,
};

const char *ammoequal[6] = {
        "Ammo_300Magnum","Ammo_45AC","Ammo_12Guage",
        "Ammo_556mm","Ammo_762mm","Ammo_9mm",
};
const char *ammoreturn[6] = {
        ".300", "4.5", "12G",
        "5.56", "7.62", "9mm",
};
int ammoId[6] = {
        306001,305001,304001,303001,302001,301001
};
Color ammoColor[6];

//weapon
bool weapon[47] = {
        x2, x3, x4, x6, x8, k98,
        AKM, AUG, AWM, Crossbow, DP12, DP28,
        Deagle, Dot, Flare, G36, Grenade, Groza,
        Holo, M1014, M16, M24, M249, M4,
        M762, MK14, MK47, MP5K, Mini14, Molotov, PP19,
        Pan, QBU, QBZ, S12K, S1897, S686,
        SCAR, SKS, SLR, Stun, Tommy, UMP,
        Uzi, VSS, Vector, Win94,
};
const char *weaponequals[47] = {
        "MZJ_2X","MZJ_3X","MZJ_4X","MZJ_6X","MZJ_8X","Kar98k","AKM","AUG",
        "AWM","CrossBow","DP12","DP28","DesertEagle","MZJ_HD","Flare","G36",
        "Grenade_Shoulei","Groza","MZJ_QX","M1014","M16A4","M24","M249","M416",
        "M762","Mk14","Mk47","MP5K","Mini14","Grenade_Burn","PP19","Pan","QBU","QBZ",
        "S12K","S1897","S686","SCAR","SKS","SLR","Grenade_Stun","TommyGun",
        "UMP9","MachineGun_Uzi","VSS","Vector","Win94",
};
const char *weaponreturn[47] = {
        "2x", "3x", "4x", "6x", "8x", "98k",
        "AKM", "AUG", "AWM", "Crossbow", "DP12", "DP28",
        "Deagle", "Dot", "Flare", "G36", "Grenade", "Groza",
        "Holo", "M1014", "M16", "M24", "M249", "M4",
        "M762", "MK14", "MK47", "MP5K", "Mini14", "Molotov", "PP19",
        "Pan", "QBU", "QBZ", "S12K", "S1897", "S686",
        "SCAR", "SKS", "SLR", "Stun", "Tommy", "UMP",
        "Uzi", "VSS", "Vector", "Win94",
};
int weaponId[47] = {
        203003,203014,203004,203015,203005,103001,
        101001,101006,103003,107001,000000,//null
        105002,106010,203001,106007,101010,602004,101005,
        203002,000000,//null
        101002,000000,//null
        105001,101004,101008,103002,000000,//null
        102007,103006,602003,106002,108004,
        103010,101007,104003,104002,104001,101003,
        103004,103009,602001,102004,102002,
        102001,103005,102003,103008
};
Color weaponColor[47];

//armor
bool armor[4] = {
        Armor2, Armor3,
        Helmet2, Helmet3,
};
const char *armorequals[4] = {
        "Armor_Lv2","Armor_Lv3",
        "Helmet_Lv2","Helmet_Lv3",
};
const char *armorreturn[4] = {
        "Armor2", "Armor3",
        "Helmet2", "Helmet3",
};
int armorId[4]{
        503002,503003,502002,502003
};
Color armorColor[4];

//health
bool healthing[5] = {
        Bandage, Drink, FirstAid,
        Injection, Pills,
};
const char *healtequals[5] = {
        "Bandage","Drink",
        "Firstaid","Injection","Pills",
};
const char *healtreturn[5] = {
        "Bandage", "Drink", "FirstAid",
        "Injection", "Pills",
};
int healthId[5] = {
        601004,601001,601005,601002,601003
};
Color healtColor[5];

//misc
bool misc[26] = {
        Aircraft, Airdrop, Angled, Backpack2, Backpack3,
        CompensatorAR, CompensatorSMG, CompensatorSNP, EQMAR,
        EQMSMG, EQMSNP, FlashHiderAR, FlashHiderSMG,
        FlashHiderSNP, Half, Light, Loot, StockARSMG,
        StockSNP, SuppressorAR, SuppressorSMG, SuppressorSNP,
        Thumb, Vertical, ShopToken, GasCan
};
const char *miscequals[26] = {
        "AirDropPlane","AirDropBox","Angled","Bag_Lv2","Bag_Lv3","QK_Large_C",
        "Mid_Compensator","QK_Sniper","Large_EQ_","Mid_EQ_","Sniper_EQ_",
        "Large_FlashHider","Mid_FlashHider","Sniper_FlashHider","HalfGrip",
        "LightGrip","PickUpListWrapperActor","QT_A_"/*"QT_UZI"*/,"ZDD_Sniper",
        "Large_Suppressor","Mid_Suppressor","Sniper_Suppressor","ThumbGrip",
        "Vertical", "GoldenTokenWrapper_C", "GasCan",
};
const char *miscreturn[26] = {
        "Aircraft", "Airdrop", "Angled", "Backpack2", "Backpack3",
        "CompensatorAR", "CompensatorSMG", "CompensatorSNP", "EQMAR",
        "EQMSMG", "EQMSNP", "FlashHiderAR", "FlashHiderSMG",
        "FlashHiderSNP", "Half", "Light", "Loot", "StockARSMG",
        "StockSNP", "SuppressorAR", "SuppressorSMG", "SuppressorSNP",
        "Thumb", "Vertical", "ShopToken", "GasCan",
};
int miscId[24] = {
        00000,00000,202001,501005/*501002*/,501006/*501003*/,
        201009,201002,201003,204013,204006,204009,201010,201004,201005,
        202005/*205003*/,202004,00000,205002/*SMG 205001*/,204014,201011,201006,
        201007,202006,202002
};
Color miscColor[24];

const char *Enemyweapon[45] = {
        "AUG","M762","SCAR-L","M416","M16A-4",
        "Mk47 Mutant","G36C","QBZ","AKM","Groza","Bizon",
        "TommyGun","MP5K","UMP","Vector","Uzi","DP28",
        "M249","AWM","QBU","SLR","SKS","Mini14","M24",
        "Kar98k","VSS","Win94","Mk14","S12K","DBS","S686",
        "S1897","Sickle","Machete","Crowbar",
        "CrossBow","Pan","SawedOff","R1895","Vz61","P92","P18C",
        "R45","P1911","DesertEagle",
};

int EnemyweaponId[45] = {
        101006,101008,101003,101004,
        101002,101009,101010,101007,
        101001,101005,102005,102004,
        102007,102002,102003,102001,
        105002,105001,103003,103010,
        103009,103004,103006,103002,
        103001,103005,103008,103007,
        104003,104004,104001,104002,
        108003,108001,108002,107001,
        108004,106006,106003,106008,
        106001,106004,106005,106002,
        106010,
};

#endif
