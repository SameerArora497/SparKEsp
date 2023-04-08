#ifndef ESP_H
#define ESP_H

#include <jni.h>
#include "StructsCommon.h"

class ESP {
private:
    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;

public:
    ESP() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    ESP(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (_env != nullptr && _cvsView != nullptr && _cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getWidth", "()I");
			_env->DeleteLocalRef(canvas);
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getHeight", "()I");
			_env->DeleteLocalRef(canvas);
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    void DrawLine(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
			_env->DeleteLocalRef(canvasView);
        }
    }
	
	void SlideTo(int stat, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID slideto = _env->GetMethodID(canvasView, "SlideTo",
												"(IFFFF)V");
            _env->CallVoidMethod(_cvsView, slideto, (int) stat, start.x, start.y, end.x, end.y);
			_env->DeleteLocalRef(canvasView);
        }
    }

    void DrawText(Color color, const char *txt, Vector2 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 _env->NewStringUTF(txt), pos.x, pos.y, size);
			_env->DeleteLocalRef(canvasView);
        }
    }
	
	void DrawPlayerText(Color color, const wchar_t *txt, Vector2 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 wcstojstr(_env, txt), pos.x, pos.y, size);
			_env->DeleteLocalRef(canvasView);
        }
    }
	
	static jstring wcstojstr(JNIEnv *env, const wchar_t *input) {
        jobject bb = env->NewDirectByteBuffer((void *)input, wcslen(input) * sizeof(wchar_t));
        jstring UTF32LE = env->NewStringUTF("UTF-32LE");

        jclass charsetClass = env->FindClass("java/nio/charset/Charset");
        jmethodID forNameMethod = env->GetStaticMethodID(charsetClass, "forName", "(Ljava/lang/String;)Ljava/nio/charset/Charset;");
        jobject charset = env->CallStaticObjectMethod(charsetClass, forNameMethod, UTF32LE);

        jmethodID decodeMethod = env->GetMethodID(charsetClass, "decode", "(Ljava/nio/ByteBuffer;)Ljava/nio/CharBuffer;");
        jobject cb = env->CallObjectMethod(charset, decodeMethod, bb);

        jclass charBufferClass = env->FindClass("java/nio/CharBuffer");
        jmethodID toStringMethod = env->GetMethodID(charBufferClass, "toString", "()Ljava/lang/String;");
        jstring ret = (jstring)env->CallObjectMethod(cb, toStringMethod);

        env->DeleteLocalRef(bb);
        env->DeleteLocalRef(UTF32LE);
        env->DeleteLocalRef(charsetClass);
        env->DeleteLocalRef(charset);
        env->DeleteLocalRef(cb);
        env->DeleteLocalRef(charBufferClass);

        return ret;
    }

    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawFilledCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.x, pos.y, radius);
			_env->DeleteLocalRef(canvasView);
        }
    }
	
	void DrawCircle(Color color,float stroke, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke, pos.x, pos.y, radius);
			_env->DeleteLocalRef(canvasView);
        }
    }

    void DrawBox(Color color, float stroke, Rect rect) {
        Vector2 v1 = Vector2(rect.x, rect.y);
        Vector2 v2 = Vector2(rect.x + rect.width, rect.y);
        Vector2 v3 = Vector2(rect.x + rect.width, rect.y + rect.height);
        Vector2 v4 = Vector2(rect.x, rect.y + rect.height);
        DrawLine(color,stroke, v1, v2);
        DrawLine(color,stroke, v2, v3);
        DrawLine(color,stroke, v3, v4);
        DrawLine(color,stroke, v4, v1);
    }
	
	void DrawFilledRect(Color color, Vector2 pos, float width, float height) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledrect = _env->GetMethodID(canvasView, "DrawFilledRect",
                                                           "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.x, pos.y, width, height);
        }
    }
	
	void DrawSSHealth(Vector2 end, float health, float percent) {
		Rect Box(end.x - 124*percent, end.y - 30.0f*percent, 248*percent,10*percent);
		DrawBox(Color(0,0,0,120),1.6*percent,Box);
		float hw = (health*2.5)*percent;
		if(hw > 248*percent) { hw = 248*percent; }		
		Color clr = Color(0, 255, 0, 120);
        if (health <= (100 * 0.6)) {
            clr = Color(255, 255, 0, 120);
        }
        if (health < (100 * 0.3)) {
            clr = Color(255, 0, 0, 120);
        }
		DrawFilledRect(clr, Vector2(end.x - 124*percent, end.y - 30.0f*percent), hw,10*percent);  
    }
	
	void DrawOTH(Vector2 start, int num) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawOTH",
                                                   "(Landroid/graphics/Canvas;IFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, num, start.x, start.y);
        }
    }

    void DrawCrosshair(Color clr, Vector2 center, float size = 20) {
        float x = center.x - (size / 2.0f);
        float y = center.y - (size / 2.0f);
        DrawLine(clr, 3, Vector2(x, center.y), Vector2(x + size, center.y));
        DrawLine(clr, 3, Vector2(center.x, y), Vector2(center.x, y + size));
    }

    void DrawCurveRect(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            _env->CallVoidMethod(_cvsView, _env->GetMethodID(canvasView, "DrawCurvedRect",
                                                             "(Landroid/graphics/Canvas;IIIIFFFFF)V")
                    , _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }

    void DrawFilledCurveRect(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            _env->CallVoidMethod(_cvsView, _env->GetMethodID(canvasView, "DrawFilledCurvedRect",
                                                             "(Landroid/graphics/Canvas;IIIIFFFFF)V")
                    , _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.x, start.y, end.x, end.y);
        }
    }
};

#endif
