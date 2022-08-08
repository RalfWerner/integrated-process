#!/bin/bash
# 1.used as ~/.bashrc & shortcut t  x=termux-x11 #JOB_0:115.173.=fluxbox
e=echo t=u/tmp tw=$t/xw X=Xwayland x=$X XDG_RUNTIME_DIR=$t;[ -z "$WxH" ]&& WxH=1400x1400
cd;[ "${1::1}" = ":" -o -z "$1" ]&& . uu.sh . .;[ -n "$DISPLAY" ]&& D=$DISPLAY; x1=termux-x11
c="am start -n com.termux" z=$c/.app.TermuxActivity y=$c.x11/.MainActivity w=$y pb=~/.bashrc
t=". $pb" c= p=; alias t="$t" sf="find u/ -type f|sort" o="pkill $WM" w="$WM>$tw. 2>&1&" \
n="u uu n i/touch.c i/check.c i/config.h /home/.termux/termux.properties &"
z2="$z";[ -n "$(pgrep m.termux.window)" ]&& z="$c/.window.TermuxFloatActivity";typeset -i i=0
vm="am start -n com.coboltforge.dontmind.multivnc/.MainMenuActivity" sc=.shortcuts d=$x1.deb
vr="am start -n com.realvnc.viewer.android/.app.ConnectionChooserActivity" b=u/bin/$x1 v=.vnc
#
# 2.check Display selection ($D), Server (Start if needed) and Packages Update (if needed)
shopt -s expand_aliases;[ "${1::1}" = ":" ]&& D=$1;if [ -n "$RT" ];then WM= ## below VNC ##
elif [ $D = :1 ];then w=$vm w=$vr px=$(pgrep -o Xvnc);[ ! -f u/bin/Xvnc ]&& pkg i tigervnc -y
if [ -z "$px" ];then rm -rf $v/l* u/tmp/.X*; $e geometry=$WxH>$v/config;$e '#'>$v/xstartup
vncserver $D -localhost; fi ; elif [ $D = :0 ];then [ ! -f u/bin/$X ]&& pkg i xwayland -y
[ ! -f $b -a -f $d ]&& dpkg -i $d; if [ -f $b ];then x=$x1; else $w; fi ## X-Server start ##
while [ -z "`pgrep -o $X`" -a $i -lt 15 ]; do sleep 1;[ ! -f $b -o $i = 0 ]&& $x $D>$tw 2>&1&
[ -f $b ]&& $e $x:$i; i+=1; done ;[ $i -gt 0 ]&& $z; fi ; export DISPLAY=$D ## << or IP 
if [ -n $WM ];then pw=$(pgrep -o $WM); [ -n "$pw" ]&& twm= ## below X-Client start ##
[ ! -e u/bin/$WM ]&& pkg i $WM -y;[ -f u/bin/$WM -a ! -f "$tw." ]&& $WM>$tw. 2>&1&
fi ; ## above install WM package but startet only once (toggle by aliases o/w) ##
#
# 3.shortcut processes and preparation of termux widget table ($sc) 
[ "${1::1}" = ":" ]&& shift; [ -z "$pp" ]&& pp="$e W=> invalid $@"; if [ -n "$1" ];then
case $1 in l) ls -log . i/;; x) h=24 l=70x20;[ -n "$2" ]&& h=$2;[ -n "$3" ]&& l=$3
 xterm -fb -Adobe-Courier-Bold-R-*--$h-*-*-*-*-*-*-* -geometry $l+0-0 -bg "#eeeece" -fg blue&
 ;; 0)$w;;1)$vm;; 2)$z;; 3)$vr;; t)c=touch;; c)c=check p="c*m bashrc *.c :202834.0 "
 if [ ! -f ~/u/bin/gfortran && $1 = i ];then h=https://its-pointless.github.io
  pkg in wget gnupg -y; a=u/etc/apt s=$a/sources.list.d/gcc.list; p=pointless.gpg
  $e deb $h/files/24 termux extras>$s; wget $h/$p;apt-key add $p; mv $p $a/trusted.gpg.d/
  pkg in setup-scripts gcc-9 libgfortran5 -y; setupclang-gfort-9; fi
 ;; s)sf|head ;sf|wc -l;; d)z=$2;[ -z "$2" ]&& z=2; mv 1 $z;sf>1;diff 1 $z>3;; *)#$pp;alias
esac ;else $e "usage:t [:0|:1] [<f>] [<p>] ($RT$D,f=0-3,x,t...)";fi ;yt="$y;$t " yv="$vm;$t "
if [ ! -e $sc/$c -a -z "$RT" ];then mkdir -p $sc; u="bash uu.sh" b=${c::1} a=aterm n=nedit-PC
 cd $sc;$e $u ud n /home/$sc/$n>$n;$e "$yt:0 $b">$c;$e "$yv:1 $b">$c-VNC;$e "$yv:1 x">$a-VNC
 $e "$yt:0 x">$a;$e nano $pb>nano-bashrc;$e "env;ls -l;pstree;$pp;exit 1">env-ls; cd ~/i
 v="`ls *.jp*`"; cd; for b in $v; do $e "termux-open i/$b">$sc/view-$b; done ;ls -l i/ $sc;fi
#
# 4.compile sources of $x in a loop. local WLAN (PC.Phone - see line 2 above behind JOB)
if [ -n "$c" ];then cd ~/i; X=~/u/bin x=$X/$c.exe; head -n 9 $c.c|grep -v TEST>makefile
 [ ! -f $X/make ]&& pkg i aterm make xorgproto clang libxpm imlib2 libxi libcairo -y
 for g in 1400x700 700x1400;do printf '%s\n' $b "$t$g;$vm;. $pb :1 $1">~/$sc/$c-$g; done
 t='x=$(pgrep -o Xvnc);[ -n "$x" ]&& kill $x;WxH=' i=9; export X WM y z vm vr; shift
 while [ $i = 9 ];do T=`head -n 1 $c.c` T=${T:13:1} C=gtk+-3.0 U="gcc -std=c99 "
  if [ ${c::1} = t ];then p="petm.xpm bg1.j*";[ $T -gt 5 ]&& p="*.jp* *pn c*mp4"
   [ $T -gt 5 ]&& U=c++ && C="gtk+-2.0 opencv" ;[ $T = 5 ]&& p="*png"; [ -n "$*" ]&& p=$*
   U+=" $c.c -w "; [ $T -ge 5 ]&& U+="`pkg-config --cflags $C --libs` -o "; export U 
  fi ; make $x;ls -l $x;$e p=$DISPLAY,$p;pwd; $x $p; i=$?;pwd;done ;cd ;fi
#============================= remove from here up to the end ===============================
# Die vier Teile des scriptes oben sollten selbsterklaerend sein fuer jemand der Linux/bash
# kennt. Ist das nicht so oder es wird nur "benutzt" hier doch ein paar Erklaerungen dazu:
#
# 1. Beschreibt lokal noetige Var/aliases und auch in uu.sh und macht ein Geraete/LAN-check
# 2. Hier werden X11- / VNC-Server zu $D=:0/:1 gestartet, evtl. die erforderlichen Pakete
#    dazu installiert und evtuell auch ein Window-Manager (=fluxbox Zeile 2) gestartet.
# 3. Weitere Variablen und aliases beschreiben und die Parameter zu dem script analysieren:
#  - Umschalten (toggeln) zwischen den Apps, Allgemeine prozesse starten oder c=*.c-Quellen
#  - Eventuell die Widget-Tabelle mit scripten fuellen oder "usage text" anzeigen.
# 4. Dieser Teil wird nur bei "c=Quelle" benutzt mit Quelle=touch/... (t/m/c). Dabei wird:
#  - die Installation der erforderlichen Pakete getan in der Umgebung ~/u und ~/i (uu.sh)
#  - zwei alternative Positions-scripte des gedrehten Geraetes zur Widget-Tabelle addiert,
#  - ein "make loop" gestartet, der die Quelle compiliert und ausfuehrt bis i#9 ist.
#
# Ohne Kenntnis der Quellen kann auch ein simpler X(a)term check ("t :1 x") gemacht werden.
# Das script "uu.sh" brauchst du nicht lesen koennen, aber wissen, wozu es benoetigt wird:
#  - Ist termux zum ersten mal gestartet, sollte uu.sh nach "~/" kopiert werden und mit:
# ". uu.sh ." einmalig gestartet werden. Anschliessend gibt es ~/u und ~/i ($0 ist dort)
#  - Danach startet es das alias "u" (usage Meldung) und "u ky" aendert die Extra-Keys.
#
# Bist du ein "richtiger Experte" ueberlege ob folgendes (vor 2.) funktionieren koennte:
# ============================ Nur fuer erfahrene Experten ==================================
# d=${L##*.};[ "${1:1:1}" = 5 ]&& d="${L%%.*}"; $e $D=${DPY%.*}.$d$D;DISPLAY=${DPY%.*}.$d$D
# Der Wert von $L ist oben in Zeile zwei hinter ":"! Du solltest ihn auf dein LAN anpassen!
# $DPY findest du in line 18-19 von "uu.sh"                              =================
# damit wird die lokale IP-Adresse von den beiden Geraeten (4...:L) ermittelt. und sollte 
# die Ausgabe auf einem Dieser ermoeglichen. Im Fall vom Widget "nedit-PC" geht's bei mir!
# In dem Fall wird ein "debian" distro (RT=ud) durch uu.sh installiert/benutzt (nicht noetig),
# in dem der XClient "nedit" enthalten ist. Das entspricht etwa "t :4 c" auf meinem PC.
# 
# Wie das mit :5 (IP-Adresse eines anderen Handys) und VNC geht weiss ich nicht - du?
# Ich benutze meistens "openssh" (sshd) und "mc", um gut klar zu kommen (siehe unten)
# Mit nedit koennen aber die meisten linux befehle auch vom PC aus erfolgen. Falls doch:
# o=sshd;[ ! -f u/bin/$o ]&& pkg i openssh mc;[ -z "`pgrep -o $o`" ]&& $o # ohne "#" vorne
#
# Aergere dich nicht ueber den kompakten Program-Stil - hilft mir beim Verstehen! Die 40 LoC
# hier sind auf "einem" Split-Screen vollstaendig sichtbar und darunter auch noch Multi-VNC.
# Bilder dazu (nano- und aterm.VNC in Widget-Tabelle) im Bug-Report #174
#
# Tipps (german hints):
# =====================
# Speicher ist mit Termux, evtl ein Problem. Was google uebriglaesst, reicht oft nicht oder
# muss auf SD-Card (sd) verwaltet werden. die 141Mb des "ip.zip" sind dort gut plaziert.
# Wesentlich sind die 9 APK (unzip->160Mb) und davon die 96Mb von Termux (auch nach sd).
# Von allen APK wird eigentlich nur ein Viertel gebraucht, wegen der vier "arch", von denen
# nur einer zum aktuellen Geraet passt.
#
# Trotzdem erfolgt der APK-Install ganz + unzipped + bei Termux doppelte "arch"-version fuer
# den "bootstrap" (unzip->u=../usr). Das ist aber erst der Anfang und braucht bis hier fuer:
# Termux:132Mb (u:75Mb), X11:25Mb, multivnc:28Mb, realvnc:31Mb und Widget:0.2Mb -> 216Mb
# u/ ist nach bootstrap 75Mb wird aber gleich zu beginn aktualisiert (pkg up) und um weitere
# pakete:zip,aapt und proot erweitert dann ist u:83Mb und die installation braucht bei
# Termux:218Mb
#
# Da fehlen noch alle Pakete fuer X/VNC-Server,make und proot-distro's "mit" ist dann in ~/..:
# usr:647Mb und ud:460Mb und mit einem ubuntu-distro, das auch make enthaelt (uu:770) ist dann
# Termux:2.1Gb. Du brauchst aber nur 1.42Gb freien Speicher, wenn du nicht mehr als nur xterm
# Bug/Feature testen willst.         ====== ist nach oben unbegrenzt - Tb ist kein Linux-Limit
#
# xterm funktioniert kaum ohne WM aber touch/check braucht keinen WM,was den Bedarf reduziert
# Termux:1.16Gb, wenn kein WM installiert wird ("_" oder "=" aus Zeile zwei oben entfernen).
# Ich habe hier einen "spartanischen" WM gewaehlt, der hinter "=" steht. fluxbox enthaelt auch
# aterm (xterm), das dann nicht separat installiert werden braucht und alle xorg-fonts und
# feh als "Foto-Tool", (nicht verwechseln mit der MultiTouch-Foto-App beim "view*" Widget)
# Zum Test reicht das. Die Grenzen deines Geraetes bekommst du eher mit WM=xfce4 heraus.
#
# Berechtigungen und Settings:
# ============================
# Eigentlich sollten bei der Installation alle noetigen Rechte erlaubt werden, werden aber
# auch leicht uebersehen oder auf manchen Geraeten ignogiert. Hier die wichtigsten:
# - Storage-Access (allow) muss! erlaubt auf manchen Geraeten sdcard nicht oder nach repeat.
# - Display "over" other Apps ist auch immer noetig auch fuer "float"-App (kein Thema hier).
#
# Die X11_02_04 App kann RS=Reseed Screen (haette ich gern bei MultiVNC) aber kein fullscreen
# Warum die beiden Option Schalter sind habe ich nicht verstanden (unnoetig) der PiP-Switch
# hier sollte immer "aus" sein und beim "Touchscreen input mode" solltest du "Direct mode"
# setzen. Das erlaubt dem XClient die Multi-Touch-Analyse und sollte auch von MultiVNC
# verarbeitet werden koennen, wenn dort RS moeglich ist (wie bei TV).
#
# Diese Version hat die identischen ExtraKeys (EK) wie Termux mit dem KB-Key und als Popup
# darueber (sweep up) die X11-Settings aber noch etliche bugs.
#
# touch und check sind "Experimentier Quellen" (XClients) ohne "Release Anspruch" und in
# =====================
# ip.zip enthalten. Auf check.c gehe ich hier nicht ein. touch.c ist fuer den featcher-check.
# in #169. Dort sind mehrere Beispiele mit dieser Quelle und "Emulate Mouse" und RS-Verhalten.
# Beim "Direct mode" (Multi-Touch) werden aktuell zusaetzlich Generic-Events gelogget
# bei touch: Maus und Finger und bei TEST=4:"finger-trace-lines" nur im "Direct mode"
#
# Gesten-Events(4-6) und Key-Events(2-3) mit Fingern (Maus/S-Pen):
# - Tab-Move-Release auf einem Fenster mit dem ersten Finger (oder Maus mit MB1) bewegt Dieses
#   zu der Release-Position. Bei XCB (*.jpg) bleibt das Fenster vollstaendig im RS und bei
#   Xlib (*.xpm) bleiben mindestens 20% des Fensters im RS.
# - Endet die Geste an den vier Raendern des RS, werden folgen die Aktionen, die auch einem
#   Key-Event entsprechen:"links/2": wechselt zur Termux-App,"oben/c": compiliert/startet neu,
#   "rechts/1 oder 0": wechselt von der X11-App zur MultiVNC-App oder von dort zur X11-App,
#   "unten/3": wechselt zur RealVNC-App (und fullscreen falls Split benutzt wurde)
#
# Wird Split (Termux oben) benutzt, sollte der log der aktuell unten angezeigten X11/*VNC-App
# eingestellt werden (NEXT=popup vom ENTER-EK) oder im DRAWER=pupup von KB-EK oder links-sweep
# Auf deinem PiP-faehigen Samsung empfehle ich drei Picture,S-Pen und floating KB zu nutzen.
#
# Termux/X11-Entwickler/Status:
# =============================
# Die 10-20 Entwickler sind sehr fleissig, nicht perfekt und teilweise etwas unorganisiert.
# Neue Versionen sind "rolling releases". Nachdem der Initiator @fornwall sich zurueckzog,
# wird die Termux-App von @agnostic-apollo verantwortet. Er hat die EK-Entwicklung wesentlich
# vorangebracht und auch an der integration in X11 (@twaik,@suhan-pradkar) mitgearbeitet.
# Dies ist in wenigen Tagen erfolgt und war (zwar unvollkommen) am 1.Sept fertig.
#
# Wenn die X11-App nicht mehr reagiert oder der Widget-Start nicht funktioniert muss die App
# manuell (ueber die Benachrichtigung) mit "Exit" gestoppt und erneut gestartet werden.
#
# Aktuell ist "basic" die stabilste version, *02.04 ist die Letzte ohne "Run-Command".
# Ab *02.06 wird der App-Start komplizierter und ist noch in einem "Experimentier-Stadium":
# dazu ist $d (Zeile 8) ebenfalls nach $HOME zu kopieren (fuer dpkg in Zeile 16).
#
# Das letzte offizielle Termux-Release (0.117) ist vom 8.Jul, die in "ip.zip" hat aber den
# letzten Stand der "master" updates. Vermutlich wird dieses Jahr noch 0.118 freigegeben.
# Wenn du diese Datei mit dem "nano bashrc" Widget anzeigst und du den folgenden link 
#
# https://github.com/bk138/multivnc/issues/169
#
# mit "long-tap" markierst kannst du ihn mit "More" oeffnen. Im "Split mode" wird das dann in
# "Chrome" unter Termux angezeigt.
#
if [ a = b ];then # zwei bashrc OTS-Beispiele mit reduzierten packeten
#!/bin/bash # VNC-Xserver & WM=fluxbox (includes feh and aterm) JOB_1:115.173.=fluxbox
z="am start -n" r="$z com.realvnc.viewer.android/.app.ConnectionChooserActivity"
case $1 in 0|1) $r;; 2) $z com.termux/.app.TermuxActivity;; *). uu.sh . .; esac ;f= v=.vnc
[ -n "$1" -o -n "$RT" ]&& return;[ ! -f u/bin/Xvnc ]&& pkg i tigervnc $WM -y;t=$PREFIX/tmp
alias t='. ~/.bashrc' n='u uu n /home/.termux/termux.properties &'; export DISPLAY=:1
if [ -z "$(pgrep -o Xvnc)" ];then rm -rf $v/l* $t/.X*; [ -z "$WxH" ]&& WxH=700x700
  $e geometry=$WxH>$v/config; $e '#'>$v/xstartup; vncserver :1 -localhost; $r; fi
for p in $WM aterm feh; do s=$(pgrep -o $p); if [ -z $s ];then $p $f>$t/$p 2>&1&
fi ;f=;[ ${p::1} = a ]&& f="-g 300x200+0+400 i/bg2*";done ;feh --bg-fill i/bg1*; $pp
fi 
