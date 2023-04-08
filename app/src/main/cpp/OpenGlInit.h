#ifndef RESOURCE1_OPENGLINIT_H
#define RESOURCE1_OPENGLINIT_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/native_window_jni.h>
#include "struct.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_android.h"
#include "imgui/OPPOSans.h"
#include "struct.h"
#include "timer.h"
#include "log.h"

#include "socket.h"
#include "initial_function.h"
#include "OpenGlInput.h"
#include "settings.h"
#include "imguipp.h"
#include "OpenGlimg.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include <chrono>
#include <iostream>
#include <ratio>
#include <thread>
#include <OpenGlRW.h>

Request request;
Response response;
Options options = {1, -1,3,false,
                   1,false,200, 0, 0,
                   0.0, 90.0, 20000,1, false,
                   false, false, false, 0, 0,
                   30000, 0, 0};
float x,y;
char getString[30];
char postName[30];
char PlayerNation[100];
char PlayerNameByte[100];
int botCount,playerCount,grenadeCount,itemCount,vehicleCount,allplayerCount;

class Settlement {
public:
    static std::vector < std::string > string_split(
            std::string s,
            std::string delimiter)
    {
        size_t pos_start = 0;
        size_t pos_end;
        size_t delim_len = delimiter.length();
        std::string token;
        std::vector < std::string > res;
        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
        {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }
        res.push_back(s.substr(pos_start));
        return res;
    }
};

class OpenGlInit {
private:
    JNIEnv *_env;
    jobject holder;
    int surfaceWidth;
    int surfaceHigh;

public:

    ImFont *imFont;
    ImColor TextColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor CircleFilledColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor CircleColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor LineColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
    ImColor LinesColor = ImColor(1.0f, 1.0f, 0.0f, 1.0f);
    ImColor RedCircleFilled = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
    ImColor RectColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
    ImColor RectFilledColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
    ImColor HealthColor[200];
    ImColor EnemyColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor AlertColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor savingItemColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor loadItemColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor vehicleClr[18];
    ImColor ammoClr[6];
    ImColor weaponClr[47];
    ImColor armorClr[4];
    ImColor healtClr[5];
    ImColor miscClr[24];
    ImColor espClr[12];

    int CircleFilledNum_segments = 0;
    int CircleNum_segments = 0;
    float CircleThickness = 2.0f;
    float RectThickness = 2.0f;
    float RectRounding = 0.0f;
    float RectFilledRounding = 0.0f;
    float LinesThickness = 2.0f;

    EGLDisplay mEglDisplay = EGL_NO_DISPLAY;
    EGLSurface mEglSurface = EGL_NO_SURFACE;
    EGLConfig mEglConfig  = nullptr;
    EGLNativeWindowType SurfaceWin;
    EGLContext mEglContext = EGL_NO_CONTEXT;

    ImGuiIO *io;
    ImGuiStyle *style;
    ImguiAndroidInput *input;
    ImGuiWindow *g_window = nullptr;
    ImGuiContext *g = nullptr;
    ImGuiContext *glContext;
    ImVec4 active = imguipp::to_vec4(255, 255, 255, 180);
    ImVec4 inactive = imguipp::to_vec4(255, 255, 255, 180);

    int fpsCheck = 0;
    float FPStime;
    timer AutoFPS;

    float *NumIo;
    float FrameHeight;

    bool isChage = false;
    bool isDestroy = false;
    bool *DrawIo;

    std::thread *SurfaceThread = nullptr;

    const char *menuList[40] = {
            "eye.png",
            "gun.png",
            "aim.png",
            "edit.png",
            "clear0.png",
            "clear1.png",
            "vec0.png",
            "vec1.png",
            "vec2.png",
            "vec3.png",
            "vec4.png",
            "vec5.png",
            "vec6.png",
            "bot.png",
            "airdrop.png",
            "logo.png",
            "death.png",
            "armor.png",
            "backpack.png",
            "helmet.png",
            "pistol.png",
            "rifle.png",
            "scope.png",
            "smg.png",
            "sniper.png",
            "shotgun.png",
            "airplane.png",
            "grenade.png",
            "firstaidkit.png",
            "molotov.png",
            "ammo.png",
            "gold.png",
            "gascan.png",
            "compe.png",
            "hider.png",
            "mag.png",
            "suppres.png",
            "memory.png",
            "warning.png",
            "arrow.png"
    };

    const char *Flags[239] = {
            "ad.png",
            "ae.png",
            "af.png",
            "ag.png",
            "ai.png",
            "al.png",
            "am.png",
            "ao.png",
            "ar.png",
            "as.png",
            "at.png",
            "au.png",
            "aw.png",
            "ax.png",
            "az.png",
            "ba.png",
            "bb.png",
            "bd.png",
            "be.png",
            "bf.png",
            "bg.png",
            "bh.png",
            "bi.png",
            "bj.png",
            "bm.png",
            "bn.png",
            "bo.png",
            "bq.png",
            "br.png",
            "bs.png",
            "bt.png",
            "bw.png",
            "by.png",
            "bz.png",
            "bzbz.png",
            "ca.png",
            "cc.png",
            "ce.png",
            "cf.png",
            "cg.png",
            "ch.png",
            "ci.png",
            "ck.png",
            "cl.png",
            "cm.png",
            "cn.png",
            "co.png",
            "corsica.png",
            "cr.png",
            "cu.png",
            "cv.png",
            "cw.png",
            "cx.png",
            "cy.png",
            "cz.png",
            "de.png",
            "dhsh.png",
            "dj.png",
            "dk.png",
            "dm.png",
            "dz.png",
            "ea.png",
            "ec.png",
            "ee.png",
            "eg.png",
            "eh.png",
            "en.png",
            "er.png",
            "es.png",
            "et.png",
            "fj.png",
            "fk.png",
            "fl.png",
            "fm.png",
            "fo.png",
            "fr.png",
            "g1.png",
            "ga.png",
            "gb.png",
            "gd.png",
            "ge.png",
            "gg.png",
            "gh.png",
            "gi.png",
            "gl.png",
            "gm.png",
            "gn.png",
            "gq.png",
            "gr.png",
            "gt.png",
            "gu.png",
            "gw.png",
            "gy.png",
            "hawaii.png",
            "hk.png",
            "hn.png",
            "hr.png",
            "ht.png",
            "hu.png",
            "id.png",
            "ie.png",
            "il.png",
            "im.png",
            "in.png",
            "io.png",
            "iq.png",
            "ir.png",
            "is.png",
            "it.png",
            "je.png",
            "jm.png",
            "jo.png",
            "jp.png",
            "ke.png",
            "kg.png",
            "kh.png",
            "ki.png",
            "km.png",
            "kn.png",
            "kp.png",
            "kr.png",
            "kw.png",
            "ky.png",
            "kz.png",
            "la.png",
            "lb.png",
            "li.png",
            "lk.png",
            "lr.png",
            "ls.png",
            "lt.png",
            "lu.png",
            "lv.png",
            "ly.png",
            "ma.png",
            "madeira.png",
            "mc.png",
            "md.png",
            "me.png",
            "mg.png",
            "mh.png",
            "mk.png",
            "ml.png",
            "mm.png",
            "mn.png",
            "mo.png",
            "mp.png",
            "mq.png",
            "mr.png",
            "ms.png",
            "mt.png",
            "mu.png",
            "mv.png",
            "mw.png",
            "mx.png",
            "my.png",
            "mz.png",
            "na.png",
            "nato.png",
            "ne.png",
            "nf.png",
            "ng.png",
            "ni.png",
            "nl.png",
            "no.png",
            "np.png",
            "nr.png",
            "nu.png",
            "nz.png",
            "om.png",
            "ossetia.png",
            "pa.png",
            "pe.png",
            "pf.png",
            "pg.png",
            "ph.png",
            "pk.png",
            "pl.png",
            "pn.png",
            "pr.png",
            "ps.png",
            "pt.png",
            "pw.png",
            "py.png",
            "qa.png",
            "ro.png",
            "rs.png",
            "ru.png",
            "rw.png",
            "sa.png",
            "sb.png",
            "sc.png",
            "sd.png",
            "se.png",
            "sg.png",
            "si.png",
            "sk.png",
            "sl.png",
            "sn.png",
            "so.png",
            "sr.png",
            "ss.png",
            "st.png",
            "sv.png",
            "sy.png",
            "sz.png",
            "tc.png",
            "td.png",
            "tg.png",
            "th.png",
            "tj.png",
            "tk.png",
            "tl.png",
            "tm.png",
            "tn.png",
            "to.png",
            "tr.png",
            "tt.png",
            "tv.png",
            "tw.png",
            "tz.png",
            "ua.png",
            "ug.png",
            "us.png",
            "uy.png",
            "uz.png",
            "va.png",
            "ve.png",
            "vg.png",
            "vi.png",
            "vn.png",
            "vu.png",
            "wales.png",
            "ws.png",
            "xk.png",
            "ye.png",
            "za.png",
            "zm.png",
            "zw.png"
    };

    ImTextureID displayESP;
    ImTextureID itemESP;
    ImTextureID aimESP;
    ImTextureID fireEsp;
    ImTextureID memory;
    ImTextureID warning;
    ImTextureID arrow;
    ImTextureID clear0;
    ImTextureID clear1;
    ImTextureID vec[39];
    ImTextureID flags[239];

    ImColor RedColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
    ImColor RedColorAlpha = ImColor(1.0f, 0.0f, 0.0f, 0.5f);
    ImColor WhiteColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImColor BlackColor = ImColor(0.0f, 0.0f, 0.0f, 1.0f);
    ImColor GreenColor = ImColor(0.0f, 1.0f, 0.0f, 1.0f);
    ImColor GreenColorAlpha = ImColor(0.0f, 1.0f, 0.0f, 0.5f);
    ImColor YellowColor = ImColor(1.0f, 1.0f, 0.0f, 1.0f);
    ImColor OrangeColor = ImColor(1.0f, 0.5f, 0.0f, 1.0f);
    ImColor OrangeColorAlpha = ImColor(1.0f, 0.5f, 0.0f, 0.5f);

    OpenGlInit() {
        _env = nullptr;
        holder = nullptr;
        surfaceWidth = 0;
        surfaceHigh = 0;
    }

    OpenGlInit(JNIEnv *env, jobject surface, int SurfaceWidth, int SurfaceHigh) {
        _env = env;
        holder = surface;
        surfaceWidth = SurfaceWidth;
        surfaceHigh = SurfaceHigh;
    }

    bool isValid() const {
        return (_env != nullptr && holder != nullptr && surfaceWidth != 0 && surfaceHigh != 0);
    }

    void onSurfaceCreate(int SurfaceWidth, int SurfaceHigh) {
        SurfaceWin = ANativeWindow_fromSurface(_env, holder);
        surfaceWidth = SurfaceWidth;
        surfaceHigh = SurfaceHigh;
        SurfaceThread = new std::thread([this] { drawGL(); });
        SurfaceThread->detach();
    }

    void onSurfaceChange(int SurfaceWidth, int SurfaceHigh) {
        surfaceWidth = SurfaceWidth;
        surfaceHigh = SurfaceHigh;
        isChage = true;
    }

    void onSurfaceDestroy() {
        ImGui::ClearIniSettings();
        ImGui::ClearDragDrop();
        ImGui::ClearActiveID();
        isDestroy = true;
    }

    int initEgl() {
        mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (mEglDisplay == EGL_NO_DISPLAY) { return -1; }

        EGLint *version = new EGLint[2];
        if (!eglInitialize(mEglDisplay, &version[0], &version[1])) { return -1; }

        const EGLint attribs[] = {EGL_BUFFER_SIZE, 32, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8,
                                  EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_STENCIL_SIZE, 8, EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE};

        EGLint num_config;
        if (!eglGetConfigs(mEglDisplay, NULL, 1, &num_config)) { return -1; }

        if (!eglChooseConfig(mEglDisplay, attribs, &mEglConfig, 1, &num_config)) { return -1; }

        int attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, attrib_list);

        if (mEglContext == EGL_NO_CONTEXT) { return -1; }

        mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, SurfaceWin, NULL);
        if (mEglSurface == EGL_NO_SURFACE) { return -1; }

        if (!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) { return -1; }
        return 1;
    }

    void clearBuffers() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    int swapBuffers() {
        if (eglSwapBuffers(mEglDisplay, mEglSurface)) {
            return 1;
        }
        return 0;
    }

    void initDraw(){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO();
        io->IniSavingRate = 10.0f;

        ImGui_ImplAndroid_Init(SurfaceWin);
        ImGui_ImplOpenGL3_Init("#version 100");
        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        imFont = io->Fonts->AddFontFromMemoryTTF((void *) OPPOSans_H, OPPOSans_H_size, 32.0f, &font_cfg, io->Fonts->GetGlyphRangesChineseFull());
        io->MouseDoubleClickTime = 0.0001f;
        io->ConfigWindowsMoveFromTitleBarOnly = true;

        g = ImGui::GetCurrentContext();
        style = ImGui::GetStyleP();
        style->ScaleAllSizes(3.0f);
        style->ItemSpacing.x  = 20;
        style->ItemSpacing.y  = 10;
        style->FramePadding.x = 20;
        style->FramePadding.y = 10;
        style->ResizeGripSize = 45.0f;

        loadItemFunFromDisk();
        LoadFuncFromDisk();
        displayESP = (void*)(intptr_t)getImageFromDisk(menuList[0]);
        itemESP = (void*)(intptr_t)getImageFromDisk(menuList[1]);
        aimESP = (void*)(intptr_t)getImageFromDisk(menuList[2]);
        fireEsp = (void*)(intptr_t)getImageFromDisk(menuList[3]);
        memory = (void*)(intptr_t)getImageFromDisk(menuList[37]);
        clear0 = (void*)(intptr_t)getImageFromDisk(menuList[4]);
        clear1 = (void*)(intptr_t)getImageFromDisk(menuList[5]);
        vec[0] = (void*)(intptr_t)getImageFromDisk(menuList[6]);
        vec[1] = (void*)(intptr_t)getImageFromDisk(menuList[7]);
        vec[2] = (void*)(intptr_t)getImageFromDisk(menuList[8]);
        vec[3] = (void*)(intptr_t)getImageFromDisk(menuList[9]);
        vec[4] = (void*)(intptr_t)getImageFromDisk(menuList[10]);
        vec[5] = (void*)(intptr_t)getImageFromDisk(menuList[11]);
        vec[6] = (void*)(intptr_t)getImageFromDisk(menuList[12]);
        vec[7] = (void*)(intptr_t)getImageFromDisk(menuList[13]);
        vec[8] = (void*)(intptr_t)getImageFromDisk(menuList[14]);
        vec[9] = (void*)(intptr_t)getImageFromDisk(menuList[15]);
        vec[10] = (void*)(intptr_t)getImageFromDisk(menuList[16]);

        vec[11] = (void*)(intptr_t)getImageFromDisk(menuList[17]);
        vec[12] = (void*)(intptr_t)getImageFromDisk(menuList[18]);
        vec[13] = (void*)(intptr_t)getImageFromDisk(menuList[19]);
        vec[14] = (void*)(intptr_t)getImageFromDisk(menuList[20]);
        vec[15] = (void*)(intptr_t)getImageFromDisk(menuList[21]);
        vec[16] = (void*)(intptr_t)getImageFromDisk(menuList[22]);
        vec[17] = (void*)(intptr_t)getImageFromDisk(menuList[23]);
        vec[18] = (void*)(intptr_t)getImageFromDisk(menuList[24]);
        vec[19] = (void*)(intptr_t)getImageFromDisk(menuList[25]);

        vec[20] = (void*)(intptr_t)getImageFromDisk(menuList[26]);
        vec[21] = (void*)(intptr_t)getImageFromDisk(menuList[27]);
        vec[22] = (void*)(intptr_t)getImageFromDisk(menuList[28]);
        vec[23] = (void*)(intptr_t)getImageFromDisk(menuList[29]);
        vec[24] = (void*)(intptr_t)getImageFromDisk(menuList[30]);
        vec[25] = (void*)(intptr_t)getImageFromDisk(menuList[31]);
        vec[26] = (void*)(intptr_t)getImageFromDisk(menuList[32]);

        vec[27] = (void*)(intptr_t)getImageFromDisk(menuList[33]);
        vec[28] = (void*)(intptr_t)getImageFromDisk(menuList[34]);
        vec[29] = (void*)(intptr_t)getImageFromDisk(menuList[35]);
        warning = (void*)(intptr_t)getImageFromDisk(menuList[38]);
        arrow = (void*)(intptr_t)getImageFromDisk(menuList[39]);

        for (int i=0; i<239; i++) {
            flags[i] = (void *) (intptr_t) getFlagFromDisk(Flags[i]);
        }
    }

    void imguiMainWinStart() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame();
        ImGui::NewFrame();
    }

    void imguiMainWinEnd() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void drawGL(){
        if (checkstatus()) {
            initEgl();
            initDraw();

            AutoFPS.SetFps(fpsCount);
            AutoFPS.AotuFPS_init(1);
            AutoFPS.setAffinity();

            input->initImguiIo(io);
            input->setImguiContext(g);
            input->setwin(g_window);

            while (!isDestroy) {

                if (isChage) {
                    glViewport(0, 0, surfaceWidth, surfaceHigh);
                    isChage = false;
                }
                if (isDestroy) {
                    delete SurfaceThread;
                    SurfaceThread = nullptr;
                    ImGui::ClosePopupsExceptModals();
                    ImGui::CloseCurrentPopup();
                    ImGui::DestroyContext();
                }

                clearBuffers();
                imguiMainWinStart();
                DrawWindow();

                int width = surfaceWidth;
                int high = surfaceHigh;
                int otherscale = scale / 18;
                int lineScale = scale / 100;
                botCount = 0;
                playerCount = 0;

                sprintf(getString, " FPS %6.2f", 1000.0f / FPStime);
                std::string Str = std::string(currentDateTime() + getString);
                DrawTextCxy(width / 4, 25, RedColor, 35, Str.c_str());

                if (fovScreen) {
                    DrawCircle(width / 2, high / 2, options.aimingRange, RedColor);
                }

                options.isOrientation = reverseTouch;
                if (options.isOrientation) {
                    options.touchPosX = aimposx;
                    options.shootLoopX = AutoShootPosX;
                } else {
                    options.touchPosX = -aimposx;
                    options.shootLoopX = -AutoShootPosX;
                }
                if (options.isOrientation) {
                    options.touchPosY = aimposy;
                    options.shootLoopY = AutoShootPosY;
                } else {
                    options.touchPosY = -aimposy;
                    options.shootLoopY = -AutoShootPosY;
                }

                /*if (AdjustCamera) {
                    if (options.isOrientation) {
                        DrawCircleFilled(width / 2 - options.touchPosX,
                                         high / 2 + options.touchPosY,
                                         20, GreenColor);
                    } else {
                        DrawCircleFilled(width / 2 + options.touchPosX,
                                         high / 2 - options.touchPosY,
                                         20, GreenColor);
                    }
                }*/

                request.ScreenHeight = high;
                request.ScreenWidth = width;
                request.Mode = InitMode;
                request.options = options;
                send((void *) &request, sizeof(request));
                receive((void *) &response);

                if (response.Success) {
                    grenadeCount = response.GrenadeCount;
                    itemCount = response.ItemsCount;
                    vehicleCount = response.VehicleCount;
                    allplayerCount = response.PlayerCount;

                    for (int i = 0; i < allplayerCount; i++) {
                        x = response.Players[i].HeadLocation.x;
                        y = response.Players[i].HeadLocation.y;
                        if (response.Players[i].isBot) {
                            botCount++;
                        } else {
                            playerCount++;
                        }

                        float magic_number = (response.Players[i].Distance * response.fov);
                        float mx = (width / 4) / magic_number;
                        float my = (width / 1.38) / magic_number;
                        float top = y - my + (width / 1.7) / magic_number;
                        float bottom = y + my + high / 4 / magic_number;

                        if (response.Players[i].HeadLocation.z != 1) {
                            if (x > -50 && x < width + 50) {

                                sprintf(PlayerNameByte, "%s", realname(response.Players[i].PlayerNameByte).c_str());
                                sprintf(PlayerNation, "%s", realname(response.Players[i].PlayerNation).c_str());

                                if (espGeneric[6]) {
                                    ImGui::GetBackgroundDrawList()->
                                            AddImage(arrow,
                                                     ImVec2( x - 10, top - 35 - vertical - otherscale),
                                                     ImVec2(x + 10, top - 25 - vertical - otherscale),
                                                     ImVec2(0.0f, 0.0f),
                                                     ImVec2(1.0f, 1.0f),
                                                     WhiteColor);
                                } else {
                                    ImGui::GetBackgroundDrawList()->
                                            AddImage(arrow,
                                                     ImVec2( x - 10, top - 15 - vertical - otherscale),
                                                     ImVec2(x + 10, top - 5 - vertical - otherscale),
                                                     ImVec2(0.0f, 0.0f),
                                                     ImVec2(1.0f, 1.0f),
                                                     WhiteColor);
                                }

                                float neck = (response.Players[i].Bone.neck.x - width / 2) *
                                             (response.Players[i].Bone.neck.x - width / 2) +
                                             (response.Players[i].Bone.neck.y - high / 2) *
                                             (response.Players[i].Bone.neck.y - high / 2);

                                float cheast = (response.Players[i].Bone.cheast.x - width / 2) *
                                               (response.Players[i].Bone.cheast.x - width / 2) +
                                               (response.Players[i].Bone.cheast.y - high / 2) *
                                               (response.Players[i].Bone.cheast.y - high / 2);

                                float pelvis = (response.Players[i].Bone.pelvis.x - width / 2) *
                                               (response.Players[i].Bone.pelvis.x - width / 2) +
                                               (response.Players[i].Bone.pelvis.y - high / 2) *
                                               (response.Players[i].Bone.pelvis.y - high / 2);

                                float lSh = (response.Players[i].Bone.lSh.x - width / 2) *
                                            (response.Players[i].Bone.lSh.x - width / 2) +
                                            (response.Players[i].Bone.lSh.y - high / 2) *
                                            (response.Players[i].Bone.lSh.y - high / 2);

                                float rSh = (response.Players[i].Bone.rSh.x - width / 2) *
                                            (response.Players[i].Bone.rSh.x - width / 2) +
                                            (response.Players[i].Bone.rSh.y - high / 2) *
                                            (response.Players[i].Bone.rSh.y - high / 2);

                                float lElb = (response.Players[i].Bone.lElb.x - width / 2) *
                                             (response.Players[i].Bone.lElb.x - width / 2) +
                                             (response.Players[i].Bone.lElb.y - high / 2) *
                                             (response.Players[i].Bone.lElb.y - high / 2);

                                float rElb = (response.Players[i].Bone.rElb.x - width / 2) *
                                             (response.Players[i].Bone.rElb.x - width / 2) +
                                             (response.Players[i].Bone.rElb.y - high / 2) *
                                             (response.Players[i].Bone.rElb.y - high / 2);

                                float lWr = (response.Players[i].Bone.lWr.x - width / 2) *
                                            (response.Players[i].Bone.lWr.x - width / 2) +
                                            (response.Players[i].Bone.lWr.y - high / 2) *
                                            (response.Players[i].Bone.lWr.y - high / 2);

                                float rWr = (response.Players[i].Bone.rWr.x - width / 2) *
                                            (response.Players[i].Bone.rWr.x - width / 2) +
                                            (response.Players[i].Bone.rWr.y - high / 2) *
                                            (response.Players[i].Bone.rWr.y - high / 2);

                                float lTh = (response.Players[i].Bone.lTh.x - width / 2) *
                                            (response.Players[i].Bone.lTh.x - width / 2) +
                                            (response.Players[i].Bone.lTh.y - high / 2) *
                                            (response.Players[i].Bone.lTh.y - high / 2);

                                float rTh = (response.Players[i].Bone.rTh.x - width / 2) *
                                            (response.Players[i].Bone.rTh.x - width / 2) +
                                            (response.Players[i].Bone.rTh.y - high / 2) *
                                            (response.Players[i].Bone.rTh.y - high / 2);

                                float lKn = (response.Players[i].Bone.lKn.x - width / 2) *
                                            (response.Players[i].Bone.lKn.x - width / 2) +
                                            (response.Players[i].Bone.lKn.y - high / 2) *
                                            (response.Players[i].Bone.lKn.y - high / 2);

                                float rKn = (response.Players[i].Bone.rKn.x - width / 2) *
                                            (response.Players[i].Bone.rKn.x - width / 2) +
                                            (response.Players[i].Bone.rKn.y - high / 2) *
                                            (response.Players[i].Bone.rKn.y - high / 2);

                                float lAn = (response.Players[i].Bone.lAn.x - width / 2) *
                                            (response.Players[i].Bone.lAn.x - width / 2) +
                                            (response.Players[i].Bone.lAn.y - high / 2) *
                                            (response.Players[i].Bone.lAn.y - high / 2);

                                float rAn = (response.Players[i].Bone.rAn.x - width / 2) *
                                            (response.Players[i].Bone.rAn.x - width / 2) +
                                            (response.Players[i].Bone.rAn.y - high / 2) *
                                            (response.Players[i].Bone.rAn.y - high / 2);

                                if (response.Players[i].HeadLocation.x > neck &&
                                    response.Players[i].HeadLocation.y > neck ||
                                    response.Players[i].HeadLocation.x > cheast &&
                                    response.Players[i].HeadLocation.y > cheast ||
                                    response.Players[i].HeadLocation.x > pelvis &&
                                    response.Players[i].HeadLocation.y > pelvis ||
                                    response.Players[i].HeadLocation.x > lSh &&
                                    response.Players[i].HeadLocation.y > lSh ||
                                    response.Players[i].HeadLocation.x > rSh &&
                                    response.Players[i].HeadLocation.y > rSh ||
                                    response.Players[i].HeadLocation.x > lElb &&
                                    response.Players[i].HeadLocation.y > lElb ||
                                    response.Players[i].HeadLocation.x > rElb &&
                                    response.Players[i].HeadLocation.y > rElb ||
                                    response.Players[i].HeadLocation.x > lWr &&
                                    response.Players[i].HeadLocation.y > lWr ||
                                    response.Players[i].HeadLocation.x > rWr &&
                                    response.Players[i].HeadLocation.y > rWr ||
                                    response.Players[i].HeadLocation.x > lTh &&
                                    response.Players[i].HeadLocation.y > lTh ||
                                    response.Players[i].HeadLocation.x > rTh &&
                                    response.Players[i].HeadLocation.y > rTh ||
                                    response.Players[i].HeadLocation.x > lKn &&
                                    response.Players[i].HeadLocation.y > lKn ||
                                    response.Players[i].HeadLocation.x > rKn &&
                                    response.Players[i].HeadLocation.y > rKn ||
                                    response.Players[i].HeadLocation.x > lAn &&
                                    response.Players[i].HeadLocation.y > lAn ||
                                    response.Players[i].HeadLocation.x > rAn &&
                                    response.Players[i].HeadLocation.y > rAn) {
                                    EnemyColor = ImColor(0.0f, 1.0f, 0.0f, 1.0f);
                                    AlertColor = ImColor(0.0f, 1.0f, 0.0f, 0.4f);
                                    if (response.Players[i].isBot) {
                                        std::string ainame = "AI";
                                        std::string space = ": ";
                                        std::string pstatus = "AI Player";
                                        sprintf(getString, "%0.0f", response.Players[i].Health);
                                        std::string Str = std::string(ainame + space + getString + space + pstatus);
                                        DrawTextCxy2(width / 2 - 90 - strlen(Str.c_str()),
                                                     high / 2 + 250,
                                                     OrangeColor, 35, Str.c_str());
                                    } else {
                                        std::string space = ": ";
                                        std::string pstatus = "Player";
                                        sprintf(getString, "%0.0f", response.Players[i].Health);
                                        std::string Str = std::string(PlayerNameByte + space + getString + space + pstatus);
                                        DrawTextCxy2(width / 2 - 130 - strlen(Str.c_str()),
                                                     high / 2 + 250,
                                                     OrangeColor, 35, Str.c_str());
                                    }
                                } else {
                                    if (response.Players[i].isBot) {
                                        EnemyColor = ImColor(1.0f, 1.0f, 1.0f, 1.0f);
                                        AlertColor = ImColor(1.0f, 1.0f, 1.0f, 0.4f);
                                    } else {
                                        if (response.Players[i].Distance < 140) {
                                            EnemyColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
                                            AlertColor = ImColor(1.0f, 0.0f, 0.0f, 0.4f);
                                        } else if (response.Players[i].Distance > 140 &&
                                                   response.Players[i].Distance < 250) {
                                            EnemyColor = ImColor(1.0f, 1.0f, 0.0f, 1.0f);
                                            AlertColor = ImColor(1.0f, 1.0f, 0.0f, 0.4f);
                                        } else if (response.Players[i].Distance > 250) {
                                            EnemyColor = ImColor(1.0f, 0.5f, 0.0f, 1.0f);
                                            AlertColor = ImColor(1.0f, 0.5f, 0.0f, 0.4f);
                                        }
                                    }
                                }

                                if (espGeneric[0]) { //Health
                                    float healthLength = width / 60;
                                    if (healthLength < mx)
                                        healthLength = mx;
                                    if (response.Players[i].Health == 0) {
                                        if (espGeneric[6]) {
                                            //DrawFillRec
                                            DrawRectFilled(x - healthLength - (30 + otherscale) -
                                                           (otherscale * 2),
                                                           top - 65 - (otherscale * 2) - vertical,
                                                           x - healthLength +
                                                           (2 * healthLength) *
                                                           response.Players[i].Health /
                                                           100 + (30 + otherscale) + otherscale +
                                                           otherscale,
                                                           top - 35 - otherscale - vertical,
                                                           RedColorAlpha);
                                            //DrawRec
                                            DrawRect(x - healthLength - (30 + otherscale) -
                                                     (otherscale * 2),
                                                     top - 65 - (otherscale * 2) - vertical,
                                                     x + healthLength + (30 + otherscale) +
                                                     otherscale + otherscale,
                                                     top - 35 - otherscale - vertical,
                                                     BlackColor, 1);
                                        } else {
                                            //DrawFillRec
                                            DrawRectFilled(x - healthLength - (30 + otherscale) -
                                                           (otherscale * 2),
                                                           top - 45 - (otherscale * 2) - vertical,
                                                           x - healthLength +
                                                           (2 * healthLength) *
                                                           response.Players[i].Health /
                                                           100 + (30 + otherscale) + otherscale +
                                                           otherscale,
                                                           top - 15 - otherscale - vertical,
                                                           RedColorAlpha);
                                            //DrawRec
                                            DrawRect(x - healthLength - (30 + otherscale) -
                                                     (otherscale * 2),
                                                     top - 45 - (otherscale * 2) - vertical,
                                                     x + healthLength + (30 + otherscale) +
                                                     otherscale + otherscale,
                                                     top - 15 - otherscale - vertical,
                                                     BlackColor, 1);
                                        }
                                    } else {
                                        if (espGeneric[6]) {
                                            //DrawFillRec
                                            DrawRectFilled(x - healthLength - (30 + otherscale) -
                                                           (otherscale * 2),
                                                           top - 65 - (otherscale * 2) - vertical,
                                                           x - healthLength +
                                                           (2 * healthLength) *
                                                           response.Players[i].Health /
                                                           100 + (30 + otherscale) + otherscale +
                                                           otherscale,
                                                           top - 35 - otherscale - vertical,
                                                           GreenColorAlpha);
                                            //DrawRec
                                            DrawRect(x - healthLength - (30 + otherscale) -
                                                     (otherscale * 2),
                                                     top - 65 - (otherscale * 2) - vertical,
                                                     x + healthLength + (30 + otherscale) +
                                                     otherscale + otherscale,
                                                     top - 35 - otherscale - vertical,
                                                     BlackColor, 1);
                                        } else {
                                            //DrawFillRec
                                            DrawRectFilled(x - healthLength - (30 + otherscale) -
                                                           (otherscale * 2),
                                                           top - 45 - (otherscale * 2) - vertical,
                                                           x - healthLength +
                                                           (2 * healthLength) *
                                                           response.Players[i].Health /
                                                           100 + (30 + otherscale) + otherscale +
                                                           otherscale,
                                                           top - 15 - otherscale - vertical,
                                                           GreenColorAlpha);
                                            //DrawRec
                                            DrawRect(x - healthLength - (30 + otherscale) -
                                                     (otherscale * 2),
                                                     top - 45 - (otherscale * 2) - vertical,
                                                     x + healthLength + (30 + otherscale) +
                                                     otherscale + otherscale,
                                                     top - 15 - otherscale - vertical,
                                                     BlackColor, 1);
                                        }
                                    }
                                }
                                if (espGeneric[11]) {//nations flags
                                    if (!response.Players[i].isBot) {
                                        //PlayerNation[i] = realname(response.Players[i].PlayerNation).c_str();
                                        //sprintf(getString, "%s", realname(response.Players[i].PlayerNation).c_str());
                                        //LOGE("nationsManme %s", getString);
                                        if (espGeneric[6]) {
                                            //DrawText
                                            ImGui::GetBackgroundDrawList()->AddImage(getFlags(PlayerNation),
                                                                                     ImVec2(x - 100 + 145 - vertical + (otherscale * 2), top - 60 - vertical - (otherscale * 2)),
                                                                                     ImVec2(x - 80 + 145 - vertical + (otherscale * 3), top - 42 - vertical - otherscale),
                                                                                     ImVec2(0.0f, 0.0f),
                                                                                     ImVec2(1.0f, 1.0f),
                                                                                     WhiteColor);
                                        } else {
                                            //DrawText
                                            ImGui::GetBackgroundDrawList()->AddImage(getFlags(PlayerNation),
                                                                                     ImVec2(x - 100 + 145 - vertical + (otherscale * 2), top - 40 - vertical - (otherscale * 2)),
                                                                                     ImVec2(x - 80 + 145 - vertical + (otherscale * 3), top - 22 - vertical - otherscale),
                                                                                     ImVec2(0.0f, 0.0f),
                                                                                     ImVec2(1.0f, 1.0f),
                                                                                     WhiteColor);
                                        }
                                    }
                                }
                                if (espGeneric[1]) {//name
                                    if (response.Players[i].isBot) {
                                        if (espGeneric[6]) {
                                            //DrawText
                                            ImGui::GetBackgroundDrawList()->
                                                    AddImage(vec[7],
                                                             ImVec2(x - 100 + 80 - vertical -
                                                                    otherscale,
                                                                    top - 60 - vertical -
                                                                    (otherscale * 2)),
                                                             ImVec2(x - 80 + 80 - vertical -
                                                                    (otherscale / 4),
                                                                    top - 42 - vertical -
                                                                    otherscale),
                                                             ImVec2(0.0f, 0.0f),
                                                             ImVec2(1.0f, 1.0f),
                                                             WhiteColor);
                                            DrawTextCxy2(x + strlen("AI") + 2 - (otherscale / 4),
                                                         top - 57 - vertical - (otherscale * 2),
                                                         WhiteColor, 15 + otherscale, "AI");
                                        } else {
                                            //DrawText
                                            ImGui::GetBackgroundDrawList()->
                                                    AddImage(vec[7],
                                                             ImVec2(x - 100 + 80 - vertical -
                                                                    otherscale,
                                                                    top - 40 - vertical -
                                                                    (otherscale * 2)),
                                                             ImVec2(x - 80 + 80 - vertical -
                                                                    (otherscale / 4),
                                                                    top - 22 - vertical -
                                                                    otherscale),
                                                             ImVec2(0.0f, 0.0f),
                                                             ImVec2(1.0f, 1.0f),
                                                             WhiteColor);
                                            DrawTextCxy2(x + strlen("AI") + 2 - (otherscale / 4),
                                                         top - 37 - vertical - (otherscale * 2),
                                                         WhiteColor, 15 + otherscale, "AI");
                                        }
                                    } else {
                                        if (espGeneric[6]) {
                                            //DrawText
                                            getName(PlayerNameByte, x, top, 1, otherscale);
                                        } else {
                                            //DrawText
                                            getName(PlayerNameByte, x, top, 2, otherscale);
                                        }
                                    }
                                }
                                if (espGeneric[2] && !response.Players[i].isBot) {//teamId
                                    sprintf(getString, "%d", response.Players[i].TeamID);
                                    int leng = strlen(getString);
                                    if (espGeneric[6]) {
                                        //DrawText
                                        if (leng == 1 ) {
                                            DrawTextCxy(x - 40 - (otherscale * 4),
                                                        top - 42 - vertical - otherscale - (otherscale),
                                                        WhiteColor, 15 + otherscale, getString);
                                        } else if (leng == 2) {
                                            DrawTextCxy(x - 30 - (otherscale * 4),
                                                        top - 42 - vertical - otherscale - (otherscale),
                                                        WhiteColor, 15 + otherscale, getString);
                                        } else {
                                            DrawTextCxy(x - 20 - (otherscale * 4),
                                                        top - 42 - vertical - otherscale - (otherscale),
                                                        WhiteColor, 15 + otherscale, getString);
                                        }
                                    } else {
                                        //DrawText
                                        if (leng == 1 ) {
                                            DrawTextCxy(x - 40 - (otherscale * 4),
                                                        top - 22 - vertical - (otherscale * 2),
                                                        WhiteColor, 15 + otherscale, getString);
                                        } else if (leng == 2) {
                                            DrawTextCxy(x - 30 - (otherscale * 4),
                                                        top - 22 - vertical - (otherscale * 2),
                                                        WhiteColor, 15 + otherscale, getString);
                                        } else {
                                            DrawTextCxy(x - 20 - (otherscale * 4),
                                                        top - 22 - vertical - (otherscale * 2),
                                                        WhiteColor, 15 + otherscale, getString);
                                        }
                                    }
                                }
                                if (espGeneric[3]) {//distance
                                    sprintf(getString, "%0.0f M", response.Players[i].Distance);
                                    //DrawText
                                    DrawTextCxy2(x + strlen(getString) - 18 - otherscale,
                                                 bottom,
                                                 WhiteColor, 15 + otherscale, getString);
                                }
                                if (espGeneric[4]) {//RedDot
                                    //DrawFillCircle
                                    DrawCircleFilled(response.Players[i].Bone.pelvis.x,
                                                     response.Players[i].Bone.pelvis.y,
                                                     1 + lineScale, EnemyColor);
                                }
                                //skeleton
                                if (espGeneric[5] && response.Players[i].Bone.isBone) {
                                    //DrawLine
                                    DrawLine(response.Players[i].HeadLocation.x,
                                             response.Players[i].HeadLocation.y + 20,
                                             response.Players[i].Bone.neck.x,
                                             response.Players[i].HeadLocation.y + 20,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.neck.x,
                                             response.Players[i].Bone.neck.y,
                                             response.Players[i].Bone.cheast.x,
                                             response.Players[i].Bone.cheast.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.cheast.x,
                                             response.Players[i].Bone.cheast.y,
                                             response.Players[i].Bone.pelvis.x,
                                             response.Players[i].Bone.pelvis.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.neck.x,
                                             response.Players[i].Bone.neck.y,
                                             response.Players[i].Bone.lSh.x,
                                             response.Players[i].Bone.lSh.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.neck.x,
                                             response.Players[i].Bone.neck.y,
                                             response.Players[i].Bone.rSh.x,
                                             response.Players[i].Bone.rSh.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.lSh.x,
                                             response.Players[i].Bone.lSh.y,
                                             response.Players[i].Bone.lElb.x,
                                             response.Players[i].Bone.lElb.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.rSh.x,
                                             response.Players[i].Bone.rSh.y,
                                             response.Players[i].Bone.rElb.x,
                                             response.Players[i].Bone.rElb.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.lElb.x,
                                             response.Players[i].Bone.lElb.y,
                                             response.Players[i].Bone.lWr.x,
                                             response.Players[i].Bone.lWr.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.rElb.x,
                                             response.Players[i].Bone.rElb.y,
                                             response.Players[i].Bone.rWr.x,
                                             response.Players[i].Bone.rWr.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.pelvis.x,
                                             response.Players[i].Bone.pelvis.y,
                                             response.Players[i].Bone.lTh.x,
                                             response.Players[i].Bone.lTh.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.pelvis.x,
                                             response.Players[i].Bone.pelvis.y,
                                             response.Players[i].Bone.rTh.x,
                                             response.Players[i].Bone.rTh.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.lTh.x,
                                             response.Players[i].Bone.lTh.y,
                                             response.Players[i].Bone.lKn.x,
                                             response.Players[i].Bone.lKn.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.rTh.x,
                                             response.Players[i].Bone.rTh.y,
                                             response.Players[i].Bone.rKn.x,
                                             response.Players[i].Bone.rKn.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.lKn.x,
                                             response.Players[i].Bone.lKn.y,
                                             response.Players[i].Bone.lAn.x,
                                             response.Players[i].Bone.lAn.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawLine(response.Players[i].Bone.rKn.x,
                                             response.Players[i].Bone.rKn.y,
                                             response.Players[i].Bone.rAn.x,
                                             response.Players[i].Bone.rAn.y,
                                             EnemyColor, 1 + lineScale);
                                    DrawCircle(response.Players[i].HeadLocation.x,
                                               response.Players[i].HeadLocation.y,
                                               high / 6 / magic_number, EnemyColor);
                                }
                                if (espGeneric[6]) {//weapon
                                    //drawWeapom
                                    getWeapon(WhiteColor, response.Players[i].Weapon.id, x, top - 20 - vertical - otherscale,
                                              otherscale);
                                }
                                if (espGeneric[8]) {//radarLine
                                    if (espGeneric[6]) {
                                        //DrawLine
                                        if (lineStyle == 0) {
                                            if (espGeneric[1] || espGeneric[0]) {
                                                DrawLine(width / 2, 0,
                                                         response.Players[i].HeadLocation.x,
                                                         top - 66 - vertical - (otherscale * 2),
                                                         EnemyColor,
                                                         1 + lineScale);
                                            } else {
                                                if (espGeneric[6]) {
                                                    DrawLine(width / 2, 0,
                                                             response.Players[i].HeadLocation.x,
                                                             top - 35 -
                                                             vertical - (otherscale * 2),
                                                             EnemyColor,
                                                             1 + lineScale);
                                                } else {
                                                    DrawLine(width / 2, 0,
                                                             response.Players[i].HeadLocation.x,
                                                             top - 15 -
                                                             vertical - (otherscale * 2),
                                                             EnemyColor,
                                                             1 + lineScale);
                                                }
                                            }
                                        } else {
                                            DrawLine(width / 2, width / 2 - 190,
                                                     response.Players[i].HeadLocation.x,
                                                     bottom + 12 - vertical + otherscale,
                                                     EnemyColor,
                                                     1 + lineScale);
                                        }
                                    } else {
                                        //DrawLine
                                        if (lineStyle == 0) {
                                            if (espGeneric[1] || espGeneric[0]) {
                                                DrawLine(width / 2, 0,
                                                         response.Players[i].HeadLocation.x,
                                                         top - 46 - vertical - (otherscale * 2),
                                                         EnemyColor,
                                                         1 + lineScale);
                                            } else {
                                                if (espGeneric[6]) {
                                                    DrawLine(width / 2, 0,
                                                             response.Players[i].HeadLocation.x,
                                                             top - 35 -
                                                             vertical - (otherscale * 2),
                                                             EnemyColor,
                                                             1 + lineScale);
                                                } else {
                                                    DrawLine(width / 2, 0,
                                                             response.Players[i].HeadLocation.x,
                                                             top - 15 -
                                                             vertical - (otherscale * 2),
                                                             EnemyColor,
                                                             1 + lineScale);
                                                }
                                            }
                                        } else {
                                            DrawLine(width / 2, width / 2 - 190,
                                                     response.Players[i].HeadLocation.x,
                                                     bottom + 12 - vertical + otherscale,
                                                     EnemyColor,
                                                     1 + lineScale);
                                        }
                                    }
                                }
                                if (boxStyle != 0) {
                                    if (boxStyle == 1) {
                                        //DrawBox 1
                                        DrawRect(x - mx, top,
                                                 x + mx, bottom, EnemyColor,
                                                 1 + lineScale);
                                    } else {
                                        //DrawBox 2
                                        DrawRect(+response.Players[i].Bone.pelvis.x - mx / 1.2f,
                                                 +response.Players[i].Bone.neck.y - mx / 2,
                                                 response.Players[i].Bone.pelvis.x + mx / 1.2f,
                                                 response.Players[i].Bone.rAn.y,
                                                 EnemyColor,
                                                 1 + lineScale);
                                    }
                                }

                            }//checkEnemyPosition
                        }
                        if (espGeneric[9]) {//edgewarning
                            if (response.Players[i].HeadLocation.z == 1.0f) {
                                if (y > high - high / 12)
                                    y = high - high / 12;
                                else if (y < high / 12)
                                    y = high / 12;
                                if (x < width / 2) {
                                    //DrawFillCircle
                                    DrawCircleFilled(width - otherscale, y,
                                                     65 + otherscale,
                                                     AlertColor);
                                    //DrawText
                                    sprintf(getString, "%0.0fM", response.Players[i].Distance);
                                    DrawTextCxy(width - width / 120 + strlen(getString) - otherscale -
                                                (otherscale * 2),
                                                y + 10 - otherscale + otherscale,
                                                WhiteColor, 25 + otherscale, getString);
                                } else {
                                    //DrawFillCircle
                                    DrawCircleFilled(0 + otherscale, y,
                                                     65 + otherscale,
                                                     AlertColor);
                                    //DrawText
                                    sprintf(getString, "%0.0fM", response.Players[i].Distance);
                                    DrawTextCxy(width / 120 + 25 + strlen(getString) + otherscale -
                                                (otherscale * 2),
                                                y + 10 + otherscale - otherscale,
                                                WhiteColor, 25 + otherscale, getString);
                                }
                            } else if (x < -width / 10 || x > width + width / 10) {
                                if (y > high - high / 12)
                                    y = high - high / 12;
                                else if (y < high / 12)
                                    y = high / 12;
                                if (x > width / 2) {
                                    //DrawFillCircle
                                    DrawCircleFilled(width - otherscale, y,
                                                     65 + otherscale,
                                                     AlertColor);
                                    //DrawText
                                    sprintf(getString, "%0.0fM", response.Players[i].Distance);
                                    DrawTextCxy(width - width / 120 + strlen(getString) - otherscale -
                                                (otherscale * 2),
                                                y + 10 - otherscale + otherscale,
                                                WhiteColor, 25 + otherscale, getString);
                                } else {
                                    //DrawFillCircle
                                    DrawCircleFilled(0 + otherscale, y,
                                                     65 + otherscale,
                                                     AlertColor);
                                    //DrawText
                                    sprintf(getString, "%0.0fM", response.Players[i].Distance);
                                    DrawTextCxy(width / 120 + 25 + strlen(getString) + otherscale -
                                                (otherscale * 2),
                                                y + 10 + otherscale - otherscale,
                                                WhiteColor, 25 + otherscale, getString);
                                }
                            }
                        }
                    }
                    if (espGeneric[7]) {//enemyCount
                        sprintf(getString, "%d", playerCount + botCount);
                        std::string pstatus = " Player in 300m";
                        std::string Str = std::string(getString + pstatus);
                        if (botCount + playerCount > 0) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(clear1,
                                             ImVec2(width / 2 + 180 + (otherscale * 4),
                                                    60 + 15 - otherscale + otherscale),
                                             ImVec2(width / 2 - 180 - (otherscale * 4),
                                                    115 + 1 + otherscale),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             WhiteColor);
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(warning,
                                             ImVec2(width / 2 - 105 - (otherscale * 2),
                                                    60 + 15 - otherscale + otherscale),
                                             ImVec2(width / 2 - 145 - (otherscale * 3),
                                                    115 + 1 + otherscale),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             WhiteColor);

                            if (botCount + playerCount < 10) {
                                //DrawTextCxy2(width / 2 - strlen(getString) - 2 - (otherscale / 4),
                                //             77, BlackColor, 20 + otherscale, getString);
                                DrawTextCxy2(width / 2 - 88 - strlen(Str.c_str()) - otherscale - otherscale,
                                             77, WhiteColor, 35 + otherscale, Str.c_str());
                            } else {
                                //DrawTextCxy2(width / 2 - strlen(getString) - 4 - (otherscale / 4),
                                //             77, BlackColor, 20 + otherscale, getString);
                                DrawTextCxy2(width / 2 - 88 - strlen(Str.c_str()) - otherscale - otherscale,
                                             77, WhiteColor, 35 + otherscale, Str.c_str());
                            }
                        } else {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(clear0,
                                             ImVec2(width / 2 + 110 + (otherscale * 3),
                                                    60 + 15 - otherscale + otherscale),
                                             ImVec2(width / 2 - 110 - (otherscale * 3),
                                                    105 + 1 + otherscale),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             WhiteColor);
                            DrawTextCxy2(width / 2 - strlen("CLEAR") - 30 - otherscale, 77, WhiteColor,
                                         25 + otherscale, "CLEAR");
                        }
                    }
                    //Grenade
                    if (espGeneric[10]) {
                        for (int i = 0; i < grenadeCount; i++) {
                            //DrawTextAlertGrenade
                            DrawTextCxy2(
                                    width / 2 - strlen("Warning!!!") - 55 - otherscale - otherscale,
                                    120 + otherscale,
                                    RedColor,
                                    30 + otherscale, "Warning!!!");
                            if (response.Grenade[i].Location.z != 1.0f) {
                                if (response.Grenade[i].type == 1) {
                                    //DrawTextGrenade
                                    DrawTextCxy2(
                                            response.Grenade[i].Location.x - strlen("Grenade") -
                                            18 - otherscale - otherscale,
                                            response.Grenade[i].Location.y - 20 - otherscale,
                                            RedColor, 15 + otherscale, "Grenade");
                                    DrawCircleFilled(response.Grenade[i].Location.x,
                                                     response.Grenade[i].Location.y,
                                                     4, RedColor);
                                } else if (response.Grenade[i].type == 2) {
                                    //DrawTextGrenade
                                    DrawTextCxy2(
                                            response.Grenade[i].Location.x - strlen("Molotove") -
                                            18 - otherscale - otherscale,
                                            response.Grenade[i].Location.y - 20 - otherscale,
                                            RedColor, 15 + otherscale, "Molotove");
                                    DrawCircleFilled(response.Grenade[i].Location.x,
                                                     response.Grenade[i].Location.y,
                                                     4, RedColor);
                                } else if (response.Grenade[i].type == 3) {
                                    //DrawTextGrenade
                                    DrawTextCxy2(
                                            response.Grenade[i].Location.x - strlen("Stunk") - 16 -
                                            otherscale,
                                            response.Grenade[i].Location.y - 20 - otherscale,
                                            RedColor, 15 + otherscale, "Stunk");
                                    DrawCircleFilled(response.Grenade[i].Location.x,
                                                     response.Grenade[i].Location.y,
                                                     4, RedColor);
                                } else {
                                    //DrawTextMolotove
                                    DrawTextCxy2(
                                            response.Grenade[i].Location.x - strlen("Smoke") - 16 -
                                            otherscale,
                                            response.Grenade[i].Location.y - 20 - otherscale,
                                            RedColor, 15 + otherscale, "Smoke");
                                    DrawCircleFilled(response.Grenade[i].Location.x,
                                                     response.Grenade[i].Location.y,
                                                     4, RedColor);
                                }
                            }
                        }
                    }
                    //vehicle
                    for (int i = 0; i < vehicleCount; i++) {
                        if (response.Vehicles[i].Location.z != 1.0f) {
                            //DrawText
                            //LOGE("ITEMNames=%s", response.Vehicles[i].VehicleName);
                            VehicleCheck(vehicleClr, vehicle, response.Vehicles[i].VehicleName,
                                         response.Vehicles[i].Distance,
                                         vehicleequals, vehiclereturn,
                                         response.Vehicles[i].Location.x,
                                         response.Vehicles[i].Location.y - vertical, otherscale);
                        }
                    }
                    //ItemList
                    for (int i = 0; i < itemCount; i++) {
                        if (response.Items[i].Location.z != 1.0f) {
                            //DrawText
                            //LOGE("ITEMNames=%s", response.Items[i].ItemName);
                            itemCheck(ammoClr, 6, ammo, response.Items[i].ItemName,
                                      response.Items[i].Distance,
                                      ammoequal, ammoreturn, response.Items[i].Location.x,
                                      response.Items[i].Location.y - vertical, otherscale);
                            itemCheck(weaponClr, 47, weapon, response.Items[i].ItemName,
                                      response.Items[i].Distance,
                                      weaponequals, weaponreturn, response.Items[i].Location.x,
                                      response.Items[i].Location.y - vertical, otherscale);
                            itemCheck(armorClr, 4, armor, response.Items[i].ItemName,
                                      response.Items[i].Distance,
                                      armorequals, armorreturn, response.Items[i].Location.x,
                                      response.Items[i].Location.y - vertical, otherscale);
                            itemCheck(healtClr, 5, healthing, response.Items[i].ItemName,
                                      response.Items[i].Distance,
                                      healtequals, healtreturn, response.Items[i].Location.x,
                                      response.Items[i].Location.y - vertical, otherscale);
                            itemCheck(miscClr, 26, misc, response.Items[i].ItemName,
                                      response.Items[i].Distance,
                                      miscequals, miscreturn, response.Items[i].Location.x,
                                      response.Items[i].Location.y - vertical, otherscale);
                        }
                    }//endItem
                } else {
                    ImGui::GetBackgroundDrawList()->
                            AddImage(clear0,
                                     ImVec2(width / 2 + 110 + (otherscale * 3),
                                            60 + 15 - otherscale + otherscale),
                                     ImVec2(width / 2 - 110 - (otherscale * 3),
                                            105 + 1 + otherscale),
                                     ImVec2(0.0f, 0.0f),
                                     ImVec2(1.0f, 1.0f),
                                     WhiteColor);
                    DrawTextCxy2(width / 2 - strlen("CLEAR") - 30 - otherscale, 77, WhiteColor,
                                 25 + otherscale, "CLEAR");
                }

                imguiMainWinEnd();
                swapBuffers();
                AutoFPS.SetFps(fpsCount);
                FPStime = AutoFPS.AotuFPS();
            }
        }
    }

    void VehicleCheck(ImColor clr[], bool ItemBool[], const char *ItemName, float ItemDistance, const char *ItemEqual[], const char *ItemReturn[], int x, int y, int scale){
        for (int i = 0; i < 21; ++i) {
            if (ItemBool[i]){
                if (isPartOf(ItemName, ItemEqual[i])){
                    sprintf(getString, "%s(%0.0f)",ItemReturn[i], ItemDistance);
                    //esp.DrawVehicleText(clr[i],buffer,i,Vec2(x, y - 10 - scale), size);
                    if (espGeneric[12]) {
                        if (isPartOf(ItemReturn[i], vehiclereturn[0])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[0],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], vehiclereturn[1]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[3]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[4]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[5]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[6]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[8]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[9]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[11]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[12]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[16]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[17]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[18]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[19])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[1],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], vehiclereturn[2])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[2],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], vehiclereturn[7])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[4],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], vehiclereturn[10]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[20])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[3],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], vehiclereturn[13])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[5],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], vehiclereturn[14]) ||
                            isPartOf(ItemReturn[i], vehiclereturn[15])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[6],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                    }
                    DrawTextCxy2(x - strlen(getString) - 30 - scale - scale, y - 10, clr[i], 15 + scale, getString);
                }
            }
        }
    }

    void itemCheck(ImColor clr[],int count, bool ItemBool[], const char *ItemName, float ItemDistance, const char *ItemEqual[], const char *ItemReturn[], int x, int y, int scale){
        for (int i = 0; i < count; ++i) {
            if (ItemBool[i]){
                if (isPartOf(ItemName, ItemEqual[i])){
                    sprintf(getString, "%s(%0.0f)",ItemReturn[i], ItemDistance);
                    //esp.DrawItemText(clr[i],buffer,Vec2(x, y - 10 - scale), size);
                    //esp.DrawFillCircle(Color().Green(),Vec2(x, y - 4),4);
                    if (espGeneric[12]) {
                        if (isPartOf(ItemReturn[i], miscreturn[1])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[8],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[16])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[10],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], armorreturn[0]) ||
                            isPartOf(ItemReturn[i], armorreturn[1])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[11],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[3]) ||
                            isPartOf(ItemReturn[i], miscreturn[4])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[12],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], armorreturn[2]) ||
                            isPartOf(ItemReturn[i], armorreturn[3])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[13],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[14])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[14],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[6]) ||
                            isPartOf(ItemReturn[i], weaponreturn[11]) ||
                            isPartOf(ItemReturn[i], weaponreturn[15]) ||
                            isPartOf(ItemReturn[i], weaponreturn[17]) ||
                            isPartOf(ItemReturn[i], weaponreturn[20]) ||
                            isPartOf(ItemReturn[i], weaponreturn[22]) ||
                            isPartOf(ItemReturn[i], weaponreturn[23]) ||
                            isPartOf(ItemReturn[i], weaponreturn[24]) ||
                            isPartOf(ItemReturn[i], weaponreturn[33]) ||
                            isPartOf(ItemReturn[i], weaponreturn[37])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[15],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[1]) ||
                            isPartOf(ItemReturn[i], weaponreturn[2]) ||
                            isPartOf(ItemReturn[i], weaponreturn[3]) ||
                            isPartOf(ItemReturn[i], weaponreturn[4]) ||
                            isPartOf(ItemReturn[i], weaponreturn[13]) ||
                            isPartOf(ItemReturn[i], weaponreturn[18])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[16],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[41]) ||
                            isPartOf(ItemReturn[i], weaponreturn[42]) ||
                            isPartOf(ItemReturn[i], weaponreturn[43]) ||
                            isPartOf(ItemReturn[i], weaponreturn[45])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[17],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[5]) ||
                            isPartOf(ItemReturn[i], weaponreturn[21]) ||
                            isPartOf(ItemReturn[i], weaponreturn[28]) ||
                            isPartOf(ItemReturn[i], weaponreturn[32]) ||
                            isPartOf(ItemReturn[i], weaponreturn[38])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[18],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[46])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[19],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[0])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[20],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], healtreturn[0]) ||
                            isPartOf(ItemReturn[i], healtreturn[1]) ||
                            isPartOf(ItemReturn[i], healtreturn[2]) ||
                            isPartOf(ItemReturn[i], healtreturn[3]) ||
                            isPartOf(ItemReturn[i], healtreturn[4])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[22],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[16])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[21],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], weaponreturn[29])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[23],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], ammoreturn[1]) ||
                            isPartOf(ItemReturn[i], ammoreturn[3]) ||
                            isPartOf(ItemReturn[i], ammoreturn[4]) ||
                            isPartOf(ItemReturn[i], ammoreturn[5])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[24],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[24])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[25],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[25])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[26],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[5]) ||
                            isPartOf(ItemReturn[i], miscreturn[6]) ||
                            isPartOf(ItemReturn[i], miscreturn[7])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[27],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[8]) ||
                            isPartOf(ItemReturn[i], miscreturn[9]) ||
                            isPartOf(ItemReturn[i], miscreturn[10])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[29],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[11]) ||
                            isPartOf(ItemReturn[i], miscreturn[12]) ||
                            isPartOf(ItemReturn[i], miscreturn[13])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[28],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                        if (isPartOf(ItemReturn[i], miscreturn[19]) ||
                            isPartOf(ItemReturn[i], miscreturn[20]) ||
                            isPartOf(ItemReturn[i], miscreturn[21])) {
                            ImGui::GetBackgroundDrawList()->
                                    AddImage(vec[30],
                                             ImVec2(x - 100 + 80, y - 45),
                                             ImVec2(x - 70 + 80, y - 15),
                                             ImVec2(0.0f, 0.0f),
                                             ImVec2(1.0f, 1.0f),
                                             ImColor(1.0f, 1.0f, 1.0f, 1.0f));
                        }
                    }
                    DrawTextCxy2(x - strlen(getString) - 30 - scale - scale, y - 10, clr[i], 15 + scale, getString);
                }
            }
        }
    }

    void getWeapon(ImColor clr, int id, int x, int y, int scale){
        for (int i = 0; i < 45; ++i) {
            if (id == EnemyweaponId[i]){
                DrawTextCxy2(x - strlen(Enemyweapon[i]) - 10 - scale, y, clr, 15 + scale, Enemyweapon[i]);
            }
        }
    }

    ImTextureID getFlags(const char *flagsname){
        for (int i = 0; i < 239; ++i) {
            if (isPartOf(flagsname, FlagsNames[i])) {
                return flags[i];
            }
        }
    }

    void getName(const char *name, int x, int y, int kode, int scale){
        if (kode == 1) {
            DrawTextCxy2(x + strlen(name) - 50 - scale - scale,
                         y - 57 - vertical - scale - (scale),
                         WhiteColor, 15 + scale, name);
        } else {
            DrawTextCxy2(x + strlen(name) - 50 - scale - scale,
                         y - 37 - vertical - scale - (scale * 2),
                         WhiteColor, 15 + scale, name);
        }
    }

    std::string realname(std::string name)
    {
        char getvec[100];
        std::vector<int> vec;
        std::stringstream ss(name);
        for(int i; ss >>i;){
            vec.push_back(i);
            if (ss.peek()==':')
                ss.ignore();
        }
        //int nameint[10];
        std::vector<char> nameint(10);
        for(std::size_t i = 0; i < 11; i++){
            if (i<11){
                nameint[i] = static_cast<char>(vec[i]);
            }
        }
        std::string realname (nameint.begin(),nameint.end());
        //char str[sizeof(nameint) + 1];
        //memcpy(str, nameint, sizeof(vec));
        //str[sizeof(nameint)] = '\0';
        //sprintf(getString, "%s", str);
        //LOGE("Name = > %s\n", getString);
        return realname;
    }

    //std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
    //std::chrono::system_clock::time_point b = std::chrono::system_clock::now();

    void EglThread() {
        initEgl();
        initDraw();

        AutoFPS.SetFps(fpsCount);
        AutoFPS.AotuFPS_init(1);
        AutoFPS.setAffinity();

        input->initImguiIo(io);
        input->setImguiContext(g);
        input->setwin(g_window);

        while (!isDestroy) {

            if (isChage) {
                glViewport(0, 0, surfaceWidth, surfaceHigh);
                isChage = false;
            }
            clearBuffers();
            imguiMainWinStart();
            DrawWindow();
            drawGL();
            imguiMainWinEnd();
            swapBuffers();
            AutoFPS.SetFps(fpsCount);
            FPStime = AutoFPS.AotuFPS();
            //m_fps.Update();
        }
    }

    //menuList

    void loadItemFunFromDisk(){
        readDataColorLoop2(vehicle, Dirpatch, "vehicles.ini", "vehiclesClr.ini", sizeof(vehicle), vehicleClr);
        readDataColorLoop2(ammo, Dirpatch, "ammos.ini", "ammosClr.ini", sizeof(ammo), ammoClr);
        readDataColorLoop2(weapon, Dirpatch, "weapon.ini", "weaponClr.ini", sizeof(weapon), weaponClr);
        readDataColorLoop2(armor, Dirpatch, "armors.ini", "armorsClr.ini", sizeof(armor), armorClr);
        readDataColorLoop2(healthing, Dirpatch, "health.ini", "healthClr.ini", sizeof(healthing), healtClr);
        readDataColorLoop2(misc, Dirpatch, "misc.ini", "miscClr.ini", sizeof(misc), miscClr);
        //readDataColorLoop2(espGeneric, Dirpatch, "espGenerics.ini", "espGenericsClr.ini", sizeof(espGeneric), espClr);
    }

    void LoadFuncFromDisk(){
        fpsCount = getInt(Dirpatch, "first.ini", 1);
        fpsCheck = getInt(Dirpatch, "first.ini", 2);
        espGeneric[0] = getInt(Dirpatch, "first.ini", 3);
        espGeneric[1] = getInt(Dirpatch, "first.ini", 4);
        espGeneric[2] = getInt(Dirpatch, "first.ini", 5);
        espGeneric[3] = getInt(Dirpatch, "first.ini", 6);
        espGeneric[4] = getInt(Dirpatch, "first.ini", 7);
        espGeneric[5] = getInt(Dirpatch, "first.ini", 8);
        espGeneric[6] = getInt(Dirpatch, "first.ini", 9);
        espGeneric[7] = getInt(Dirpatch, "first.ini", 10);
        espGeneric[8] = getInt(Dirpatch, "first.ini", 11);
        espGeneric[9] = getInt(Dirpatch, "first.ini", 12);
        espGeneric[10] = getInt(Dirpatch, "first.ini", 13);
        espGeneric[11] = getInt(Dirpatch, "first.ini", 14);
        boxStyle = getInt(Dirpatch, "first.ini", 15);
        scale = getInt(Dirpatch, "first.ini", 16);
        aimmode = getInt(Dirpatch, "first.ini", 17);
        options.aimbotmode = getInt(Dirpatch, "first.ini", 18);
        aimprior = getInt(Dirpatch, "first.ini", 19);
        options.priority = getInt(Dirpatch, "first.ini", 20);
        aimstate = getInt(Dirpatch, "first.ini", 21);
        options.aimingState = getInt(Dirpatch, "first.ini", 22);
        options.pour = getInt(Dirpatch, "first.ini", 23);
        AimToBot = getInt(Dirpatch, "first.ini", 24);
        options.aimIgnoreBot = AimToBot;
        fovScreen = getInt(Dirpatch, "first.ini", 25);
        options.aimingRange = getInt(Dirpatch, "first.ini", 26);
        //options.isOrientation = getInt(Dirpatch, "first.ini", 27);
        //AdjustCamera = getInt(Dirpatch, "first.ini", 28);
        //aimposx = getInt(Dirpatch, "first.ini", 29);
        //aimposy = getInt(Dirpatch, "first.ini", 30);
        /*if (options.isOrientation) {
            options.touchPosX = getInt(Dirpatch, "first.ini", 29);
        } else {
            options.touchPosX = -getInt(Dirpatch, "first.ini", 29);
        }
        if (options.isOrientation) {
            options.touchPosY = getInt(Dirpatch, "first.ini", 30);
        } else {
            options.touchPosY = -getInt(Dirpatch, "first.ini", 30);
        }*/
        aimspeed = getInt(Dirpatch, "first.ini", 31);
        options.swipeSpeed = 108.0f - getFloat(Dirpatch, "first.ini", 31);
        RecoilADS = getBool(Dirpatch, "first.ini", 32);
        options.isRecoil = RecoilADS;
        options.decline = getFloat(Dirpatch, "first.ini", 33);
        lockAimpost = getInt(Dirpatch, "first.ini", 34);
        touchspeed = getInt(Dirpatch, "first.ini", 35);
        options.touchSpeed = getInt(Dirpatch, "first.ini", 35);
        AutoShoot = getInt(Dirpatch, "first.ini", 36);
        AutoShoots = AutoShoot;
        shootLoopType = getInt(Dirpatch, "first.ini", 37);
        options.shootLoopType = shootLoopType;
        AutoShootTime = getInt(Dirpatch, "first.ini", 39);
        options.shootLoopTime = AutoShootTime;
        shootLoopRecoil = getInt(Dirpatch, "first.ini", 40);
        options.shootLoopRecoil = shootLoopRecoil;
        aimObj = getInt(Dirpatch, "first.ini", 41);
        options.aimObj = aimObj;
        options.wideval = 90;
        espGeneric[12] = getInt(Dirpatch, "first.ini", 42);
    }

    void setinput(ImguiAndroidInput *input_) {
        input = input_;
    }

    void DrawWindow() {
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowBgAlpha(0.8);
        ImGui::GetStyle().WindowRounding = 15.0f;
        ImGui::GetStyle().ChildRounding = 5.0f;
        ImGui::GetStyle().FrameRounding = 5.0f;
        ImGui::GetStyle().GrabRounding = 5.0f;
        ImGui::GetStyle().PopupRounding = 15.0f;
        ImGui::GetStyle().ScrollbarRounding = 5.0f;
        style->WindowBorderSize = 0;
        style->FramePadding = ImVec2(15, 15);
        style->ItemSpacing = ImVec2( 10, 10);
        style->ItemInnerSpacing = ImVec2( 10, 10);
        style->IndentSpacing = 50.0f;
        style->ItemInnerSpacing = ImVec2( 10, 10);
        style->ColumnsMinSpacing = 50.0f;

        input->ItemActive  = ImGui::IsAnyItemActive();
        input->ItemHovered = ImGui::IsAnyItemHovered();
        input->ItemFocused = ImGui::IsAnyItemFocused();

        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        style->WindowMinSize = ImVec2(1000, input->winWidth * 0.75);
        ImVec4* colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_TitleBg] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_TitleBgActive] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 255, 255, 180);

        colors[ImGuiCol_Button] = ImColor(30,144,255, 180);
        colors[ImGuiCol_ButtonActive] = ImColor(30,144,255, 180);
        colors[ImGuiCol_ButtonHovered] = ImColor(30,144,255, 180);

        colors[ImGuiCol_Separator] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_SeparatorActive] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_SeparatorHovered] = ImColor(255, 255, 255, 180);

        colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_FrameBgActive] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_FrameBgHovered] = ImColor(255, 255, 255, 180);

        colors[ImGuiCol_Header] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_HeaderActive] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_HeaderHovered] = ImColor(255, 255, 255, 180);

        colors[ImGuiCol_TabHovered] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_TabActive] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_TabUnfocused] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_TabUnfocusedActive] = ImColor(255, 255, 255, 180);
        colors[ImGuiCol_Tab] = ImColor(255, 255, 255, 180);

        colors[ImGuiCol_CheckMark] = ImColor(30,144,255, 180);
        colors[ImGuiCol_SliderGrab] = ImColor(30,144,255, 180);
        colors[ImGuiCol_SliderGrabActive] = ImColor(30,144,255, 180);

        colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
        colors[ImGuiCol_ScrollbarGrab] = ImColor(102, 102, 102, 180);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(102, 102, 102, 180);
        colors[ImGuiCol_ScrollbarGrabActive] = ImColor(102, 102, 102, 180);

        colors[ImGuiCol_WindowBg] = ImColor(255, 255, 255, 255);
        colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0, 0);
        colors[ImGuiCol_PopupBg] = ImColor(0, 0, 0, 0);

        colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
        colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 0);

        colors[ImGuiCol_Text] = ImColor(0, 0, 0, 255);
        colors[ImGuiCol_MenuBarBg] = ImColor(255, 255, 255, 220);

        /*FrameHeight = ImGui::GetFrameHeight();

        if (input->Scrollio&&!input->Activeio) {
            input->funScroll(g->WheelingWindow ? g->WheelingWindow : g->HoveredWindow);
        }*/
        if (EspView) {
            if (ImGui::Begin("STARKSKILLZ", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
                input->winio = ImGui::IsWindowCollapsed();
                input->winWidth = ImGui::GetWindowWidth();
                input->winHeight = ImGui::GetWindowHeight();
                input->g_window = g_window = ImGui::GetCurrentWindow();
                //ImGui::SetWindowSize({900, 700}, ImGuiCond_Once);
                //ImGui::SetWindowPos({0, 0}, ImGuiCond_Once);
                LeftListWin(-1, -1);
            }
            ImRect titleBarRect = g_window->TitleBarRect();
            ImGui::PushClipRect(titleBarRect.Min, titleBarRect.Max, false);
            ImGui::SetCursorPos(ImVec2(input->winWidth * 0.86f, 0.0f));
            ImGui::Image(vec[9], ImVec2(150, 65));
            ImGui::PopClipRect();
            ImGui::End();
        }
    }

    GLuint getImageFromDisk(std::string filename){
        int my_image_width = 0;
        int my_image_height = 0;
        GLuint my_image_texture = 0;
        std::string patch = std::string(Dirpatch + ".image/" + filename);
        LoadTextureFromFile(patch.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        return my_image_texture;
    }

    GLuint getFlagFromDisk(std::string filename){
        int my_image_width = 0;
        int my_image_height = 0;
        GLuint my_image_texture = 0;
        std::string patch = std::string(Dirpatch + "flag/" + filename);
        LoadTextureFromFile(patch.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        return my_image_texture;
    }

    void LeftListWin(float width, float height) {
        ImGui::Columns(2);
        ImGui::SetColumnOffset(1, 180);
        {
            if (Layout("leftmenu", 180, -1)) {

                ImVec2 size = ImVec2(70, 70);
                ImVec2 uv0 = ImVec2(0.0f, 0.0f);
                ImVec2 uv1 = ImVec2(1.0f, 1.0f);
                ImVec2 uv2 = ImVec2(30.0f, 25.0f);
                ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                ImVec4 tint_col = imguipp::to_vec4(0, 0, 0, 255);

                ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);
                if (ImGui::ImageButtonEx(1,displayESP, size, uv0, uv1, uv2, bg_col, tint_col))
                    Settings::Tab = 1;

                ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
                if (ImGui::ImageButtonEx(2,itemESP, size, uv0, uv1, uv2, bg_col, tint_col))
                    Settings::Tab = 2;

                ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 3 ? active : inactive);
                if (ImGui::ImageButtonEx(3,aimESP, size, uv0, uv1, uv2, bg_col, tint_col))
                    Settings::Tab = 3;

                ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 4 ? active : inactive);
                if (ImGui::ImageButtonEx(4,fireEsp, size, uv0, uv1, uv2, bg_col, tint_col))
                    Settings::Tab = 4;

                ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 5 ? active : inactive);
                if (ImGui::ImageButtonEx(5,memory, size, uv0, uv1, uv2, bg_col, tint_col))
                    Settings::Tab = 5;
            }
            LayoutEnd();
        } ImGui::NextColumn();
        {
            LOGE("tab=%d", Settings::Tab);
            if (Settings::Tab == 1) {
                ListItemPage_0();
            } else if (Settings::Tab == 2) {
                ListItemPage_2();
            } else if (Settings::Tab == 3) {
                ListItemPage_1();
            } else if (Settings::Tab == 4) {
                ListItemPage_3();
            } else if (Settings::Tab == 5) {
                ListItemPage_4();
            } else {
                ListItemPage_0();
            }
        }
    }

    bool Layout(char *name, float width, float height) {
        return ImGui::BeginChild(name, ImVec2(width, height));
    }

    void LayoutEnd() {
        ImGui::EndChild();
    }

    void ListItemPage_0() {

        if (Layout("page1", input->winWidth * 0.79f, -1)) {

            ImGui::Text("Display");

            ImGui::Text("Render framerate");
            if(ImGui::RadioButton("60 FPS", &fpsCheck, 0.0)){
                fpsCount = 60;
                writeInt(Dirpatch, "first.ini", 60, 0);
                writeInt(Dirpatch, "first.ini", 0, 1);
            }
            if(ImGui::RadioButton("90 FPS", &fpsCheck, 1.0)){
                fpsCount = 90;
                writeInt(Dirpatch, "first.ini", 90, 0);
                writeInt(Dirpatch, "first.ini", 1, 1);
            }
            if(ImGui::RadioButton("120 FPS", &fpsCheck, 2.0)){
                fpsCount = 120;
                writeInt(Dirpatch, "first.ini", 120, 0);
                writeInt(Dirpatch, "first.ini", 2, 1);
            }
            if(ImGui::RadioButton("240 FPS", &fpsCheck, 4.0)){
                fpsCount = 240;
                writeInt(Dirpatch, "first.ini", 240, 0);
                writeInt(Dirpatch, "first.ini", 4, 1);
            }

            ImGui::Text("\nEsp generic adjustment");
            if (Layout("row0", input->winWidth * 0.30f, 470.0f)) {
                if (ImGui::Checkbox("Health", &espGeneric[0])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[0], 2);
                }
                if (ImGui::Checkbox("Name", &espGeneric[1])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[1], 3);
                }
                if (ImGui::Checkbox("TeamID", &espGeneric[2])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[2], 4);
                }
                if (ImGui::Checkbox("Distance", &espGeneric[3])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[3], 5);
                }
                if (ImGui::Checkbox("Red dots", &espGeneric[4])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[4], 6);
                }
                if (ImGui::Checkbox("Skeletons", &espGeneric[5])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[5], 7);
                }
            }
            LayoutEnd();

            ImGui::SameLine();
            if (Layout("row1", input->winWidth * 0.30f, 470.0f)) {
                if (ImGui::Checkbox("Weapon", &espGeneric[6])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[6], 8);
                }
                if (ImGui::Checkbox("Enemy count", &espGeneric[7])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[7], 9);
                }
                if (ImGui::Checkbox("Radar line", &espGeneric[8])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[8], 10);
                }
                if (ImGui::Checkbox("Edge warning", &espGeneric[9])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[9], 11);
                }
                if (ImGui::Checkbox("Grenade alert", &espGeneric[10])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[10], 12);
                }
                if (ImGui::Checkbox("Nations flags", &espGeneric[11])) {
                    writeInt(Dirpatch, "first.ini", espGeneric[11], 13);
                }
            }
            LayoutEnd();

            ImGui::Text("Bounding box display mode");
            if(ImGui::RadioButton("Off", &boxStyle, 0.0)){
                boxStyle = 0;
                writeInt(Dirpatch, "first.ini", boxStyle, 14);
            }
            if(ImGui::RadioButton("Legacy", &boxStyle, 1.0)){
                writeInt(Dirpatch, "first.ini", boxStyle, 14);
                boxStyle = 1;
            }
            if(ImGui::RadioButton("Precise", &boxStyle, 2.0)){
                writeInt(Dirpatch, "first.ini", boxStyle, 14);
                boxStyle = 2;
            }

            ImGui::Text("\nEsp scaling");
            ImGui::Text("Adjust the size of overly UI elements");
            if(ImGui::SliderInt("Scale", &scale, 0, 300, "%d")){
                writeInt(Dirpatch, "first.ini", scale, 15);
            }
        }
        LayoutEnd();
    }

    void ListItemPage_1() {
        if (Layout("page2", input->winWidth * 0.79f, -1)) {

            ImGui::Text("Controls");

            ImGui::Text("Aimbot Mode");
            if(ImGui::RadioButton("Touch stimulation (recommended)", &aimObj, 0.0)){
                options.aimObj = 0;
                aimObj = 0;
                writeInt(Dirpatch, "first.ini", aimObj, 40);
            }
            if (ImGui::RadioButton("Memory (High risk)", &aimObj, 1.0)) {
                options.aimObj = 1;
                aimObj = 1;
                writeInt(Dirpatch, "first.ini", aimObj, 40);
            }
            if(ImGui::RadioButton("Off", &aimObj, 2.0)){
                options.aimObj = 2;
                aimObj = 2;
                writeInt(Dirpatch, "first.ini", aimObj, 40);
            }

            if (aimObj == 1 || aimObj == 0) {
                ImGui::Text("");
                if (ToggleButton("lockAimPos", &lockAimpost)){
                    writeInt(Dirpatch, "first.ini", lockAimpost, 33);
                }
                ImGui::SameLine();
                ImGui::Text("Lock aimbot button position");

                ImGui::Text("\nLock body parts on enemy player.");
                if(ImGui::RadioButton("Head", &aimmode, 0.0)){
                    options.aimbotmode = 1;
                    writeInt(Dirpatch, "first.ini", aimmode, 16);
                    writeInt(Dirpatch, "first.ini", 1, 17);
                }
                if(ImGui::RadioButton("Chest", &aimmode, 1.0)){
                    options.aimbotmode = 2;
                    writeInt(Dirpatch, "first.ini", aimmode, 16);
                    writeInt(Dirpatch, "first.ini", 2, 17);
                }
                if(ImGui::RadioButton("Waist", &aimmode, 2.0)){
                    options.aimbotmode = 3;
                    writeInt(Dirpatch, "first.ini", aimmode, 16);
                    writeInt(Dirpatch, "first.ini", 3, 17);
                }

                ImGui::Text("\nTarget selection mode");
                if(ImGui::RadioButton("Crosshair", &aimprior, 0.0)){
                    options.priority = 1;
                    writeInt(Dirpatch, "first.ini", aimprior, 18);
                    writeInt(Dirpatch, "first.ini", 1, 19);
                }
                if(ImGui::RadioButton("Distance", &aimprior, 1.0)){
                    options.priority = 0;
                    writeInt(Dirpatch, "first.ini", aimprior, 18);
                    writeInt(Dirpatch, "first.ini", 0, 19);
                }

                ImGui::Text("\nWhen aimbot is active.");
                if(ImGui::RadioButton("Always on", &aimstate, 0.0)){
                    options.aimingState = 3;
                    writeInt(Dirpatch, "first.ini", aimstate, 20);
                    writeInt(Dirpatch, "first.ini", 3, 21);
                }
                if(ImGui::RadioButton("Aiming down sight", &aimstate, 1.0)){
                    options.aimingState = 1;
                    writeInt(Dirpatch, "first.ini", aimstate, 20);
                    writeInt(Dirpatch, "first.ini", 1, 21);
                }
                if(ImGui::RadioButton("Firing", &aimstate, 2.0)){
                    options.aimingState = 2;
                    writeInt(Dirpatch, "first.ini", aimstate, 20);
                    writeInt(Dirpatch, "first.ini", 2, 21);
                }

                ImGui::Text("");
                if (ToggleButton("pour", &options.pour)){
                    writeInt(Dirpatch, "first.ini", options.pour, 22);
                }
                ImGui::SameLine();
                ImGui::Text("Locking knocked out player.\nallow aim  to lock player knocked out");

                ImGui::Text("");
                if (ToggleButton("aimtobot", &AimToBot)){
                    options.aimIgnoreBot = AimToBot;
                    writeInt(Dirpatch, "first.ini", AimToBot, 23);
                }
                ImGui::SameLine();
                ImGui::Text("Ignore AI player.\ndisable aim to lock player AI");

                ImGui::Text("");
                if (ToggleButton("fovScreen", &fovScreen)){
                    writeInt(Dirpatch, "first.ini", fovScreen, 24);
                }
                ImGui::SameLine();
                ImGui::Text("Show FOV range on screen.");

                ImGui::Text("");
                ImGui::Text("Set FOV size\naim will only lock enemies within FOV\nrange.");
                if(ImGui::SliderInt("Fov", &options.aimingRange, 200, 1200, "%d")){
                    writeInt(Dirpatch, "first.ini", options.aimingRange, 25);
                }

                /*ImGui::Text("");
                if (ToggleButton("inversion", &options.isOrientation)){
                    writeInt(Dirpatch, "first.ini", options.isOrientation, 26);
                }
                ImGui::SameLine();
                ImGui::Text("Reverse touch position\ntrun on this when screen orientation\nhas changed.");*/

                /*ImGui::Text("");
                ImGui::Text("Set (X) touch position.");
                if(ImGui::SliderInt("X", &aimposx, 0, -1200, "%d")){
                    options.touchPosX = aimposx;
                    writeInt(Dirpatch, "first.ini", aimposx, 28);
                }

                ImGui::Text("");
                ImGui::Text("Set (Y) touch position.");
                if(ImGui::SliderInt("Y", &aimposy, -500, 500, "%d")){
                    options.touchPosY = aimposy;
                    writeInt(Dirpatch, "first.ini", aimposy, 29);
                }*/

                if (options.aimObj == 0) {
                    ImGui::Text("");
                    if (ToggleButton("adjustcamera", &AdjustCamera)) {
                        writeInt(Dirpatch, "first.ini", AdjustCamera, 27);
                    }
                    ImGui::SameLine();
                    ImGui::Text("Adjust touch position");

                    ImGui::Text("");
                    ImGui::Text("Swipe speed");
                    ImGui::Text("adjust touch when moving to enemy.\nvalue too high can causes shaking.");
                    if (ImGui::SliderFloat("Swipe", &aimspeed, 90.0f, 100.0f, "%.1f")) {
                        options.swipeSpeed = 108.0f - aimspeed;
                        writeFLoat(Dirpatch, "first.ini", aimspeed, 30);
                    }

                    ImGui::Text("");
                    ImGui::Text("Touch time");
                    ImGui::Text("reduce shake on swipe speed. value\ntoo high can cause slowly.");
                    if (ImGui::SliderInt("Touch", &touchspeed, 20000, 30000, "%d")) {
                        options.touchSpeed = touchspeed;
                        writeInt(Dirpatch, "first.ini", touchspeed, 34);
                    }

                    /*ImGui::Text("");
                    if (ToggleButton("recoil", &RecoilADS)){
                        options.isRecoil = RecoilADS;
                        writeInt(Dirpatch, "first.ini", RecoilADS, 31);
                    }
                    ImGui::SameLine();
                    ImGui::Text("Recoil kick ADS\nused recoil based on player camera manager");*/
                }

                ImGui::Text("");
                ImGui::Text("Recoil compensation");
                ImGui::Text("adjust recoil when firing.");
                if(ImGui::SliderFloat("Recoil", &options.decline, -50.0f, 100.0f, "%.1f")){
                    writeFLoat(Dirpatch, "first.ini", options.decline, 32);
                }
            }
        }
        LayoutEnd();
    }

    void ListItemPage_3() {
        if (Layout("page1", input->winWidth * 0.79f, -1)) {
            ImGui::Text("Advanced");
            ImGui::Text("Automatic Firing");
            if(ImGui::RadioButton("Touch firing", &AutoShoots, 1.0)){
                AutoShoot = 1;
                writeInt(Dirpatch, "first.ini", 1, 35);
            }
            if(ImGui::RadioButton("Off", &AutoShoots, 0.0)){
                AutoShoot = 0;
                writeInt(Dirpatch, "first.ini", 0, 35);
            }

            /*if (ToggleButton("Autoshoot", &AutoShoot)){
                writeInt(Dirpatch, "first.ini", AutoShoot, 35);
            }
            ImGui::SameLine();
            ImGui::Text("Enable function");*/

            ImGui::Text("");
            if(ImGui::RadioButton("Tapping", &shootLoopType, 0.0)){
                options.shootLoopType = 0;
                writeInt(Dirpatch, "first.ini", shootLoopType, 36);
            }
            if(ImGui::RadioButton("Hold", &shootLoopType, 1.0)){
                options.shootLoopType = 1;
                writeInt(Dirpatch, "first.ini", shootLoopType, 36);
            }

            ImGui::Text("");
            if (ToggleButton("Autoshootpos", &AutoShootPos)){
                writeInt(Dirpatch, "first.ini", AutoShootPos, 37);
            }
            ImGui::SameLine();
            ImGui::Text("Adjust auto shoot position");

            if (options.shootLoopType == 0) {
                ImGui::Text("");
                ImGui::Text("Auto shoot loop time");
                if (ImGui::SliderInt("Time", &AutoShootTime, 30000, 45000, "%d")) {
                    options.shootLoopTime = AutoShootTime;
                    writeInt(Dirpatch, "first.ini", AutoShootTime, 38);
                }
                ImGui::Text("");
                ImGui::Text("Auto shoot tap recoil");
                if (ImGui::SliderInt("Tap", &shootLoopRecoil, 0.0f, 200.0f, "%d")) {
                    options.shootLoopRecoil = shootLoopRecoil;
                    writeInt(Dirpatch, "first.ini", shootLoopRecoil, 39);
                }
            }
        }
    }

    void ListItemPage_4() {
        if (Layout("page1", input->winWidth * 0.79f, -1)) {
            ImGui::Text("Memory function (High Risk)");
            ImVec2 size = ImVec2(35, 35);
            ImVec2 uv0 = ImVec2(0.0f, 0.0f);
            ImVec2 uv1 = ImVec2(1.0f, 1.0f);
            ImVec2 uv2 = ImVec2(15.5f, 15.5f);
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            ImVec4 tint_col = imguipp::to_vec4(0, 0, 0, 255);

            ImGui::ImageButtonEx(6,warning, size, uv0, uv1, uv2, bg_col, tint_col);
            ImGui::SameLine();
            ImGui::Text("Use this function\nAt your own risk");

            ImGui::Text("Weapon");
            if (Layout("row2", input->winWidth * 0.35f, 220.0f)) {
                if (ImGui::Checkbox("Less recoil", &options.lessrecoil)){ }
                if (ImGui::Checkbox("Zero recoil", &options.zerorecoil)){ }
                if (ImGui::Checkbox("No Shake", &options.noshake)){ }
            }
            LayoutEnd();
            ImGui::SameLine();
            if (Layout("row3", input->winWidth * 0.35f, 220.0f)) {
                if (ImGui::Checkbox("Autogun fast shoot", &options.autofastshoot)){ }
                if (ImGui::Checkbox("Burstgun fast shoot", &options.burstfastshoot)){ }
                if (ImGui::Checkbox("Fast switch weapon", &options.fastswitchweapon)){ }
            }
            LayoutEnd();

            ImGui::Text("Weapon Hit");
            if (Layout("row4", input->winWidth * 0.35f, 220.0f)) {
                if (ImGui::Checkbox("Instant hit", &options.instanhit)){ }
                if (ImGui::Checkbox("Increase damage", &options.damage)){ }
                if (ImGui::Checkbox("Bullet spread", &options.bulletspread)){ }
            }
            LayoutEnd();
            ImGui::SameLine();
            if (Layout("row5", input->winWidth * 0.35f, 220.0f)) {
                if (ImGui::Checkbox("Hit X", &options.hitx)){ }
            }
            LayoutEnd();

            ImGui::Text("Player Speed");
            if (Layout("row6", input->winWidth * 0.35f, 220.0f)) {
                if (ImGui::Checkbox("Prone", &options.pronspeed)){ }
                if (ImGui::Checkbox("Swim", &options.swimspeed)){ }
                if (ImGui::Checkbox("Parachute", &options.parasutspeed)){ }
            }
            LayoutEnd();
            ImGui::SameLine();
            if (Layout("row7", input->winWidth * 0.35f, 220.0f)) {
                if (ImGui::Checkbox("Acceleration", &options.longjump)){ }
            }
            LayoutEnd();

            ImGui::Text("Player view");
            if (Layout("row8", input->winWidth * 0.79f, 150.0f)) {
                if (ImGui::Checkbox("Small crosshair", &options.smallcroshair)){ }
                if (ImGui::Checkbox("Wide view", &options.wideview)){ }
            }
            LayoutEnd();

            if (Layout("row9", input->winWidth * 0.79f, 220.0f)) {
                if (options.wideview) {
                    ImGui::Text("Wide value");
                    if (ImGui::SliderFloat("wide", &options.wideval, 90.0f, 140.0f, "%.1f")) {}

                    ImGui::Text("Scope value");
                    if (ImGui::SliderFloat("scope", &options.scopeval, 0.0f, 30.0f, "%.1f")) {}
                }
            }
            LayoutEnd();
        }
    }

    void ListItemPage_2() {
        if (Layout("vehicleCall", input->winWidth * 0.99f, -1)) {
            ImGui::Text("Item Types");
            ImGui::BeginGroup();
            ImGui::Text("");
            ImGui::SameLine();
            if(colorButton(" ", 1, ImColor(248,64,64, 255))){
                ColorSetting2(vehicle, Dirpatch, "vehiclesClr.ini", sizeof(vehicle), vehicleClr, ImColor(248,64,64, 255));
                ColorSetting2(ammo, Dirpatch, "ammosClr.ini", sizeof(ammo), ammoClr, ImColor(248,64,64, 255));
                ColorSetting2(weapon, Dirpatch, "weaponClr.ini", sizeof(weapon), weaponClr, ImColor(248,64,64, 255));
                ColorSetting2(armor, Dirpatch, "armorsClr.ini", sizeof(armor), armorClr, ImColor(248,64,64, 255));
                ColorSetting2(healthing, Dirpatch, "healthClr.ini", sizeof(healthing), healtClr, ImColor(248,64,64, 255));
                ColorSetting2(misc, Dirpatch, "miscClr.ini", sizeof(misc), miscClr, ImColor(248,64,64, 255));
            }
            ImGui::SameLine();
            if(colorButton("  ", 2, ImColor(96,248,96, 255))){
                ColorSetting2(vehicle, Dirpatch, "vehiclesClr.ini", sizeof(vehicle), vehicleClr, ImColor(96,248,96, 255));
                ColorSetting2(ammo, Dirpatch, "ammosClr.ini", sizeof(ammo), ammoClr, ImColor(96,248,96, 255));
                ColorSetting2(weapon, Dirpatch, "weaponClr.ini", sizeof(weapon), weaponClr, ImColor(96,248,96, 255));
                ColorSetting2(armor, Dirpatch, "armorsClr.ini", sizeof(armor), armorClr, ImColor(96,248,96, 255));
                ColorSetting2(healthing, Dirpatch, "healthClr.ini", sizeof(healthing), healtClr, ImColor(96,248,96, 255));
                ColorSetting2(misc, Dirpatch, "miscClr.ini", sizeof(misc), miscClr, ImColor(96,248,96, 255));
            }
            ImGui::SameLine();
            if(colorButton("   ", 3, ImColor(248,184,216, 255))){
                ColorSetting2(vehicle, Dirpatch, "vehiclesClr.ini", sizeof(vehicle), vehicleClr, ImColor(248,184,216, 255));
                ColorSetting2(ammo, Dirpatch, "ammosClr.ini", sizeof(ammo), ammoClr, ImColor(248,184,216, 255));
                ColorSetting2(weapon, Dirpatch, "weaponClr.ini", sizeof(weapon), weaponClr, ImColor(248,184,216, 255));
                ColorSetting2(armor, Dirpatch, "armorsClr.ini", sizeof(armor), armorClr, ImColor(248,184,216, 255));
                ColorSetting2(healthing, Dirpatch, "healthClr.ini", sizeof(healthing), healtClr, ImColor(248,184,216, 255));
                ColorSetting2(misc, Dirpatch, "miscClr.ini", sizeof(misc), miscClr, ImColor(248,184,216, 255));
            }
            ImGui::SameLine();
            if(colorButton("    ", 4, ImColor(248,248,88, 255))){
                ColorSetting2(vehicle, Dirpatch, "vehiclesClr.ini", sizeof(vehicle), vehicleClr, ImColor(248,248,88, 255));
                ColorSetting2(ammo, Dirpatch, "ammosClr.ini", sizeof(ammo), ammoClr, ImColor(248,248,88, 255));
                ColorSetting2(weapon, Dirpatch, "weaponClr.ini", sizeof(weapon), weaponClr, ImColor(248,248,88, 255));
                ColorSetting2(armor, Dirpatch, "armorsClr.ini", sizeof(armor), armorClr, ImColor(248,248,88, 255));
                ColorSetting2(healthing, Dirpatch, "healthClr.ini", sizeof(healthing), healtClr, ImColor(248,248,88, 255));
                ColorSetting2(misc, Dirpatch, "miscClr.ini", sizeof(misc), miscClr, ImColor(248,248,88, 255));
            }
            ImGui::SameLine();
            if(colorButton("     ", 5, ImColor(120,248,248, 255))){
                ColorSetting2(vehicle, Dirpatch, "vehiclesClr.ini", sizeof(vehicle), vehicleClr, ImColor(120,248,248, 255));
                ColorSetting2(ammo, Dirpatch, "ammosClr.ini", sizeof(ammo), ammoClr, ImColor(120,248,248, 255));
                ColorSetting2(weapon, Dirpatch, "weaponClr.ini", sizeof(weapon), weaponClr, ImColor(120,248,248, 255));
                ColorSetting2(armor, Dirpatch, "armorsClr.ini", sizeof(armor), armorClr, ImColor(120,248,248, 255));
                ColorSetting2(healthing, Dirpatch, "healthClr.ini", sizeof(healthing), healtClr, ImColor(120,248,248, 255));
                ColorSetting2(misc, Dirpatch, "miscClr.ini", sizeof(misc), miscClr, ImColor(120,248,248, 255));
            }
            ImGui::SameLine();
            if(colorButton("      ", 6, ImColor(255, 255, 255, 255))){
                ColorSetting2(vehicle, Dirpatch, "vehiclesClr.ini", sizeof(vehicle), vehicleClr, ImColor(255, 255, 255, 255));
                ColorSetting2(ammo, Dirpatch, "ammosClr.ini", sizeof(ammo), ammoClr, ImColor(255, 255, 255, 255));
                ColorSetting2(weapon, Dirpatch, "weaponClr.ini", sizeof(weapon), weaponClr, ImColor(255, 255, 255, 255));
                ColorSetting2(armor, Dirpatch, "armorsClr.ini", sizeof(armor), armorClr, ImColor(255, 255, 255, 255));
                ColorSetting2(healthing, Dirpatch, "healthClr.ini", sizeof(healthing), healtClr, ImColor(255, 255, 255, 255));
                ColorSetting2(misc, Dirpatch, "miscClr.ini", sizeof(misc), miscClr, ImColor(255, 255, 255, 255));
            }
            ImGui::SameLine();
            ImGui::Text("");
            ImGui::SameLine();
            if(ImGui::Checkbox("Image", &espGeneric[12])){
                writeInt(Dirpatch, "first.ini", espGeneric[12], 41);
            }
            ImGui::EndGroup();

            ImGui::Columns(2);
            ImGui::SetColumnOffset(1, input->winWidth * 0.22f);
            {
                if (Layout("leftmenu2", input->winWidth * 0.20f, -1)) {

                    ImGui::PushStyleColor(ImGuiCol_Button, Settings::ItemTab == 4 ? active : inactive);
                    if (ImGui::Button("Vehicle", ImVec2(input->winWidth * 0.15f, 80)))
                        Settings::ItemTab = 4;

                    ImGui::Spacing();
                    ImGui::PushStyleColor(ImGuiCol_Button, Settings::ItemTab == 5 ? active : inactive);
                    if (ImGui::Button("Ammo", ImVec2(input->winWidth * 0.15f, 80)))
                        Settings::ItemTab = 5;

                    ImGui::Spacing();
                    ImGui::PushStyleColor(ImGuiCol_Button, Settings::ItemTab == 6 ? active : inactive);
                    if (ImGui::Button("Weapon", ImVec2(input->winWidth * 0.15f, 80)))
                        Settings::ItemTab = 6;

                    ImGui::Spacing();
                    ImGui::PushStyleColor(ImGuiCol_Button, Settings::ItemTab == 7 ? active : inactive);
                    if (ImGui::Button("Armor", ImVec2(input->winWidth * 0.15f, 80)))
                        Settings::ItemTab = 7;

                    ImGui::Spacing();
                    ImGui::PushStyleColor(ImGuiCol_Button, Settings::ItemTab == 8 ? active : inactive);
                    if (ImGui::Button("Health", ImVec2(input->winWidth * 0.15f, 80)))
                        Settings::ItemTab = 8;

                    ImGui::Spacing();
                    ImGui::PushStyleColor(ImGuiCol_Button, Settings::ItemTab == 9 ? active : inactive);
                    if (ImGui::Button("Misc", ImVec2(input->winWidth * 0.15f, 80)))
                        Settings::ItemTab = 9;

                    ImGui::PopStyleColor(3);
                }
                LayoutEnd();
            } ImGui::NextColumn();
            {
                if (Settings::ItemTab == 4) {

                    if (ImGui::Button("All", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(vehicle, Dirpatch, "vehicles.ini", sizeof(vehicle), 1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("None", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(vehicle, Dirpatch, "vehicles.ini", sizeof(vehicle), 0);
                    }

                    if (Layout("leftmenu3", input->winWidth * 0.55f, -1)) {
                        vehicleCall();
                    }
                    LayoutEnd();
                } else if (Settings::ItemTab == 5) {

                    if (ImGui::Button("All", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(ammo, Dirpatch, "ammos.ini", sizeof(ammo), 1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("None", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(ammo, Dirpatch, "ammos.ini", sizeof(ammo), 0);
                    }

                    if (Layout("leftmenu4", input->winWidth * 0.55f, -1)) {
                        ammoCall();
                    }
                    LayoutEnd();
                } else if (Settings::ItemTab == 6) {

                    if (ImGui::Button("All", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(weapon, Dirpatch, "weapon.ini", sizeof(weapon), 1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("None", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(weapon, Dirpatch, "weapon.ini", sizeof(weapon), 0);
                    }

                    if (Layout("leftmenu5", input->winWidth * 0.55f, -1)) {
                        weaponCall();
                    }
                    LayoutEnd();
                } else if (Settings::ItemTab == 7) {

                    if (ImGui::Button("All", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(armor, Dirpatch, "armors.ini", sizeof(armor), 1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("None", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(armor, Dirpatch, "armors.ini", sizeof(armor), 0);
                    }

                    if (Layout("leftmenu6", input->winWidth * 0.55f, -1)) {
                        armorCall();
                    }
                    LayoutEnd();
                } else if (Settings::ItemTab == 8) {

                    if (ImGui::Button("All", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(healthing, Dirpatch, "health.ini", sizeof(healthing), 1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("None", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(healthing, Dirpatch, "health.ini", sizeof(healthing), 0);
                    }

                    if (Layout("leftmenu7", input->winWidth * 0.55f, -1)) {
                        healthCall();
                    }
                    LayoutEnd();
                } else if (Settings::ItemTab == 9) {

                    if (ImGui::Button("All", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(misc, Dirpatch, "misc.ini", sizeof(misc), 1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("None", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(misc, Dirpatch, "misc.ini", sizeof(misc), 0);
                    }

                    if (Layout("leftmenu8", input->winWidth * 0.55f, -1)) {
                        miscCall();
                    }
                    LayoutEnd();
                } else {

                    if (ImGui::Button("All", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(vehicle, Dirpatch, "vehicles.ini", sizeof(vehicle), 1);
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("None", ImVec2(input->winWidth * 0.20f, 80))) {
                        saveDataLoop2(vehicle, Dirpatch, "vehicles.ini", sizeof(vehicle), 0);
                    }

                    if (Layout("leftmenu3", input->winWidth * 0.55f, -1)) {
                        vehicleCall();
                    }
                    LayoutEnd();
                }
            }
        }
        LayoutEnd();
    }

    void vehicleCall(){
        if (Layout("row2", input->winWidth * 0.20f, 880.0f)) {
            if (ImGui::Checkbox("Aquaril", &vehicle[0])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[0], 0);
            }
            if (ImGui::Checkbox("BDRM", &vehicle[1])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[1], 1);
            }
            if (ImGui::Checkbox("Boat", &vehicle[2])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[2], 2);
            }
            if (ImGui::Checkbox("Buggy", &vehicle[3])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[3], 3);
            }
            if (ImGui::Checkbox("Bus", &vehicle[4])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[4], 4);
            }
            if (ImGui::Checkbox("Coupe", &vehicle[5])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[5], 5);
            }
            if (ImGui::Checkbox("Dacia", &vehicle[6])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[6], 6);
            }
            if (ImGui::Checkbox("Glider", &vehicle[7])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[7], 7);
            }
            if (ImGui::Checkbox("Ladaniva", &vehicle[8])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[8], 8);
            }
            if (ImGui::Checkbox("Utv", &vehicle[18])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[18], 18);
            }
            if (ImGui::Checkbox("Atv", &vehicle[20])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[20], 20);
            }
        }
        LayoutEnd();

        ImGui::SameLine();
        if (Layout("row3", input->winWidth * 0.20f, 880.0f)) {
            if (ImGui::Checkbox("Mirado", &vehicle[9])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[9], 9);
            }
            if (ImGui::Checkbox("Motorbike", &vehicle[10])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[10], 10);
            }
            if (ImGui::Checkbox("Pickup", &vehicle[11])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[11], 11);
            }
            if (ImGui::Checkbox("Rony", &vehicle[12])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[12], 12);
            }
            if (ImGui::Checkbox("Scooter", &vehicle[13])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[13], 13);
            }
            if (ImGui::Checkbox("Snowbike", &vehicle[14])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[14], 14);
            }
            if (ImGui::Checkbox("Snowmobile", &vehicle[15])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[15], 15);
            }
            if (ImGui::Checkbox("Tuk", &vehicle[16])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[16], 16);
            }
            if (ImGui::Checkbox("Uaz", &vehicle[17])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[17], 17);
            }
            if (ImGui::Checkbox("Bigfoot", &vehicle[19])) {
                writeInt(Dirpatch, "vehicles.ini", vehicle[19], 19);
            }
        }
        LayoutEnd();
    }

    void ammoCall(){
        if (Layout("row4", input->winWidth * 0.20f, 160.0f)) {
            if (ImGui::Checkbox(".45", &ammo[1])) {
                writeInt(Dirpatch, "ammos.ini", ammo[1], 1);
            }
            if (ImGui::Checkbox("5.56", &ammo[3])) {
                writeInt(Dirpatch, "ammos.ini", ammo[3], 3);
            }
        }
        LayoutEnd();

        ImGui::SameLine();
        if (Layout("row5", input->winWidth * 0.20f, 160.0f)) {
            if (ImGui::Checkbox("7.62", &ammo[4])) {
                writeInt(Dirpatch, "ammos.ini", ammo[4], 4);
            }
            if (ImGui::Checkbox("9mm", &ammo[5])) {
                writeInt(Dirpatch, "ammos.ini", ammo[5], 5);
            }
        }
        LayoutEnd();
    }

    void weaponCall(){
        if (Layout("row6", input->winWidth * 0.20f, 1220.0f)) {
            if (ImGui::Checkbox("3x", &weapon[1])) {
                writeInt(Dirpatch, "weapon.ini", weapon[1], 1);
            }
            if (ImGui::Checkbox("4x", &weapon[2])) {
                writeInt(Dirpatch, "weapon.ini", weapon[2], 2);
            }
            if (ImGui::Checkbox("6x", &weapon[3])) {
                writeInt(Dirpatch, "weapon.ini", weapon[3], 3);
            }
            if (ImGui::Checkbox("8x", &weapon[4])) {
                writeInt(Dirpatch, "weapon.ini", weapon[4], 4);
            }
            if (ImGui::Checkbox("98k", &weapon[5])) {
                writeInt(Dirpatch, "weapon.ini", weapon[5], 5);
            }
            if (ImGui::Checkbox("Akm", &weapon[6])) {
                writeInt(Dirpatch, "weapon.ini", weapon[6], 6);
            }
            if (ImGui::Checkbox("Dp28", &weapon[11])) {
                writeInt(Dirpatch, "weapon.ini", weapon[11], 11);
            }
            if (ImGui::Checkbox("Dot", &weapon[13])) {
                writeInt(Dirpatch, "weapon.ini", weapon[13], 13);
            }
            if (ImGui::Checkbox("Flare", &weapon[14])) {
                writeInt(Dirpatch, "weapon.ini", weapon[14], 14);
            }
            if (ImGui::Checkbox("G36c", &weapon[15])) {
                writeInt(Dirpatch, "weapon.ini", weapon[15], 15);
            }
            if (ImGui::Checkbox("Grenade", &weapon[16])) {
                writeInt(Dirpatch, "weapon.ini", weapon[16], 16);
            }
            if (ImGui::Checkbox("Groza", &weapon[17])) {
                writeInt(Dirpatch, "weapon.ini", weapon[17], 17);
            }
            if (ImGui::Checkbox("Holo", &weapon[18])) {
                writeInt(Dirpatch, "weapon.ini", weapon[18], 18);
            }
            if (ImGui::Checkbox("M16", &weapon[20])) {
                writeInt(Dirpatch, "weapon.ini", weapon[20], 20);
            }
            if (ImGui::Checkbox("M24", &weapon[21])) {
                writeInt(Dirpatch, "weapon.ini", weapon[21], 21);
            }
        }
        LayoutEnd();

        ImGui::SameLine();
        if (Layout("row7", input->winWidth * 0.20f, 1220.0f)) {
            if (ImGui::Checkbox("M249", &weapon[22])) {
                writeInt(Dirpatch, "weapon.ini", weapon[22], 22);
            }
            if (ImGui::Checkbox("M4", &weapon[23])) {
                writeInt(Dirpatch, "weapon.ini", weapon[23], 23);
            }
            if (ImGui::Checkbox("M762", &weapon[24])) {
                writeInt(Dirpatch, "weapon.ini", weapon[24], 24);
            }
            if (ImGui::Checkbox("Mini14", &weapon[28])) {
                writeInt(Dirpatch, "weapon.ini", weapon[28], 28);
            }
            if (ImGui::Checkbox("Molotov", &weapon[29])) {
                writeInt(Dirpatch, "weapon.ini", weapon[29], 29);
            }
            if (ImGui::Checkbox("Qbu", &weapon[32])) {
                writeInt(Dirpatch, "weapon.ini", weapon[32], 32);
            }
            if (ImGui::Checkbox("Qbz", &weapon[33])) {
                writeInt(Dirpatch, "weapon.ini", weapon[33], 33);
            }
            if (ImGui::Checkbox("Scar", &weapon[37])) {
                writeInt(Dirpatch, "weapon.ini", weapon[37], 37);
            }
            if (ImGui::Checkbox("SKS", &weapon[38])) {
                writeInt(Dirpatch, "weapon.ini", weapon[38], 38);
            }
            if (ImGui::Checkbox("Tommy", &weapon[41])) {
                writeInt(Dirpatch, "weapon.ini", weapon[41], 41);
            }
            if (ImGui::Checkbox("Ump", &weapon[42])) {
                writeInt(Dirpatch, "weapon.ini", weapon[42], 42);
            }
            if (ImGui::Checkbox("Uzi", &weapon[43])) {
                writeInt(Dirpatch, "weapon.ini", weapon[43], 43);
            }
            if (ImGui::Checkbox("Vector", &weapon[45])) {
                writeInt(Dirpatch, "weapon.ini", weapon[45], 45);
            }
            if (ImGui::Checkbox("Win94", &weapon[46])) {
                writeInt(Dirpatch, "weapon.ini", weapon[46], 46);
            }
        }
        LayoutEnd();
    }

    void armorCall(){
        if (Layout("row8", input->winWidth * 0.36f, 500.0f)) {
            if (ImGui::Checkbox("armor(2)", &armor[0])) {
                writeInt(Dirpatch, "armors.ini", armor[0], 0);
            }
            if (ImGui::Checkbox("armor(3)", &armor[1])) {
                writeInt(Dirpatch, "armors.ini", armor[1], 1);
            }
            if (ImGui::Checkbox("Helmet(2)", &armor[2])) {
                writeInt(Dirpatch, "armors.ini", armor[2], 2);
            }
            if (ImGui::Checkbox("Helmet(3)", &armor[3])) {
                writeInt(Dirpatch, "armors.ini", armor[3], 3);
            }
            if (ImGui::Checkbox("BackPack(2)", &misc[3])) {
                writeInt(Dirpatch, "misc.ini", misc[3], 3);
            }
            if (ImGui::Checkbox("BackPack(3)", &misc[4])) {
                writeInt(Dirpatch, "misc.ini", misc[4], 4);
            }
        }
        LayoutEnd();
    }

    void healthCall(){
        if (Layout("row10", input->winWidth * 0.20f, 240.0f)) {
            if (ImGui::Checkbox("Bandage", &healthing[0])) {
                writeInt(Dirpatch, "health.ini", healthing[0], 0);
            }
            if (ImGui::Checkbox("Drink", &healthing[1])) {
                writeInt(Dirpatch, "health.ini", healthing[1], 1);
            }
            if (ImGui::Checkbox("FirstAid", &healthing[2])) {
                writeInt(Dirpatch, "health.ini", healthing[2], 2);
            }
        }
        LayoutEnd();

        ImGui::SameLine();
        if (Layout("row11", input->winWidth * 0.20f, 240.0f)) {
            if (ImGui::Checkbox("Injection", &healthing[3])) {
                writeInt(Dirpatch, "health.ini", healthing[3], 3);
            }
            if (ImGui::Checkbox("Pills", &healthing[4])) {
                writeInt(Dirpatch, "health.ini", healthing[4], 4);
            }
        }
        LayoutEnd();
    }

    void miscCall(){
        if (Layout("row12", input->winWidth * 0.20f, 960.0f)) {
            if (ImGui::Checkbox("Airplane", &misc[0])) {
                writeInt(Dirpatch, "misc.ini", misc[0], 0);
            }
            if (ImGui::Checkbox("Airdrop", &misc[1])) {
                writeInt(Dirpatch, "misc.ini", misc[1], 1);
            }
            if (ImGui::Checkbox("Angled", &misc[2])) {
                writeInt(Dirpatch, "misc.ini", misc[2], 2);
            }
            if (ImGui::Checkbox("CompAR", &misc[5])) {
                writeInt(Dirpatch, "misc.ini", misc[5], 5);
            }
            if (ImGui::Checkbox("CompSMG", &misc[6])) {
                writeInt(Dirpatch, "misc.ini", misc[6], 6);
            }
            if (ImGui::Checkbox("CompSNP", &misc[7])) {
                writeInt(Dirpatch, "misc.ini", misc[7], 7);
            }
            if (ImGui::Checkbox("MgzAR", &misc[8])) {
                writeInt(Dirpatch, "misc.ini", misc[8], 8);
            }
            if (ImGui::Checkbox("MgzSMG", &misc[9])) {
                writeInt(Dirpatch, "misc.ini", misc[9], 9);
            }
            if (ImGui::Checkbox("MgzSNP", &misc[10])) {
                writeInt(Dirpatch, "misc.ini", misc[10], 10);
            }
            if (ImGui::Checkbox("HiderAR", &misc[11])) {
                writeInt(Dirpatch, "misc.ini", misc[11], 11);
            }
            if (ImGui::Checkbox("HiderSMG", &misc[12])) {
                writeInt(Dirpatch, "misc.ini", misc[12], 12);
            }
            if (ImGui::Checkbox("ShopToken", &misc[24])) {
                writeInt(Dirpatch, "misc.ini", misc[24], 24);
            }
        }
        LayoutEnd();

        ImGui::SameLine();
        if (Layout("row13", input->winWidth * 0.20f, 960.0f)) {
            if (ImGui::Checkbox("HiderSNP", &misc[13])) {
                writeInt(Dirpatch, "misc.ini", misc[13], 13);
            }
            if (ImGui::Checkbox("Half", &misc[14])) {
                writeInt(Dirpatch, "misc.ini", misc[14], 14);
            }
            if (ImGui::Checkbox("Light", &misc[15])) {
                writeInt(Dirpatch, "misc.ini", misc[15], 15);
            }
            if (ImGui::Checkbox("Loot", &misc[16])) {
                writeInt(Dirpatch, "misc.ini", misc[16], 16);
            }
            if (ImGui::Checkbox("StockAR", &misc[17])) {
                writeInt(Dirpatch, "misc.ini", misc[17], 17);
            }
            if (ImGui::Checkbox("StockSNP", &misc[18])) {
                writeInt(Dirpatch, "misc.ini", misc[18], 18);
            }
            if (ImGui::Checkbox("SuppAR", &misc[19])) {
                writeInt(Dirpatch, "misc.ini", misc[19], 19);
            }
            if (ImGui::Checkbox("SuppSMG", &misc[20])) {
                writeInt(Dirpatch, "misc.ini", misc[20], 20);
            }
            if (ImGui::Checkbox("SuppSNP", &misc[21])) {
                writeInt(Dirpatch, "misc.ini", misc[21], 21);
            }
            if (ImGui::Checkbox("Thumb", &misc[22])) {
                writeInt(Dirpatch, "misc.ini", misc[22], 22);
            }
            if (ImGui::Checkbox("Vertical", &misc[23])) {
                writeInt(Dirpatch, "misc.ini", misc[23], 23);
            }
            if (ImGui::Checkbox("GasCan", &misc[25])) {
                writeInt(Dirpatch, "misc.ini", misc[25], 25);
            }
        }
        LayoutEnd();
    }

    bool ToggleButton(const char* str_id, bool* v)
    {
        ImVec4* colors = ImGui::GetStyle().Colors;
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        float height = ImGui::GetFrameHeight();
        float width = height * 1.55f;
        float radius = height * 0.50f;
        bool state = false;

        ImGui::InvisibleButton(str_id, ImVec2(width, height));
        if (ImGui::IsItemClicked()) *v = !*v;
        ImGuiContext& gg = *GImGui;
        float ANIM_SPEED = 0.085f;
        if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
            float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
        if (ImGui::IsItemHovered()) {
            draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height - 20), ImGui::GetColorU32(
                    *v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)),
                                     height * 0.5f);
            state = true;
        } else {
            draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height - 20), ImGui::GetColorU32(
                    *v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)),
                                     height * 0.50f);
            state = false;
        }
        draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), p.y + radius - 10), radius - 1.5f, IM_COL32(255, 255, 255, 255));

        return state;
    }

    bool colorButton(const char* label, int num, ImColor color){
        bool state = false;
        ImVec4 active = color;
        ImVec4 inactive = color;
        ImGui::PushStyleColor(ImGuiCol_Button, Settings::ColorTab == num ? active : inactive);
        if (ImGui::Button(label, ImVec2(80, 60))){
            state = true;
        } else {
            state = false;
        }

        return state;
    }

    const std::string currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
        return buf;
    }

    bool checkstatus(){
        if (charEquals(Patchsh1.c_str(), "0") &&
            charEquals(Patchsh256.c_str(), "1") &&
            charEquals(Patchmd5.c_str(), "2")){
            return true;
        } else {
            return false;
        }
    }

    /*
    *DrawText
            * 参数1：屏幕x
            * 参数2：屏幕y
            * 参数3：透明度 最小值0  最大值1.0F
    * 参数4：红色 最小值0  最大值1.0F
    * 参数5：绿色 最小值0  最大值1.0F
    * 参数6：蓝色 最小值0  最大值1.0F
    * 参数7：绘制字符串
    */
    void DrawText(float X, float Y, float a, float r, float g, float b, const char *data) {
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X, Y), ImColor(r, g, b, a), data);
    }
    void DrawText(float X, float Y, const char *data) {
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X, Y), TextColor, data);
    }
    void DrawTextCx(float X, float Y, float a, float r, float g, float b, const char *data) {
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X -= ((int) ImGui::CalcTextSize(data).x >> 1), Y), ImColor(r, g, b, a), data);
    }
    void DrawTextCx(float X, float Y, const char *data) {
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X -= ((int) ImGui::CalcTextSize(data).x >> 1), Y), TextColor, data);
    }
    void DrawTextCy(float X, float Y, float a, float r, float g, float b, const char *data) {
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X, Y -= ((int) ImGui::CalcTextSize(data).y >> 1)), ImColor(r, g, b, a), data);
    }
    void DrawTextCy(float X, float Y, const char *data) {
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X, Y -= ((int) ImGui::CalcTextSize(data).y >> 1)), TextColor, data);
    }
    void DrawTextCxy(float X, float Y, float a, float r, float g, float b, const char *data) {
        auto size = ImGui::CalcTextSize(data);
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X -= ((int) size.x >> 1), Y -= ((int) size.y >> 1)), ImColor(r, g, b, a), data);
    }
    float sizetmp;
    void DrawTextCxy(float X, float Y, float a, float r, float g, float b, float size_, const char *data) {
        sizetmp = imFont->FontSize;
        imFont->FontSize = size_;
        auto size = ImGui::CalcTextSize(data);
        imFont->FontSize = sizetmp;
        ImGui::GetBackgroundDrawList()->AddText(imFont, size_, ImVec2(X -= ((int) size.x >> 1), Y -= ((int) size.y >> 1)), ImColor(r, g, b, a), data);
    }
    void DrawTextCxy(float X, float Y, ImColor color, float size_, const char *data) {
        sizetmp = imFont->FontSize;
        imFont->FontSize = size_;
        auto size = ImGui::CalcTextSize(data);
        imFont->FontSize = sizetmp;
        ImGui::GetBackgroundDrawList()->AddText(imFont, size_, ImVec2(X -= ((int) size.x >> 1), Y -= ((int) size.y >> 1)), color, data);
    }
    void DrawTextCxy2(float X, float Y, ImColor color, float size_, const char *data) {
        ImGui::GetBackgroundDrawList()->AddText(imFont, size_, ImVec2(X, Y), color, data);
    }
    void DrawTextCxy(float X, float Y, ImColor &color, const char *data) {
        auto size = ImGui::CalcTextSize(data);
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X -= ((int) size.x >> 1), Y -= ((int) size.y >> 1)), color, data);
    }
    void DrawTextCxy(float X, float Y, ImColor *color, const char *data) {
        auto size = ImGui::CalcTextSize(data);
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X -= ((int) size.x >> 1), Y -= ((int) size.y >> 1)), *color, data);
    }
    void DrawTextCxy(float X, float Y, ImColor color, const char *data) {
        auto size = ImGui::CalcTextSize(data);
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X -= ((int) size.x >> 1), Y -= ((int) size.y >> 1)), color, data);
    }
    void DrawTextCxy(float X, float Y, const char *data) {
        auto size = ImGui::CalcTextSize(data);
        ImGui::GetBackgroundDrawList()->AddText(imFont, imFont->FontSize, ImVec2(X -= ((int) size.x >> 1), Y -= ((int) size.y >> 1)), TextColor, data);
    }

    void DrawLine(float startx, float starty, float endx, float endy, ImColor &color, float thickness) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(startx, starty), ImVec2(endx, endy), color, thickness);
    }

    /*
     *DrawLine
     * 参数1：屏幕x,y 排列的连续数组
     * 参数2：线段数量
     * 参数3：透明度 最小值0  最大值1.0F
     * 参数4：红色 最小值0  最大值1.0F
     * 参数5：绿色 最小值0  最大值1.0F
     * 参数6：蓝色 最小值0  最大值1.0F
     * 参数7：线条宽度
     */
    void DrawLines(float *points, int points_count, float a, float r, float g, float b, float thickness) {
        ImGui::GetBackgroundDrawList()->AddPolyline((ImVec2 *) points, points_count, ImColor(r, g, b, a), 0, thickness);
    }
    void DrawLines(float *points, int points_count, float a, float r, float g, float b) {
        ImGui::GetBackgroundDrawList()->AddPolyline((ImVec2 *) points, points_count, ImColor(r, g, b, a), 0, LinesThickness);
    }
    void DrawLines(float *points, int points_count, ImColor &color, float thickness) {
        ImGui::GetBackgroundDrawList()->AddPolyline((ImVec2 *) points, points_count, color, 0, thickness);
    }
    void DrawLines(float *points, int points_count, ImColor &color) {
        ImGui::GetBackgroundDrawList()->AddPolyline((ImVec2 *) points, points_count, color, 0, LinesThickness);
    }
    void DrawLines(float *points, int points_count) {
        ImGui::GetBackgroundDrawList()->AddPolyline((ImVec2 *) points, points_count, LinesColor, 0, LinesThickness);
    }

    /*
     *DrawRect
     * 参数1：屏幕x 左上
     * 参数2：屏幕y 左上
     * 参数3：屏幕x 右下
     * 参数4：屏幕y 右下
     * 参数5：透明度 最小值0  最大值1.0F
     * 参数6：红色 最小值0  最大值1.0F
     * 参数7：绿色 最小值0  最大值1.0F
     * 参数8：蓝色 最小值0  最大值1.0F
     * 参数9：方框四角角度 0 为直角线条
     * 参数10：线条宽度
     */
    void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b, float rounding, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), rounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), RectRounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, RectRounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color, float rounding, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, rounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), RectRounding, ImDrawFlags_RoundCornersAll, RectThickness);
    }
    void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), RectColor, RectRounding, ImDrawFlags_RoundCornersAll, RectThickness);
    }
    void DrawRectCxy(float centerX, float centerY, int width, int high, float a, float r, float g, float b, float rounding, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), ImColor(r, g, b, a), rounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRectCxy(float centerX, float centerY, int width, int high, ImColor &color, float rounding, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), color, rounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRectCxy(float centerX, float centerY, int width, int high, ImColor *color, float rounding, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), *color, rounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRectCxy(float centerX, float centerY, int width, int high, float a, float r, float g, float b, float thickness) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), ImColor(r, g, b, a), RectRounding, ImDrawFlags_RoundCornersAll, thickness);
    }
    void DrawRectCxy(float centerX, float centerY, int width, int high, float a, float r, float g, float b) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), ImColor(r, g, b, a), RectRounding, ImDrawFlags_RoundCornersAll, RectThickness);
    }
    void DrawRectCxy(float centerX, float centerY, int width, int high) {
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), RectColor, RectRounding, ImDrawFlags_RoundCornersAll, RectThickness);
    }

    /*
     *DrawRectFilled
     * 参数1：屏幕x 左上
     * 参数2：屏幕y 左上
     * 参数3：屏幕x 右下
     * 参数4：屏幕y 右下
     * 参数5：透明度 最小值0  最大值1.0F
     * 参数6：红色 最小值0  最大值1.0F
     * 参数7：绿色 最小值0  最大值1.0F
     * 参数8：蓝色 最小值0  最大值1.0F
     * 参数9：方框四角角度 0 为直角线条
     */
    void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b, float rounding) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), rounding);
    }
    void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), RectFilledRounding);
    }
    void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color, float rounding) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, rounding);
    }
    void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, RectFilledRounding);
    }
    void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), RectFilledColor, RectFilledRounding);
    }
    void DrawRectFilledCxy(float centerX, float centerY, int width, int high, float a, float r, float g, float b, float rounding) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), ImColor(r, g, b, a), rounding);
    }
    void DrawRectFilledCxy(float centerX, float centerY, int width, int high, ImColor &color, float rounding) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), color, rounding);
    }
    void DrawRectFilledCxy(float centerX, float centerY, int width, int high, float a, float r, float g, float b) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), ImColor(r, g, b, a), RectFilledRounding);
    }
    void DrawRectFilledCxy(float centerX, float centerY, int width, int high, ImColor color) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), color, RectFilledRounding);
    }
    void DrawRectFilledCxy(float centerX, float centerY, int width, int high) {
        ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(centerX - (width >> 1), centerY - (high >> 1)), ImVec2(centerX + (width >> 1), centerY + (high >> 1)), RectFilledColor, RectFilledRounding);
    }

    /*
     *DrawCircle
     * 参数1：屏幕x 圆中心
     * 参数2：屏幕y 圆中心
     * 参数3：圆半径
     * 参数4：透明度 最小值0  最大值1.0F
     * 参数5：红色 最小值0  最大值1.0F
     * 参数6：绿色 最小值0  最大值1.0F
     * 参数7：蓝色 最小值0  最大值1.0F
     * 参数8：圆，线条数量  默认0为完整圆形， 填入指定的参数生成指定线段的圆
     * 参数9：圆，线条宽度
     */
    void DrawCircle(float X, float Y, float radius, float a, float r, float g, float b, int num_segments, float thickness) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(X, Y), radius, ImColor(r, g, b, a), num_segments, thickness);
    }
    void DrawCircle(float X, float Y, float radius, float a, float r, float g, float b, float thickness) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(X, Y), radius, ImColor(r, g, b, a), CircleNum_segments, thickness);
    }
    void DrawCircle(float X, float Y, float radius, float a, float r, float g, float b) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(X, Y), radius, ImColor(r, g, b, a), CircleNum_segments, CircleThickness);
    }
    void DrawCircle(float X, float Y, float radius, ImColor color) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(X, Y), radius, color, CircleNum_segments, CircleThickness);
    }
    void DrawCircle(float X, float Y, float radius) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(X, Y), radius, CircleColor, CircleNum_segments, CircleThickness);
    }

    /*
     *CircleFilled
     * 参数1：屏幕x 圆中心
     * 参数2：屏幕y 圆中心
     * 参数3：圆半径
     * 参数4：透明度 最小值0  最大值1.0F
     * 参数5：红色 最小值0  最大值1.0F
     * 参数6：绿色 最小值0  最大值1.0F
     * 参数7：蓝色 最小值0  最大值1.0F
     * 参数8：圆，线条数量  默认0为完整圆形， 填入指定的参数生成指定线段的圆
     */
    void DrawCircleFilled(float X, float Y, float radius, float a, float r, float g, float b, int num_segments) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(X, Y), radius, ImColor(r, g, b, a), num_segments);
    }
    void DrawCircleFilled(float X, float Y, float radius, float a, float r, float g, float b) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(X, Y), radius, ImColor(r, g, b, a), CircleFilledNum_segments);
    }
    void DrawCircleFilled(float X, float Y, float radius, ImColor &color, int num_segments) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(X, Y), radius, color, num_segments);
    }
    void DrawCircleFilled(float X, float Y, float radius, ImColor &color) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(X, Y), radius, color, CircleFilledNum_segments);
    }
    void DrawCircleFilled(float X, float Y, float radius) {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(X, Y), radius, CircleFilledColor, CircleFilledNum_segments);
    }
};

#endif
