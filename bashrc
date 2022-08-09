#!/bin/bash
if [ "${0##*/}" = bashrc ];then RT=s p0=s e=echo DPY=$MY_IP_ADDRESS; else . uu.sh . .; fi
ct=com.termux c="am start -n $ct" z="$c/.app.TermuxActivity" y="$c.x11/.MainActivity" z2=$z
XDG_RUNTIME_DIR=u/tmp u="bash uu.sh uu" t="bash ~/.bashrc" w='$WM&' I=:0 b='pkill $WM'
vr="am start -n com.realvnc.viewer.android/.app.ConnectionChooserActivity" v=pgrep=$sb/pgrep
[ -z "$RT" ]&& v=; alias t="$t" o="$b" fb="$b;WM=fluxbox;$w" ob="$b;WM=openbox;$w" $v
[ -n "$(pgrep m.termux.window)" ]&& z="$c/.window.TermuxFloatActivity"
vm="am start -n com.coboltforge.dontmind.multivnc/.MainMenuActivity" v="$vm" X=Xwayland
# =======> update of all neccessary packages (virgin termux pkg update) #JOB_0:115.174. fluxbox
if [ ! -f ~/.issy ];then if [ -z "$RT" ];then pkg up # $s/../trusted.gpg.d/$p;# pkg in xwayland
 pkg in x11-repo; x="termux-api imagemagick mpv-x make openssh mc clang libxpm gnupg libxi git"
 pkg in $x aterm fluxbox tigervnc feh openbox pcmanfm xorgproto proot aapt apksigner wget
 h=https://its-pointless.github.io p=pointless.gpg s=u/etc/apt/sources.list.d
 $e deb $h/files/24 termux extras>$s/gcc.list; wget $h/$p;apt-key add $p; rm $p; pkg up
 pkg in setup-scripts gcc-9 libgfortran5 libmpc libisl htop-legacy; setupclang-gfort-9
else date;apt update && apt upgrade -y; date # steps from "virgin" ubuntu - install of packages
 $e "I=> ubuntu/debian pu"; p=/bin/ps; rm $p; ln -s /system/$p $p ;s="--fix-missing -y"
 x="make xterm libx11-dev libxi-dev libx11-xcb-dev libxpm-dev libimlib2-dev libcairo-dev $s"
 apt-get install tigervnc-standalone-server fluxbox nedit gfortran $x;date ; fi
s=Home/sd;printf " %s\n" "SDB  120   *   $s/ip/" "FONT 2:202834.1" "TSDB $s/ip/EXE"\
 "EDITOR         IP      display" "TSDB $s">.issy; $e "#">.vnc/xstartup
fi ; p1=`pgrep -o Xvnc`; [ -z "$p0" ]&& p0=`pgrep -o $X`; s=widget; sc=.shortcuts; u0="$y;$u n0"
if [ -d $s -o $PWD != $HOME ];then s=;elif [ -d /termux/$s/ -a -d $s ];then ln -s /termux/$s $s
elif [ ! -d $s ];then mkdir $s; cd $s; yt="$y;$t ";$e "$yt:0 c">favorite-check;$e htop>htop
 $e "$yt:0 t">touch-check;$e $t d>dialog-API;$e mc sd/ip>mc;$e $t o>pcmanfm-VNC;$e $u n>nedit-PC
 $e "env;ls -l;$pp;pstree;exit 1">env-ls-ps;$e "$yt:0 i">IP-MGR;$e "$yt:0 x">pcmanfm-Xorg
 $e "$yt:0 b">xlunch-Xorg;$e $t b>xlunch-VNC;$e $u0>nedit-X; cd; [ ! -e $sc ]&& ln -s $s $sc; fi
#
# =======> use as .bashrc ($0=$SHELL) pkg list-icdn |grep -c arch
if [ $0 = bash -o $0 = -bash ];then [ $PWD != $HOME ]&& $e '"new $0 in $PWD `ll;env;pp`"';return
elif [ $0 = $SHELL -o $0 = /bin/bash ];then [ ! -d TMP ]&& mkdir TMP;[ -z "$p0" ]&& set $I
h=${DPY%.*}.${L##*.};[ "$h" = "$DPY" ]&& h=${DPY%.*}.`$e $L|cut -d . -f2`; ps=`pgrep -o sshd`
[ -z "$ps" ]&& sshd; alias hf="sftp -P 8022 $h" h="ssh -p 8022 $h" k="kill -9 $PPID"\
 n="u uu n i/touch.c i/check.c /home/.termux/termux.properties &"
[ $0 = /bin/bash ]&& return; $e moin $X:$p0, Xvnc:$p1 sshd:$ps $@; w=.
export DISPLAY=${I% *}; [ -z "$1" ]&& return; else WM=; fi ; a=`$e "$1"|tr "0-3" N`
# =======> usage, X11<=>termux switch and "on device"builds
typeset -i i=0; api=$PREFIX/libexec/termux-api; p="$@"; act='--user 0 -a android.intent.action'
if [ "$1" = "-h" -o $# = 0 ];then printf '%s\n' "usage t [n] [opt] [url] [file] ($p1,$p0)$PWD" "
[opt] s(share), u(url) by api, e(EDIT) default VIEW by app" " d dialogs and values by\
 Termux-API, i Integrated Process on Android smart phone" " l extract with logcat to TMP/T.log,\
 tgz manage backups of ~/.." " m media player (mpv), p pictures by magick (display), a (animate)
 f feh local graphic tool (3.1.3) from https://feh.finalrewind.org or Termux package (3.7.1)
 o open WM=openbox+xterm+pcmanfm, x same but WM=fluxbox, b xlunch.c" " c check.c source for X11\
 interface (check.c), t touch.c (Xserver=$X/$WM)" "" "[n] default:0 $X or :1 (VNC) $L for [n=PC\
 ...] ${DPY%.*}" " selected to view on differend devices in my LAN (00 phone),:1 none Xvnc/VCN\
 used" '' " api=$api, dpy=$DPY" " app=/system/bin/app_process (am by script)"
elif [ "$a" = N ];then case $1 in 0)$y;; 1)$vm;; 2)$z;; *)$vr; esac ; exit
elif [ $1 = build ];then cd;p=packages; w=xwayland; x=x11-$p; h=https://github.com/termux/$x
 date; git clone $h;cd $x; git submodule update --init; cd termux-$p; cp -a ../disabled-$p/$w $p
 scripts/setup-termux.sh; termux-chroot "cd `pwd`; build-package.sh -If $w";date;exit
#
# =======> API dialogs t u https://wiki.termux.com/wiki/Graphical_Environment
elif [ $1 = d ];then shift; m=spinner; b="Dialog Test with"; h="--es input_hint"; i=$2
a=exit,selfie,speech,confirm,sheet,checkbox,radio,spinner,date,time,counter,plane
t=;f=; [ $# -gt 0 ]&& a=`echo $1,$a|tr ',' ' '`;[ $i -gt 0 ]&& m=$1;$e "$b $api m=$m,f=$f,p=$@"
while [ "$f" = "" ]; do c="--es input_values $a"; case $m in exit) break ;;
 spinner) t="Select next:";; sensor) [ $i -eq 0 ]&& i=20; $e "t=$t, i=$i"; #$api Sensor -a list
  while read d; do if [ "${d#*:}" = " [" ];then t=; elif [ "$d" = "]" ];then $e $t>s;cat s;
    elif [ "$d" != "}" ];then t+=$d; fi ; done < <(termux-sensor -d 100 -n $i -s ori);
  $e $t; c="--ez multiple_lines 2 $t";;
 plane) t="plane on"; am broadcast $act.AIRPLANE_MODE --ez state true;c=$h; m=text;;
 selfie) f=tmp.jpg; $api CameraPhoto --es camera 1 --es file `realpath $f`;break ;;
 counter) c="--eia input_range 0,9,$i";;date) t=;; time)c=;;text)c="--ez multiple_lines 2 $h";;
 confirm) c=$h; t="Yes sheet or exit";;speech) c=$h; t="say something and I repeat after beep"
 $e $t|$api TextToSpeech; sleep .1;; esac; $e b=$b, m=$m, t=$t c=$c h=$h
d=`$api Dialog --es input_method $m --es input_title "$b $m" $c "$t"`
c=$m; [ $m != sensor ]&& t=`echo $d|cut -d, -f2|cut -c10-`
if [ -z "$t" ];then t=rotated; elif [ $m = counter ];then m=text; i=${t:1:${#t}-2}
 elif [ $m = date ];then m=time; elif [ $m = time ];then m=counter;t="`date`"
 elif [ $m = speech ];then m=text;echo $t|$api TextToSpeech;elif [ $m = sensor ];then $e m=text
 elif [ $m = confirm ];then m=sheet; [ `echo $d|grep -c no` = 1 ]&& break
 elif [ $m = text ];then m=spinner; [ `echo $d|grep -c ": -2"` = 1 ]&& break
 elif [ `echo $d|grep -c error` = 1 ];then m=text;t=`echo $d|cut -d, -f4|cut -c10-`
 else t=; for n in `echo $a|tr ',' ' '`; do if [ `echo $d|grep -c $n` = 1 ]
  then m=$n; if [ `echo $m|grep -c '\.'` = 1 ];then f2="$f $n"cc
  $api Share --es file $(echo `realpath $n`|sed 's/^\///'); sleep 0;m=$c;fi ;fi ;done ;fi
done ; shift ;set "$f";fi ; I=~/i fc=182834 g=1230x600 p=$* u=u/bin/ d=$DISPLAY;[ -z $d ]&& d=:1
AC="-Adobe-Courier-Bold-R-*-" x=termux-x11 x1=$x u1=$u$x;fc=162034.0;$e `pwd`, $I,$fc
# =======> set display depending on the $1 specification, if this is valid or a number from $L
if [ ! -d $I ];then $e I=$I, PWD=$PWD;I=$PWD fc=162034.900;fi ;[ ! -f $u1 ]&& x=$X
if [[ $1<9 ]]&&[[ $1>0 ]]&&[ $# != 1 ];then d=${DPY%.*}.`echo $L|cut -d . -f$1`:0; shift
 elif [[ -z ${1##.*} ]]&&[[ -n ${1#.*} ]]&&[[ $# != 1 ]];then d=${DPY%.*}$1:0; shift
 elif [[ -z ${1##:*} ]]&&[[ -n ${1#:*} ]]&&[ ${#1} = 2 ];then d=$1; shift; fi
if [ $d = :0 -a -z "$p0" ];then if [ ! -f $u1 ];then $y; else $x $d>TMP/TX 2>&1&
   fi ;while [ -z "$p0" -a $i -lt 5 ]; do sleep 1; [ $x = $X ]&& $x $d>TMP/TX 2>&1&
       p0=`pgrep -o $X`;i+=1;$e Start$d:$x=$p0 try $i; done ; elif [ $d = :1 -a -z "$p1" ];then
  if [ -f $u/Xvnc ];then rm -rf .vnc/l* u/tmp/.X*;  [ -z "$WxH" ]&& WxH=1400x1400
  $e "geometry=$WxH">~/.vnc/config; vncserver -localhost;$v2; fi
 elif [ $d = :2 ]||[ $d = :3 ]&&[ -n "`type xnest`" ];then [ $d = :3 ]&& g=700x1230
  if [ -z "`pgrep -o xnest`" -a -n "`type xnest`" ];then xnest $d -wr -geometry $g&
fi ;fi ; x=$1;[ -z $1 ]&& x=n;[ $x = x ]&& WM=fluxbox;[ $x = o ]&& WM=openbox 
export DISPLAY=$d WM y z vr vm; [ -n "$WM" ]&&[ -z "`pgrep -o $WM`" ]&& $WM >TMP/TWM 2>&1&
if [ `$e _a_b_c_f_m_t_o_p_x|grep -c _$x` = 1 ];then r=; shift; i=9; m=1; gx=40x20+0-0
[ "$1" = + ]&& r="rm *.o" && shift; p=$*
if [ $x = x -o $x = o ];then [ -z "$p" ]&& p=24;f="$AC-$p-*-*-*-*-*-*-*";m=0;p=;I=; X=pcmanfm
  s="xterm -fn $f -geometry $gx -bg #eeeece -fg blue";[ -z "`pgrep -o $X`" ]&& $X>>TMP/TX 2>&1&
 elif [ $x = c ];then s=~/TMP/check.exe; [ -z "$p" ]&& p="P*pm bashrc *.c *.f pet*m :$fc.70"
 elif [ $x = t ];then s=~/TMP/touch.exe t=touch.c
 elif [ $x = f ];then s=~/TMP/feh ;I=$I/feh ; [ -n "$r" ]&& r="rm $I/*.o"
 elif [ $x = m ];then s="mpv -geometry $g-0+0 -vo x11" m=0; [ -z "$p" ]&& p="*.mp4"
 elif [ $x = p -o $x = a ];then s=display;[ $x = a ]&& s=animate; n=`identify $p|cut -d' ' -f3`
  s="$s -resize $g -geometry $g+0+0"; m=0; [ -z "$p" ]&& p="petm.xpm bg*.jp*"
 elif [ $x = b ];then s=~/TMP/xlunch.exe; g=`cd $I/..;pwd`/xlunch/extra
  c="-f $g/OpenSans-Regular.ttf/15 -i $g/sample_entries.dsv -L #$g/highlight.png --bgfill"
  b=$g/wp.jpg; b=check.png b1=petm.xpm; [ "$p" = d ]&& p="-d -g $b $c --dontquit"
  A="-A $g/ghost.xpm;petm.xpm;-150,-60;ls?-l?*.png -A peti.xpm;$g/ghost.xpm;150,-60;exit?9" 
  [ -z "$p" ]&& p="$c -b 20 -I 15 -T 10 -X -l 12 -s 80 -g $b $A -x 10 -y 10 -w 500 -h 300"
fi ; $e "$d($x) s:$s $p"; cd $I;$r; r=$I;[ $x = f ]&& r=..;if [ $w = . ];then $s $p&
 else while [ $i = 9 ];do cd $I;T=`head -n 1 $t` T=${T:13:1} C=gtk+-3.0 U="gcc -std=c99 "
  if [ $x = t ];then p="petm.xpm bg1.j*";[ $T -gt 5 ]&& p="*.jp* *pn c*mp4"
   [ $T -gt 5 ]&& U=c++ && C="gtk+-2.0 opencv" ;[ $T = 5 ]&& p="*png"; [ -n "$*" ]&& p=$*
   U+=" $t -w "; [ $T -ge 5 ]&& U+="`pkg-config --cflags $C --libs` -o ";export U 
  fi ;[ $m = 1 ]&& make $s;cd $r; $s $p; i=$?;done ; fi
#
# =======> Integrated process on the display selected above (with IP-Mgr and *mod loops)
elif [ $x = i ];then I=$PWD ;cd; rm -f HLPDIR EXEDIR; export LANG=C; E=i/EXE;[ ! -d $E ]&& E=$I
cd; ln -s $E EXEDIR;export ISSYLIB=$I/.. SAVENAM=$HOME/TMP/T`date +%X | cut -c-2,4-5,7-8`
echo IP-MGR:$ISSYLIB, Date:`date +%d.%m.%y` Time:`date +%X`,$DISPLAY;p="$E/petm.xpm $E/timi.xpm"
touch $SAVENAM; chmod +x $SAVENAM; ln -s $E HLPDIR; R=0; x=~/TMP/issy.exe
while [ $R != 5 -a $R != 1 ]; do cd $E; make $x; cd; $x $p; R=$?; $e "Ret:$E:$x,$R";exit
 if [ $R = 3 ];then chmod +x $SAVENAM; $SAVENAM &
    elif [ $R = 0 ];then $SAVENAM $ISSYLIB; fi ;# [ $R = 3 -o $R = 255 ]&& break
done ; rm -f $HOME/TMP/T* `find $E -maxdepth 1 -type f -size 0`
elif [ -d $x -a $i -gt 1 ];then $e "=>$*";while read a b c d sp d1 d2 d3 F T b; do [ -n $c ]&&\
 printf '%-20s %.1s%7s%4s%3s %5s%s%s\n' $F $a $sp $d1 $d2 $d3 $T $b; done < <(ls -lh$2 $1)
elif [ -f $api ];then v=VIEW;s=.;r=;n=' '; b=broadcast; c="-n $ct/$ct.app.TermuxOpenReceiver"
while [ -n "$1" ]; do [ $s != u -a -f $1 ]&& r+=$($e `realpath $1`|sed 's/^\///')
 if [ $1 = l ];then s=TMP/Tlog; logcat -d>$s; grep 'E ' $s; ls -l $s; exit
 elif [ $1 = c ];then c+=' --ez chooser true';
 elif [ $1 = u ];then s=u; r="https://www.google.com";n=/search?q=
 elif [ $1 = s ];then v=s; elif [ ! -f $1 -a $s != u ];then a="$api Torch --ez enabled"
  $a true; $e $1 invalid|$api Toast --ez short true --es background red;$a false 
 elif [ $v = s ];then $api Share --es file $f; elif [ $s = u ];then
  case $1 in w)f="https://en.wikipedia.org/wiki/X.Org_Server#XWayland";; g)n=+;;
   ip)f=https://github.com/RalfWerner/integrated-process;; *) f+=$n$1;; esac 
 fi ; [ $# = 1 ]&& am broadcast $act.$v $c -d $r; shift
done;[ $x != n ]&& $e Invalid:x=$x, i=$i, '$1'=$1 RT=$RT; fi
if [ -n "$h" ];then $z; $pp; alias;fi ;# remove this line for non debug
