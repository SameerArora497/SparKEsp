LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := openGL_lib

LOCAL_SRC_FILES := imgui/imgui.cpp\
imgui/imgui_draw.cpp\
imgui/imgui_impl_android.cpp\
imgui/imgui_impl_opengl3.cpp\
imgui/imgui_tables.cpp\
imgui/imgui_widgets.cpp\
desilib.cpp\
OpenGlInput.cpp\
imguipp.cpp
#ImguiInEgl.cpp\
#native_draw.cpp\
#native_initial.cpp

LOCAL_CPP_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Socket
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Client

LOCAL_CPPFLAGS := -ffunction-sections -fdata-sections -fvisibility=hidden
LOCAL_CPPFLAGS += -fno-rtti -fno-exceptions
LOCAL_CPPFLAGS += -DNDEBUG

LOCAL_LDFLAGS += -Wl,--gc-sections
LOCAL_LDFLAGS += -L$(SYSROOT)/usr/lib -lz -llog
#openGl
LOCAL_LDFLAGS += -llog -lEGL -lGLESv2 -landroid
LOCAL_CFLAGS += -std=c++14

include $(BUILD_SHARED_LIBRARY)
