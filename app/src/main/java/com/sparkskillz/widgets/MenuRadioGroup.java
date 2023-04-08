package com.sparkskillz.widgets;

import static a.f.AimbotValue;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;

import com.sparkskillz.pubg.R;

import java.util.Arrays;

public class MenuRadioGroup extends LinearLayout  {

    int isActive;
    String tittle,key;
    CharSequence[] radios;
    RadioButton[] radioButtons;
    SharedPreferences m_Prefs;

    public MenuRadioGroup(Context context, AttributeSet attributeSet) {
        super(context, attributeSet);

        m_Prefs = context.getSharedPreferences(context.getPackageName(), Context.MODE_PRIVATE);

        if (attributeSet != null) {
            TypedArray typedArray = context.obtainStyledAttributes(attributeSet, R.styleable.MenuSwitch);
            isActive = typedArray.getInt(R.styleable.MenuSwitch_defaultValue,0);
            tittle = typedArray.getString(R.styleable.MenuSwitch_title);
            key = typedArray.getString(R.styleable.MenuSwitch_key);
            radios = typedArray.getTextArray(R.styleable.MenuSwitch_entries);

            try {
                setOrientation(LinearLayout.VERTICAL);
                View inflate = LinearLayout.inflate(getContext(), R.layout.menu_widget_category, null);
                TextView tittletextView = inflate.findViewById(R.id.title);
                tittletextView.setText(tittle);
                addView(inflate);
                String getStr = removeFirstandLast(Arrays.toString(radios));
                String[] heys = getStr.split(",");
                int i2 = 0;
                int lenth = heys.length;
                radioButtons = new RadioButton[lenth];
                if (m_Prefs.contains(key)) {
                    isActive = m_Prefs.getInt(key,0);
                    AimbotValue(key,isActive);
                }
                while (i2 < lenth) {
                    LinearLayout linearLayout = (LinearLayout) LinearLayout.inflate(getContext(),
                            R.layout.menu_widget_radiobutton, null);
                    ((TextView) linearLayout.findViewById(R.id.title)).setText(radios[i2]);
                    RadioButton radioButton = linearLayout.findViewById(R.id.checkbox);
                    radioButton.setChecked(i2 == isActive);
                    linearLayout.setOnClickListener(view -> {
                        for (int i=0;i<lenth;i++) {
                            if (radioButtons[i] == radioButton) {
                                AimbotValue(key,i);
                                m_Prefs.edit().putInt(key,i).apply();
                                radioButton.setChecked(true);
                            } else {
                                radioButtons[i].setChecked(false);
                            }
                        }
                    });
                    addView(linearLayout);
                    radioButtons[i2] = radioButton;
                    i2++;
                }
            } catch (Exception e) {
                Toast.makeText(context, e.getMessage(), Toast.LENGTH_SHORT).show();
            } finally {
                typedArray.recycle();
            }
        }
    }

    String removeFirstandLast(String str) {
        str = str.substring(1, str.length() - 1);
        return str;
    }
}
