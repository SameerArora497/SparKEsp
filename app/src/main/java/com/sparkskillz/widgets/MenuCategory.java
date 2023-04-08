package com.sparkskillz.widgets;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.sparkskillz.pubg.R;

public class MenuCategory extends FrameLayout {

    String tittle,key,summary;

    public MenuCategory(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        if (attrs != null) {
            @SuppressLint("CustomViewStyleable")
            TypedArray typedArray = context.obtainStyledAttributes(attrs, R.styleable.MenuSwitch);
            tittle = typedArray.getString(R.styleable.MenuSwitch_title);
            key = typedArray.getString(R.styleable.MenuSwitch_key);
            summary = typedArray.getString(R.styleable.MenuSwitch_summary);
            typedArray.recycle();
        }
        View inflate = FrameLayout.inflate(getContext(), R.layout.menu_widget_category, null);

        TextView tittletextView = inflate.findViewById(R.id.title);
        tittletextView.setText(tittle);

        if (summary != null) {
            TextView txtsummary = inflate.findViewById(R.id.summary);
            txtsummary.setVisibility(VISIBLE);
            txtsummary.setText(summary);
        }

        addView(inflate);
    }

}
