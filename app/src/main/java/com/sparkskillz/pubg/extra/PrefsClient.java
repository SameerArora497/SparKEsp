package com.sparkskillz.pubg.extra;

import android.content.Context;
import android.content.SharedPreferences;

import java.util.Set;

public class PrefsClient {

    private static final String LENGTH = "_length";
    private static final String DEFAULT_STRING_VALUE = "";
    private static final int DEFAULT_INT_VALUE = -1;
    private static final double DEFAULT_DOUBLE_VALUE = -1d;
    private static final float DEFAULT_FLOAT_VALUE = -1f;
    private static final long DEFAULT_LONG_VALUE = -1L;
    private static final boolean DEFAULT_BOOLEAN_VALUE = false;
    private static PrefsClient prefsInstance;
    private SharedPreferences sharedPreferences;

    private PrefsClient(Context context) {
        //Log.e("KMODS PrefsClient", "PrefsClient 1");
        sharedPreferences = context.getApplicationContext().getSharedPreferences(
                context.getPackageName() + "_preferences",
                Context.MODE_PRIVATE
        );
    }

    private PrefsClient(Context context, String preferencesName) {
        //Log.e("KMODS PrefsClient", "PrefsClient 2");
        sharedPreferences = context.getApplicationContext().getSharedPreferences(
                preferencesName,
                Context.MODE_PRIVATE
        );
    }

    public static PrefsClient with(Context context) {
        //Log.e("KMODS PrefsClient", "PrefsClient with 1");
        if (prefsInstance == null) {
            prefsInstance = new PrefsClient(context);
        }
        return prefsInstance;
    }

    public static PrefsClient with(Context context, boolean forceInstantiation) {
        //Log.e("KMODS PrefsClient", "PrefsClient with 2");
        if (forceInstantiation) {
            prefsInstance = new PrefsClient(context);
        }
        return prefsInstance;
    }

    public static PrefsClient with(Context context, String preferencesName) {
       // Log.e("KMODS PrefsClient", "PrefsClient with 3");
        if (prefsInstance == null) {
            prefsInstance = new PrefsClient(context, preferencesName);
        }
        return prefsInstance;
    }

    public static PrefsClient with(Context context, String preferencesName, boolean forceInstantiation) {
        //Log.e("KMODS PrefsClient", "PrefsClient with 4");
        if (forceInstantiation) {
            prefsInstance = new PrefsClient(context, preferencesName);
        }
        return prefsInstance;
    }

    // String related methods

    public String read(String what) {
       // Log.e("KMODS PrefsClient", "read 1");
        return sharedPreferences.getString(what, DEFAULT_STRING_VALUE);
    }

    public boolean readkey(String what) {
        // Log.e("KMODS PrefsClient", "read 1");
        return sharedPreferences.getBoolean(what, DEFAULT_BOOLEAN_VALUE);
    }

    public String read(String what, String defaultString) {
        //Log.e("KMODS PrefsClient", "read 2");
        return sharedPreferences.getString(what, defaultString);
    }

    public void write(String where, String what) {
        //Log.e("KMODS PrefsClient", "write 1");
        sharedPreferences.edit().putString(where, what).apply();
    }

    public void writekey(String where, boolean what) {
        //Log.e("KMODS PrefsClient", "write 1");
        sharedPreferences.edit().putBoolean(where, what).apply();
    }

    // int related methods

    public int readInt(String what) {
        //Log.e("KMODS PrefsClient", "readInt 1");
        return sharedPreferences.getInt(what, DEFAULT_INT_VALUE);
    }

    public int readInt(String what, int defaultInt) {
        //Log.e("KMODS PrefsClient", "readInt 2");
        return sharedPreferences.getInt(what, defaultInt);
    }

    public void writeInt(String where, int what) {
        //Log.e("KMODS PrefsClient", "writeInt 1");
        sharedPreferences.edit().putInt(where, what).apply();
    }

    // double related methods

    public double readDouble(String what) {
        //Log.e("KMODS PrefsClient", "readDouble 1");
        if (!contains(what))
            return DEFAULT_DOUBLE_VALUE;
        return Double.longBitsToDouble(readLong(what));
    }

    public double readDouble(String what, double defaultDouble) {
        //Log.e("KMODS PrefsClient", "readDouble 2");
        if (!contains(what))
            return defaultDouble;
        return Double.longBitsToDouble(readLong(what));
    }

    public void writeDouble(String where, double what) {
        //Log.e("KMODS PrefsClient", "writeDouble 1");
        writeLong(where, Double.doubleToRawLongBits(what));
    }

    // float related methods

    public float readFloat(String what) {
        //Log.e("KMODS PrefsClient", "readFloat 1");
        return sharedPreferences.getFloat(what, DEFAULT_FLOAT_VALUE);
    }

    public float readFloat(String what, float defaultFloat) {
        //Log.e("KMODS PrefsClient", "readFloat 2");
        return sharedPreferences.getFloat(what, defaultFloat);
    }

    public void writeFloat(String where, float what) {
        //Log.e("KMODS PrefsClient", "writeFloat 1");
        sharedPreferences.edit().putFloat(where, what).apply();
    }

    // long related methods

    public long readLong(String what) {
       // Log.e("KMODS PrefsClient", "readLong 1");
        return sharedPreferences.getLong(what, DEFAULT_LONG_VALUE);
    }

    public long readLong(String what, long defaultLong) {
        //Log.e("KMODS PrefsClient", "readLong 2");
        return sharedPreferences.getLong(what, defaultLong);
    }

    public void writeLong(String where, long what) {
        //Log.e("KMODS PrefsClient", "writeLong 1");
        sharedPreferences.edit().putLong(where, what).apply();
    }

    // boolean related methods

    public boolean readBoolean(String what) {
        //Log.e("KMODS PrefsClient", "readBoolean 1");
        return readBoolean(what, DEFAULT_BOOLEAN_VALUE);
    }

    public boolean readBoolean(String what, boolean defaultBoolean) {
        //Log.e("KMODS PrefsClient", "readBoolean 2");
        return sharedPreferences.getBoolean(what, defaultBoolean);
    }

    public void writeBoolean(String where, boolean what) {
        //Log.e("KMODS PrefsClient", "writeBoolean 1");
        sharedPreferences.edit().putBoolean(where, what).apply();
    }

    // String set methods

    public void putStringSet(final String key, final Set<String> value) {
        //Log.e("KMODS PrefsClient", "putStringSet 1");
        sharedPreferences.edit().putStringSet(key, value).apply();
    }

    public Set<String> getStringSet(final String key, final Set<String> defValue) {
        //Log.e("KMODS PrefsClient", "getStringSet 1");
        return sharedPreferences.getStringSet(key, defValue);
    }

    // end related methods

    public void remove(final String key) {
        //Log.e("KMODS PrefsClient", "remove 1");
        if (contains(key + LENGTH)) {
            // Workaround for pre-HC's lack of StringSets
            int stringSetLength = readInt(key + LENGTH);
            if (stringSetLength >= 0) {
                sharedPreferences.edit().remove(key + LENGTH).apply();
                for (int i = 0; i < stringSetLength; i++) {
                    sharedPreferences.edit().remove(key + "[" + i + "]").apply();
                }
            }
        }
        sharedPreferences.edit().remove(key).apply();
    }

    public boolean contains(final String key) {
        //Log.e("KMODS PrefsClient", "contains 1");
        return sharedPreferences.contains(key);
    }

    public void clear() {
        //Log.e("KMODS PrefsClient", "clear 1");
        sharedPreferences.edit().clear().apply();
    }
}