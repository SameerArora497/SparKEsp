
#ifndef MASTER_LOGIN_H
#define MASTER_LOGIN_H


#include "curl/curl.h"

const char *GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/ StrEnc("E8X\\7r7ys_Q%JS+L+~", "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C", 18).c_str(), /*()Landroid/content/ContentResolver;*/ StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L", "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77", 35).c_str());
    jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/ StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"", "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47", 32).c_str());
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/ StrEnc("e<F*J5c0Y", "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E", 9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/ StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H", "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73", 71).c_str());

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(/*android_id*/ StrEnc("ujHO)8OfOE", "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21", 10).c_str()));
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("m5I{GKGWBP-VOxkA", "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/ StrEnc("|}[q:", "\x31\x32\x1F\x34\x76", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("0iW=2^>0zTRB!B90", "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54", 16).c_str());
    jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/ StrEnc("@{[FP", "\x02\x29\x1A\x08\x14", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
    jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/ StrEnc("YN4DaP)!{wRGN}", "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18", 14).c_str(), /*()Ljava/lang/String;*/ StrEnc("VnpibEspM(b]<s#[9cQD", "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F", 20).c_str());

    auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
    return env->GetStringUTFChars(str, 0);
}

const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());

    auto len = strlen(uuid);

    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,", "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB", "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
    jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW", "\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0", "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());

    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}

std::string RSA_Encrypt(const std::string &clear_text, const std::string &pub_key) {
    std::string result;
    BIO *key = BIO_new_mem_buf((unsigned char *) pub_key.c_str(), -1);
    RSA *rsa = RSA_new();
    rsa = PEM_read_bio_RSA_PUBKEY(key, &rsa, NULL, NULL);
    if (!rsa) {
        return "";
    }

    int key_len = RSA_size(rsa);
    int block_len = key_len - 11;

    char *sub_text = new char[key_len + 1];
    memset(sub_text, 0, key_len + 1);
    int ret = 0;
    int pos = 0;
    std::string sub_str;

    while (pos < clear_text.length()) {
        sub_str = clear_text.substr(pos, block_len);
        memset(sub_text, 0, key_len + 1);
        ret = RSA_public_encrypt(sub_str.length(), (const unsigned char *) sub_str.c_str(), (unsigned char *) sub_text, rsa, RSA_PKCS1_PADDING);
        if (ret >= 0) {
            result.append(std::string(sub_text, ret));
        }
        pos += block_len;
    }

    BIO_free_all(key);
    RSA_free(rsa);
    delete[] sub_text;

    return result;
}

std::string RSA_Decrypt(const std::string &cipher_text, const std::string &pub_key) {
    std::string result;
    BIO *key = BIO_new_mem_buf((unsigned char *) pub_key.c_str(), -1);
    RSA *rsa = RSA_new();

    rsa = PEM_read_bio_RSA_PUBKEY(key, &rsa, NULL, NULL);
    if (!rsa) {
        return "";
    }

    int len = RSA_size(rsa);
    char *buf = new char[len + 1];
    memset(buf, 0, len + 1);

    int ret = RSA_public_decrypt(cipher_text.length(), (const unsigned char *) cipher_text.c_str(), (unsigned char *) buf, rsa, RSA_PKCS1_PADDING);
    if (ret >= 0) {
        result.append(std::string(buf, ret));
    }

    free(buf);
    BIO_free_all(key);
    RSA_free(rsa);

    return result;
}

uint8_t PUBLIC_KEY[450] = {0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0xE2, 0xE5, 0xE7, 0xE9, 0xEE, 0x80, 0xF0, 0xF5, 0xE2, 0xEC, 0xE9, 0xE3, 0x80, 0xEB, 0xE5, 0xF9, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0xAA, 0xED, 0xE9, 0xE9, 0xE2, 0xE9, 0xCA, 0xE1, 0xEE, 0xE2, 0xC7, 0xCB, 0xD1, 0xC8, 0xCB, 0xC9, 0xE7, 0x99, 0xD7, 0x90, 0xE2, 0xE1, 0xF1, 0xE5, 0xE6, 0xE1, 0xE1, 0xEF, 0xE3, 0xE1, 0xF1, 0x98, 0xE1, 0xED, 0xE9, 0xE9, 0xE2, 0xE3, 0xC7, 0xEB, 0xE3, 0xE1, 0xF1, 0xE5, 0xE1, 0x91, 0xD4, 0xCF, 0xEA, 0x96, 0xED, 0x95, 0xCB, 0xF4, 0xEA, 0xCD, 0xCA, 0xE2, 0xC9, 0xE6, 0xD0, 0xFA, 0xCE, 0xC8, 0xC3, 0xAA, 0x96, 0x90, 0xCB, 0x8B, 0xD8, 0xE7, 0xF7, 0xD6, 0xC6, 0xE1, 0xC4, 0xD1, 0xD7, 0xD6, 0xE5, 0xEA, 0xE7, 0xE2, 0xED, 0x95, 0x93, 0xDA, 0xEA, 0x94, 0xCF, 0x99, 0xF9, 0xDA, 0x91, 0xF0, 0xC3, 0x90, 0x94, 0xE6, 0xEA, 0x98, 0xF4, 0xF6, 0xFA, 0xE1, 0xE8, 0xC1, 0x95, 0x8F, 0xCB, 0x96, 0xEA, 0xC8, 0xC7, 0xD0, 0x8F, 0xC7, 0xF3, 0xC6, 0xC7, 0xE1, 0xF6, 0x8F, 0xF0, 0xEB, 0xC1, 0xC5, 0xD8, 0xCA, 0xAA, 0x96, 0x90, 0x94, 0x98, 0xD3,
                           0xEA, 0xCE, 0xC9, 0x8B, 0xF9, 0x97, 0xF8, 0xE2, 0xD2, 0xC8, 0xEE, 0xF9, 0x93, 0xE5, 0xD2, 0xC7, 0xF2, 0xEA, 0x96, 0xED, 0xCF, 0xC5, 0xED, 0xCB, 0xDA, 0xF0, 0xE9, 0xEF, 0xD4, 0xEA, 0xE7, 0xCB, 0x90, 0xC7, 0xD8, 0xEF, 0xF7, 0x95, 0x93, 0xC6, 0xCF, 0x8F, 0xD3, 0xC8, 0xEB, 0xC8, 0xCD, 0xF5, 0xC2, 0x96, 0xC7, 0xC7, 0x90, 0xD0, 0xCE, 0xD6, 0xD0, 0x92, 0xE8, 0xAA, 0x98, 0xE3, 0xE9, 0x97, 0xD2, 0x99, 0xFA, 0xEC, 0xEB, 0x96, 0xC7, 0xF3, 0xF9, 0xC4, 0xF6, 0xD0, 0xD5, 0x98, 0xD4, 0xF9, 0xCA, 0xFA, 0xEC, 0xEE, 0xD1, 0xE6, 0x95, 0xF3, 0xF2, 0xCB, 0xCE, 0xE1, 0xE7, 0xED, 0x92, 0x93, 0xC8, 0xC9, 0x8F, 0xF8, 0x8B, 0xCD, 0xF4, 0x92, 0xF8, 0x93, 0xEC, 0xEF, 0x93, 0xF0, 0x91, 0xC8, 0xCB, 0xC1, 0x8F, 0xC7, 0xF5, 0xCD, 0xF5, 0xEB, 0xC5, 0x95, 0xCF, 0xFA, 0xAA, 0x90, 0x8B, 0xEB, 0xC6, 0xF1, 0x90, 0xF4, 0xCA, 0x96, 0x91, 0xF7, 0xCE, 0xE6, 0x93, 0xE7, 0x92, 0xC1, 0x95, 0xF7, 0xF9, 0xE2, 0xD9, 0x96, 0x8F, 0xCA, 0xE7, 0xE5, 0xDA, 0xC8, 0xF1, 0xC5, 0xEC, 0xC7, 0x95, 0x92, 0x91, 0x90,
                           0xF4, 0x99, 0xD9, 0x91, 0xD3, 0xD8, 0xF6, 0xEC, 0xE5, 0xF6, 0xF6, 0xF6, 0x95, 0xD8, 0xC8, 0xCA, 0xF1, 0xE8, 0xE7, 0xE1, 0xD2, 0x95, 0xD7, 0xC6, 0x97, 0xF1, 0xE9, 0xAA, 0xCD, 0x96, 0xF5, 0xC7, 0xCE, 0xF7, 0xEC, 0xD9, 0xCD, 0x8B, 0xDA, 0xC6, 0x99, 0xE9, 0xCA, 0xC6, 0xC9, 0xCE, 0xE2, 0xC7, 0xF2, 0x99, 0xF0, 0xF4, 0x99, 0xC3, 0xE8, 0xFA, 0xF4, 0x93, 0xD0, 0xC4, 0x8B, 0x97, 0xC9, 0xE1, 0x91, 0xE4, 0xF7, 0x93, 0x92, 0xE3, 0x98, 0xC4, 0xD7, 0xF5, 0xEA, 0xD6, 0xE2, 0xF4, 0xF0, 0xCE, 0xD8, 0xDA, 0xEE, 0xC9, 0xEA, 0x96, 0xCF, 0x96, 0xE2, 0x90, 0xF3, 0xCC, 0xAA, 0xD5, 0xD7, 0xE9, 0xE4, 0xE1, 0xF1, 0xE1, 0xE2, 0xAA, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D, 0xE5, 0xEE, 0xE4, 0x80, 0xF0, 0xF5, 0xE2, 0xEC, 0xE9, 0xE3, 0x80, 0xEB, 0xE5, 0xF9, 0x8D, 0x8D, 0x8D, 0x8D, 0x8D};


#include <curl/curl.h>
struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

#endif
