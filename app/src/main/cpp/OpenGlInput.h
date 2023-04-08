#ifndef FIND_ROODS_IMGUI_ANDROID_INPUT_H
#define FIND_ROODS_IMGUI_ANDROID_INPUT_H
#include <mutex>
#include "timer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <jni.h>
#include <unistd.h>

typedef struct ClassInfo {
	JavaVM *jvm;
	jobject obj;
	jclass pJclass;
	jclass  AssGLSL;
	jclass   GLFont;
	jmethodID show;
	jmethodID io;
	jmethodID openInput;
	jmethodID closeInput;
	jmethodID isLongTouch;
};

using namespace std;
class ImguiAndroidInput{

	enum eTouchEvent {
		TOUCH_DOWN,
		TOUCH_UP,
		TOUCH_MOVE,
		TOUCH_CANCEL,
		TOUCH_OUTSIDE
	};

	timer TOUCH_TIMER;
	float DOWN_x;
	float DOWN_y;
	bool moveio;
	float SetScrollX;
	float SetScrollY;
	float ScrollXMAX;
	float ScrollYMAX;
	float TOUCH_TIME;

	float nowScrollX;
	float nowScrollY;
	float Seed_up;

	float ScrollXRatio;
	float ScrollYRatio;
	
	enum InputAction {
		Action_DOWN,
		Action_UP
	};

	static inline int ActiveInputsw;
	static inline std::condition_variable cond;
	static inline char *Copybuf;
	std::mutex Copylk;
	static inline const char *Pastebuf;
	std::mutex Pastelk;
	static inline int SelectSize;
	std::mutex Selectlk;
	std::mutex Cutlk;
	ImGuiIO* io;
	ImGuiContext *g = nullptr;
	unsigned int touchTime = 0;
	static inline void Copy(ImGuiInputTextCallbackData *CallbackData);
	static inline void Paste(ImGuiInputTextCallbackData *CallbackData);
	static inline void SelectAll(ImGuiInputTextCallbackData *CallbackData);
	static inline void Cut(ImGuiInputTextCallbackData *CallbackData);
	void StartLockWheelingWindow(ImGuiWindow* window);

public:

	ImGuiWindow *g_window = nullptr;
	ImguiAndroidInput(){};
	void initImguiIo(ImGuiIO* io);
	void setwin(ImGuiWindow *g_window_);
	void setImguiContext(ImGuiContext *g_);
	void toast(string &str) const;
	void ioset(jint pos,jint v) const;
	bool openInput();
	bool closeInput();
	void isLongTouch(int x,int y);
	bool loopRun = false;
	void longTouchLoop();
	void funMshowinit(jclass thiz, JNIEnv *env);
	void setMaxFPS(int MAX_FPS);
	
	static int inputCallback(ImGuiInputTextCallbackData *CallbackData);
	string JNI_Cut();
	int JNI_SelectAll();
	void JNI_Paste(string data);
	string JNI_Copy();
	void addUTF8(const char * in_data);
	void InputKey(int action,int code);
	
	bool Inputio;
	bool Scrollio;
	bool Activeio;
	float ScrollX;
	float ScrollY;
	float f;
	void InputTouchEvent(int event_get_action,float x,float y);
	float funScroll();
    float funScroll(ImGuiWindow* Window);
	bool runScroll = false;
	bool upio = false;
	int fps;
	int max_fps = 0;
	bool oldio   = false;
	bool oldiow  = false;
	bool winio;
	bool fullwinio;
	float winWidth;
	float winHeight;
	float oldwinWidth;
	float oldwinHeight;
	bool ItemActive;
	bool ItemHovered;
	bool ItemFocused;
	bool ItemEdited;
	bool ItemScrollio;
	static ClassInfo gClassInfo;
};

#endif
