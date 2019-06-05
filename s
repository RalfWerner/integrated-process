#!/bin/bash 
D=192.168.0.1;alias ll="ls -la" dd="du -hd 1"; e=echo; test ! -d ~/TMP && mkdir ~/TMP
# =======> update of all neccessary packages
if [ ! -d ~/.ssh ];then ln -s /storage/emulated/0 d; ln -s /storage/6533-6333 sd; rm -r storage
 test ! -d sd && ln -sf d sd; ln -s ../usr u; ln -s sd/ip/s .bashrc; x="xterm fluxbox tigervnc termux-api"
 x="$x libxpm imagemagick-x mpv-x libx11-dev libcairo-devel make clang wget gnupg coreutils";# feh openbox pcmanfm
 pkg in termux-keyring x11-repo; pkg up; pkg in mc openssh imlib2-dev $x; pkg up
 rm -r storage; mkdir .ssh; cp sd/ip/x/au* ~/.ssh; cp sd/ip/x/mc.ext .config/mc
 p=pointless.gpg; wget https://its-pointless.github.io/$p; apt-key add $p; dd ..
 echo deb https://its-pointless.github.io/files/ termux extras>>u/etc/apt/sources.list
 pkg in coreutils gcc-8 libgfortran5 libxi libxi-dev; pkg up; setupclang-gfort-8; rm $p
 if [ ! -f u/bin/Xorg -a -d sd/ip/x ];then cd ~/sd/ip/x; a=`uname -m`; test ! -d $a && tar -xzf *$a.t*
  d="libxfixes libexpat libxdamage libdrm libpixman libpciaccess libxfont2 libxkbfile libxshmfence"
  cd $a; pkg in $d mesa xkeyboard-config xorg-xkbcomp; pkg up; dpkg -i *.deb; cd; fi
fi
# =======> use as `bashrc`
if [ $0 = bash ];then test $PWD != $HOME && $e "new $0 in $PWD `ps;ll`"; return
elif [ $0 = "$SHELL" ];then export PATH=./:$PATH DISPLAY=:1 DPY=`ip route|tr -s ' '|cut -d' ' -f9`
PS1="\\[\\e[01;34m\\][\\[\\e[0m\\]\\[\\e[00;32m\\]\\w\\[\\e[0m\\]\\[\\e[01;34m\\]]\\[\\e[0;34m\\]\\[\\e[0m\\]\\[\\e[1;37m\\]\\$\\[\\e[0m\\]\\[\\e[00;37m\\] \\[\\e[0m\\]"
h=12; alias h="ssh -p 8022 $D$h" hf="sftp -p 8022 $D$h"
alias pp='ps -o pid,ppid,comm,etime' k="kill `ps -o pid,comm|grep com|cut -dc -f1`"
fb=u/bin/fluxbox; test `ps|grep -c " sshd"` = 1 && sshd; #e="termux-tts-speak"
if [ ! -f u/bin/Xorg -a ! -f u/bin/Xvnc ];then $e only XSDL available
elif [ -f u/bin/Xvnc ];then test `ps|grep -c "Xvnc "` = 1 && vncserver
elif [ -f u/bin/Xorg -a `ps|grep -c "Xorg "` = 1 ];then .shortcuts/Xorg.sh
 export DISPLAY=:0; g="-geometry 40x20+10+10"; test `ps|grep -c Xorg` = 1 && Xorg&
 f="-fn -*-*-bold-r-*--24-*-*-*-*-*-*-*"; test -f $fb -a `ps|grep -c fluxb` = 1 && $fb&
 test `ps|grep -c aterm` = 1 && aterm $g $f -bg "#eeeece" -fg blue&
fi; if [ ! -f t ];then echo 'bash ~/.bashrc $@'>t; chmod +x t;fi; $e "moin sshd $DPY"; return
#echo "pkg list-installed;echo 'ssh-keygen;cat d/ip*.pub>>.ssh/authorized_keys'"
#ssh-keygen -f ~/.ssh/known_hosts -R [192.168.178.46]:8022
#
# =======> termux-setup-storage; tar -xzf /storage/6533-6333/t.tgz -C ..
elif [ "$1" = tgz ];then c=sd/t.tgz; cd; pwd; ls -lh $c
 if [ "$2" = new ];then tar czf - ..>$c; elif [ "$2" != list ];then echo " use $0 tgz [opt]
 opt: new, t=list, x=extract"; else echo "*/*/">../t; tar -tzf $c -C .. -T ../t; fi; exit
elif [ "$1" = info ];then termux-info; exit
fi
#System information:Linux localhost 3.18.66-gde8dc79
#Termux-packages arch:aarch64 Android version:8.0.0
#Device manufacturer:HUAWEI Device model:LDN-L21
#apt install --reinstall $(dpkg -l | grep ^ii | awk '{ print $2 }');objdump -x ~/TMP/touch | grep RUNPATH
# =======> check of all three xserver and API D=192.168.178.;L=30_32_33_45_46_48; 
#!/data/data/com.termux/files/usr/bin/bash
typeset -i i=0; api=$PREFIX/libexec/termux-api; p="$@"; act='--user 0 -a android.intent.action'
L=14_15_73_58; LL="PC,aarch,arm"
if [ "$1" = "-h" -o $# = 0 ];then printf '%s\n' "usage t [n] [opt] [url] [file] (version 0.1)" ''"
 opt s(share), u(url) by api, e(EDIT) default VIEW by app" " d dialogs and values by Termux-API,\
 i Integrated Process on Android smart phone" " l extract with logcat to TMP/T.log,\
 tgz manage backups of ~/.." " m media player (mpv), p pictures by magick (display), a (animate)
 f feh local graphic tool (3.1.3) from https://feh.finalrewind.org or Termux package (3.1.1)
 o openbox and pcmanfm to check segfault of sparkle and other Xserver
 x xterm (fullscreen), c test source for X11 interface (check.c)" "" " n 00_$L for $D[n] ($LL)\
 XSDL, :0 Xorg or none (VNC)" " selected to view on differend devices in my LAN (00 phone), none\
 Xvnc/VCN used" '' " api=$api, dpy=$DPY" " app=/system/bin/app_process (am by script)" ""; exit

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
  then m=$n; if [ `echo $m|grep -c '\.'` = 1 ];then f2="$f $n";# 
  $api Share --es file $(echo `realpath $n`|sed 's/^\///'); sleep 0;m=$c;fi;fi; done; fi
done ; p="$f"; fi
if [ `echo _00_:0_$L|grep -c $1` = 0 ];then i=3; x=$1
 else export DISPLAY=$D$1:0; i=6; x=$2; test "$2" = "" && x=2;
 test $1 = :0 -a `ps|grep -c Xorg` = 1 && Xorg&
 test $1 = :0 && export DISPLAY=:0; test $1 = 00 && export DISPLAY=$DPY:0; fi
# =======> X11 packages https://www.gerwiki.de/imagemagick/useful_hints
#c=o; printf '%s\n' "t :0 $c&" "t 00 $c&" "t $c&">a;chmod +x a; a&
I=~/sd/ip; if [ -d $I ];then E=$I/EXE; else I=`pwd`; E=$I; fi
if [ `echo _x_p_a_m_c_f_t_o|grep -c _$x` = 1 ];then g=1440x720; 
p="`echo $p|cut -c$i-`"; f="-*-*-bold-r-*--32-*-*-*-*-*-*-*"
if [ $x = x ];then g=88x22; g=40x20; test `ps|grep -c fluxb` = 1 && fluxbox&
  s="xterm -fn $f -geometry $g+0-0 $c-bg ";#eeeece" -fg blue";#s=fluxbox
 elif [ $x = m ];then s="mpv -geometry $g-0+0 -vo x11"
 elif [ $x = o ];then s=pcmanfm;# test `ps|grep -c openb` = 1 && openbox&
  test -f ~/u/bin/openbox -a $1 != 15 && s="openbox --startup pcmanfm"
 elif [ $x = f ];then s=~/TMP/feh ;I=$I/feh; i=9
 elif [ $x = t -a "$p" = m ];then s=~/TMP/multi.exe; i=9; p=--with-ownership
 elif [ $x = t ];then s=~/TMP/touch.exe; test "$p" = "" && p=check.xpm; i=9
 elif [ $x = p -o $x = a ];then n=`identify $p|cut -d' ' -f3`; s=display
  test $x = a && s=animate; s="$s -resize $g -geometry $g+0+0"
 elif [ $x = c ];then s=~/TMP/check.exe;cd $I; 
  test "$p" = "" && p="`ls *.c P*pm` `ls c*m ti*m`"; i=9; fi
while [ 1 ];do cd $I; test $i = 9 && make $s; $e "$DISPLAY ($x) $s "$p""
   test $x = f && cd ..; $s $p; i=$?; test $i != 9 && break; done ; exit

elif [ $x = i ];then export ISSYLIB=$E; cd; rm -f HLPDIR EXEDIR; export LANG=C
ln -s $E EXEDIR; export SAVENAM=$HOME/TMP/T`date +%X | cut -c-2,4-5,7-8`
echo IP-MGR:$ISSYLIB, Date:`date +%d.%m.%y` Time:`date +%X`,$DISPLAY,$1
touch $SAVENAM; chmod +x $SAVENAM; ln -s $E HLPDIR; R=0
while [ $R != 5 -a $R != 1 ]; do 
 cd $E; make ~/TMP/issy.exe; cd; ~/TMP/issy.exe; R=$?; $e "Ret:$R"
 if [ $R = 3 ];then chmod +x $SAVENAM; $SAVENAM &
    elif [ $R = 0 ];then $SAVENAM $ISSYLIB; fi ; test $R != 9 && break
done ; rm -f $HOME/TMP/T*; else i=0; fi; test $i != 0 && exit

#export CLASSPATH=$PREFIX/libexec/termux-am/am.apk;a="com.example.termuxam.Am"
#unset LD_LIBRARY_PATH LD_PRELOAD; exec $app / $a -d $f; # <== integrated am
v=VIEW; b=broadcast; c="-n com.termux/com.termux.app.TermuxOpenReceiver"
for n in $p; do i=i+1; f=$n; test -f $n && f=$(echo `realpath $n`|sed 's/^\///')
 if [ $n = l ];then s=TMP/T.log; logcat -d>$s; grep 'E ' $s; ls -l $s
 elif [ $n = e ];then v=EDIT; elif [ $n = u ];then b=start; c=""
 elif [ $n = s ];then v=s; elif [ ! -f $n -a "$c" != "" ];then a="$api Torch --ez enabled"
  $a true;echo $n invalid|$api Toast --ez short true --es background red;$a false 
 elif [ $v = s ];then $api Share --es file $f
 else am $b $act.$v $c -d $f; fi
done
