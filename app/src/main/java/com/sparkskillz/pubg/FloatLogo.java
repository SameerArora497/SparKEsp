package com.sparkskillz.pubg;

import static a.f.ItemValue;

import android.annotation.SuppressLint;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.graphics.PixelFormat;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.os.IBinder;
import android.view.GestureDetector;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.viewpager.widget.PagerAdapter;
import androidx.viewpager.widget.ViewPager;

import com.google.android.flexbox.FlexboxLayout;
import com.sparkskillz.pubg.extra.ESPView;
import com.sparkskillz.pubg.extra.RecorderFakeUtils;
import com.sparkskillz.widgets.NoScrollViewPager;

import java.io.IOException;

import io.michaelrocks.paranoid.Obfuscate;
import q.rorbin.verticaltablayout.TabAdapter;
import q.rorbin.verticaltablayout.VerticalTabLayout;

@Obfuscate
public class FloatLogo extends Service {

    Context floater;
    private String daemonPath;

    private WindowManager mWindowManager;
    private View mFloatingView;
    private View logoView;

    private ESPView overlayView;

    SharedPreferences sharedPreferences;
    private static boolean isRunning = false;

    public FloatLogo() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();

        floater = this;

        mWindowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
        sharedPreferences = getSharedPreferences(getPackageName(), Context.MODE_PRIVATE);

        try {
            DrawCanvas();
            FloatMenu();
            logoMenu();
            daemonPath = getFilesDir().getAbsolutePath() + "/sock 5";
            if (!isRunning) {
                startDaemon();
                isRunning = true;
            }
        } catch (Exception ex){
            Toast.makeText(this, ex.toString(), Toast.LENGTH_SHORT).show();
        }
    }

    private void FloatMenu(){
        mFloatingView = LayoutInflater.from(this).inflate(R.layout.float_menu, null);
        mFloatingView.setVisibility(View.GONE);
        mFloatingView.setAlpha(0.92f);
        final WindowManager.LayoutParams params = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.WRAP_CONTENT,
                WindowManager.LayoutParams.MATCH_PARENT,
                getLayoutType(),
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE,
                PixelFormat.RGBA_8888);
        params.gravity = Gravity.TOP | Gravity.START;
       // RecorderFakeUtils.setFakeRecorderWindowLayoutParams(params);
        mWindowManager.addView(mFloatingView, params);

        final GestureDetector gestureDetector = new GestureDetector(this, new SingleTapConfirm());

        VerticalTabLayout tablayout = mFloatingView.findViewById(R.id.main_tab);
        ViewPager viewpager = mFloatingView.findViewById(R.id.main_viewpager);
        viewpager.setAdapter(new MyPageAdapter(this));
        tablayout.setupWithViewPager(viewpager);

        mFloatingView.setOnTouchListener(new View.OnTouchListener() {
            private int initialX;
            private int initialY;
            private float initialTouchX;
            private float initialTouchY;

            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (gestureDetector.onTouchEvent(event)) {
                    logoView.setVisibility(View.VISIBLE);
                    mFloatingView.setVisibility(View.GONE);
                    return true;
                } else {
                    switch (event.getAction()) {
                        case MotionEvent.ACTION_DOWN:
                            initialX = params.x;
                            initialY = params.y;
                            initialTouchX = event.getRawX();
                            initialTouchY = event.getRawY();
                            return true;

                        case MotionEvent.ACTION_MOVE:
                            params.x = initialX + (int) (event.getRawX() - initialTouchX);
                            params.y = initialY + (int) (event.getRawY() - initialTouchY);
                            mWindowManager.updateViewLayout(mFloatingView, params);
                            return true;
                    }
                    return false;
                }
            }
        });
    }

    private void logoMenu () {
        logoView = LayoutInflater.from(this).inflate(R.layout.float_logo, null);
        logoView.setAlpha(0.75f);
        final WindowManager.LayoutParams params = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.WRAP_CONTENT,
                WindowManager.LayoutParams.WRAP_CONTENT,
                getLayoutType(),
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE,
                PixelFormat.RGBA_8888);
        params.gravity = Gravity.TOP | Gravity.START;
       // RecorderFakeUtils.setFakeRecorderWindowLayoutParams(params);
        mWindowManager.addView(logoView, params);

        final GestureDetector gestureDetector = new GestureDetector(this, new SingleTapConfirm());

        logoView.findViewById(R.id.relativeLayoutParent).setOnTouchListener(new View.OnTouchListener() {
            private int initialX;
            private int initialY;
            private float initialTouchX;
            private float initialTouchY;

            @SuppressLint("ClickableViewAccessibility")
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (gestureDetector.onTouchEvent(event)) {
                    logoView.setVisibility(View.GONE);
                    mFloatingView.setVisibility(View.VISIBLE);
                    return true;
                } else {
                    switch (event.getAction()) {
                        case MotionEvent.ACTION_DOWN:
                            initialX = params.x;
                            initialY = params.y;
                            initialTouchX = event.getRawX();
                            initialTouchY = event.getRawY();
                            return true;

                        case MotionEvent.ACTION_MOVE:
                            params.x = initialX + (int) (event.getRawX() - initialTouchX);
                            params.y = initialY + (int) (event.getRawY() - initialTouchY);
                            mWindowManager.updateViewLayout(logoView, params);
                            return true;
                    }
                    return false;
                }
            }
        });
    }

    private void DrawCanvas() throws PackageManager.NameNotFoundException {
        overlayView = new ESPView(this);
        final WindowManager.LayoutParams params = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.MATCH_PARENT,
                WindowManager.LayoutParams.MATCH_PARENT,
                getLayoutType(),
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL |
                        WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN |
                        WindowManager.LayoutParams.FLAG_FULLSCREEN,
                PixelFormat.TRANSLUCENT);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P)
            params.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        params.gravity = Gravity.TOP | Gravity.START;
        params.x = 0;
        params.y = 0;
        RecorderFakeUtils.setFakeRecorderWindowLayoutParams(params);
        mWindowManager.addView(overlayView, params);
    }

    private int getLayoutType() {
        int LAYOUT_FLAG;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_PHONE;
        } else {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_TOAST;
        }
        return LAYOUT_FLAG;
    }

    private void startDaemon(){
        new Thread(a.f::getReady).start();
        new Thread(a.f::Init).start();
        new Thread(() -> {
            String cmd = daemonPath;
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            RunShell(cmd);
        }).start();
    }

    class MyPageAdapter extends PagerAdapter implements TabAdapter {

        Context context;
        String[] title;
        int[] drawables;

        public MyPageAdapter(Context context) {
            this.context = context;
            title = new String[]{"ESP","Items","Memory","Settings"};
            drawables = new int[]{R.drawable.ic_player,R.drawable.ic_list,R.drawable.ic_binary, R.drawable.ic_settings};
        }

        @Override
        public int getCount() {
            return title.length;
        }

        @SuppressLint("InflateParams")
        @Override
        public View getTabItemView(int position) {
            LayoutInflater li = LayoutInflater.from(this.context);
            View v = li.inflate(R.layout.tab_item,null);

            @SuppressLint("UseCompatLoadingForDrawables")
            Drawable drawable = getDrawable(drawables[position]);
            ImageView imgView = v.findViewById(R.id.imgView);
            imgView.setImageDrawable(drawable);

            TextView titleTv = v.findViewById(R.id.titleTv);
            titleTv.setText(title[position]);
            return v;
        }

        @Override
        public boolean isViewFromObject(View view, Object object) {
            return view == object;
        }

        @NonNull
        @Override
        public Object instantiateItem(ViewGroup container, int position) {
            View view;
             if (position == 1) {
                view = LayoutInflater.from(container.getContext()).inflate(R.layout.items_list,container,false);
                VerticalTabLayout tablayout = view.findViewById(R.id.item_tab);
                NoScrollViewPager noScrollViewPager = view.findViewById(R.id.item_viewpager);
                noScrollViewPager.setAdapter(new MyAdapater(context));
                tablayout.setupWithViewPager(noScrollViewPager);
            } else if (position == 2) {
                 view = LayoutInflater.from(container.getContext()).inflate(R.layout.menu_memory,container,false);
            }  else if (position == 3) {
                view = LayoutInflater.from(container.getContext()).inflate(R.layout.menu_settings,container,false);
            } else {
                view = LayoutInflater.from(container.getContext()).inflate(R.layout.menu_esp,container,false);
            }
            container.addView(view);
            return view;
        }

        @Override
        public void destroyItem(ViewGroup container, int position, Object object) {
            container.removeView((View) object);
        }
    }

    class MyAdapater extends PagerAdapter implements TabAdapter {

        Context context;
        String[] title;

        String[] Rifles = {"AKM","AUG-A3","QBZ","M416","SCAR-L","M249","M16A4","DP28","Groza","M762"};

        String[] MachineGuns = {"UMP9","Thmopson SMG","Vector","P90","PP19-Bizon","Uzi"};

        String[] Snipers = {"AWM","Kar98k","SKS","Mini14","VSS","Win94","M24"};

        String[] Shotguns = {"S12K","S1897","S686","DBS"};

        String[] Pistols = {"P92","Skorpion","FlareGun","DesertEagle"};

        String[] Grenades = {"Fragnade","Molotov","Smoke","Stun","StickBomb"};

        String[] Ammos = {"9mm","7.62mm","5.56mm","300Magnum","Flare"};

        String[] Scopes = {"2x","3x","4x","6x","8x","RedDot","Canted Sight"};

        String[] Armors = {"Armor(L3)","Helmet(L3)","Bag(L3)"};

        String[] Medics = {"MedKit","FirstAid","Injection","Painkiller","EnergyDrink"};

        String[] Attachments = {"LazerSight","SniperEQ","LargeEQ"};

        String[] Vehicles = {"Plane","Buggy","Dacia","Rony","UAZ","Motorcycle",
                             "Motorcycle Cart","BigBoat","AquaRail","Monster Truck"};

        String[] Others = {"GasCan","Ghillie","LootBox","AirDrop"};

        public MyAdapater(Context context) {
            this.context = context;
            title = new String[]{"Rifles","Machine Guns","Snipers","Shotguns","Pistols","Grenades",
                                 "Ammos","Scopes","Extra","Medics","Attachments","Vehicles","Others"};
        }

        @Override
        public int getCount() {
            return title.length;
        }

        @Override
        public boolean isViewFromObject(View view, Object object) {
            return view == object;
        }

        String[] work;

        @NonNull
        @Override
        public Object instantiateItem(@NonNull ViewGroup container, int position) {
            View view = LayoutInflater.from(context).inflate(R.layout.items_pager,container,false);

            FlexboxLayout flexboxLayout = view.findViewById(R.id.container);
            if (position == 1){
                work = MachineGuns;
            } else if (position == 2) {
                work = Snipers;
            } else if (position == 3) {
                work = Shotguns;
            } else if (position == 4) {
                work = Pistols;
            } else if (position == 5) {
                work = Grenades;
            } else if (position == 6) {
                work = Ammos;
            } else if (position == 7) {
                work = Scopes;
            } else if (position == 8) {
                work = Armors;
            } else if (position == 9) {
                work = Medics;
            } else if (position == 10) {
                work = Attachments;
            } else if (position == 11) {
                work = Vehicles;
            } else if (position == 12) {
                work = Others;
            } else {
                work = Rifles;
            }
            for (String s : work) {
                LinearLayout linearLayout = (LinearLayout) LinearLayout.inflate(context,
                        R.layout.items_pager_item, null);
                ItemValue(s,getItemChecked(s));
                ((CheckBox) linearLayout.findViewById(R.id.checkbox)).setChecked(getItemChecked(s));
                ((TextView) linearLayout.findViewById(R.id.checkbox_text)).setText(s);
                flexboxLayout.addView(linearLayout);
            }

            view.findViewById(R.id.select_all).setOnClickListener(view1 -> {
                for (int i = 0;i<flexboxLayout.getFlexItemCount();i++) {
                    View view2 = (LinearLayout)flexboxLayout.getFlexItemAt(i);
                    TextView textView = view2.findViewById(R.id.checkbox_text);
                    String key = textView.getText().toString();
                    ItemValue(key,true);
                    setItemChecked(key,true);
                    CheckBox checkbox = view2.findViewById(R.id.checkbox);
                    checkbox.setChecked(true);
                }
            });

            view.findViewById(R.id.select_none).setOnClickListener(view12 -> {
                for (int i = 0;i<flexboxLayout.getFlexItemCount();i++) {
                    View view2 = (LinearLayout)flexboxLayout.getFlexItemAt(i);
                    TextView textView = view2.findViewById(R.id.checkbox_text);
                    String key = textView.getText().toString();
                    ItemValue(key,false);
                    setItemChecked(key,false);
                    CheckBox checkbox = view2.findViewById(R.id.checkbox);
                    checkbox.setChecked(false);
                }
            });

            container.addView(view);
            return view;
        }

        @Override
        public void destroyItem(ViewGroup container, int position, Object object) {
            container.removeView((View) object);
        }

        @Override
        public View getTabItemView(int position) {
            LayoutInflater li = LayoutInflater.from(this.context);
            View v = li.inflate(R.layout.tab_item,null);
            ImageView imgView = v.findViewById(R.id.imgView);
            imgView.setVisibility(View.GONE);
            TextView titleTv = v.findViewById(R.id.titleTv);
            titleTv.setText(title[position]);
            return v;
        }
    }

    private String getToast(String str1,String str2) {
        String version = "Running: "+str1+" v";
        try {
            version = version+getPackageManager().getPackageInfo(str2,0).versionName;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return version+" 64bit";
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        isRunning = false;
        if (mFloatingView != null) mWindowManager.removeView(mFloatingView);
        if (logoView != null) mWindowManager.removeView(logoView);
        if (overlayView != null) mWindowManager.removeView(overlayView);
    }

    boolean getItemChecked(String key){
        return sharedPreferences.getBoolean(key,false);
    }

    void setItemChecked(String key,boolean b){
        sharedPreferences.edit().putBoolean(key,b).apply();
    }

    void RunShell(String Path) {
        try {
            Runtime.getRuntime().exec(new String[]{"sh","-c",Path});
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class SingleTapConfirm extends GestureDetector.SimpleOnGestureListener {
    @Override
    public boolean onSingleTapUp(MotionEvent event) {
        return true;
    }
}

