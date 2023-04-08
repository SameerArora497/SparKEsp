package com.sparkskillz.pubg;

import static a.f.GetPkg;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import a.b;
import a.c;
import a.e;
import io.michaelrocks.paranoid.Obfuscate;

@Obfuscate
public class MainActivity extends AppCompatActivity {

    Context ctx;
    int totalsecs;
    SharedPreferences m_Prefs;
    public static boolean isRoot;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTheme(R.style.AppTheme_MainScreen);
        setContentView(R.layout.activity_main);

        if (!Settings.canDrawOverlays(this)) {
            startActivity(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                    Uri.parse("package:" + getPackageName())));
        }

        ctx = this;
        m_Prefs = getSharedPreferences(getPackageName(), Context.MODE_PRIVATE);

        String str = "SPARK VERSION: V"+BuildConfig.VERSION_NAME+" | PUBG VERSION: 1.8+";
        TextView verText = findViewById(R.id.verText);
        verText.setText(str);

        LinearLayout startBtn = findViewById(R.id.startBtn);
        LinearLayout stopBtn = findViewById(R.id.stopBtn);

        startBtn.setOnClickListener(view -> {
            String gameName = GetPkg();
            Intent launchIntent = getPackageManager().getLaunchIntentForPackage(gameName);
            if (launchIntent != null) {
                ((ActivityManager)getSystemService(Activity.ACTIVITY_SERVICE)).killBackgroundProcesses(gameName);
                startActivity(launchIntent);
                new Handler().postDelayed(() -> startService(new Intent(ctx, c.class)), 3000);
            } else {
                Toast.makeText(ctx, "Game("+gameName+") is not installed!!", Toast.LENGTH_SHORT).show();
            }
        });

        stopBtn.setOnClickListener(view -> stopService(new Intent(ctx, c.class)));

        Button settingsBtn = findViewById(R.id.settingsBtn);
        settingsBtn.setOnClickListener(view -> startActivity(new Intent(ctx, e.class)));

        Button logoutBtn = findViewById(R.id.logoutBtn);
        logoutBtn.setOnClickListener(view -> {
            m_Prefs.edit().remove("USER_KEY").apply();
            m_Prefs.edit().remove("USER_PASS").apply();
            startActivity(new Intent(ctx, b.class));
            finish();
        });

        Button visitBtn = findViewById(R.id.visitBtn);
        visitBtn.setOnClickListener(view -> {
            Uri uri = Uri.parse("https:://telegram.me/SameerAroraYT");
            Intent intent = new Intent(Intent.ACTION_VIEW, uri);
            startActivity(intent);
        });

        TextView expiryStatus = findViewById(R.id.expiryStatus);
        totalsecs = getIntent().getIntExtra("time",0);
        Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @SuppressLint({"DefaultLocale"})
            @Override
            public void run() {
                if (totalsecs > 0) {
                    int seconds = totalsecs % 60;
                    int minutes = (totalsecs % 3600) / 60;
                    int hours = totalsecs / 3600;
                    int days = hours / 24;
                    hours = hours % 24;
                    expiryStatus.setText(String.format("Subscription Time: %01dD %01dH %01dM %01dS", days, hours, minutes, seconds));
                    totalsecs--;
                    handler.postDelayed(this,1000);
                } else {
                    Toast.makeText(ctx, "Key Expiredre...", Toast.LENGTH_SHORT).show();
                }
            }
        }, 0);

        loadAsset();
    }

    public void loadAsset() {
        String pathf = getFilesDir().toString()+"/sock";
        try {
            OutputStream myOutput = new FileOutputStream(pathf);
            byte[] buffer = new byte[1024];
            int length;
            InputStream myInput = getAssets().open("sock");
            while ((length = myInput.read(buffer)) > 0) {
                myOutput.write(buffer, 0, length);
            }
            myInput.close();
            myOutput.flush();
            myOutput.close();
            RunShell("chmod 777 "+pathf);
        } catch (IOException e) {
            Toast.makeText(this, e.getMessage(), Toast.LENGTH_SHORT).show();
        }
    }

    void RunShell(String Path) {
        try {
            Runtime.getRuntime().exec(new String[]{"sh","-c",Path});
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
