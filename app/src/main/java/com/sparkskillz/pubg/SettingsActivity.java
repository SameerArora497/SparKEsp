package com.sparkskillz.pubg;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.sparkskillz.pubg.extra.SettingsFragment;

import io.michaelrocks.paranoid.Obfuscate;

@Obfuscate
public class SettingsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTheme(R.style.AppTheme_SettingScreen);
        setContentView(R.layout.activity_settings);
        getSupportActionBar().setTitle("Jill");
        if (findViewById(R.id.idFrameLayout) != null) {
            if (savedInstanceState != null) {
                return;
            }
            getFragmentManager().beginTransaction().add(R.id.idFrameLayout, new SettingsFragment()).commit();
        }
    }
}