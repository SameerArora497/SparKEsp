#ifndef HACKS_H
#define HACKS_H

#include "main.h"
#include "Log.h"

bool isValidPlayer(PlayerData data){
	return (data.Body != Vector2::Zero() && data.Head != Vector2::Zero());
}
bool isValidVehicle(VehicleData data){
    return (data.Location != Vector2::Zero());
}
bool isValidItem(ItemData data){
    return (data.Location != Vector2::Zero());
}
bool isValidGrenade(GrenadeData data){
    return (data.Location != Vector2::Zero());
}
bool isValidAR(ARData data){
    return (data.Location != Vector2::Zero());
}
bool isValidSG(SGData data){
    return (data.Location != Vector2::Zero());
}
bool isValidSMG(SMGData data){
    return (data.Location != Vector2::Zero());
}
bool isValidSNP(SNPData data){
    return (data.Location != Vector2::Zero());
}
bool isValidMISC(MISCData data){
    return (data.Location != Vector2::Zero());
}
bool isValidPIS(PISData data){
    return (data.Location != Vector2::Zero());
}
bool isValidGR(GRData data){
    return (data.Location != Vector2::Zero());
}
bool isValidWEP(WEPData data){
    return (data.Location != Vector2::Zero());
}
bool isValidAMMO(AMMOData data){
    return (data.Location != Vector2::Zero());
}
bool isValidQK(QKData data){
    return (data.Location != Vector2::Zero());
}
bool isValidQT(QTData data){
    return (data.Location != Vector2::Zero());
}
bool isValidDJ(DJData data){
    return (data.Location != Vector2::Zero());
}
bool isValidZDD(ZDDData data){
    return (data.Location != Vector2::Zero());
}
bool isValidMZJ(MZJData data){
    return (data.Location != Vector2::Zero());
}
bool isValidWB(WBData data){
    return (data.Location != Vector2::Zero());
}
bool isValidCON(CONData data){
    return (data.Location != Vector2::Zero());
}
bool isValidARM(ARMData data){
    return (data.Location != Vector2::Zero());
}

int isOutsideSafezone(Vector2 pos, Vector2 screen) {
    Vector2 mSafezoneTopLeft(screen.x * 0.04f, screen.y * 0.04f);
    Vector2 mSafezoneBottomRight(screen.x * 0.96f, screen.y * 0.96f);

    int result = 0;
    if (pos.y < mSafezoneTopLeft.y) {
        result |= 1;
    }
    if (pos.x > mSafezoneBottomRight.x) {
        result |= 2;
    }
    if (pos.y > mSafezoneBottomRight.y) {
        result |= 4;
    }
    if (pos.x < mSafezoneTopLeft.x) {
        result |= 8;
    }
    return result;
}

Vector2 pushToScreenBorder(Vector2 Pos, Vector2 screen, int borders, int offset) {
    int x = (int)Pos.x;
    int y = (int)Pos.y;
    if ((borders & 1) == 1) {
        y = 0 - offset;
    }
    if ((borders & 2) == 2) {
        x = (int)screen.x + offset;
    }
    if ((borders & 4) == 4) {
        y = (int)screen.y + offset;
    }
    if ((borders & 8) == 8) {
        x = 0 - offset;
    }
    return Vector2(x, y);
}

#define VehicleNames 18
static const char* vehicles[] = {
	"Buggy",
	"Dacia",
	"Tuk",
	"Rony",
	"Mirado",
	"UAZ",
	"Minibus",
	"PickUp",
	"Scooter",
	"Motorbike",
	"Snowbike",
	"Motorbike",
	"PG117",
	"Aqua Rail",
	"Air Plane",
	"BDRM",
	"Snowbike",
	"Ladaniva"
};

std::string getVName(int code) {
	return vehicles[code-1];
}

#define GrenadeNames 4
static const char* grenada_explosiona[] = {
	"Smoke",
	"Molotov",
	"Stun",
	"Frag"
};


std::string getGName(int code) {
	if ( code == 99 ) {
		return "Gr.Ukn";
	} else {
		return grenada_explosiona[code-1];
	}
}

#define ARNames 10
static const char* assaults[] = {
	"M762",
	"SCAR",
	"M416",
	"M16A",
	"Mk47",
	"G36",
	"QBZ",
	"AKM",
	"Groza",
	"AUG",
};

std::string getARName(int code) {
	return assaults[code-1];
}

#define SGNames 5
static const char* shotguns[] = {
	"S12K",
	"S686",
	"S1897",
	"SawedOff",
	"DBS",
};

std::string getSGName(int code) {
	return shotguns[code-1];
}

#define SMGNames 6
static const char* smgs[] = {
	"Bizon",
	"TommyGun",
	"MP5",
	"UMP9",
	"Vector",
	"Uzi",
};

std::string getSMGName(int code) {
	return smgs[code-1];
}

#define SNPNames 9
static const char* snipers[] = {
	"AWM",
	"QBU",
	"SLR",
	"SKS",
	"Mini14",
	"M24",
	"Kar98K",
	"VSS",
	"Win94",
};

std::string getSNPName(int code) {
	return snipers[code-1];
}

#define MISCNames 3
static const char* miscs[] = {
	"DP28",
	"M249",
	"XBow",
};

std::string getMISCName(int code) {
	return miscs[code-1];
}

#define PISNames 7
static const char* pistols[] = {
	"R1895",
	"Scorpion",
	"P92",
	"P18C",
	"R45",
	"P1911",
	"Deagle",
};

std::string getPISName(int code) {
	return pistols[code-1];
}

#define GRNames 3
static const char* grenades[] = {
	"Frag.Gr",
	"Smoke.Gr",
	"Molotov",
};

std::string getGRName(int code) {
	return grenades[code-1];
}

#define WEPNames 5
static const char* bpwep[] = {
	"Mk14", //Warning -> Moved to Sniper
	"Sickle",
	"Machete",
	"Crowbar",
	"Pan",
};

std::string getWEPName(int code) {
	return bpwep[code-1];
}

#define AMMONames 8
static const char* ammos[] = {
	"7.62",
	"45ACP",
	"5.56",
	"9mm",
	"300Mag",
	"12G",
	"Bolt",
	"Flare",
};

std::string getAMMOName(int code) {
	return ammos[code-1];
}

#define QKNames 11
static const char* accqk[] = {
	"SMG.Flash",
	"SMG.Supp",
	"SMG.Comp",
	"AR.Supp",
	"AR.Flash",
	"AR.Comp",
	"SG.Choke",
	"SG.Duck",
	"Snp.Flash",
	"Snp.Comp",
	"Snp.Supp",
};

std::string getQKName(int code) {
	return accqk[code-1];
}

#define QTNames 3
static const char* accqt[] = {
	"TacStock",
	"Cheekpad",
	"Stock",
};

std::string getQTName(int code) {
	return accqt[code-1];
}

#define DJNames 9
static const char* accdj[] = {
	"Snp.ExQd",
	"SMG.Ex",
	"SMG.Qd",
	"Snp.Ex",
	"Snp.Qd",
	"AR.Qd",
	"AR.ExQd",
	"AR.Ex",
	"SMG.ExQd",
};

std::string getDJName(int code) {
	return accdj[code-1];
}

#define ZDDNames 2
static const char* acczdd[] = {
	"XBowPad",
	"Bul.Loops",
};

std::string getZDDName(int code) {
	return acczdd[code-1];
}

#define MZJNames 8
static const char* accmzj[] = {
	"8x.Scope",
	"2x.Scope",
	"RedDot",
	"3x.Scope",
	"Holo",
	"6x.Scope",
	"4x.Scope",
	"Canted",
};

std::string getMZJName(int code) {
	return accmzj[code-1];
}

#define WBNames 6
static const char* accwb[] = {
	"Thmb.Grip",
	"Lsr.Sight",
	"Angl.Grip",
	"Lght.Grip",
	"Half.Grip",
	"Vert.Grip",
};

std::string getWBName(int code) {
	return accwb[code-1];
}

#define CONNames 6
static const char* consumables[] = {
	"Pills",
	"Syringe",
	"Drinks",
	"FirstAid",
	"Bandage",
	"MedKit",
};

std::string getCONName(int code) {
	return consumables[code-1];
}

#define ARMNames 10
static const char* armors[] = {
	"Lv3.Bag",
	"Lv2.Bag",
	"Lv1.Bag",
	"Lv3.Armor",
	"Lv2.Armor",
	"Lv1.Armor",
	"Lv3.Helm",
	"Lv2.Helm",
	"Lv1.Helm",
	"Ghillie",
};

std::string getARMName(int code) {
	return armors[code-1];
}

void DrawNameBox(ESP esp, Vector2 end, float health, float distance, wchar_t playername[30], int TeamID, int intPlayer, bool isTeamMate) {
	float percent = playerTextSize/17;
    float hw = 250*percent;
	char dist[10];
	sprintf(dist,"%d M",(int)distance);
	char ID[10];
	sprintf(ID,"%d",TeamID);

	bool isPlayer;
	if (intPlayer == 0) {
		isPlayer = false;
	} else {
		isPlayer = true;
	}

	if(isPlayerName || isPlayerDist || isPlayerHealth) {
        esp.DrawFilledRect(Color(0,0,0,120), Vector2(end.x - 125*percent, end.y - 60.0f*percent), hw,30*percent);
        esp.DrawFilledRect(Color(255,0,0,120), Vector2(end.x - 120*percent, end.y - 55.0f*percent), 25*percent,20*percent);
        esp.DrawFilledRect(Color(0,0,255,120), Vector2(end.x + 71*percent, end.y - 56.0f*percent), 50*percent,22*percent);



	    esp.DrawText((isTeamMate ? Color::Blue() : (isPlayer ? Color::Yellow() : Color::White())), ID, Vector2(end.x - 108*percent, end.y - 40.0f*percent),playerTextSize-4);
	}
}

void DrawOTHBox(ESP esp, Vector2 end, float distance, const char *txt, float Size, Color bclr, bool drawText, bool drawDistance) {
	float percent = Size/17;
	char dist[10];
	sprintf(dist,"%d M",(int)distance);

	if(drawText && drawDistance) {
		esp.DrawFilledRect(bclr, Vector2(end.x - 75*percent, end.y - 60.0f*percent), 150*percent, 30*percent);
		esp.DrawFilledRect(bclr, Vector2(end.x + 21*percent, end.y - 56.0f*percent), 50*percent, 22*percent);
		esp.DrawText(Color::White(), txt, Vector2(end.x - 28*percent, end.y - 40.0f*percent), Size);
		esp.DrawText(Color::White(), dist, Vector2(end.x + 46*percent, end.y - 40.0f*percent),Size-4);
	}
	else if(drawText) {
		esp.DrawFilledRect(bclr, Vector2(end.x - 50*percent, end.y - 60.0f*percent), 100*percent, 30*percent);
		esp.DrawText(Color::White(), txt, Vector2(end.x, end.y - 40.0f*percent), Size);
	}
	else if(drawDistance) {
		esp.DrawFilledRect(bclr, Vector2(end.x - 34*percent, end.y - 60.0f*percent), 68*percent, 30*percent);
		esp.DrawText(Color::White(), dist, Vector2(end.x, end.y - 40.0f*percent),Size);
	}
}

int e_countTotal = 0;

void DrawESP(ESP esp, int screenWidth, int screenHeight) {

	int botCount = 0;
	float percent = playerTextSize/17;
	float mScale = screenHeight / (float) 1080;
	Vector2 screen(screenWidth, screenHeight);
    Vector2 center(screenWidth/2, screenHeight/2);

	if(isDrawCrosshair){
		esp.DrawCrosshair(Color(0, 0, 0, 255), center, 42);
	}

	esp.DrawText(Color(255, 160, 0), "SparksEsp v1.0 FPS 59", Vector2(200, 60), 22);

	Response response = getData(screenWidth, screenHeight);

	e_countTotal = 0;

	if(response.Success){

		int count = response.PlayerCount;

		/* if(response.MyIdentified != 1) {
			esp.DrawText(Color::Red(), "Local Player Not Identified", identity, 12);
		} */

		if(count > 0) {
			int t_ally = 0;
			for(int i=0; i < count; i++){
				PlayerData player = response.Players[i];
				if(!isValidPlayer(player))
					continue;

				bool isTeamMate = player.TeamID == response.MyTeamID;

				if ( isTeamMate ) {
					t_ally++;
				}

				if(isTeamMate && !isTeamMateShow)
					continue;

				Vector2 location = player.Body;

				std::string dist = to_string((int) player.Distance);
				dist += "M";

				int borders = isOutsideSafezone(location, screen);

				if(isPlayer360 && borders != 0){
					Vector2 hintDotRenderPos = pushToScreenBorder(location, screen, borders, (int)((mScale * 100) / 3)*percent);
					Vector2 hintTextRenderPos = pushToScreenBorder(location, screen, borders, -(int)((mScale * 36))*percent);
					if ( player.Health > 0.0f) {
						if ( player.BotST == 0 ) {
							esp.DrawFilledCircle((isTeamMate ? Color(0, 85, 255, 128) : Color(156, 156, 156, 128)), hintDotRenderPos, (mScale * 100)*percent);
							esp.DrawText(Color::White(), dist.c_str(), hintTextRenderPos, playerTextSize);
						} else {
							if ( player.Distance >= 200.0f ) {
								esp.DrawFilledCircle((isTeamMate ? Color(0, 85, 255, 128) : Color(186, 171, 0, 128)), hintDotRenderPos, (mScale * 100)*percent);
							}
							else if ( player.Distance >= 100.0f && player.Distance < 200.0f ) {
								esp.DrawFilledCircle((isTeamMate ? Color(0, 85, 255, 128) : Color(255, 138, 28, 128)), hintDotRenderPos, (mScale * 100)*percent);
							}
							else if ( player.Distance <= 100.0f ) {
								esp.DrawFilledCircle((isTeamMate ? Color(0, 85, 255, 128) : Color(255, 0, 0, 128)), hintDotRenderPos, (mScale * 100)*percent);
							}
							esp.DrawText(Color::Yellow(), dist.c_str(), hintTextRenderPos, playerTextSize);
						}
					} else {
						esp.DrawFilledCircle((isTeamMate ? Color(0, 85, 255, 128) : Color(156, 156, 156, 128)), hintDotRenderPos, (mScale * 100)*percent);
						esp.DrawText(Color::Black(), dist.c_str(), hintTextRenderPos, playerTextSize);
					}
				} else {
					float boxHeight = fabsf(player.Root.y - player.Head.y);
					float boxWidth = boxHeight * 0.56;

					Rect PlayerRect(player.Head.x - (boxWidth / 2), player.Head.y, boxWidth, boxHeight);

					Color line_clr = Color(255, 160, 0);
					if (isTeamMate) {
						line_clr = Color(0, 85, 255, 255);
					} else if (player.BotST == 0) {
						line_clr = Color(255, 255, 255);
					}

					if(isPlayerLine) {
						esp.DrawLine(line_clr, lineThickness, Vector2((screenWidth / 2), 135), player.Neck);
					}

					if(isPlayerBox) {
						esp.DrawBox(line_clr, boxThickness, PlayerRect);
					}

					if(isPlayerBone) {
						if ( player.BotST == 0 ) {
							esp.DrawLine(Color::White(), boneThickness, player.Neck, player.Chest);
							esp.DrawLine(Color::White(), boneThickness, player.Chest, player.Pelvis);
							esp.DrawLine(Color::White(), boneThickness, player.Chest, player.LShoulder);
							esp.DrawLine(Color::White(), boneThickness, player.Chest, player.RShoulder);
							esp.DrawLine(Color::White(), boneThickness, player.LShoulder, player.LElbow);
							esp.DrawLine(Color::White(), boneThickness, player.RShoulder, player.RElbow);
							esp.DrawLine(Color::White(), boneThickness, player.LElbow, player.LWrist);
							esp.DrawLine(Color::White(), boneThickness, player.RElbow, player.RWrist);
							esp.DrawLine(Color::White(), boneThickness, player.Pelvis, player.LThigh);
							esp.DrawLine(Color::White(), boneThickness, player.Pelvis, player.RThigh);
							esp.DrawLine(Color::White(), boneThickness, player.LThigh, player.LKnee);
							esp.DrawLine(Color::White(), boneThickness, player.RThigh, player.RKnee);
							esp.DrawLine(Color::White(), boneThickness, player.LKnee, player.LAnkle);
							esp.DrawLine(Color::White(), boneThickness, player.RKnee, player.RAnkle);
						} else {
							esp.DrawLine(line_clr, boneThickness, player.Neck, player.Chest);
							esp.DrawLine(line_clr, boneThickness, player.Chest, player.Pelvis);
							esp.DrawLine(line_clr, boneThickness, player.Chest, player.LShoulder);
							esp.DrawLine(line_clr, boneThickness, player.Chest, player.RShoulder);
							esp.DrawLine(line_clr, boneThickness, player.LShoulder, player.LElbow);
							esp.DrawLine(line_clr, boneThickness, player.RShoulder, player.RElbow);
							esp.DrawLine(line_clr, boneThickness, player.LElbow, player.LWrist);
							esp.DrawLine(line_clr, boneThickness, player.RElbow, player.RWrist);
							esp.DrawLine(line_clr, boneThickness, player.Pelvis, player.LThigh);
							esp.DrawLine(line_clr, boneThickness, player.Pelvis, player.RThigh);
							esp.DrawLine(line_clr, boneThickness, player.LThigh, player.LKnee);
							esp.DrawLine(line_clr, boneThickness, player.RThigh, player.RKnee);
							esp.DrawLine(line_clr, boneThickness, player.LKnee, player.LAnkle);
							esp.DrawLine(line_clr, boneThickness, player.RKnee, player.RAnkle);
						}
					}

                    float top = player.Neck.y;

					if(isPlayerHealth) {
						Color clrHealth;
						float sdk = -12;
						float healthLength = screenWidth / 28;

						if (player.Health < 25)
							clrHealth = Color(200, 0, 0, 120);
						else if (player.Health < 50)
							clrHealth = Color(200, 165, 0, 120);
						else if (player.Health < 75)
							clrHealth = Color(0, 128, 0, 120);
						else
							clrHealth = Color(0, 255, 0, 120);

						esp.DrawFilledCurveRect(clrHealth, 7,
												Vector2(player.Neck.x - healthLength,sdk + top - screenHeight / 26),
												Vector2(player.Neck.x - healthLength + (2 * healthLength) *
																		player.Health / 100,sdk + top - screenHeight / 110));
						esp.DrawCurveRect(Color(0, 0, 0), 7, Vector2(player.Neck.x - healthLength, sdk + top - screenHeight / 26),
										  Vector2(player.Neck.x + healthLength, sdk + top - screenHeight / 110));

					}

					if(isPlayerName) {
						std::wstring pIdentify = player.PlayerName;
						esp.DrawPlayerText(Color::White(), pIdentify.c_str(), Vector2(player.Neck.x, top - screenHeight / 35),
										   screenHeight / 80);
					}

					if(isPlayerDist) {
                        esp.DrawText(Color(255, 255, 0), dist.c_str(), Vector2(player.Neck.x, top - 5), screenHeight / 80);
					}

				}
			}
			e_countTotal = count - t_ally;
		}

		count = response.VehicleCount;
		if(count > 0){
			if(isVehicleName || isVehicleDist) {
				for(int i=0; i < count; i++){
					//LOGE("Draw Debug - Vehicle C: %d",i);
					VehicleData vehicle = response.Vehicles[i];
					if(!isValidVehicle(vehicle)){ continue;}
					//if( vehicle.Distance < 0.0f ) { continue; }
					Vector2 location = vehicle.Location;

					int recast_vn = vehicle.Name;
					std::string vname = getVName(recast_vn);
					if(isVehicleName || isVehicleDist) {
						DrawOTHBox(esp, Vector2(location.x, location.y+60), vehicle.Distance, vname.c_str(), vehicleTextSize, Color(25, 66, 133, 120), isVehicleName, isVehicleDist);
					}
					/*
                    std::string dist;
                    dist += "[ ";
                    dist += std::to_string((int) vehicle.Distance);
                    dist += "M";
                    dist += " ]";

                    if(isVehicleName) {
                        //LOGE("Draw Debug - VName");
                        esp.DrawText(Color::Teal(), vname.c_str(), Vector2(
                                location.x, location.y - (30 * mScale)), vehicleTextSize);
                    }
                    if(isVehicleDist) {
                        //LOGE("Draw Debug - VDist");
                        esp.DrawText(Color::Teal(), dist.c_str(), Vector2(
                                location.x, location.y - (10 * mScale)), vehicleTextSize);
                    }
                    */
				}
			}
		}

		count = response.GrenadeCount; //-- Grenade Warning
		if(count > 0){
			if ( isGrenadeName || isGrenadeDist ) {
				for(int i=0; i < count; i++){
					GrenadeData grenade = response.Grenade[i];
					if(!isValidGrenade(grenade)){ continue;}
					Vector2 location = grenade.Location;

					int recast_gn = grenade.Name;
					std::string gname = getGName(recast_gn);

                    std::string dist;
                    dist += "[ ";
                    dist += std::to_string((int) grenade.Distance);
                    dist += "M";
                    dist += " ]";

                    if(isGrenadeName) {
                        esp.DrawText(Color::Orange(), gname.c_str(), Vector2(
                                location.x, location.y - (30 * mScale)), grenadeTextSize);
                    }
                    if(isGrenadeDist) {
                        esp.DrawText(Color::Orange(), dist.c_str(), Vector2(
                                location.x, location.y - (10 * mScale)), grenadeTextSize);
                    }
				}
			}
		}

		count = response.ItemsCount;
		if(count > 0){
			if ( isLootBoxName || isLootBoxDist ) {
				for(int i=0; i < count; i++){
					//LOGE("Draw Debug - ItemsCounts: %d",i);
					ItemData item = response.Items[i];
					if(!isValidItem(item)){ continue;}
					//if( item.Distance < 0.0f ) { continue; }
					Vector2 location = item.Location;
					if (isOutsideSafezone(location, screen)) { continue; }

					if(isLootBoxName || isLootBoxDist) {
						std::string boxName;
						boxName = "LootBox";
						DrawOTHBox(esp, Vector2(location.x, location.y+60), item.Distance, boxName.c_str(), lootTextSize, Color(104, 0, 168, 120), isLootBoxName, isLootBoxDist);
					}
					/*
                    std::string dist;
                    dist += "[ ";
                    dist += std::to_string((int) item.Distance);
                    dist += "M";
                    dist += " ]";

                    if(isLootBoxName) {
                        int recast_in = item.Name;
                        std::string boxName;
                        if ( recast_in == 1 ) {
                            boxName = "LootBox";
                            esp.DrawText(Color::Pink(), boxName.c_str(), Vector2(
                                location.x, location.y - (30 * mScale)), lootTextSize);
                        }
                        else if ( recast_in == 2 ) {
                            boxName = "Airdrop";
                            esp.DrawText(Color::Pink(), boxName.c_str(), Vector2(
                                location.x, location.y - (30 * mScale)), lootTextSize);
                        }
                    }
                    if(isLootBoxDist) {
                        //LOGE("Draw Debug - BoxDist");
                        esp.DrawText(Color::Pink(), dist.c_str(), Vector2(
                                location.x, location.y - (10 * mScale)), lootTextSize);
                    }
                    */
				}
			}
		}

		count = response.GRCount;
		if(count > 0) {
			for(int i=0; i < count; i++) {
				GRData GR = response.GR[i];
				if(!isValidGR(GR)){ continue;}
				Vector2 location = GR.Location;
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getGRName(GR.Name);
				std::string loot;

				if ( GR.Name == 1 && isFragGrenade ) DrawOTHBox(esp, Vector2(location.x, location.y+60), GR.Distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( GR.Name == 2 && isSmokeGrenade) DrawOTHBox(esp, Vector2(location.x, location.y+60), GR.Distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( GR.Name == 3 && isMolotov) DrawOTHBox(esp, Vector2(location.x, location.y+60), GR.Distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) GR.Distance);
                loot += "M";
                loot += "]";

                if(isFragGrenade) {
                    if ( GR.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSmokeGrenade) {
                    if ( GR.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isMolotov) {
                    if ( GR.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		int curDis = 0;
		count = response.ARCount;
		if(count > 0) {
			for(int i=0; i < count; i++) {
				ARData AR = response.AR[i];

				if(!isValidAR(AR)){
					continue;
				}

				Vector2 location = AR.Location;
				if (isOutsideSafezone(location, screen)) {
					continue;
				}

				std::string name = getARName(AR.Name);

				std::string loot;
                loot += name;
                loot += " [";
                loot += std::to_string((int) AR.Distance);
                loot += "M";
                loot += "]";

                if(isM762) {
                    if ( AR.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSCAR) {
                    if ( AR.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isM416) {
                    if ( AR.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isM16A) {
                    if ( AR.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isMk47) {
                    if ( AR.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isG36) {
                    if ( AR.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isQBZ) {
                    if ( AR.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isAKM) {
                    if ( AR.Name == 8 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isGroza) {if ( curDis > maxItemDisp ) { continue; }
                    curDis += 1;
                    if ( AR.Name == 9 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isAUG) {
                    if ( AR.Name == 10 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
			}
		}

		count = response.SMGCount;
		if(count > 0) {
			for(int i=0; i < count; i++) {
				SMGData SMG = response.SMG[i];
				if(!isValidSMG(SMG)){ continue;}
				Vector2 location = SMG.Location;
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getSMGName(SMG.Name);
				std::string loot;

                loot += name;
                loot += " [";
                loot += std::to_string((int) SMG.Distance);
                loot += "M";
                loot += "]";

                if(isBizon) {
                    if ( SMG.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isTommyGun) {
                    if ( SMG.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isMP5) {
                    if ( SMG.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isUMP9) {
                    if ( SMG.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isVector) {
                    if ( SMG.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isUzi) {
                    if ( SMG.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
			}
		}

		count = response.ARMCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				ARMData ARM = response.ARM[i]; //--> Change this (2)
				if(!isValidARM(ARM)){ continue;}
				Vector2 location = ARM.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getARMName(ARM.Name); //--> Change this (2)
				std::string loot;

                loot += name;
                loot += " [";
                loot += std::to_string((int) ARM.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isLv3Bag) {
                    if ( ARM.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv2Bag) {
                    if ( ARM.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv1Bag) {
                    if ( ARM.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv3Armor) {
                    if ( ARM.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv2Armor) {
                    if ( ARM.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv1Armor) {
                    if ( ARM.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv3Helm) {
                    if ( ARM.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv2Helm) {
                    if ( ARM.Name == 8 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLv1Helm) {
                    if ( ARM.Name == 9 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isGhillie) {
                    if ( ARM.Name == 10 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
			}
		}

		count = response.SNPCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				SNPData SNP = response.SNP[i]; //--> Change this
				if(!isValidSNP(SNP)){ continue;}
				Vector2 location = SNP.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getSNPName(SNP.Name); //--> Change this
				std::string loot;

				float distance = SNP.Distance;
				int itemName = SNP.Name;
				if ( itemName == 1 && isAWM ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isQBU) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isSLR) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 4 && isSKS) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 5 && isMini14) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 6 && isM24) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 7 && isKar98K) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 8 && isVSS) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 9 && isWin94) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) SNP.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isAWM) {
                    if ( SNP.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isQBU) {
                    if ( SNP.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSLR) {
                    if ( SNP.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSKS) {
                    if ( SNP.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isMini14) {
                    if ( SNP.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isM24) {
                    if ( SNP.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isKar98K) {
                    if ( SNP.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isVSS) {
                    if ( SNP.Name == 8 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isWin94) {
                    if ( SNP.Name == 9 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.MISCCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				MISCData MISC = response.MISC[i]; //--> Change this
				if(!isValidMISC(MISC)){ continue;}
				Vector2 location = MISC.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getMISCName(MISC.Name); //--> Change this
				std::string loot;

				float distance = MISC.Distance;
				int itemName = MISC.Name;
				if ( itemName == 1 && isDP28 ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isM249) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isCrossBow) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) MISC.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isDP28) {
                    if ( MISC.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isM249) {
                    if ( MISC.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isCrossBow) {
                    if ( MISC.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.PISCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				PISData PIS = response.PIS[i]; //--> Change this
				if(!isValidPIS(PIS)){ continue;}
				Vector2 location = PIS.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getPISName(PIS.Name); //--> Change this
				std::string loot;

				float distance = PIS.Distance;
				int itemName = PIS.Name;
				if ( itemName == 1 && isR1895 ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isVz61) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isP92) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 4 && isP18C) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 5 && isR45) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 6 && isP1911) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 7 && isDeagle) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) PIS.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isR1895) {
                    if ( PIS.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isVz61) {
                    if ( PIS.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isP92) {
                    if ( PIS.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isP18C) {
                    if ( PIS.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isR45) {
                    if ( PIS.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isP1911) {
                    if ( PIS.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isDeagle) {
                    if ( PIS.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.SGCount;
		if(count > 0) {
			for(int i=0; i < count; i++) {
				SGData SG = response.SG[i];
				if(!isValidSG(SG)){ continue;}
				Vector2 location = SG.Location;
				if (isOutsideSafezone(location, screen)) { continue; }
				//int recast_sg = SG.Name;
				std::string name = getSGName(SG.Name);
				std::string loot;

				float distance = SG.Distance;
				int itemName = SG.Name;
				if ( itemName == 1 && isS12K ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isS686) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isS1897) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 4 && isSawedOff) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 5 && isDBS) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) SG.Distance);
                loot += "M";
                loot += "]";

                if(isS12K) {
                    if ( SG.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isS686) {
                    if ( SG.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isS1897) {
                    if ( SG.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSawedOff) {
                    if ( SG.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isDBS) {
                    if ( SG.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.WEPCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				WEPData WEP = response.WEP[i]; //--> Change this
				if(!isValidWEP(WEP)){ continue;}
				Vector2 location = WEP.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getWEPName(WEP.Name); //--> Change this
				std::string loot;

				float distance = WEP.Distance;
				int itemName = WEP.Name;
				if ( itemName == 2 && isSickle ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isMachete) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 4 && isCrowbar) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 5 && isPan) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 1 && isMk14) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) WEP.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isSickle) {
                    if ( WEP.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isMachete) {
                    if ( WEP.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isCrowbar) {
                    if ( WEP.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isPan) {
                    if ( WEP.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isMk14) {
                    if ( WEP.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.QKCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				QKData QK = response.QK[i]; //--> Change this
				if(!isValidQK(QK)){ continue;}
				Vector2 location = QK.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getQKName(QK.Name); //--> Change this
				std::string loot;

				float distance = QK.Distance;
				int itemName = QK.Name;
				if ( itemName == 1 && isSMGFlashHider ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isSMGSuppressor) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isSMGCompensator) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 4 && isARSuppressor) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 5 && isARFlashHider) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 6 && isARCompensator) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 7 && isSGChoke) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 8 && isSGDuckbill) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 9 && isSnipFlashHider) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 10 && isSnipCompensator) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 11 && isSnipSuppressor) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) QK.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isSMGFlashHider) {
                    if ( QK.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSMGSuppressor) {
                    if ( QK.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSMGCompensator) {
                    if ( QK.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isARSuppressor) {
                    if ( QK.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isARFlashHider) {
                    if ( QK.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isARCompensator) {
                    if ( QK.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSGChoke) {
                    if ( QK.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSGDuckbill) {
                    if ( QK.Name == 8 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSnipFlashHider) {
                    if ( QK.Name == 9 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSnipCompensator) {
                    if ( QK.Name == 10 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSnipSuppressor) {
                    if ( QK.Name == 11 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.DJCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				DJData DJ = response.DJ[i]; //--> Change this (2)
				if(!isValidDJ(DJ)){ continue;}
				Vector2 location = DJ.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getDJName(DJ.Name); //--> Change this (2)
				std::string loot;

				float distance = DJ.Distance;
				int itemName = DJ.Name;
				if ( itemName == 1 && isSnipExQuickdraw ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isSMGExtended) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isSMGQuickdraw) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 4 && isSnipExtended) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 5 && isSnipQuickdraw) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 6 && isARQuickdraw) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 7 && isARExQuickdraw) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 8 && isARExtended) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 9 && isSMGExQuickdraw) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) DJ.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isSnipExQuickdraw) {
                    if ( DJ.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSMGExtended) {
                    if ( DJ.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSMGQuickdraw) {
                    if ( DJ.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSnipExtended) {
                    if ( DJ.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSnipQuickdraw) {
                    if ( DJ.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isARQuickdraw) {
                    if ( DJ.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isARExQuickdraw) {
                    if ( DJ.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isARExtended) {
                    if ( DJ.Name == 8 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isSMGExQuickdraw) {
                    if ( DJ.Name == 9 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.MZJCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				MZJData MZJ = response.MZJ[i]; //--> Change this (2)
				if(!isValidMZJ(MZJ)){ continue;}
				Vector2 location = MZJ.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getMZJName(MZJ.Name); //--> Change this (2)
				std::string loot;

				float distance = MZJ.Distance;
				int itemName = MZJ.Name;
				if ( itemName == 1 && is8xScope ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && is2xScope) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isRedDot) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 4 && is3xScope) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 5 && isHolo) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 6 && is6xScope) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 7 && is4xScope) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 8 && isCanted) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) MZJ.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(is8xScope) {
                    if ( MZJ.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is2xScope) {
                    if ( MZJ.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isRedDot) {
                    if ( MZJ.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is3xScope) {
                    if ( MZJ.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isHolo) {
                    if ( MZJ.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is6xScope) {
                    if ( MZJ.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is4xScope) {
                    if ( MZJ.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isCanted) {
                    if ( MZJ.Name == 8 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.QTCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				QTData QT = response.QT[i]; //--> Change this
				if(!isValidQT(QT)){ continue;}
				Vector2 location = QT.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getQTName(QT.Name); //--> Change this
				std::string loot;

				float distance = QT.Distance;
				int itemName = QT.Name;
				if ( itemName == 1 && isTacStock ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isCheekpad) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 3 && isStock) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) QT.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isTacStock) {
                    if ( QT.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isCheekpad) {
                    if ( QT.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isStock) {
                    if ( QT.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.ZDDCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				ZDDData ZDD = response.ZDD[i]; //--> Change this (2)
				if(!isValidZDD(ZDD)){ continue;}
				Vector2 location = ZDD.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getZDDName(ZDD.Name); //--> Change this (2)
				std::string loot;

				float distance = ZDD.Distance;
				int itemName = ZDD.Name;
				if ( itemName == 1 && isCrossbowPad ) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);
				if ( itemName == 2 && isBulletLoops) DrawOTHBox(esp, Vector2(location.x, location.y+60), distance, name.c_str(), itemsTextSize, Color(0,117,16,120), true, true);

				/*
                loot += name;
                loot += " [";
                loot += std::to_string((int) ZDD.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isCrossbowPad) {
                    if ( ZDD.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isBulletLoops) {
                    if ( ZDD.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                */
			}
		}

		count = response.WBCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				WBData WB = response.WB[i]; //--> Change this (2)
				if(!isValidWB(WB)){ continue;}
				Vector2 location = WB.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getWBName(WB.Name); //--> Change this (2)
				std::string loot;

                loot += name;
                loot += " [";
                loot += std::to_string((int) WB.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isThumbGrip) {
                    if ( WB.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLaserSight) {
                    if ( WB.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isAngledGrip) {
                    if ( WB.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isLightGrip) {
                    if ( WB.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isHalfGrip) {
                    if ( WB.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isVerticalGrip) {
                    if ( WB.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
			}
		}

		count = response.CONCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				CONData CON = response.CON[i]; //--> Change this (2)
				if(!isValidCON(CON)){ continue;}
				Vector2 location = CON.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getCONName(CON.Name); //--> Change this (2)
				std::string loot;

                loot += name;
                loot += " [";
                loot += std::to_string((int) CON.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(isPills) {
                    if ( CON.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isInjections) {
                    if ( CON.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isDrinks) {
                    if ( CON.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isFirstAid) {
                    if ( CON.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isBandage) {
                    if ( CON.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isMedKit) {
                    if ( CON.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
			}
		}

		count = response.AMMOCount; //--> Change this
		if(count > 0) {
			for(int i=0; i < count; i++) {
				AMMOData AMMO = response.AMMO[i]; //--> Change this
				if(!isValidAMMO(AMMO)){ continue;}
				Vector2 location = AMMO.Location; //--> Change this
				if (isOutsideSafezone(location, screen)) { continue; }
				std::string name = getAMMOName(AMMO.Name); //--> Change this

				std::string loot;
                loot += name;
                loot += " [";
                loot += std::to_string((int) AMMO.Distance); //--> Change this
                loot += "M";
                loot += "]";

                if(is762) {
                    if ( AMMO.Name == 1 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is45ACP) {
                    if ( AMMO.Name == 2 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is556) {
                    if ( AMMO.Name == 3 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is9mm) {
                    if ( AMMO.Name == 4 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is300Mag) {
                    if ( AMMO.Name == 5 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(is12G) {
                    if ( AMMO.Name == 6 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isBolt) {
                    if ( AMMO.Name == 7 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
                if(isFlare) {
                    if ( AMMO.Name == 8 ) esp.DrawText(Color::Green(), loot.c_str(), Vector2(
                            location.x, location.y - (30 * mScale)), itemsTextSize);
                }
			}
		}
	}

	if (isDrawCount) {
		std::string extra;
		Color color1,color2;
		if (e_countTotal <= 0) {
			color1 = Color(50, 205, 50);
			color2 = Color(50, 205, 50, 60);
			extra = "Clear";
		} else {
			color1 = Color(255, 0, 0);
			color2 = Color(255, 0, 0, 60);
			extra = to_string(e_countTotal);
		}
		esp.DrawCurveRect(color1, 10,Vector2(screenWidth / 2 - 85, 65),
						  Vector2(screenWidth / 2 + 85, 135));
		esp.DrawFilledCurveRect(color2, 10,Vector2(screenWidth / 2 - 85, 65),
								Vector2(screenWidth / 2 + 85, 135));
		esp.DrawText(Color(255, 255, 255), extra.c_str(),
					 Vector2(screenWidth / 2, 115), 35);
	}
}

#endif //HACKS_H
