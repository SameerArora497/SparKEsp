package com.sparkskillz.pubg.extra;

import android.annotation.SuppressLint;
import android.os.Build;
import android.text.TextUtils;
import android.view.WindowManager;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class RecorderFakeUtils {

    public static final String ROM_MIUI = "MIUI";
    public static final String ROM_EMUI = "EMUI";
    public static final String ROM_FLYME = "FLYME";
    public static final String ROM_OPPO = "OPPO";
    public static final String ROM_SMARTISAN = "SMARTISAN";
    public static final String ROM_VIVO = "VIVO";
    public static final String ROM_QIKU = "QIKU";
    public static final String ROM_NUBIAUI = "NUBIAUI";
    public static final String ROM_ONEPLUS = "OXYGEN";
    public static final String ROM_SAMSUNG = "ONEUI";
    public static final String ROM_BLACKSHARK = "JOYUI";
    public static final String ROM_ROG = "REPLIBLIC";
    
    private static final String KEY_VERSION_MIUI = "ro.miui.ui.version.name";
    private static final String KEY_VERSION_EMUI = "ro.build.version.emui";
    private static final String KEY_VERSION_OPPO = "ro.build.version.opporom";
    private static final String KEY_VERSION_SMARTISAN = "ro.smartisan.version";
    private static final String KEY_VERSION_VIVO = "ro.vivo.os.version";
    private static final String KEY_VERSION_NUBIA = "ro.build.nubia.rom.name";
    private static final String KEY_VERSION_ONEPLIS = "ro.build.ota.versionname";
    private static final String KEY_VERSION_SAMSUNG = "ro.channel.officehubrow";
    private static final String KEY_VERSION_BLACKSHARK = "ro.blackshark.rom";
    private static final String KEY_VERSION_ROG = "ro.build.fota.version";
    private static String sName;

    //华为
    public static boolean isEmui() {
        return check(ROM_EMUI);
    }

    //小米
    public static boolean isMiui() {
        return check(ROM_MIUI);
    }

    //vivo
    public static boolean isVivo() {
        return check(ROM_VIVO);
    }

    //oppo
    public static boolean isOppo() {
        return check(ROM_OPPO);
    }

    //魅族
    public static boolean isFlyme() {
        return check(ROM_FLYME);
    }

    //红魔
    public static boolean isNubia() {
        return check(ROM_NUBIAUI);
    }

    //一加
    public static boolean isOnePlus() {
        return check(ROM_ONEPLUS);
    }

    //三星
    public static boolean isSanSung() {
        return check(ROM_SAMSUNG);
    }

    //黑鲨
    public static boolean isBLACKSHARK() {
        return check(ROM_BLACKSHARK);
    }

    //ROG
    public static boolean isRog() {
        return check(ROM_ROG);
    }

    public static boolean isActivice() { return false;}

    public static void setFakeRecorderWindowLayoutParams(WindowManager.LayoutParams layoutParams)  {
        try {
            /* 华为 OPPO VIVO 红魔 设置 Title 就行*/
            layoutParams.setTitle(RecorderFakeUtils.getFakeRecordWindowTitle());
            /* 下面是特殊的 */
            if (check(ROM_FLYME)) {
                /* 理论全系魅族 */
                if (!setMeizuParams(layoutParams, 0x2000)) {
                    if (isActivice()) {
                        setMeizuParams_new(layoutParams, 1024); //最新魅族
                    }
                }
            } else if (check(ROM_MIUI) || check(ROM_BLACKSHARK)) {
                /* 理论全系小米 黑鲨 */
                setXiaomiParams(layoutParams,6666);
            } else if (check(ROM_ONEPLUS) && (isActivice() || Build.VERSION.SDK_INT == 30)) {
                /* 一加 Android 11 测试通过 其他需要Xposed */
                Field privateflagField = layoutParams.getClass().getDeclaredField("PRIVATE_FLAG_IS_ROUNDED_CORNERS_OVERLAY");
                privateflagField.setAccessible(true);
                setOnePulsParams(layoutParams, (int)privateflagField.get(layoutParams.getClass()));
            } else if (isSanSung()) {
                /* 三星s7+平板 测试通过 */
                setSamsungFlags(layoutParams);
            } else if (check(ROM_ROG)) {
                /* ROG 测试通过 */
                layoutParams.memoryType |= 0x10000000;
            }
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private static boolean setXiaomiParams(WindowManager.LayoutParams params, int flagValue) {
        try {
            //layoutParams.flags = layoutParams.flags | WindowManager.LayoutParams.FLAG_DITHER;
            params.flags = params.flags | WindowManager.LayoutParams.FLAG_DITHER;
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    @SuppressLint("PrivateApi")
    private static boolean setMeizuParams(WindowManager.LayoutParams params, int flagValue) {
        try {
            Class MeizuParamsClass = Class.forName("android.view.MeizuLayoutParams");
            Field flagField = MeizuParamsClass.getDeclaredField("flags");
            flagField.setAccessible(true);
            Object MeizuParams = MeizuParamsClass.newInstance();
            flagField.setInt(MeizuParams, flagValue);
            Field mzParamsField = params.getClass().getField("meizuParams");
            mzParamsField.set(params, MeizuParams);
            return true;
        } catch (IllegalAccessException | ClassNotFoundException | NoSuchFieldException | InstantiationException e) {
            return false;
        }
    }

    private static boolean setMeizuParams_new(WindowManager.LayoutParams params, int flagValue) {
        try {
            Field mzParamsField = params.getClass().getDeclaredField("meizuFlags");
            mzParamsField.setAccessible(true);
            mzParamsField.setInt(params, flagValue);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private static void setOnePulsParams(WindowManager.LayoutParams params, int flagValue) {
        try {
            Field flagField = params.getClass().getDeclaredField("privateFlags");
            flagField.setAccessible(true);
            flagField.set(params, flagValue);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void setSamsungFlags(WindowManager.LayoutParams params) {
        try {
            Method semAddExtensionFlags = params.getClass().getMethod("semAddExtensionFlags", Integer.TYPE);
            Method semAddPrivateFlags = params.getClass().getMethod("semAddPrivateFlags", Integer.TYPE);
            semAddExtensionFlags.invoke(params, -2147352576);
            semAddPrivateFlags.invoke(params, params.flags);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    /**
     * 总结下可以操作的是 华为，魅族，OPPO，VIVO，红魔，小米，一加 ORG
     *
     * @return
     */
    private static String getFakeRecordWindowTitle() {
        if (sName == null) {
            check("");
        }
        if (sName == null) {
            return "";
        }
        switch (sName) {
            case ROM_MIUI:
                return "com.miui.screenrecorder";
            case ROM_EMUI:
                return "ScreenRecoderTimer";
            case ROM_OPPO:
                return "com.coloros.screenrecorder.FloatView";
            case ROM_VIVO:
                return "screen_record_menu";
            case ROM_ONEPLUS:
                return "op_screenrecord";
            case ROM_FLYME:
                return "SysScreenRecorder";
            case ROM_NUBIAUI:
                return "NubiaScreenDecorOverlay";
            case ROM_BLACKSHARK:
                return "com.blackshark.screenrecorder";
            case ROM_ROG:
                return "com.asus.force.layer.transparent.SR.floatingpanel";
        }
        return "";
    }

    private static boolean check(String rom) {
        if (sName != null) {
            return sName.equals(rom);
        }

        if (!TextUtils.isEmpty(getProp(KEY_VERSION_MIUI))) {
            sName = ROM_MIUI;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_BLACKSHARK))) {
            sName = ROM_BLACKSHARK;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_EMUI))) {
            sName = ROM_EMUI;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_OPPO))) {
            sName = ROM_OPPO;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_VIVO))) {
            sName = ROM_VIVO;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_SMARTISAN))) {
            sName = ROM_SMARTISAN;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_NUBIA))) {
            sName = ROM_NUBIAUI;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_ONEPLIS)) && getProp(KEY_VERSION_ONEPLIS).toLowerCase().contains("oxygen")) {
            sName = ROM_ONEPLUS;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_ROG)) && getProp(KEY_VERSION_ROG).toLowerCase().contains("CN_Phone")) {
            sName = ROM_ROG;
        } else if (!TextUtils.isEmpty(getProp(KEY_VERSION_SAMSUNG))) {
            sName = ROM_SAMSUNG;
        } else {
            String sVersion = Build.DISPLAY;
            if (sVersion.toUpperCase().contains(ROM_FLYME)) {
                sName = ROM_FLYME;
            } else {
                sName = Build.MANUFACTURER.toUpperCase();
            }
        }
        return sName.equals(rom);
    }

    private static String getProp(String name) {
        String line = null;
        BufferedReader input = null;
        try {
            Process p = Runtime.getRuntime().exec("getprop " + name);
            input = new BufferedReader(new InputStreamReader(p.getInputStream()), 1024);
            line = input.readLine();
            input.close();
        } catch (IOException ex) {
            return null;
        } finally {
            if (input != null) {
                try {
                    input.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return line;
    }

}



