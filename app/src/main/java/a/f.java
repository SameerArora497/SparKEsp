package a;

import android.content.Context;
import android.graphics.Canvas;

import com.sparkskillz.pubg.extra.ESPView;

public class f {

    public native static String GetPkg();
    public native static void getReady();

    public native static int gettime();
    public native static String Check(Context mContext, String userKey);

    public static native void AimbotValue(String key, int isActive);
    public static native void ItemValue(String key, boolean isActive);
    public static native void SwitchValue(String key, boolean isActive);
    public native static boolean SwitchMemory(String key, boolean isActive);

    public static native int Init();
    public static native void Stop();
    public static native void DrawOn(ESPView espView, Canvas canvas);
}
