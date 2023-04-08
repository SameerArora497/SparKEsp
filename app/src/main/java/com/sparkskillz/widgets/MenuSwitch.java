package com.sparkskillz.widgets;

import static a.f.SwitchMemory;
import static a.f.SwitchValue;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.sparkskillz.pubg.R;

public class MenuSwitch extends FrameLayout {

    boolean isActive;
    String tittle,key,summary;
    SharedPreferences m_Prefs;

    public MenuSwitch(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);

        m_Prefs = context.getSharedPreferences(context.getPackageName(), Context.MODE_PRIVATE);

        if (attributeSet != null) {
            TypedArray typedArray = context.obtainStyledAttributes(attributeSet, R.styleable.MenuSwitch);
            isActive = typedArray.getBoolean(R.styleable.MenuSwitch_defaultValue,false);
            tittle = typedArray.getString(R.styleable.MenuSwitch_title);
            key = typedArray.getString(R.styleable.MenuSwitch_key);
            summary = typedArray.getString(R.styleable.MenuSwitch_summary);

            try {
                View inflate = FrameLayout.inflate(getContext(), R.layout.menu_widget_switch, null);

                TextView tittletextView = inflate.findViewById(R.id.title);
                tittletextView.setText(tittle);

                if (summary != null) {
                    TextView txtsummary = inflate.findViewById(R.id.summary);
                    txtsummary.setVisibility(VISIBLE);
                    txtsummary.setText(summary);
                }

                @SuppressLint("UseSwitchCompatOrMaterialCode")
                Switch switchCompat = inflate.findViewById(R.id.checkbox);
                if (m_Prefs.contains(key)){
                    isActive = m_Prefs.getBoolean(key,false);
                    SwitchValue(key,isActive);
                }

                switchCompat.setChecked(isActive);

                inflate.setOnClickListener(view -> {
                    boolean bool = switchCompat.isChecked();
                    if (key.equals("pubg_less_recoil") || key.equals("pubg_bullet_track") || key.equals("pubg_sit_scope")){
                        String txt;
                        if (SwitchMemory(key,!bool)){
                            txt = key.equals("pubg_less_recoil") ? "Lobby Bypass Activated✅✅" : "Magic Bullet Activated✅✅";
                        } else {
                            txt = "Error or Function Cant be De-Activated";
                        }
                        Toast.makeText(getContext(), txt, Toast.LENGTH_SHORT).show();
                    } else {
                        SwitchValue(key,!bool);
                        m_Prefs.edit().putBoolean(key,!bool).apply();
                    }
                    switchCompat.setChecked(!bool);
                });

                addView(inflate);
            } catch (Exception e){
                Toast.makeText(context, e.getMessage(), Toast.LENGTH_SHORT).show();
            } finally {
                typedArray.recycle();
            }
        }
    }


}
