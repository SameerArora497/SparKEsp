package com.sparkskillz.pubg;

import static a.f.Check;
import static a.f.gettime;

import android.annotation.SuppressLint;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import a.d;
import io.michaelrocks.paranoid.Obfuscate;

@Obfuscate
public class LoginActivity extends AppCompatActivity {

    static {
        System.loadLibrary("SameerArora");
    }

    Context context;
    Button BtnLogin;
    EditText mail,pass;
    SharedPreferences m_Prefs;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTheme(R.style.AppTheme_LoginScreen);
        setContentView(R.layout.activity_login);

        context = this;
        m_Prefs = getSharedPreferences(getPackageName(), Context.MODE_PRIVATE);

        String str = "SPARK VERSION: V"+BuildConfig.VERSION_NAME+" | PUBG VERSION: 1.8+";
        TextView verText = findViewById(R.id.verText);
        verText.setText(str);

        mail = findViewById(R.id.username);
        pass = findViewById(R.id.pass);

        ImageView pasteIcon = findViewById(R.id.pasteIcon);
        pasteIcon.setOnClickListener(view -> {
            ClipboardManager clipboard = (ClipboardManager) getSystemService(CLIPBOARD_SERVICE);
            String ed = clipboard.getText().toString();
            if (ed.length() > 25 & !ed.equals("")) {
                mail.setText(ed.substring(0, 18));
                pass.setText(ed.substring(19, 27));
            } else {
                Toast.makeText(LoginActivity.this, "Invalid Key", Toast.LENGTH_LONG).show();
            }
        });

        BtnLogin = findViewById(R.id.loginBtn);
        BtnLogin.setOnClickListener(view ->  Login(mail.getText().toString()+":"+pass.getText().toString()));

        ImageView tgIcon = findViewById(R.id.tgIcon);
        tgIcon.setOnClickListener(view -> {
            Uri uri = Uri.parse("https:://telegram.me/SameerAroraYT");
            Intent intent = new Intent(Intent.ACTION_VIEW, uri);
            startActivity(intent);
        });

        if (m_Prefs.contains("USER_KEY") & m_Prefs.contains("USER_PASS")){
            mail.setText(m_Prefs.getString("USER_KEY",null));
            pass.setText(m_Prefs.getString("USER_PASS",null));
        }
    }

    void Login(final String userKey) {
        BtnLogin.setVisibility(View.GONE);

        ProgressBar pgBar = findViewById(R.id.pgBar);
        pgBar.setVisibility(View.VISIBLE);

        TextView pgBarText = findViewById(R.id.pgBarText);
        pgBarText.setVisibility(View.VISIBLE);

        @SuppressLint("HandlerLeak")
        Handler loginHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                if (msg.what == 1) {
                    pgBar.setVisibility(View.GONE);
                    pgBarText.setVisibility(View.GONE);
                    BtnLogin.setVisibility(View.VISIBLE);
                    Toast.makeText(context, msg.obj.toString(), Toast.LENGTH_SHORT).show();
                } else if (msg.what == 2) {
                    pgBarText.setText("Login ...");
                } else {
                    Intent i = new Intent(context, d.class);
                    i.putExtra("time",gettime());
                    startActivity(i);
                    Toast.makeText(context, "Login Success...", Toast.LENGTH_SHORT).show();
                    finish();
                }
            }
        };

        new Thread(() -> {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Message msg = new Message();
            if(!isInternetAvailable()){
                msg.what = 1;
                msg.obj = "connect server error.";
                loginHandler.sendMessage(msg);
            } else {
                loginHandler.sendEmptyMessage(2);
                String result = Check(context, userKey);
                if (result.equals("OK")) {
                    m_Prefs.edit().putString("USER_KEY", mail.getText().toString()).apply();
                    m_Prefs.edit().putString("USER_PASS", pass.getText().toString()).apply();
                    loginHandler.sendEmptyMessage(0);
                } else {
                    m_Prefs.edit().clear().apply();
                    msg.what = 1;
                    msg.obj = result;
                    loginHandler.sendMessage(msg);
                }
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
}
