package com.sameer.arora;

import android.app.Activity;
import android.app.Application;
import android.app.Instrumentation;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.graphics.Color;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Handler;
import android.util.ArrayMap;
import android.view.View;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.cardview.widget.CardView;

import com.tomer.fadingtextview.FadingTextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.ref.WeakReference;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.Locale;

import dalvik.system.DexClassLoader;
import io.github.rupinderjeet.kprogresshud.KProgressHUD;
import io.michaelrocks.paranoid.Obfuscate;

@Obfuscate
public class MainActivity extends Activity {

    Context ctx;
    private Prefs prefs;
    CardView cardView;
    Button downBtn;
    TextView warningTxt;
    RelativeLayout ancCard,warningCard;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_LIGHT_STATUS_BAR);
        setContentView(R.layout.activity_main);

        String[] texts = {"SparkLoader v2.2","Best in-Class Cheats","Made by SparkSkillz"};
        FadingTextView fadingTextView = findViewById(R.id.appTitle);
        fadingTextView.setTimeout(5000);
        fadingTextView.setTexts(texts);

        ctx = this;
        prefs = Prefs.with(ctx);

        if(!prefs.contains(Const.SVERSION)){
            prefs.write(Const.SVERSION, BuildConfig.VERSION_NAME);
        }

        warningCard = findViewById(R.id.warningCard);
        ancCard = findViewById(R.id.ancCard);

        Button launchBtn = findViewById(R.id.launchBtn);
        downBtn = findViewById(R.id.downBtn);
        Button refreshBtn = findViewById(R.id.refreshBtn);

        warningTxt = findViewById(R.id.warningTxt);
        cardView = findViewById(R.id.cardView);

        warningCard.setVisibility(View.GONE);
        if (!isInternetAvailable()) {
            warningCard.setVisibility(View.VISIBLE);
            warningTxt.setText("Failed to Check for Update, Please Check your internet connection, and if problem persist, then download a newer loader from Loader");
            ancCard.setVisibility(View.GONE);
            cardView.setVisibility(View.GONE);
        }

        launchBtn.setVisibility(View.GONE);
        if(prefs.contains(Const.PLUG_DIR) && prefs.contains(Const.PVERSION)){
            launchBtn.setVisibility(View.VISIBLE);
            downBtn.setText("Re-Download");
            TextView version = findViewById(R.id.version);
            version.setText("v"+prefs.read(Const.PVERSION));
        }

        launchBtn.setOnClickListener(view -> launchLoader());

        downBtn.setOnClickListener(view -> {
            if (isInternetAvailable()) {
                downloadLoader();
            } else {
                warningCard.setVisibility(View.VISIBLE);
                warningTxt.setText("Failed To Download, Please Check your internet connection, and if problem persist, then download a newer loader from Loader");
                cardView.setVisibility(View.GONE);
            }
        });

        refreshBtn.setOnClickListener(View -> Utils.triggerRebirth(this));

        KProgressHUD dialog = KProgressHUD.create(this)
                .setStyle(KProgressHUD.Style.SPIN_INDETERMINATE)
                .setLabel("Refreshing Loader")
                .setCancellable(false)
                .setAnimationSpeed(2)
                .setDimAmount(0.5f)
                .show();

        new Thread(() -> {
            try {
                HttpURLConnection connection = (HttpURLConnection) new URL(Const.UPDATE_LINK).openConnection();
                connection.setRequestMethod("GET");
                connection.setInstanceFollowRedirects(true);
                connection.setConnectTimeout(10000);
                connection.setReadTimeout(10000);
                connection.setRequestProperty("Connection", "close");
                connection.connect();
                int responseCode = connection.getResponseCode();
                if (responseCode != 200) {
                    throw new IOException("Request Code Not 200");
                }

                JSONObject update;

                InputStream inputStream = connection.getInputStream();
                ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                byte[] bArr = new byte[8192];
                while (true) {
                    long read = inputStream.read(bArr, 0, 8192);
                    if (read != -1) {
                        byteArrayOutputStream.write(bArr, 0, (int) read);
                    } else {
                        inputStream.close();
                        connection.disconnect();
                        update = new JSONObject(byteArrayOutputStream.toString("UTF-8"));
                        break;
                    }
                }

                final String newSVer = update.getJSONObject(Const.STUB).getString(Const.VERSION);
                final String currSVer = prefs.read(Const.PVERSION, BuildConfig.VERSION_NAME);

                if (!currSVer.equals(newSVer)) {
                    runOnUiThread(() -> {
                        downBtn.setTextColor(Color.parseColor("#00ff00"));
                        downBtn.setText("Update " + newSVer);
                    });
                }
            } catch (IOException | JSONException e) {
                e.printStackTrace();
                runOnUiThread(() -> {
                    dialog.dismiss();
                    warningCard.setVisibility(View.VISIBLE);
                    warningTxt.setText("Failed to Check for Update, Please Check your internet connection, and if problem persist, then download a newer loader from Loader");
                    cardView.setVisibility(View.GONE);
                });
            }
            dialog.dismiss();
        }).start();
    }

    private void launchLoader() {
        // Loads plugin and launch it
        File loaderPath = new File(prefs.read(Const.PLUG_DIR), Const.PLUG_NAME);
        if(loaderPath.exists()) {
            try {
                changeClassLoader(loaderPath.getAbsolutePath());
                ResourcePatcher.Patch(this, loaderPath.getAbsolutePath());
                Application app = changeTopApplication(a.a.class.getName());
                if (app != null) {
                    app.onCreate();
                }
                startActivity(new Intent(MainActivity.this, a.b.class));
                finish();
            } catch (Throwable throwable) {
                Toast.makeText(ctx, throwable.getMessage(), Toast.LENGTH_SHORT).show();
                throwable.printStackTrace();
            }
        }
    }

    public void downloadLoader() {
        KProgressHUD dialog = KProgressHUD.create(this)
                .setStyle(KProgressHUD.Style.SPIN_INDETERMINATE)
                .setLabel("Downloading")
                .setCancellable(false)
                .setAnimationSpeed(2)
                .setDimAmount(0.5f)
                .show();
        new Thread(() -> {
            try {
                HttpURLConnection connection = (HttpURLConnection) new URL(Const.UPDATE_LINK).openConnection();
                connection.setRequestMethod("GET");
                connection.setInstanceFollowRedirects(true);
                connection.setConnectTimeout(10000);
                connection.setReadTimeout(10000);
                connection.setRequestProperty("Connection", "close");
                connection.connect();
                int responseCode = connection.getResponseCode();
                if (responseCode != 200) {
                    throw new IOException("Request Code Not 200");
                }

                JSONObject update;

                InputStream inputStream = connection.getInputStream();
                ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                byte[] bArr = new byte[8192];
                while (true) {
                    long read = inputStream.read(bArr, 0, 8192);
                    if (read != -1) {
                        byteArrayOutputStream.write(bArr, 0, (int) read);
                    } else {
                        inputStream.close();
                        connection.disconnect();
                        update = new JSONObject(byteArrayOutputStream.toString("UTF-8"));
                        break;
                    }
                }

                final String newSVer = update.getJSONObject(Const.STUB).getString(Const.VERSION);
                final String currSVer = prefs.read(Const.SVERSION, BuildConfig.VERSION_NAME);


                String version = update.getJSONObject(Const.PLUGIN).getString(Const.VERSION);
                String dlLink = update.getJSONObject(Const.PLUGIN).getString(Const.URL);

                File loaderDir = new File(getFilesDir(), Const.PLUGIN);
                if(loaderDir.exists()){
                    Utils.deleteRecursive(loaderDir);
                }
                loaderDir.mkdir();

                if(!prefs.contains(Const.PLUG_DIR)){
                    prefs.write(Const.PLUG_DIR, loaderDir.getAbsolutePath());
                }

                File loaderPath = new File(loaderDir, Const.PLUG_NAME);

                connection = (HttpURLConnection) new URL(dlLink).openConnection();
                connection.setRequestMethod("GET");
                connection.setInstanceFollowRedirects(true);
                connection.setConnectTimeout(10000);
                connection.setReadTimeout(10000);
                connection.setRequestProperty("Connection", "close");
                connection.connect();
                responseCode = connection.getResponseCode();
                if (responseCode != 200) {
                    throw new IOException("Request Code Not 200");
                }

                InputStream bStream = connection.getInputStream();
                FileOutputStream fileOut = new FileOutputStream(loaderPath);

                byte[] data = new byte[1024];
                long total = 0;
                int count;
                while ((count = bStream.read(data)) != -1) {
                    total += count;
                    long finalTotal = total;
                    runOnUiThread(() -> {
                        float curr = (float)(finalTotal / 1024) / 1024;
                        String txt = String.format(Locale.getDefault(),"Downloading PUBGM [64-bit] ( %.2fMB )", curr);
                        dialog.setLabel(txt);
                    });
                    fileOut.write(data, 0, count);
                }

                bStream.close();
                fileOut.flush();
                fileOut.close();
                connection.disconnect();
                runOnUiThread(() -> {
                    dialog.dismiss();
                    prefs.write(Const.PVERSION, version);
                    new Handler().postDelayed(() -> Utils.triggerRebirth(ctx), 100);
                });
            } catch (IOException | JSONException e) {
                e.printStackTrace();
                runOnUiThread(() -> {
                    dialog.dismiss();
                    warningCard.setVisibility(View.VISIBLE);
                    warningTxt.setText("Failed To Download, Please Check your internet connection, and if problem persist, then download a newer loader from Loader");
                    cardView.setVisibility(View.GONE);
                });
            }
        }).start();
    }

    private boolean isInternetAvailable() {
        ConnectivityManager connectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetworkInfo = null;
        if (connectivityManager != null) {
            activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
        }
        return activeNetworkInfo != null && activeNetworkInfo.isConnected();
    }

    //ClassLoader Patch
    private void changeClassLoader(String apkPath){
        try {
            Class<?> activityThreadClass = Class.forName("android.app.ActivityThread");
            Method currentActivityThreadMethod = activityThreadClass.getDeclaredMethod("currentActivityThread");
            Object activityThread = currentActivityThreadMethod.invoke(null);
            Field mPackagesField = activityThreadClass.getDeclaredField("mPackages");
            mPackagesField.setAccessible(true);
            ArrayMap mPackages = (ArrayMap) mPackagesField.get(activityThread);
            WeakReference<?> loadedApkRef = (WeakReference) mPackages.get(getPackageName());
            Class<?> loadedApkClass = Class.forName("android.app.LoadedApk");
            ClassLoader newCL = createDexLoader(apkPath, getClassLoader().getParent());
            setAppClassLoader(loadedApkClass, loadedApkRef, newCL);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private Application changeTopApplication(String appClassName) {
        Object currentActivityThread = Reflector.invokeMethod("android.app.ActivityThread", null,
                "currentActivityThread", new Object[]{});
        Object mBoundApplication = Reflector.getFieldValue("android.app.ActivityThread", currentActivityThread, "mBoundApplication");
        Object loadedApkInfo = Reflector.getFieldValue("android.app.ActivityThread$AppBindData", mBoundApplication, "info");
        Reflector.setFieldValue("android.app.LoadedApk", loadedApkInfo, "mApplication", null);
        Object oldApplication = Reflector.getFieldValue("android.app.ActivityThread", currentActivityThread, "mInitialApplication");
        ArrayList<Application> mAllApplications = (ArrayList<Application>)
                Reflector.getFieldValue("android.app.ActivityThread", currentActivityThread, "mAllApplications");
        if (mAllApplications != null) {
            mAllApplications.remove(oldApplication);
        }
        ApplicationInfo loadedApk = (ApplicationInfo) Reflector.getFieldValue("android.app.LoadedApk", loadedApkInfo, "mApplicationInfo");
        ApplicationInfo appBindData = (ApplicationInfo) Reflector.getFieldValue("android.app.ActivityThread$AppBindData",
                mBoundApplication, "appInfo");
        loadedApk.className = appClassName;
        appBindData.className = appClassName;
        Application app = (Application) Reflector.invokeMethod(
                "android.app.LoadedApk", loadedApkInfo, "makeApplication",
                new Object[]{false, null},
                boolean.class, Instrumentation.class);
        Reflector.setFieldValue("android.app.ActivityThread", currentActivityThread, "mInitialApplication", app);
        return app;
    }

    private void setAppClassLoader(Class<?> loadedApkClass, WeakReference<?> loadedApkRef, ClassLoader newClassLoader) {
        try {
            Field mClassLoaderField = loadedApkClass.getDeclaredField("mClassLoader");
            mClassLoaderField.setAccessible(true);
            mClassLoaderField.set(loadedApkRef.get(), newClassLoader);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private ClassLoader createDexLoader(String appPath, ClassLoader parent) {
        try {
            File odexDir = getCacheDir();
            String libPath = getApplicationInfo().nativeLibraryDir;
            ClassLoader dexClassLoader;
            if (parent != null) {
                dexClassLoader = new DexClassLoader(appPath, odexDir.getAbsolutePath(), libPath, parent);
            } else {
                dexClassLoader = new DexClassLoader(appPath, odexDir.getAbsolutePath(), libPath, getClassLoader());
            }
            return dexClassLoader;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
