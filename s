#!/bin/bash
L=73_32_12_15_14_58; X=Xwayland; WM=fluxbox; I=aterm; # <=== seting of LAN (arm,arch,PC,pad ...)
DPY=$MY_IP_ADDRESS; test -z $DPY && DPY=`ip route|tr -s ' '|cut -d' ' -f9`;D=`echo $DPY|cut -c-11`
p=$PREFIX/lib;test $0 != ./s && export LD_PRELOAD=$p/libtermux-exec.so:$p/libandroid-shmem.so
export XDG_RUNTIME_DIR=u/tmp LD_LIBRARY_PATH=$p; AC="-Adobe-Courier-Bold-R-*-"
ps='ps -eo pid,ppid,comm,etime';a='$WM&';b='kill `pgrep $WM`';alias ll="ls -la" dd="du -hd 1" \
pp=$ps fb="$b;WM=fluxbox;$a" ob="$b;WM=openbox;$a" o="$b";e=echo; y=com.termux.x11/.MainActivity
# =======> update of all neccessary packages (virgin termux pkg/tgz update)
if [ ! -f ~/t ];then d=`dirname $0`;a=$d/../$1.tgz; test -f $a && tar -xzf $a -C ~/..
 test -f ~/t && exit;d=/storage/6533-6333; ln -s /storage/emulated/0 d; ln -s $d sd
 test ! -d sd/ && mv d sd; ln -s ../usr u; ln -s sd/ip/s .bashrc; ul=u/etc/apt/sources.list
 a=`uname -m`; $e deb https://dl.bintray.com/termux/termux-packages-24/ stable main>$ul
 x="termux-api imagemagick-x mpv-x make openssh mc clang libxpm gnupg libxi xwayland git wget"
 pkg in x11-repo; pkg in $x xterm fluxbox tigervnc feh openbox pcmanfm xorgproto proot apksigner
 h=https://its-pointless.github.io; p=pointless.gpg; wget $h/$p; apt-key add $p
 x="libmpc libisl setup-scripts gcc-8 libgfortran5 htop"; $e 'bash ~/.bashrc $@'>t; chmod +x t
 $e deb $h/files/ termux extras>>$ul; pkg in $x; setupclang-gfort-8; rm -r storage $p
 s=Home/sd;printf " %s\n" "SDB  120   *   $s/ip/" "FONT 2:202834.1" "TSDB $s/ip/EXE"\
 "EDITOR         IP      display" "TSDB $s">.issy; $e "geometry=1440x1440">>.vnc/config
 if [ `type ps|grep -c hashed` = 0 ];then cd u/bin; mv ps ps0; ln -s busybox ps; cd; fi
fi ; s=.shortcuts; z=com.termux/.app.TermuxActivity; p1=`pgrep -o Xvnc`; p2=`pgrep -o $X`
if [ ! -d $s -a $PWD = $HOME ];then mkdir $s; cd $s;yy="am start -n $y;./t ";$e htop>htop
 $e "$yy:0 c">favorite-check;$e "$yy:0 t">touch-check;$e ./t d>dialog-API
 $e "ls -l;env;$p;pstree;exit 1">ls-env-ps;$e mc sd/ip>mc;$e ./t o>pcmanfc-VNC;$e "$yy:0 i">IP
 $e "$yy:0 b">xlunch-Xorg;$e ./t b>xlunch-VNC;$e "$yy:0 x">pcmanfc-Xorg; cd; fi
# nl=`echo $(dirname $(pm path com.termux | cut -d: -f2))/lib`
# =======> use as bashrc ($0=$SHELL) pkg list-in |grep -c arch
if [ $0 = bash ];then test $PWD != $HOME && $e "new $0 in $PWD `ll;env;pp`"; return
elif [ $0 = "$SHELL" -o $0 = /bin/bash ];then x=om.termux.wtermux/.MainActivity
export PATH=./:~/:$PATH DISPLAY=:1; r=`pgrep -n libproot`; test $0 = /bin/bash && r=root
f="\\[\\e[01;34m\\][\\[\\e[0m\\]\\[\\e[00;32m\\]\\w\\[\\e[0m\\]\\[\\e[01;34m\\]]\\[\\e"
PS1="$r$f[0;34m\\]\\[\\e[0m\\]\\[\\e[1;37m\\]\\$\\[\\e[0m\\]\\[\\e[00;37m\\] \\[\\e[0m\\]"
test -z $p2 && am start -n $x; test ! -d TMP && mkdir TMP; test -z `pgrep -o sshd` && sshd
if [ -z `pgrep -o wtermux` ];then test -z $p2 && am start -n $y; else y=$x; fi
if [ -f u/bin/Xvnc -a -z "$p1" ];then rm -rf .vnc/l* u/tmp/.X*; vncserver -localhost; fi
if [ ! -f u/bin/$X ];then $e "$X missing";elif [ -z $p2 ];then d="-display :0";$X :0>TMP/TX 2>&1 &
 p2=`pgrep -o $X`; test -f u/bin/$WM -a -z "`pgrep -o $WM`" && $WM $d>>TMP/TWM 2>&1 &
 sleep 1; test ! -z "$I" -a -z "`pgrep -o $I`" &&\
 aterm $d -geometry 40x20+0+0 -fn $AC-24-*-*-*-*-*-*-* -bg '#eeeece' -fg blue &
elif [ $0 = /bin/bash ];then return; fi; $e "moin sshd $DPY, $X:$p2, Xvnc:$p1"
h=33; alias hf="sftp -P 8022 $D$h" h="ssh -p 8022 $D$h" k="kill $PPID"; return
#
# =======> create *.tgz and "on devive builds" (termux-setup-storage)
elif [ "$1" = tgz ];then c=sd/t.tgz; cd; date; ls -lh sd/*tgz
 if [ "$2" = ip ];then cd sd; rm *.o */*.o; tar czf - ip>ip.tgz; elif [ "$2" = t ]
  then tar czf - ..>$c; date; elif [ "$2" != x ];then $e " use $0 tgz [opt]
  opt: t/ip create <opt>.tgz, x=extract"; else $e "*/*/>../f; tar -tzf $c -C .. -T ../f";fi ; exit
elif [ "$1" = build ];then cd; p=$2; date; git clone https://github.com/termux/x11-packages
 cd x11-packages; git submodule update --init; cp -a packages/* termux-packages/packages
 test -z "$p" && p=xwayland; cd termux-packages; scripts/setup-termux.sh;
 termux-chroot; cd x11-packages/termux-packages/; ./build-package.sh -If $p; date; exit
fi
# =======> check of all three xserver and API
typeset -i i=0; api=$PREFIX/libexec/termux-api; p="$@"; act='--user 0 -a android.intent.action'
if [ "$1" = "-h" -o $# = 0 ];then printf '%s\n' "usage t [n] [opt] [url] [file] $p1 $p2" "
 opt s(share), u(url) by api, e(EDIT) default VIEW by app" " d dialogs and values by Termux-API,\
 i Integrated Process on Android smart phone" " l extract with logcat to TMP/T.log,\
 tgz manage backups of ~/.." " m media player (mpv), p pictures by magick (display), a (animate)
 f feh local graphic tool (3.1.3) from https://feh.finalrewind.org or Termux package (3.1.1)
 o check WM=openbox+xterm+pcmanfm, x same but WM=fluxbox, b xlunch.c (Xserver=$X/$WM)
 c test source for X11 interface (check.c), t touch.c" "" " n 00_$L for $D[n] aarch,arm,PC\
 XSDL, :0 $X or none (VNC)" " selected to view on differend devices in my LAN (00 phone),:1 none\
 Xvnc/VCN used" '' " api=$api, dpy=$DPY" " app=/system/bin/app_process (am by script)" ""; exit
#
# =======> API dialogs t u https://wiki.termux.com/wiki/Graphical_Environment
elif [ "$1" = d ];then m=sheet; b="Dialog Test with"; h="--es input_hint"
a=exit,selfie,speech,confirm,sheet,checkbox,radio,spinner,date,time,counter
t=f=""; test $# -gt 1 && a=`echo $p,$a|cut -c3-|sed 's/ /,/g'`
while [ "$f" = "" ]; do c="--es input_values $a"
case $m in exit) break;; spinner) t="Select next:";; 
 plane) t="plane on"; am broadcast $act.AIRPLANE_MODE --ez state true;c=$h; m=text;;
 selfie) f=tmp.jpg; $api CameraPhoto --es camera 1 --es file `realpath $f`;break ;;
 counter) c="--eia input_range 1,3,2";; date) t=;; time) c=;; text) c="--ez multiple_lines 2 $h";;
 confirm) c=$h; t="Yes sheet or exit";; speech) c=$h; t="say something and I repeat"
 echo $t|$api TextToSpeech;sleep 1; echo after beep|$api TextToSpeech;; esac
d=`$api Dialog --es input_method $m --es input_title "$b $m" $c "$t"`
c=$m; t=`echo $d|cut -d, -f2|cut -c10-`;#echo b=$b, m=$m, t=$t
if [ "$t" = "" ];then t=rotated; elif [ $m = counter ];then m=text
 elif [ $m = date ];then m=time; elif [ $m = time ];then m=counter;t="`date`"
 elif [ $m = speech ];then m=text; echo $t|$api TextToSpeech
 elif [ $m = confirm ];then m=sheet; test `echo $d|grep -c no` = 1 && break
 elif [ $m = text ];then m=spinner; test `echo $d|grep -c ": -2"` = 1 && break
 elif [ `echo $d|grep -c error` = 1 ];then m=text;t=`echo $d|cut -d, -f4|cut -c10-`
 else t=; for n in `echo $a|sed s/,/\ /g`; do if [ `echo $d|grep -c $n` = 1 ]
  then m=$n; if [ `echo $m|grep -c '\.'` = 1 ];then f2="$f $n"
  $api Share --es file $(echo `realpath $n`|sed 's/^\///'); sleep 0;m=$c;fi ;fi ;done ;fi
done ; p="$f";fi ; i=6; x=$2; u=/data/data/com.sion.sparkle/files

I=~/sd/ip; fc=182834; g=1440x720; if [ ! -d $I ];then I=`pwd`; fc=162034; fi
if [ $1 = :0 ];then export DISPLAY=:0; test -z `pgrep -o $X` && $X&
 elif [ $1 = :2 -o $1 = :3 ];then test $1 = :3 && g=700x1400
  if [ -z "`pgrep -o xnest`" -a ! -z "`type xnest`" ];then xnest $1 -wr -geometry $g&
  echo "kill `pgrep -o xnest`"; fi ; export DISPLAY=$1
 elif [ $1 = 00 ];then export DISPLAY=`$e $DPY`:0; $e ">$DPY<>$DISPLAY<"
 elif [ `echo $L|grep -c $1` = 0 ];then test -z $DISPLAY && export DISPLAY=:1; i=3; x=$1
 else export DISPLAY=$D$1:0; i=6; x=$2; test "$2" = "" && x=2; fi
# =======> X11 packages #c=o; printf '%s\n' "t :0 $c&" "t 00 $c&" "t $c&">a;chmod +x a; a&
if [ `echo _a_b_c_f_m_t_o_p_x|grep -c _$x` = 1 ];then p="`echo $p|cut -c$i-`"; i=9
if [ $x = x -o $x = o ];then g=40x20; WM=fluxbox; test $x = o && WM=openbox
  test "$p" = "" && p=24; f="$AC-$p-*-*-*-*-*-*-*"; p=;I=; pcmanfm&
  s="xterm -fn $f -geometry $g+0-0 -bg #eeeece -fg blue"; test -z `pgrep -o $WM` && $WM&
 elif [ $x = m ];then s="mpv -geometry $g-0+0 -vo x11"; i=0; unset LD_LIBRARY_PATH
 elif [ $x = f ];then s=~/TMP/feh ;I=$I/feh 
 elif [ $x = t ];then s=~/TMP/touch.exe; test "$p" = "" && p="petm.xpm check.jpeg"
 elif [ $x = p -o $x = a ];then n=`identify $p|cut -d' ' -f3`; s=display
  test $x = a && s=animate; s="$s -resize $g -geometry $g+0+0"; i=0
 elif [ $x = b ];then s=~/TMP/xlunch.exe; g=`cd $I/..;pwd`/xlunch/extra
  c="-f $g/OpenSans-Regular.ttf/20 -i $g/sample_entries.dsv -L $g/highlight.png --bgfill"
  b=$g/wp.jpg; b=check.png; test "$p" = d && p="-d -g $b $c --dontquit"
  test -z "$p" && p="$c -b 240 -I 20 -T 10 -X -l 10 -g $b"
 elif [ $x = c ];then s=~/TMP/check.exe; test -z "$p" && p="P*pm s *.c p*m :$fc.400"
fi ; while [ 1 ];do cd $I; test $i = 9 && make $s; $e "$DISPLAY ($x) $s $p"
 test $x = f && cd ..; $s $p; i=$?; test $i != 9 && break;done ; exit

elif [ $x = i ];then cd; rm -f HLPDIR EXEDIR; export LANG=C; cd $I
E=$I/EXE; if [ ! -d $E ];then cd ..; E=$I; I=`pwd`;fi ; export ISSYLIB=$I
cd; ln -s $E EXEDIR; export SAVENAM=$HOME/TMP/T`date +%X | cut -c-2,4-5,7-8`
echo IP-MGR:$ISSYLIB, Date:`date +%d.%m.%y` Time:`date +%X`,$DISPLAY
touch $SAVENAM; chmod +x $SAVENAM; ln -s $E HLPDIR; R=0
while [ $R != 5 -a $R != 1 ]; do 
 cd $E; make ~/TMP/issy.exe; cd; ~/TMP/issy.exe; R=$?; $e "Ret:$R"
 if [ $R = 3 ];then chmod +x $SAVENAM; $SAVENAM &
    elif [ $R = 0 ];then $SAVENAM $ISSYLIB;fi ; test $R = 3 -o $R = 255 && break
done ; rm -f $HOME/TMP/T*; else i=0; fi ; test $i != 0 && exit

v=VIEW; b=broadcast; c="-n com.termux/com.termux.app.TermuxOpenReceiver"
for n in $p; do i=i+1; f=$n; test -f $n && f=$(echo `realpath $n`|sed 's/^\///')
 if [ $n = l ];then s=TMP/Tlog; logcat -d>$s; grep 'E ' $s; ls -l $s
 elif [ $n = 0 ];then am start -n $y; elif [ $n = 2 ];then am start -n $z
 elif [ $n = e ];then v=EDIT; elif [ $n = u ];then b=start; c=""
 elif [ $n = s ];then v=s; elif [ ! -f $n -a "$c" != "" ];then a="$api Torch --ez enabled"
  $a true;echo $n invalid|$api Toast --ez short true --es background red;$a false 
 elif [ $v = s ];then $api Share --es file $f; else test "$c" = "" && case $n in
  w)f="https://en.wikipedia.org/wiki/X.Org_Server#XWayland";;
  ip)f=https://github.com/RalfWerner/integrated-process;;
  esac ; am $b $act.$v $c -d $f; fi
done ;#am start -n com.realvnc.viewer.android.app/ConnectionChooserActivity
