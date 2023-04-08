package com.sparkskillz.widgets;

import static a.f.AimbotValue;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.sparkskillz.pubg.R;

public class MenuSeekBar extends FrameLayout {

    String tittle,key,summary;
    int max,isActive;
    SharedPreferences m_Prefs;

    public MenuSeekBar(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);

        m_Prefs = context.getSharedPreferences(context.getPackageName(), Context.MODE_PRIVATE);

        if (attributeSet != null) {
            TypedArray typedArray = context.obtainStyledAttributes(attributeSet, R.styleable.MenuSwitch);
            isActive = typedArray.getInt(R.styleable.MenuSwitch_defaultValue,0);
            tittle = typedArray.getString(R.styleable.MenuSwitch_title);
            summary = typedArray.getString(R.styleable.MenuSwitch_summary);
            key = typedArray.getString(R.styleable.MenuSwitch_key);
            max = typedArray.getInt(R.styleable.MenuSwitch_max,0);

            try {
                View inflate = FrameLayout.inflate(getContext(), R.layout.menu_widget_seekbar, null);

                TextView tittletextView = inflate.findViewById(R.id.title);
                tittletextView.setText(tittle);

                TextView txt = inflate.findViewById(R.id.summary);
                if (summary != null) {
                    txt.setText(summary);
                } else {
                    txt.setVisibility(VISIBLE);
                }

                TextView seekbar_value = inflate.findViewById(R.id.seekbar_value);
                SeekBar seekbar = inflate.findViewById(R.id.seekbar);

                if (max != 0){
                    seekbar.setMax(max);
                }

                if (m_Prefs.contains(key)){
                    isActive = m_Prefs.getInt(key,0);
                    AimbotValue(key,isActive);
                }

                if (isActive != 0){
                    seekbar.setProgress(isActive);
                    seekbar_value.setText(""+isActive);
                } else {
                    seekbar_value.setText("0");
                }

                seekbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
                    @Override
                    public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                        seekbar_value.setText(""+i);
                        AimbotValue(key,i);
                        m_Prefs.edit().putInt(key,i).apply();
                    }

                    @Override
                    public void onStartTrackingTouch(SeekBar seekBar) {

                    }

                    @Override
                    public void onStopTrackingTouch(SeekBar seekBar) {

                    }
                });

                addView(inflate);
            } catch (Exception e) {
                Toast.makeText(context,e.getMessage(), Toast.LENGTH_SHORT).show();
            } finally {
                typedArray.recycle();
            }

        }
    }
}
