#include "OpenGlInput.h"
#include "log.h"
using namespace std;

void ImguiAndroidInput::Copy(ImGuiInputTextCallbackData *CallbackData) {
    Copybuf = (char *) malloc(CallbackData->SelectionEnd - CallbackData->SelectionStart + 2);
    bzero(Copybuf, CallbackData->SelectionEnd - CallbackData->SelectionStart + 2);
    strlcat(Copybuf, &CallbackData->Buf[CallbackData->SelectionStart], CallbackData->SelectionEnd - CallbackData->SelectionStart + 1);
}

string ImguiAndroidInput::JNI_Copy() {
    if (!io->WantTextInput) {
        return "";
    }
    std::unique_lock<std::mutex> ulo(Copylk);
    ImguiAndroidInput::ActiveInputsw = 0;
    cond.wait(ulo, [this] { return ImguiAndroidInput::ActiveInputsw == 10; });
    string tmp = Copybuf;
    if (Copybuf != nullptr) {
        free(Copybuf);
        Copybuf = nullptr;
    }
    return tmp;
}

void ImguiAndroidInput::Paste(ImGuiInputTextCallbackData *CallbackData) {
    if (CallbackData->HasSelection()) {
        CallbackData->DeleteChars(CallbackData->SelectionStart, CallbackData->SelectionEnd - CallbackData->SelectionStart);
    }
    CallbackData->InsertChars(CallbackData->CursorPos, Pastebuf);
}

void ImguiAndroidInput::JNI_Paste(string data) {
    if (!io->WantTextInput) {
        return;
    }
    std::unique_lock<std::mutex> ulo(Pastelk);
    Pastebuf = data.c_str();
    this->ActiveInputsw = 1;
    cond.wait(ulo, [this] { return this->ActiveInputsw == 11; });
}

void ImguiAndroidInput::SelectAll(ImGuiInputTextCallbackData *CallbackData) {
    CallbackData->SelectAll();
    SelectSize = CallbackData->SelectionEnd - CallbackData->SelectionStart;
}

int ImguiAndroidInput::JNI_SelectAll() {
    ImguiAndroidInput::SelectSize = 0;
    if (!io->WantTextInput) {
        return SelectSize;
    }
    std::unique_lock<std::mutex> ulo(Selectlk);
    ImguiAndroidInput::ActiveInputsw = 2;
    cond.wait(ulo, [this] { return this->ActiveInputsw == 12; });
    return this->SelectSize;
}

void ImguiAndroidInput::Cut(ImGuiInputTextCallbackData *CallbackData) {
    Copybuf = (char *) malloc(CallbackData->SelectionEnd - CallbackData->SelectionStart + 2);
    bzero(Copybuf, CallbackData->SelectionEnd - CallbackData->SelectionStart + 2);
    strlcat(Copybuf, &CallbackData->Buf[CallbackData->SelectionStart], CallbackData->SelectionEnd - CallbackData->SelectionStart + 1);
    CallbackData->DeleteChars(CallbackData->SelectionStart, CallbackData->SelectionEnd - CallbackData->SelectionStart);
}

string ImguiAndroidInput::JNI_Cut() {
    if (!io->WantTextInput) {
        return "";
    }
    std::unique_lock<std::mutex> ulo(Cutlk);
    this->ActiveInputsw = 3;
    cond.wait(ulo, [this] { return this->ActiveInputsw == 13; });
    string tmp = Copybuf;
    if (Copybuf != nullptr) {
        free(Copybuf);
        Copybuf = nullptr;
    }
    return tmp;
}

int ImguiAndroidInput::inputCallback(ImGuiInputTextCallbackData *CallbackData) {
    switch (ActiveInputsw) {
        case 0: {
            Copy(CallbackData);
            ActiveInputsw = 10;
            cond.notify_all();
        }
            break;
        case 1: {
            Paste(CallbackData);
            ActiveInputsw = 11;
            cond.notify_all();
        }
            break;
        case 2: {
            SelectAll(CallbackData);
            ActiveInputsw = 12;
            cond.notify_all();
        }
            break;
        case 3: {
            Cut(CallbackData);
            ActiveInputsw = 13;
            cond.notify_all();
        }
            break;
        default: {

        }
            break;
    }
    return 0;
}

void ImguiAndroidInput::addUTF8(const char *in_data) {
    io->AddInputCharactersUTF8(in_data);
}

void ImguiAndroidInput::initImguiIo(ImGuiIO *io) {
    this->io = io;
    moveio   = false;
    f        = 1.0f;
    Copybuf  = nullptr;
    Pastebuf = nullptr;
    Inputio  = false;
    fps      = 240;
    if (max_fps == 0) {
        max_fps = 240;
    }
}

void ImguiAndroidInput::InputKey(int action, int code) {
    switch (action) {
        case InputAction::Action_DOWN: {
            if (code == 59) {
                io->KeyShift = true;
            }
            io->KeysDown[code] = true;
        }
            break;
        case InputAction::Action_UP: {
            if (code == 59) {
                io->KeyShift = false;
            }
            io->KeysDown[code] = false;
        }
            break;
    }
    usleep(10000);
}

 ClassInfo ImguiAndroidInput::gClassInfo = {nullptr,nullptr,nullptr,nullptr,nullptr,
                                                  nullptr,nullptr,nullptr,nullptr,nullptr};
void ImguiAndroidInput::toast(string &str) const {
    if (gClassInfo.jvm == nullptr || gClassInfo.pJclass == nullptr || gClassInfo.show == nullptr) {
        return;
    }
    JNIEnv  *env         = nullptr;
    bool    shouldDetach = false;
    if (gClassInfo.jvm->GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_EDETACHED) {
        if (gClassInfo.jvm->AttachCurrentThread(&env, nullptr) >= 0) {
            shouldDetach = true;
        }
    }
    jstring tmp          = env->NewStringUTF(str.c_str());
    env->CallStaticVoidMethod(gClassInfo.pJclass, gClassInfo.show, tmp);
    env->DeleteLocalRef(tmp);
    if (shouldDetach) {
        gClassInfo.jvm->DetachCurrentThread();
    }
}

bool ImguiAndroidInput::openInput(){
    if (gClassInfo.jvm == nullptr || gClassInfo.pJclass == nullptr || gClassInfo.openInput == nullptr) {
        return false;
    }
    JNIEnv  *env         = nullptr;
    bool    shouldDetach = false;
    if (gClassInfo.jvm->GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_EDETACHED) {
        if (gClassInfo.jvm->AttachCurrentThread(&env, nullptr) >= 0) {
            shouldDetach = true;
        }
    }

    jboolean tmp =  env->CallStaticBooleanMethod(gClassInfo.pJclass,gClassInfo.openInput);
    if (shouldDetach) {
        gClassInfo.jvm->DetachCurrentThread();
    }
    return tmp;
}

bool ImguiAndroidInput::closeInput(){
    if (gClassInfo.jvm == nullptr || gClassInfo.pJclass == nullptr || gClassInfo.closeInput == nullptr) {
        return false;
    }
    JNIEnv  *env         = nullptr;
    bool    shouldDetach = false;
    if (gClassInfo.jvm->GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_EDETACHED) {
        if (gClassInfo.jvm->AttachCurrentThread(&env, nullptr) >= 0) {
            shouldDetach = true;
        }
    }
    jboolean tmp =  env->CallStaticBooleanMethod(gClassInfo.pJclass,gClassInfo.closeInput);
    if (shouldDetach) {
        gClassInfo.jvm->DetachCurrentThread();
    }
    return tmp;
}

void ImguiAndroidInput::ioset(jint pos, jint v) const {
    if (gClassInfo.jvm == nullptr || gClassInfo.pJclass == nullptr || gClassInfo.io == nullptr) {
        return;
    }
    JNIEnv  *env         = nullptr;
    bool    shouldDetach = false;
    if (gClassInfo.jvm->GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_EDETACHED) {
        if (gClassInfo.jvm->AttachCurrentThread(&env, nullptr) >= 0) {
            shouldDetach = true;
        }
    }
    jstring tmp          = env->NewStringUTF("psio");
    env->CallStaticVoidMethod(gClassInfo.pJclass, gClassInfo.io, tmp, pos, v);
    env->DeleteLocalRef(tmp);
    if (shouldDetach) {
        gClassInfo.jvm->DetachCurrentThread();
    }
}

void ImguiAndroidInput::isLongTouch(int x, int y) {
    if (gClassInfo.jvm == nullptr || gClassInfo.pJclass == nullptr || gClassInfo.isLongTouch == nullptr) {
        return;
    }
    JNIEnv  *env         = nullptr;
    bool    shouldDetach = false;
    if (gClassInfo.jvm->GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_EDETACHED) {
        if (gClassInfo.jvm->AttachCurrentThread(&env, nullptr) >= 0) {
            shouldDetach = true;
        }
    }
    env->CallStaticVoidMethod(gClassInfo.pJclass,gClassInfo.isLongTouch,x,y);
    if (shouldDetach) {
        gClassInfo.jvm->DetachCurrentThread();
    }
}

void ImguiAndroidInput::funMshowinit(jclass thiz, JNIEnv *env) {

    (*env).GetJavaVM(&gClassInfo.jvm);
    gClassInfo.pJclass = thiz;
    gClassInfo.show    = env->GetStaticMethodID(gClassInfo.pJclass, "mShow", "(Ljava/lang/String;)V");
    if (nullptr == gClassInfo.show) {
			LOGE("can't find method mShow from JniClass");
        return;
    } else {
			LOGE("find method mShow from JniClass");
    }
    gClassInfo.io = env->GetStaticMethodID(gClassInfo.pJclass, "mIO", "(Ljava/lang/String;II)V");
    if (nullptr == gClassInfo.io) {
			LOGE("can't find method mIO from JniClass");
        return;
    } else {
			LOGE("find method mIO from JniClass");
    }
    gClassInfo.openInput = env->GetStaticMethodID(gClassInfo.pJclass,"openInput","()Z");
    if (nullptr == gClassInfo.openInput) {
			LOGE("can't find method openInput from JniClass");
        return;
    } else {
			LOGE("find method openInput from JniClass");
    }
    gClassInfo.closeInput = env->GetStaticMethodID(gClassInfo.pJclass,"closeInput","()Z");
    if (nullptr == gClassInfo.closeInput) {
			LOGE("can't find method closeInput from JniClass");
        return;
    } else {
			LOGE("find method closeInput from JniClass");
    }
    gClassInfo.isLongTouch = env->GetStaticMethodID(gClassInfo.pJclass,"isLongTouch","(II)V");
    if (nullptr == gClassInfo.isLongTouch) {
			LOGE("can't find method isLongTouch from JniClass");
        return;
    } else {
			LOGE("find method isLongTouch from JniClass");
    }
    gClassInfo.obj = (*env).NewGlobalRef(thiz);
    if (nullptr == gClassInfo.obj) {
			LOGE("can't find jobject");
        return;
    } else {
			LOGE("find jobject");
    }
}


void ImguiAndroidInput::longTouchLoop(){
    if (loopRun){
        return;
    }
    thread loop([this]{
        for (;;){
            if ( TOUCH_TIMER.islooptimestart ){
                if (TOUCH_TIMER.getlooptime()>150000000&&!io->isMouseMove&&io->WantTextInput){
                    LOGE("长按了编辑框");
                    ioset(3,0);
                    loopRun = false;
                    return ;
                }
                if (io->isMouseMove || !io->WantTextInput || !io->MouseDown[0] || !loopRun){
                    loopRun = false;
                    return;
                }
            }
            usleep(1000);
        }
    });
    loop.detach();
}

void ImguiAndroidInput::InputTouchEvent(int event_get_action, float x, float y) {
	LOGE("event.key=%d",event_get_action);
    if (io->WantCaptureMouse) {
		LOGE("imgui获得焦点");
    } else {
		LOGE("imgui无焦点");
    }
    if (io->WantTextInput) {
		LOGE("imgui输入获得焦点");
        if (!Inputio && event_get_action != eTouchEvent::TOUCH_OUTSIDE) {
            Inputio = openInput();
			LOGE("imgui呼出输入法%d",Inputio);
        }
    } else {
		LOGE("imgui输入丢失焦点");
        if (Inputio) {
            Inputio = closeInput();
			LOGE("imgui关闭输入法%d",Inputio);
        }
    }
    if (ItemHovered) {
        Activeio = ItemHovered;
    }

    switch (event_get_action) {
        case eTouchEvent::TOUCH_OUTSIDE: io->MouseDown[0] = false;
            moveio   = false;
            Activeio = false;
            Scrollio = false;
            loopRun = false;
            DOWN_x   = DOWN_y   = 0;
            if (Inputio) {
                Inputio = closeInput();
			LOGE("imgui关闭输入法%d",Inputio);
            }
            break;
        case eTouchEvent::TOUCH_DOWN: DOWN_x = x;
            DOWN_y = y;
            io->MousePos.x = x;
            io->MousePos.y = y;
            io->MouseDown[0] = true;
            Activeio   = ItemHovered;
            SetScrollX = 0.0f;
            SetScrollY = 0.0f;
            ScrollXMAX = 0.0f;
            ScrollYMAX = 0.0f;
            TOUCH_TIME = 0.0f;
            upio       = false;
            Scrollio   = false;
            runScroll  = false;
            io->isMouseMove = false;
            TOUCH_TIMER.start();
            TOUCH_TIMER.looptimestart();
            longTouchLoop();
            loopRun = true;
            if (y <= g_window->TitleBarHeight() && !moveio) {
                moveio = true;
            }
            break;
        case eTouchEvent::TOUCH_UP:
            io->MouseDown[0] = false;
            SetScrollX = x - DOWN_x;
            SetScrollY = y - DOWN_y;
            moveio     = false;
            Activeio   = false;
            runScroll  = false;
            loopRun = false;
            DOWN_x     = DOWN_y = 0;
            TOUCH_TIME = TOUCH_TIMER.stop(1);
            break;
        case eTouchEvent::TOUCH_MOVE:
            io->MousePos.x = x;
            io->MousePos.y                          = y;
            loopRun = false;
            if (y > g_window->TitleBarHeight() && abs(DOWN_x - x) > 3.0f  ||  abs(DOWN_y - y) > 3.0f ){
                io->isMouseMove = true;
                Scrollio = true;
            }

			LOGE("滑动");
            break;
        default: break;
    }
	LOGE("输入法io%d",Inputio);
}

float ImguiAndroidInput::funScroll() {
    nowScrollX = ImGui::GetScrollX();
    nowScrollY = ImGui::GetScrollY();
    runScroll  = true;
    if (io->MouseDown[0]) {
        if (nowScrollX > 0.0f || nowScrollX < ImGui::GetScrollMaxX()) {
            ImGui::SetScrollX(ImGui::GetScrollX() - io->MouseDelta.x);
        }
        if (nowScrollY > 0.0f || nowScrollY < ImGui::GetScrollMaxY()) {
            ImGui::SetScrollY(ImGui::GetScrollY() - io->MouseDelta.y);
        }
        upio = false;
    } else {
        if (!upio) {
            if (TOUCH_TIME > 300) {
                SetScrollX = 0;
                SetScrollY = 0;
                Scrollio   = false;
                runScroll  = false;
            }
            Seed_up    = abs(SetScrollX) / (TOUCH_TIME);
            ScrollX    = SetScrollX / (TOUCH_TIME / 1000 * (float) fps);
            SetScrollX *= Seed_up * f;
            ScrollXMAX = SetScrollX;
            Seed_up    = abs(SetScrollY) / (TOUCH_TIME);
            ScrollY    = SetScrollY / (TOUCH_TIME / 1000 * (float) fps);
            SetScrollY *= Seed_up * f;
            ScrollYMAX = SetScrollY;
            upio       = true;
        }
        ScrollXRatio = (SetScrollX / ScrollXMAX);
        ScrollYRatio = (SetScrollY / ScrollYMAX);
        if (nowScrollX > 0.0f && nowScrollX < ImGui::GetScrollMaxX()) {
            ImGui::SetScrollX(nowScrollX - ScrollX * ScrollXRatio);
        } else {
            ScrollX = 0.0f;
        }
        if (nowScrollY > 0.0f && nowScrollY < ImGui::GetScrollMaxY()) {
            ImGui::SetScrollY(nowScrollY - ScrollY * ScrollYRatio);
        } else {
            ScrollY = 0.0f;
        }
        SetScrollX -= (ScrollX * ScrollXRatio);
        SetScrollY -= (ScrollY * ScrollYRatio);
        if (ScrollX * ScrollXRatio >= -0.9f && ScrollX * ScrollXRatio <= 0.9f && ScrollY * ScrollYRatio >= -0.9f && ScrollY * ScrollYRatio <= 0.9f) {
            SetScrollX = 0;
            SetScrollY = 0;
            Scrollio   = false;
            runScroll  = false;
        }
    }
    return nowScrollX;
}

void ImguiAndroidInput::setMaxFPS(int MAX_FPS) {
    this->max_fps = MAX_FPS;
}


void ImguiAndroidInput::StartLockWheelingWindow(ImGuiWindow *window) {
    if (g->WheelingWindow == window) {
        return;
    }
    g->WheelingWindow            = window;
    g->WheelingWindowRefMousePos = g->IO.MousePos;
    g->WheelingWindowTimer       = 2.0f;
}


float ImguiAndroidInput::funScroll(ImGuiWindow *Window) {
    if (!Window) {
        return 0.0f;
    }
    StartLockWheelingWindow(Window);
    nowScrollX = Window->Scroll.x;
    nowScrollY = Window->Scroll.y;
    runScroll  = true;
    if (io->isMouseMove) {
        ImGui::SetScrollX(Window, Window->Scroll.x - io->MouseDelta.x);
        ImGui::SetScrollY(Window, Window->Scroll.y - io->MouseDelta.y);
        upio = false;
    } else {
        if (!upio) {
            if (TOUCH_TIME > 300) {
                SetScrollX = 0;
                SetScrollY = 0;
                Scrollio   = false;
                runScroll  = false;
            }
            Seed_up    = abs(SetScrollX) / (TOUCH_TIME);
            ScrollX    = SetScrollX / (TOUCH_TIME / 1000 * (float) fps);
            SetScrollX *= Seed_up * f;
            ScrollXMAX = SetScrollX;
            Seed_up    = abs(SetScrollY) / (TOUCH_TIME);
            ScrollY    = SetScrollY / (TOUCH_TIME / 1000 * (float) fps);
            SetScrollY *= Seed_up * f;
            ScrollYMAX = SetScrollY;
            upio       = true;
        }
        ScrollXRatio = (SetScrollX / ScrollXMAX);
        ScrollYRatio = (SetScrollY / ScrollYMAX);

        if (nowScrollX > 0.0f && nowScrollX < Window->ScrollMax.x) {
            ImGui::SetScrollX(Window, nowScrollX - ScrollX * ScrollXRatio);
        } else {
            ScrollX = 0.0f;
        }
        if (nowScrollY > 0.0f && nowScrollY < Window->ScrollMax.y) {
            ImGui::SetScrollY(Window, nowScrollY - ScrollY * ScrollYRatio);
        } else {
            ScrollY = 0.0f;
        }
        SetScrollX -= (ScrollX * ScrollXRatio);
        SetScrollY -= (ScrollY * ScrollYRatio);
        if (ScrollX * ScrollXRatio >= -0.9f && ScrollX * ScrollXRatio <= 0.9f && ScrollY * ScrollYRatio >= -0.9f && ScrollY * ScrollYRatio <= 0.9f) {
            SetScrollX = 0;
            SetScrollY = 0;
            Scrollio   = false;
            runScroll  = false;
        }
    }
    return nowScrollX;
}

void ImguiAndroidInput::setImguiContext(ImGuiContext *g_) {
    this->g = g_;
}

void ImguiAndroidInput::setwin(ImGuiWindow *g_window_) {
    this->g_window = g_window_;
}

