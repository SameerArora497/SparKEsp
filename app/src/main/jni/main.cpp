#include "esp/main.h"
#include "esp/ESP.h"
#include "Socket/SocketServer.h"
#include "esp/Hacks.h"
#include "Helper/MemoryTools.h"
#include "login.h"

SocketServer server;
ESP espOverlay;
int eventFile;

int startClient(){
	//LOGE("Starting....");
	if (!server.Create()) {
		LOGE("SE:1");
		return -1;
	}
	//LOGE("Binding....");
	int sockCheck=1;
	setsockopt(server.listenfd,SOL_SOCKET,SO_REUSEADDR,&sockCheck, sizeof(int));
	if (!server.Bind()) {
		LOGE("SE:2");
		return -1;
	}
	//LOGE("Listening....");
	if (!server.Listen()) {
		LOGE("SE:3");
		return -1;
	}
	//LOGE("Accepting....");
    if (server.Accept()) {
		if(!initServer()) {
			return -1;
		};
        return 0;
    }
	return -1;
}

void stopClient(){
    if(server.isCreated){
        stopServer();
        server.Close();
    }
}

bool initServer(){
    Request request{InitMode, 0, 0, 0, 0, 0, 0};
    int code = server.send((void*) &request, sizeof(request));
    if(code > 0){
        Response response{};
        size_t length = server.receive((void*) &response);
        if(length > 0){
            return response.Success;
        }
    }
    return false;
}

bool stopServer(){
    Request request{StopMode, 0, 0, 0, 0, 0, 0};
    int code = server.send((void*) &request, sizeof(request));
    if(code > 0){
        Response response{};
        size_t length = server.receive((void*) &response);
        if(length > 0){
            return response.Success;
        }
    }
    return false;
}

Response getData(int screenWidth, int screenHeight){
    Request request{ESPMode, screenWidth, screenHeight, 0, 0, 0, 0};
    int code = server.send((void*) &request, sizeof(request));
    if(code > 0){
        Response response{};
        size_t length = server.receive((void*) &response);
        if(length > 0){
            return response;
        }
    }
    Response response{false, 0};
    return response;
}

Response sendConfig(int Type, int Code, int Value){
    Request request{Config, 0, 0, Type, Code, Value, 0};
    int code = server.send((void*) &request, sizeof(request));
    if(code > 0){
        Response response{};
        size_t length = server.receive((void*) &response);
        if(length > 0){
            return response;
        }
    }
    Response response{false, 0};
    return response;
}

Response openEVPath(int eventID) {
	Request request{OpenEvent, 0, 0, 0, 0, 0, eventID};
    int code = server.send((void*) &request, sizeof(request));
    if(code > 0){
        Response response{};
        size_t length = server.receive((void*) &response);
        if(length > 0){
            return response;
        }
    }
    Response response{false, 0};
    return response;
}


std::string Shell(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
	while (fgets(buffer, sizeof buffer, pipe) != NULL) {
		result += buffer;
	}
    pclose(pipe);
    return result;
}

extern "C"
JNIEXPORT jint JNICALL
Java_a_f_Init(JNIEnv *env, jclass type) {
    return startClient();
}

extern "C"
JNIEXPORT void JNICALL
Java_a_f_DrawOn(JNIEnv *env, jclass type, jobject espView, jobject canvas) {
    espOverlay = ESP(env, espView, canvas);
    if (espOverlay.isValid()){
        DrawESP(espOverlay, espOverlay.getWidth(), espOverlay.getHeight());
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_a_f_SwitchValue(JNIEnv *env, jclass clazz, jstring key,jboolean jboolean1) {
	if(bValid){
		std::string userKey = env->GetStringUTFChars(key, nullptr);
		if(userKey == "pubg_player_name") {
			isPlayerName = jboolean1;
		} else if (userKey == "pubg_player_health") {
			isPlayerHealth = jboolean1;
		} else if (userKey == "pubg_player_distance") {
			isPlayerDist = jboolean1;
		} else if (userKey == "pubg_esp_teammate") {
			isTeamMateShow = jboolean1;
		} else if (userKey == "pubg_esp_line") {
			isPlayerLine = jboolean1;
		} else if (userKey == "pubg_esp_box") {
			isPlayerBox = jboolean1;
		} else if (userKey == "pubg_esp_alert360") {
			isPlayer360 = jboolean1;
		} else if (userKey == "pubg_player_skeleton") {
            isPlayerBone = jboolean1;
		} else if (userKey == "pubg_esp_nearenemy") {
            isDrawCount = jboolean1;
        }  else if (userKey == "pubg_esp_throw_alert") {
            isGrenadeName = jboolean1;
        } else if (userKey == "pubg_aim_fov_show") {
			isDrawAimRadius = jboolean1;
		} else if (userKey == "pubg_esp_crosshair") {
			isDrawCrosshair = jboolean1;
		} else if (userKey == "pubg_other_ignore_bot") {
			IgnoreBot = jboolean1;
		}
	}
}

extern "C"
JNIEXPORT void JNICALL
Java_a_f_AimbotValue(JNIEnv *env, jclass clazz, jstring key,jint code) {
	if(bValid) {
		std::string userKey = env->GetStringUTFChars(key, nullptr);
		if (userKey == "pubg_aim_status") {
			isAimbot = code == 2;
			if (isAimbot) {
				sendConfig(1,0,1);
                sendConfig(16,0,touchXS);
                sendConfig(17,0,touchYS);
                sendConfig(18,0,touchSRadius);
			} else {
				sendConfig(1,0,0);
			}
			isTrueAimbot = isAimbot;
			if (isTrueAimbot) { sendConfig(2,0,1); } else { sendConfig(2,0,0); }
		} else if (userKey == "pubg_aim_mode") {
			isWhenFiring = code == 0;
			isWhenADS = code == 1;
			isAlwaysONAimbot = code == 2;
			if (isWhenFiring) { sendConfig(22,0,1); } else { sendConfig(22,0,0); }
			if (isWhenADS) { sendConfig(23,0,1); } else { sendConfig(23,0,0); }
			if (isAlwaysONAimbot) { sendConfig(24,0,1); } else { sendConfig(24,0,0); }
		} else if (userKey == "pubg_aim_target") {
			code++;
			if (code == 3){
				code = 2;
			} else if (code == 4) {
				code = 3;
			}
			sendConfig(19,0,code);
		} else if (userKey == "pubg_aim_fov") {
			AimbotRadius = (float)((touchXMax/200)*code);
			sendConfig(25,0,(int)AimbotRadius);
		} else if (userKey == "pubg_aim_swipe_speed") {
			aimLatency = code;
			sendConfig(6,0,aimLatency);
		}
	}
}

extern "C"
JNIEXPORT void JNICALL
Java_a_f_ItemValue(JNIEnv *env, jclass clazz, jstring key, jboolean flag) {
	if(bValid) {
		std::string userKey = env->GetStringUTFChars(key, nullptr);
		if (userKey == "AKM") {
			isAKM = flag;
		} else if(userKey == "AKM-XT") {
			isAKM = flag;
		} else if(userKey == "AUG-A3") {
			isAUG = flag;
		} else if(userKey == "QBZ") {
			isQBZ = flag;
		} else if(userKey == "M416") {
			isM416 = flag;
		} else if(userKey == "SCAR-L") {
			isSCAR = flag;
		} else if(userKey == "SCAR-L-XT") {
			isSCAR = flag;
		} else if(userKey == "M249") {
			isM249 = flag;
		} else if(userKey == "M16A4") {
			isAUG = flag;
		} else if(userKey == "DP28") {
			isDP28 = flag;
		} else if(userKey == "G36C") {
			isG36 = flag;
		} else if(userKey == "Mk47") {
			isMk47 = flag;
		} else if(userKey == "Groza") {
			isGroza = flag;
		} else if(userKey == "M762") {
			isM762 = flag;
		} else if(userKey == "M762-XT") {
			isM762 = flag;
		} else if(userKey == "FAMAS") {
			// isFamas = flag;
		} else if(userKey == "AN94") {
			//isAN94 = flag;
		} else if(userKey == "VAL") {
			//isVal = flag;
		} else if (userKey == "UMP9") {
			isUMP9 = flag;
		} else if(userKey == "Thmopson SMG") {
			//= flag;
		} else if(userKey == "Vector") {
			isVector = flag;
		} else if(userKey == "Vector-XT") {
			isVector = flag;
		} else if(userKey == "P90") {
			//isP90 = flag;
		} else if(userKey == "MP5K") {
			isMP5 = flag;
		} else if(userKey == "PP19-Bizon") {
			isBizon = flag;
		} else if(userKey == "Uzi") {
			isUzi = flag;
		}  else if(userKey == "Uzi-XT") {
			isUzi = flag;
		} else if(userKey == "MG3") {
			//isMG = flag;
		}

		if (userKey == "AWM") {
			isAWM = flag;
		} else if(userKey == "AMR") {
			//isAM = flag;
		} else if(userKey == "Kar98k") {
			isKar98K = flag;
		} else if(userKey == "SKS") {
			isSKS = flag;
		} else if(userKey == "SLR") {
			isSLR = flag;
		} else if(userKey == "QBU") {
			isQBU = flag;
		} else if(userKey == "Mini14") {
			isMini14 = flag;
		} else if(userKey == "VSS") {
			isVSS = flag;
		} else if(userKey == "Win94") {
			isWin94 = flag;
		} else if(userKey == "M24") {
			isM24 = flag;
		} else if(userKey == "M24-XT") {
			isM24 = flag;
		} else if(userKey == "Mk12") {
			isMk14 = flag;
		} else if(userKey == "Mosin") {
		//	isMOs = flag;
		} else if(userKey == "Mk14") {
			isMk14 = flag;
		} else if (userKey == "S12K") {
			isS12K = flag;
		} else if(userKey == "S1897") {
			isS1897 = flag;
		} else if(userKey == "S686") {
			isS686 = flag;
		} else if(userKey == "DBS") {
			isDBS = flag;
		} else if(userKey == "M1014") {
			//isM10 = flag;
		} else if(userKey == "Sawed Off") {
		   // isSwa = flag;
		} else if (userKey == "P92") {
			isP92 = flag;
		} else if(userKey == "R45") {
			isR45 = flag;
		} else if(userKey == "P18O") {
			//isP180 = flag;
		} else if(userKey == "P1911") {
			isP1911 = flag;
		} else if(userKey == "R1895") {
			isR1895 = flag;
		} else if(userKey == "Skorpion") {
			//isSk = flag;
		} else if(userKey == "Skorpion-XT") {
			//isDBS = flag;
		} else if(userKey == "FlareGun") {
			isFlare = flag;
		} else if(userKey == "DesertEagle") {
			isDeagle = flag;
		}

		else if (userKey == "7.62mm") { //Ammos
			is762 = flag;
		} else if(userKey == "5.56mm") {
			is556 = flag;
		}

		else if(userKey == "3x") { //Scopes
			is3xScope = flag;
		} else if(userKey == "6x") {
			is6xScope = flag;
		}

		else if(userKey == "Armor(L3)") { //Armors
			isS686 = flag;
		}

		else if(userKey == "Helmet(L3)") { //Helmet
			isLv3Helm = flag;
		}

		else if(userKey == "Bag(L3)") { //Bag
			isLv3Bag = flag;
		}
	}
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rtouch_Floater_Switch1(JNIEnv *env, jclass type, jint num, jboolean flag) {
    switch (num){
		//AR
		case 3:
			isM16A = flag;
			break;
		case 4:
			isMk47 = flag;
			break;
		case 5:
			isG36 = flag;
			break;
		case 6:
			isQBZ = flag;
			break;
		case 8:
			isGroza = flag;
			break;
		case 9:
			isAUG = flag;
			break;
		case 10:
			isS12K = flag;
			break;
		case 11:
			isS686 = flag;
			break;
		case 12:
			isS1897 = flag;
			break;
		case 13:
			isSawedOff = flag;
			break;
		case 14:
			isDBS = flag;
			break;
		case 15:
			isBizon = flag;
			break;
		case 16:
			isTommyGun = flag;
			break;
		case 17:
			isMP5 = flag;
			break;
		case 18:
			isUMP9 = flag;
			break;
		case 19:
			isVector = flag;
			break;
		case 20:
			isUzi = flag;
			break;
		case 21:
			isAWM = flag;
			break;
		case 22:
			isQBU = flag;
			break;
		case 23:
			isSLR = flag;
			break;
		case 24:
			isSKS = flag;
			break;
		case 25:
			isMini14 = flag;
			break;
		case 26:
			isM24 = flag;
			break;
		case 27:
			isKar98K = flag;
			break;
		case 28:
			isVSS = flag;
			break;
		case 29:
			isWin94 = flag;
			break;
		case 30:
			isMk14 = flag;
			break;
		case 31:
			isDP28 = flag;
			break;
		case 32:
			isM249 = flag;
			break;
		case 33:
			isCrossBow = flag;
			break;
		case 34:
			isR1895 = flag;
			break;
		case 35:
			isVz61 = flag;
			break;
		case 36:
			isP92 = flag;
			break;	
		case 37:
			isP18C = flag;
			break;
		case 38:
			isR45 = flag;
			break;
		case 39:
			isP1911 = flag;
			break;
		case 40:
			isDeagle = flag;
			break;
		case 41:
			isFragGrenade = flag;
			break;
		case 42:
			isSmokeGrenade = flag;
			break;
		case 43:
			isMolotov = flag;
			break;
		case 44:
			isSickle = flag;
			break;
		case 45:
			isMachete = flag;
			break;
		case 46:
			isCrowbar = flag;
			break;
		case 47:
			isPan = flag;
			break;
		case 48:
			is762 = flag;
			break;
		case 49:
			is45ACP = flag;
			break;
		case 50:
			is556 = flag;
			break;
		case 51:
			is9mm = flag;
			break;
		case 52:
			is300Mag = flag;
			break;
		case 53:
			is12G = flag;
			break;
		case 54:
			isBolt = flag;
			break;
		case 55:
			isFlare = flag;
			break;
		case 56:
			isSMGFlashHider = flag;
			break;
		case 57:
			isSMGSuppressor = flag;
			break;
		case 58:
			isSMGCompensator = flag;
			break;
		case 59:
			isARSuppressor = flag;
			break;
		case 60:
			isARFlashHider = flag;
			break;
		case 61:
			isARCompensator = flag;
			break;
		case 62:
			isSGChoke = flag;
			break;
		case 63:
			isSGDuckbill = flag;
			break;
		case 64:
			isSnipFlashHider = flag;
			break;
		case 65:
			isSnipCompensator = flag;
			break;
		case 66:
			isSnipSuppressor = flag;
			break;
		case 67:
			isTacStock = flag;
			break;
		case 68:
			isCheekpad = flag;
			break;
		case 69:
			isStock = flag;
			break;
		case 70:
			isSnipExQuickdraw = flag;
			break;
		case 71:
			isSMGExtended = flag;
			break;
		case 72:
			isSMGQuickdraw = flag;
			break;
		case 73:
			isSnipExtended = flag;
			break;
		case 74:
			isSnipQuickdraw = flag;
			break;
		case 75:
			isARQuickdraw = flag;
			break;
		case 76:
			isARExQuickdraw = flag;
			break;
		case 77:
			isARExtended = flag;
			break;
		case 78:
			isSMGExQuickdraw = flag;
			break;
		case 79:
			isCrossbowPad = flag;
			break;
		case 80:
			isBulletLoops = flag;
			break;
		case 81:
			isThumbGrip = flag;
			break;
		case 82:
			isLaserSight = flag;
			break;
		case 83:
			isAngledGrip = flag;
			break;
		case 84:
			isLightGrip = flag;
			break;
		case 85:
			isHalfGrip = flag;
			break;
		case 86:
			isVerticalGrip = flag;
			break;
		case 87:
			is8xScope = flag;
			break;
		case 88:
			is2xScope = flag;
			break;
		case 89:
			isRedDot = flag;
			break;
		case 90:
			is3xScope = flag;
			break;
		case 91:
			isHolo = flag;
			break;
		case 92:
			is6xScope = flag;
			break;
		case 93:
			is4xScope = flag;
			break;
		case 94:
			isPills = flag;
			break;
		case 95:
			isInjections = flag;
			break;
		case 96:
			isDrinks = flag;
			break;
		case 97:
			isFirstAid = flag;
			break;
		case 98:
			isBandage = flag;
			break;
		case 99:
			isMedKit = flag;
			break;
		case 100:
			isLv3Bag = flag;
			break;
		case 101:
			isLv2Bag = flag;
			break;
		case 102:
			isLv1Bag = flag;
			break;
		case 103:
			isLv3Armor = flag;
			break;
		case 104:
			isLv2Armor = flag;
			break;
		case 105:
			isLv1Armor = flag;
			break;
		case 106:
			isLv3Helm = flag;
			break;
		case 107:
			isLv2Helm = flag;
			break;
		case 108:
			isLv1Helm = flag;
			break;
		case 109:
			isGhillie = flag;
			break;
		case 110:
			isCanted = flag;
			break;
		default:
			break;
	}
}

basic_string<char, char_traits<char>, allocator<char>> TouchSIMDRIVERS(){
    std::string dir = "UkFaT1L=";
    std::string own ="ULpC";
	return own+dir;
}

std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}


extern "C"
JNIEXPORT void JNICALL
Java_a_f_EngineString(JNIEnv *env, jclass type, jint num, jstring string) {
    if (num == 0) {
        event_path = jstring2string(env,string);
        evID = event_path.back() - '0';
        openEVPath(evID);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_a_f_Stop(JNIEnv *env, jclass type) {
    stopClient();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_a_f_GetPkg(JNIEnv *env, jclass clazz) {
	return env->NewStringUTF("com.pubg.imobile");
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_a_f_SwitchMemory(JNIEnv *env, jclass clazz, jstring key, jboolean jboolean1) {

	if(bValid) {

		bool isLobby1,isMagic,isSitScope;
		std::string userKey = env->GetStringUTFChars(key, nullptr);

		if (userKey == "pubg_less_recoil") {
			if (jboolean1) {
                clearResults();
                SelectMemory(C_ALLOC);
                MemorySearch(OBFUSCATE("196864"), DWORD);
                MemoryOffset(OBFUSCATE("16842753"), 4, DWORD);
                MemoryOffset(OBFUSCATE("16384"), 1484, DWORD);
                MemoryOffset(OBFUSCATE("16384"), 1524, DWORD);
                MemoryOffset(OBFUSCATE("16384"), 1564, DWORD);
                MemoryWrite(OBFUSCATE("-698416192"), DWORD);
                isLobby1 = (iCount > 0);
                clearResults();
                SelectMemory(C_ALLOC);
                MemorySearch(OBFUSCATE("1633839468"), DWORD);
                MemoryOffset(OBFUSCATE("1936158574"), 4, DWORD);
                MemoryOffset(OBFUSCATE("7303982"), 8, DWORD);
                MemoryOffset(OBFUSCATE("16384"), -264, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), 0x110, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), 0x114, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), 0x118, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), 0x11c, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), 0x120, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), 0x124, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), -200, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), -192, DWORD);
                MemoryWrite_com(OBFUSCATE("0"), -184, DWORD);
                clearResults();
			}
			return isLobby1;
		}

		if (userKey == "pubg_bullet_track") {
			if (jboolean1){
				clearResults();
				SelectMemory(Anonymous);
				MemorySearch(OBFUSCATE("30.5"),FLOAT);
				MemoryOffset(OBFUSCATE("25"),-4,FLOAT);
				MemoryWrite(OBFUSCATE("220"),FLOAT);
				MemoryWrite_com(OBFUSCATE("220"),-4,FLOAT);
				isMagic = (iCount > 0);
				clearResults();
			}
			return isMagic;
		}

		if (userKey == "pubg_sit_scope") {
			if (jboolean1){
                clearResults();
                SelectMemory(Anonymous);
                MemorySearch(OBFUSCATE("18.38787841797"),FLOAT);
                MemoryOffset(OBFUSCATE("13.27983283997"),28,FLOAT);
                MemoryWrite(OBFUSCATE("130.5419921875"),FLOAT);
                isSitScope = (iCount > 0);
                clearResults();
			}
			return isSitScope;
		}
	}

	return false;
}

extern "C"
JNIEXPORT void JNICALL
Java_a_f_getReady(JNIEnv *env, jclass clazz) {
	Bypass();
}