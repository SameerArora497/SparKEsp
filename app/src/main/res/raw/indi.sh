echo "Antiban being Started"

PKGNAME=pubg.imobile

am force-stop com.tencent.ig
am force-stop com.pubg.krmobile
am force-stop com.rekoo.pubgm
am force-stop com.vng.pubgmobile
am force-stop com.pubg.imobile
am force-stop com.google.android.ims
am force-stop com.android.vending
am force-stop com.google.android.gsf
am force-stop com.google.android.webview

pkill com.tencent.ig
pkill com.pubg.krmobile
pkill com.rekoo.pubgm
pkill com.vng.pubgmobile
pkill com.pubg.imobile
pkill com.google.android.ims
pkill com.android.vending
pkill com.google.android.gsf
pkill com.google.android.webview

pkill com.tencent.ig
pkill com.pubg.krmobile
pkill com.rekoo.pubgm
pkill com.vng.pubgmobile
pkill com.pubg.imobile

#Fix 3rd Party

chmod 777 /proc/sys/fs/inotify
echo '128' > /proc/sys/fs/inotify/max_user_instances
echo '8192' > /proc/sys/fs/inotify/max_user_watches
echo '16384' > /proc/sys/fs/inotify/max_queued_events
cd /proc/sys/fs/inotify && echo '16384' > max_queued_events
cd /proc/sys/fs/inotify && echo '128' > max_user_instances
cd /proc/sys/fs/inotify && echo '8192' > max_user_watches
chmod 555 /proc/sys/fs/inotify

#Just A Clean

rm -rf /data/media/0/Android/data/$PKGNAME/*.dat
rm -rf /data/media/0/Android/data/$PKGNAME/files/*.dat
rm -rf /data/media/0/Android/data/$PKGNAME/files/UE4Game/*.dat

rm -rf /data/data/$PKGNAME/files
rm -rf /data/data/$PKGNAME/databases

rm -rf /data/media/0/Android/data/$PKGNAME/files/ProgramBinaryCache
touch /data/media/0/Android/data/$PKGNAME/files/ProgramBinaryCache
chmod 000 /data/media/0/Android/data/$PKGNAME/files/ProgramBinaryCache

#Path Shortcuts

DUMP() {
  pm dump $1 | grep $2 | tr ' ' '\n' | grep $1 | sed s/$2// | tr -d '\n';
};
lib=`ls -mR $(DUMP $PKGNAME legacyNativeLibraryDir=) | grep : | tr -d : | grep /arm | grep -v sosna`

SAVE(){
cp $lib/$1 $lib/$1.bak
}
RETURN(){
mv $lib/$1.bak $lib/$1
}

QUICKCHANGE() {
cp -rf $1 $1.bak;
rm -rf $1;
mv $1.bak $1;
chmod 777 $1;
};

#Iptable

iptables -I OUTPUT -p tcp -m string --string "shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "5004-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "5003-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "7001-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "7003-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3009-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3011-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "2005-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "2006-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3013-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3003-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3012-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3008-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "1005-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "7002-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "2004-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "5002-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3007-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "2004-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "5005-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "2007-shdow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "5004-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "5003-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "7001-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "7003-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3009-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3011-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "2005-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "2006-shadow.igamecj.com" --algo bm -j DROP
iptables -I OUTPUT -p tcp -m string --string "3013-shadow.igamecj.com" --algo bm -j DROP
iptables -I INPUT -s dl.listdl.com -j DROP
iptables -I OUTPUT -s dl.listdl.com -j DROP
iptables -I INPUT -s app.adjust.com -j DROP
iptables -I OUTPUT -s app.adjust.com -j DROP
iptables -I INPUT -s file-igamecj.akamaized.net -j DROP
iptables -I OUTPUT -s file-igamecj.akamaized.net -j DROP
iptables -I INPUT -s 129.226.2.165 -j DROP
iptables -I OUTPUT -s 129.226.2.165 -j DROP

#Remove Libs

rm -rf $lib/{libCrashSight.so,libgamemaster.so,libhelpshiftlistener.so,libgcloudarch.so,libigshare.so,libtgpa.so,libst-engine.so,libnpps-jni.so,liblbs.so,libapp.so};
sleep 5

#Start The Game
pm disable $PKGNAME/com.sirius.flutter.im.MeemoBGService  &>/dev/null;
pm disable $PKGNAME/com.tencent.midas.oversea.newnetwork.service.APNetDetectService  &>/dev/null;
pm disable $PKGNAME/com.sirius.meemo.foreground_service.ForegroundService &>/dev/null;

rm -rf /data/media/0/Android/data/$PKGNAME/files/TGPA
rm -rf /data/media/0/Android/data/$PKGNAME/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/SaveGames/Login
rm -rf /data/media/0/Android/data/$PKGNAME/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/MMKV;

ls -d $lib/* | egrep -v 'libprt.so|libvlink.so|libswappy.so|libITOP.so|libcubehawk.so|libdiscord_connect_sdk_android.so|libGCloudVoice.so|libgnustl_shared.so' | xargs chown 0:0

am start -S -W $PKGNAME/com.epicgames.ue4.SplashActivity > /dev/null
while [ ! -e /data/media/0/Android/data/$PKGNAME/files/TGPA ]; do sleep 0.01; done

#Edit Libs Files

ls -d $lib/* | egrep -v 'libprt.so|libvlink.so|libswappy.so|libITOP.so|libcubehawk.so|libdiscord_connect_sdk_android.so|libGCloudVoice.so|libgnustl_shared.so' | xargs chmod -R 000
chmod -R 755 $lib/*
ls -d $lib/* | egrep -v 'libprt.so|libvlink.so|libswappy.so|libITOP.so|libcubehawk.so|libdiscord_connect_sdk_android.so|libGCloudVoice.so|libgnustl_shared.so' | xargs chown 0:0
//chmod -R 000 $lib/libgcloud.so
#Fix Crash

rm -rf /data/data/$PKGNAME/{app_bugly,app_crashrecord,app_crashSight}
touch /data/data/$PKGNAME/{app_bugly,app_crashrecord,app_crashSight}
chmod 4000 /data/data/$PKGNAME/{app_bugly,app_crashrecord,app_crashSight}
rm -rf /data/data/$PKGNAME/files/ano_tmp/*
chmod -R 000 /data/data/$PKGNAME/files/ano_tmp