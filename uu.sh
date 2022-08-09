#!/bin/bash
# This script should already exist preferably in u/bin or ~. ($PATH). Use cases:
# 1.Set environment:"$*=. ." 2.Change the object symlinks (i:default s?/ip):"$*=. [object]"
# 3.execute (proot) processes see usage below:*)c, e.g:"u uu": open/create ubuntu/debian distro
# this script should sourced in .bashrc. Is $RT "not" u* or rt but $1,it will started in proot
I=$PWD a=$1 b=$2 c= e=echo o="sd i .bashrc";[ -z "$a" ]&& a=-; [ ${#3} -gt 2 -a $a = . ]&& RT=$3
#In case of 1.:<source> from ~/.bashrc -> ~/i/bashrc, this script doing:
# Setup $HOME (~/) with symlinks (ln -s ...) to use functions of an object ($2) stored in ~/sd
# The first two characters of PS1-prompt (rt/u*) identify the current proot/$RT process.
# The symlink ~/u=../usr is correct in all $RT cases and ~/i is the object-symlink
# Set root-idetifier RT and establish/list ($o) symlinks in $HOME, modified by this script
#
# Prepared:Ralf Werner Jan 2020, last Mod: Feb 2022 tkdiff uu.sh ipm/uu.sh bashrc ipm/bashrc
#
s=storage sd=/$s/emulated/0 ct=com.termux ib=i/bashrc pp='ps -eo pid,ppid,comm,etime' l= w= z=tu
u=../usr p=proot-distro pr=~/u/var/lib/$p pri=$pr/installed-rootfs sb=/system/bin ar=`uname -m`
[ -f $ib ]&& c=`grep -m 1 JOB_ $ib`; [ $ar = x86_64 ]&& z=t2; if [ -n "$c" ]
then c=${c#*_} l=${c#*:} l=${l%.*};[ "$l" = "$c" ]&& l=;[ ${c:1:1} = : ]&& DISPLAY=:${c::1}; fi
[ -z "$l" ]&& l=115.118; [ -z "$L" ]&& L="$l" wc="--wildcards usr";[ ! -e ~/i ]&& wc=
[ -z "$DPY" ]&& DPY=$($sb/ip a|grep -m 1 /24|cut -d / -f1|sed -e 's/inet//' -e 's/\ //g')
[ -z "$DPY" -o "${DPY%.*}" = 10.0.2 ]&& DPY=192.168.0.${L%%.*}; g=$TERMUX_APP__APK_PATH
if [ $a = . ];then [ -f uu ]&& . uu; [ $0 = /bin/bash -a -z "$RT" ]&& RT=rt;[ ! -d $u ]&& u=.
 f="\\[\\e[01;34m\\][\\[\\e[0m\\]\\[\\e[00;32m\\]\\w\\[\\e[0m\\]\\[\\e[01;34m\\]]\\" w=${c#*=}
 PS1="$RT$f[\\e[0;34m\\]\\[\\e[0m\\]\\[\\e[1;37m\\]\\$\\[\\e[0m\\]\\[\\e[00;37m\\] \\[\\e[0m\\]"
 [ ! -e u -a -e $u ]&& ln -s $u u; u= nl=/data/data/$ct/lib apk=$nl/../../base.apk d="pkg up -y"
 [ "$w" = "$c" ]&& w=;[ -z "$WM" ]&& WM=$w;[ ${#3} -gt 2 ]&& return; if [ ! -d $nl -a -z "$RT" ]
 then [ -f u/bin/adb ]&& u='adb shell'; if [ ! -f $apk -a -n $g ];then apk=$g
  elif [ ! -f $apk ];then apk=`$u pm path $ct|grep bas|cut -d: -f2`; else apk=noapk; fi
  [ ! -d $nl ]&& rm $nl; [ ! -e $nl -a -f $apk ]&& ln -s $(dirname $apk)/lib/* $nl; g=u/nl
  [ -d $nl -a ! -e $g ]&& ln -s $nl $g;[ ! -e $g ]&& $e "W=>$g missing nl=$nl, apk=$apk"; fi
 u=u/bin/aapt c=$ct.app.reload_style f=`df|grep $s|grep \-|cut -d% -f2`; [ -n "$RT" ]&&u=.&&sd=.
 while [ ! -w $sd ];do $e access:$sd; am broadcast --es $c $s -a $c $ct;sleep 1; rm -rf $s;done
 for g in i/$z $sd/$z $f/$z;do if [ -f $g.tgz -a ! -e $u ];then $e "restore from $g.tgz $wc"
   tar xf $g.tgz $wc; rm -rf ../usr; $sb/mv usr .. ; $d; fi ; done ; g=getprop
 if [ -z "$RT" ];then [ ! -f $u ]&& pkg i proot aapt x11-repo android-tools zip -y && $d
  if [ -f $apk ];then d=`aapt d badging $apk|head -n 4` z="$g ro.build.version"
   vt=`$e $d|cut -d= -f4` v=`$e $d|cut -d: -f5` v=${v:1:2} vr=`$g ro.product.first_api_level`
   $e Version:${vt::6}/`$z.release`=$vr target=$v $ar $DPY WM=$WM
   [ $v -ge 29 ]&& unset LD_PRELOAD; [ $v -le 28 ]&& unset TERMUX_ANDROID10; fi
 fi ;alias ll="ls -la" lt="ls -haltogL" u="bash uu.sh" s="$e u:\$(find $PREFIX -type f|wc -l)"\
 d="du -hd 1" pp="$pp" sp="$sb/$pp"; cd $I; ba=../base.apk bb=../lib/../$ba g=i/bashrc
 [ ! -e $ba -a -e ../$bb ]&& ln -s $bb $ba; export PATH=./:$PATH:$sb DPY L RT WM
#
# Search for the object (ip) path:$b - should be found or as *.tgz, (bashrc is expected in it) 
 [ "$b" = . -o -n "$RT" ]&& return; a=Android/data/$ct/files; [ -z $b ]&& b=ip; rm -f $o
 for d in $sd $f $sd/$a $f/$a; do for w in $d $d/Download; do q=$w/$b; for z in .zip .tgz ''
 do if [ ! -e i -a -w $q$z ];then if [ ! -d $q ]; then
    [ -f $q.tgz ]&& tar xf $q$z -C $w; [ -f $q.zip ]&& unzip -q $q$z "$b/*" -d $w; fi
    [ -f $w/bashrc ]&& b=.; if [ -d $w/$b ];then ls -l $w;ln -s $w sd; ln -s sd/$b i; fi ; fi
 done ;done ;done ; if [ ! -d sd ];then ln -s $sd sd; mkdir sd/ip; ln -s sd/ip i; fi
 ln -s $g .bashrc; [ ! -s $g ]&& $e ". uu.sh . .">$g; ls -l $o i/;[ $0 = uu.sh ]&& exit; return
fi ; u=../$a nl=/data/data/$ct
#
# create and "distro" in $u with Termux-external Linux installations (see also u tu u?" below)
if [ ${a::1} = u -a -z "$RT" -a ! -d $u/usr ];then b=$a;[ $ar = x86_64 ]&& a=u2; f=$sd/$a.tgz
 [ ! -e $f ]&& f=`df|grep $s|grep \-|cut -d% -f2`/$a.tgz; [ ! -e $f ]&& f=i/$a.tgz
 if [ -e $f ];then $e Restore distro:$u from $f ...; mkdir -p $u; tar xf $f -C $u; $e finish
 else case ${b:1:1} in d)d=debian;; *)d=ubuntu; esac # other:alpine archlinux fedora opensuse
 if [ ${b:1:1} = i ];then d=i386; pkg in qemu-user-$d -y; cp u/etc/$p/ubuntu.sh u/etc/$p/$d
  $e "DISTRO_ARCH=i686" >> u/etc/$p/$d ls -l u/etc/$p;cat u/etc/$p/$d; exit; fi
 bi=$pri/$d; [ ! -e u/bin/$p ]&& pkg i $p -y; [ ! -e $bi ]&& $p install $d; [ ! -e $bi ]&& exit
 for z in 'apt update' 'apt full-upgrade' 'apt-get install nedit'; do $p login $d -- $z -y
 done ; if [ -e $bi ];then mv $bi $u; rm -rf $pr/dlcache; $e "I=>$u installed"; ls -l .. $pri
fi ;fi ;a=$b;fi ; [ -z "$RT" ]&& rs=termux-reload-settings
cd;y=n;c=; p="proot -b /storage -b /system -b /data -b /dev -b /proc -b u/tmp:/tmp " g=/usr/bin
[ -d /apex ]&& p+="-b /apex "; l=/linkerconfig/ld.config.txt; [ -e $l ]&& p+="-b $l "
ne="nedit -display " n0="$ne${DPY%.*}.${L%%.*}:0 i/bashrc /home/uu.sh" bin=$g:$nl/files$g
check_pkgcache(){ [ -z "$(find u/var/cache/apt/pkgcache.bin -mmin -5)" ]&& apt update; }
case $1 in n*) if [ "$1" = n ];then c=$n0; else c="$ne:${1:1:1} $0 .bashrc";fi ;$e c=$c;;
u*)p+="-b $HOME:/home -b $nl:/u --link2symlink -0 -r $u -w /root /usr/bin/env -i HOME=/root "
   p+="RT=$1 PATH=$bin:/bin:/sbin:/system/bin TERM=xterm LANG=C.UTF-8"; if [ "${2::1}" = n ]
   then shift; c="$ne:${1:1:1} $0 .bashrc";[ $1 = n ]&& c="$n0";$e c=$c/$*;fi ;;
rt)p+="-b u:/usr -b u/bin:/bin -b u/etc:/etc -b u/lib:/lib -b u/share:/share -b u/var:/var "
   p+="-r ..";; pu) ls $u; c="package update";;
#
# backup management of termux (tu), distros (u*) and objects (i*)
tu)y=y c=sd/$z.tgz z=.; if [ ! -h sd ];then b="miss ~/sd";elif [ -z $b ];then a=.. z='usr home'
 elif [ ${b::1} = i ];then pwd;for z in sd i .;do u=uu.sh;if [ -e $z/uu.sh -a -d $z/$b/ ]
   then cd $z; zip -rq9 $b.zip $b uu.sh apk; ls -l *.zip; exit ;fi ;done ; exit
 elif [ ${b::1} = u ];then a=../$b c=sd/$b.tgz;[ ! -d $a ]&& y=; else a=`ls -l sd/*.tgz`;fi
 if [ -z "$c" ];then $e "I=> $b,$a";y=; elif [ -f $c ];then ls -l sd/*.tgz
  $e "$c, a=$a/$z, b=$b replace:y,restore:r ";read -n 1 y; fi 
 if [ "$y" = y ];then date;$e "create $c ($a) ..."; cd $a; tar czf - $z>~/$c;cd $I; date
  elif [ "$y" = r ];then date; $e "restore $c ..."; tar xf $c -C ..;date; fi ;exit ;;
#
# SYMLINK, ELF check and split for (API 29) boot-loop process
ec)cd $I;l=$2 nl+=/lib; [ -z "$l" ]&& l=u; date; if [ ${l##*.} = tgz ];then $e usr from $2
 tar tf $2 usr|sed -e s"%/% %"|grep -v /;[ ! -f $2 ]&& adb pull $sd/$2; tar xf $2 usr; exit
 elif [ $l = usr -a ! -e $l ];then cp -rp ../$l .; n=$l/libnl;mkdir -p $n; cp $nl/* $n; fi
 if [ -h $nl/0001.so ];then cp ../$l/libnl/* $l/libnl; ls -l $l/libnl|head; fi
 if [ ! -d $l ];then $e "E=> $l invalid usr/* path";exit;fi ; cd $l;s=SYMLINKS.txt;u=update
 rm -f $s; ln='ln';[ $l = usr ]&& ln='##'; $e "mkdir -p newnl libnl; $e $u nl and libnl ...">$u
 typeset -i i=0 j=0 k=0; chmod +x $u; $e "$s ($#) check ($u/$ln) start ..."
 while read -r f;do set $f;i+=1; n=n${2##*n}; if [ .${2##*.} = .so -a ${n::3} = nl/ ];then j+=1
  n=$(printf "%s/%04i.so" ${2%/*} $j); printf "%sâ%s\n" $n $1>>$s
  printf "rm %s;cp -p nl/%s newnl/%04i.so;%s -s %s %s\n" $1 ${2##*/} $j $ln $1 $n>>$u;
  else printf "%sâ%s\n" $2 $1>>$s ;[ $l = usr ]&& $e "rm $1">>$u; fi
 done < <(stat -c%N $(find -type l)|sed -e s%\'./%% -e s%\'%%g -e s%' ->'%%)
 $e finish with $j old nl of $i ELF check start ...;bin="bin lib libex* $3"
 while read -r f; do k+=1;if grep -q ELF < <(dd if=$f bs=1 count=3 skip=1 2>/dev/null);then
   j+=1;b=${f%/*};c=..;while [  $b != ${b%/*} ]; do c+=/..;b=${b%/*}; done ;
   n=$(printf "%s/nl/%04i.so" $c $j);printf "%sâ%s\n" $n $f>>$s; i+=1
   printf "mv %s newnl/%04i.so;%s -s %s %s\n" $f $j $ln $n $f>>$u; fi
 done < <(find $bin -type f); $e "#head $s $u; tail $s $u;">>$u; $e "$j,$i in $k $l/($bin)"
 [ $l != usr ]&& exit; b=bootstrap-$ar.zip; $u; rm -rf libnl $u ../$b nl; $e create $b ...
 mv newnl libnl; zip -rq9 ../$b .;cd ..; rm -rf $l; ls -hog $b $nl/*boot*; date; exit ;;
#
# set and load Toolbar/EK settings in one or two lines (usage merssage)
ky)t=~/.termux;[ ! -e $t ]&& mkdir $t; t+=/termux.properties d=display k=extra-keys p=popup
 m=macro sk="hide-soft-keyboard-on-startup=true soft-keyboard-toggle-behaviour=enable/disable"
 lf="{key:LEFT,$p:BKSP}" ed="$p:{$m:'CTRL d',$d:d}" eh="{key:END,$p:HOME}" o=`grep one $t`
 nx="{key:ENTER,$p:{$m:'CTRL n',$d:'next'}}" tp="{key:TAB,$p:PASTE}" ek=$k-style=arrows-all
 kd="{key:KEYBOARD,$p:DRAWER}";x="{$d:X11,$m:'t SPACE 0 ENTER',$p:{macro:'w ENTER',display:WM}}"
 mc="{$m:'mc SPACE i ENTER',$d:mc,$p:F10}" cd="{$m:CTRL,$d:'^',$ed}" m="#"
 if [ "$o" != "" ];then k+="=[[ESC,SHFT,$kd,{key:'/',$p:{$d:'\\\\\\\\',macro:BACKSLASH}},{key:\
  '-',$p:'|'},UP,$nx,HOME,PGUP,$x],[ALT,$cd,$tp,{key:BKSP, $p:DEL},$lf,DOWN,RIGHT,END,PGDN,$mc]]"
 else k+="=[[$cd,$tp,$lf,{key:RIGHT,$p:{macro:'o ENTER',display:off}},{key:UP,$p:PGUP},\
  {key:DOWN,$p:PGDN},$eh,$nx,$kd,$mc,$x]]"; m="#one"; fi ; m+=" fullscreen=true"
 printf '%s\n' $m $ek shortcut.next-session=ctrl+n $sk enforce-char-based-input=true "$k">$t
 $e "allow-external-apps=true">>$t; $rs; exit ;;
*)c=uu.sh;printf '%s\n' "usage:u=bash $c [opt] [cmd] or [. ]$c . [obj] to change symlinks: ~/$o
 [opt] n:nedit on PC, ne:nedit on phone, rt:proot, u*:ubuntu/distros" "  tu: create *.tgz file\
  with *:uu, tu (termux) or i (object)" "  ky:Set Keyboard with 1 (default) or 2 lines DPY=$DPY,\
  L:$L" "  ec:ELF check/split of exeutables, none:switch to */ip otherwise:show this help info" "
 [cmd] alias t [...] as termux-proot (rt) or 'proot-distro' (u? default ubuntu)
 [obj] on sdcard (i) and used as ~/.bashrc to start object funktions (default ip/bashrc)
  replace the sysmlinks: $o in ~. [obj].tgz will unpack (should be in ~/sd/*),
  The script:$ib will used for functions and pu=package update and do: . $c . .
  This checks the termux environment, versions and establishes aliases and symlinks" "
  With tu.tgz inside, this has priority, when exist in [obj=~/i] else in ~/sd. PU finish
  with: file $ib exist, but Attention: tu.tgz overwrite ~/* and u=../usr (termux)" '';$rs ;exit
esac ;shift; if [ -z "$c" ];then c="$1";shift;fi ; unset LD_PRELOAD;#$e "a=$a,RT=$RT c=$c p=$@"
if [ "$RT" = rt ];then $e "$RT:$a unsupported"; elif [ "${RT::1}" = u ];then $c "$@"&
 elif ! type proot>/dev/null 2>&1;then $e proot not installed here $RT; elif [ -n "$c" ];then
  $p sh -c "$c $*"; else l="/bin/bash -l";if [ $a != rt ];then l="/bin/su -l root"; cd $u/root
  for m in $o uu.sh; do [ -f $m ]&& rm $m; [ ! -h $m ]&& ln -s /home/$m $m; done
  $e "export RT=$a">uu; cd; fi ; exec $p $l
fi
