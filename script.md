## OTS means One Touch Start
I use [OTS](https://github.com/termux/termux-float/issues/37#issuecomment-916777123) to _start_ 
[objects](https://github.com/RalfWerner/integrated-process/tree/master/README.md#IP-objects) (all processes sshd, x11 ... and package installs) with _One Touch_ in the Termux/Widget environment. So that it also works with a _virgin Installation_, mainly two scripts outside of **Termux** are needed ([uu.sh](#uu-sh) and [bashrc](#bashrc)) and symlinks: `ln -s  /storage<> sd`). Mostly is `<>=/emulated/0` for internal storage or `/xxxx-xxxx` for a SD-card (using `df` to show). In addition to **Termux** are also, **X11** and other plugins are used. Typical is a mobile that is operated with the fingers, but may be connected to pens, mice and external keyboards.
## MB_Helper in X11 Client
Eine Möglichkeit MB=Maus-Buttons ohne Maus (finger/stift) zu nutzen, ist die Erweiterung durch den `EK_X5.h` **Header** in der Quelle des XClients oder die [Server](https://github.com/RalfWerner/integrated-process/edit/master/script.md#mb_helper-in-x11-server) Funktionen. Der Header macht mehr als dies, hier wird aber nur die **MB** Funktion beschrieben. Der **Header** kann mit main:(`#define TEST 9` und `#include "EK_X5.h"`) oder als Teil von z.B. _aterm_ verwendet werden. Ich betrachte hier nur den `TEST 9` Teil, der mit der `touch.c` Quelle durch bashrc erzeugt und gestartet werden kann (`t t`). Es wird dann nur das Window mit dem MB-Icon angezeigt.
... in progress translation later
### What is a touch, gesture and tap
A simple gesture begins with click/touch (4) and ends with the release (5) of the last button/finger/pen. In between, movements (6) can be made. Without move it calls **tap** There is the pointer (cross/arrow etc), the **cursor** (inside text), the mouse, fingers/stylus on touch-pads/screen and cursor buttons of extrakeys and keyboard. There are also three [touchscreen input modes:14](https://github.com/RalfWerner/integrated-process/assets/45426380/33e9aba1-d308-4d89-94a5-d28c805416f3) **(TIM)** in **X11**. Mouse and finger events are treated differently. Compared to older versions, **TIM**=[Simulated touchscreen:06](https://github.com/RalfWerner/integrated-process/assets/45426380/729a95a5-47ac-469e-91bc-b022f28ad3ba) has to be a **delay** in the finger Touch+Move (gesture). _Otherwise the whole gesture will be ignored._ People with trembling fingers or who are used to rapid gestures like me, possibly [have problems:11](https://github.com/RalfWerner/integrated-process/assets/45426380/4465d174-916f-46b0-870c-98b08ae3525b) with it.

I have not yet understood the reason for this change. The pointer is always hidden under the finger at this **TIM**, in contrast to **TIM**=[Trackpad:06](https://github.com/RalfWerner/integrated-process/assets/45426380/7754b5d3-b590-441c-b1c3-c315b982bcd0), where the pointer moves gesture in parallel to the finger-gesture and a _long tap_  leads to the interrupt/end of the gesture. Alternatively use **TIM**=Direct touch, which not all XClients support or they've own multi-touch gestures (pinch etc) and this **TIM** is a bit unstable.
#### check via a PC and scrcpy
**MTE**=[Multi-Touch Events:10](https://github.com/termux/termux-x11/assets/45426380/333595c3-d890-49ef-997f-b8e4f7686918) (Generic/Xinput2/35) are only recognized by **TIM**=Direct of XClients that support MTE and are not comparable to multi-click events (2 or 3 mouse buttons/4-6). My PC does not support this either.
The three **TIM** settings can also be checked without XClient if the Pointer is shown as a cross. In the **ekeys** version, however, an Xclient is to start that generates this Pointer. In the extrakeys, the Preferenz setup that I use is to change the three TIM via the KB button. Then I use the PC mouse (circle+yellow+red) to move the Pointer. This corresponds to the finger move gesture and has a follow -up (Delay), which does not take place if the mouse is used on the pad/mobile.

<details><summary> Steps to repeat the installation (example moto-g7) </summary>

1. The required installation data must be saved or downloaded in the Android environment. They contain the required apps/plugins, the `uu.sh` script (in **apk**) and object data with `bashrc` (in **ip**).
2. Install the Termux app (in **apk**), open (bootstrap), allow the memory to be authorized and update the packages with `pkg up -y`. All 5 _"Questions"_ should be confirmed with Enter. [Virgin](#virgin-termux-vt-update-with-pkg--pu-or-tgz-tu)-Termux is thus ready to work as a basis with 3300 files in `~/u` and the permission to` ~/sd`.
3. The expansion of the plugins and packages left in `~` is carried out with:`bash <>/uu.sh . -` (below). At least the APK: **api** and one XServer (here **x11a**) are installed, if necessary. When archives/backups available, one of them can _now_ be installed. Otherwise the packages of **ssh** and other usefull base tools will be installed, which are then about 5225 files in `~/u`.
The three apps: **app+API+X11** without the sources now needs: 311+7.3+14.5=333 MB on the device. This can be 10-20 times larger due to the package requirements of an object. However, it is sufficient as a good Linux terminal.
If the argument `-` is left out or replaced by an object name (default **ip**), this is set up as a link `~/i` in which is `ln -s i/bashrc .bashrc` for new terminal that installs all packages needs by the object.
</details>

After download/[installation](https://github.com/termux/termux-app/blob/master/README.md#Installation) of App+Plugin (**apk**) and bootstrap, will [uu.sh](#uu-sh) used to _one time_ Start with **`bash uu.sh . -`**. Then should the following symlinks exist: `u,sd,i,.bashrc`. The environment can be checked with alias `pp;ll` etc. If a backup extist (`~/sd/t*.tgz`), this may restored. The _useage_ of the two scripts is displayed with aliases: `u` and `t` (without parameters).
## to the script [~/.bashrc](#bashrc)
It is divided in different sections but could use outside of termux as _bash_ script (partially) too. The first Termux update contains several widget scripts [`~/.shortcuts`](https://github.com/RalfWerner/integrated-process/blob/master/bashrc#L35#L38). In order to display this on the start screen (_Long Tap_) this must be set in the widget management of the mobile phone. The corresponding functions are somewhat different on my two devices. and [api29](https://github.com/RalfWerner/integrated-process/blob/master/api29#install-api) [object](https://github.com/RalfWerner/integrated-process/tree/master/api29/#packages)
## Virgin Termux (vt) update with pkg ... (pu) or *.tgz (tu)
This requires a `*.apk` (for example, termux_73 or [my backup](https://www.dropbox.com/s/ug071qoox8gwf1c/ip.zip?dl=0)) and a first open (bash prompt) from Termux.
To perform this section, there must be _no_ **i,sd** file (will generated here) and the required data must be available on the phone in `~/sd`. (including **uu.sh, bashrc** itself).
This can be an sdcard or internal memory (sd=d) that can be used with `termux-setup-storage` in the script. For this are set up symlinks in `~/`.
Alternatively, a **tar/*.tgz update** can be used (below) if a _*.tgz_ of a previous installation exists. This is much faster (15 seconds) than **pkg**.

Is _$d_ assigned (see below) the update could start with:`bash $d/ip/s $t`.
## bashrc
In general, it's part of the **object** and also a symlink [~/i/bashrc](https://github.com/RalfWerner/integrated-process/blob/master/api29/bashrc#L1#L51)) (`ln -s **sd/ip** i` in `~` done by `u . $name`) and _checks_ the state of the installation before the first prompt. more complex [Presteps]([~/sd/ip/bashrc](https://github.com/RalfWerner/integrated-process/blob/master/bashrc#L1#L51)) start severals closed PID do with first shell open in Termux:
- start some processes (PID): sshd, Xvnc and/or possibly Xwayland (Xorg)
- and set some aliases: **pp** to _check_ PID, **ll**=`ls -la` to list files, **d**=`du -hd 1` to _check_ space
- with `$name` the Path to `~/sd` could changed, when several Objects on th device. default is `ip` on internal storage
## uu sh
`uu.sh` is a [script](https://github.com/RalfWerner/integrated-process/blob/master), that is usually **not** in the termux _bootstrap_. So it has to copied [see above](#ots-means-one-touch-start) to `~` or symlinked to `~/sd/uu.sd`. On of the first actions in [bashrc](#bashrc) is `. uu.sh . .` to check genaral states (independent from Object).
<details><summary> various test functions with alias u </summary>

since PATH also contains `:.`, **t** is enough to call `bash ~.bashrc $@`. Without parameter,_usage help_ is displayed or else the described function is executed.
The two scripts parts listed above are ignored. **s** is legible, so here are just a few special features:
- API dialogs/functions (need the installation of _api_ plugin) started with `t d` (termux only)
- LAN/DISPLAY adresses is estimated by the second parameter (without is **DISPLAY=:1** and Xvnc as Xserver the default)
- The third (second) parameter (above) identify a keychar like **d** (above) or **tgz** or files
## tgz backup of termux installation
With `t tgz` you see a separat _usage help_.The most important function is to produce `~/sd/t.tgz` from`~/..`. The process can take 8 to 80 minutes. Subsequently, however, the Termux state can be quickly restored (above) if another Virgin-Termux is used or reinitialized after `rm -r ../*`. 
Since then **~/sd** is no longer known you have to use the 
path _d=/storage/6533-6333/; t=t_ in `tar -xzf $d/$t.tgz -C ..`.
## further funktions of alias u
"Elf-Check" is basically a script (part of the bootloop process) that separates the executables from the rest of the data into $ prefix and supplements Symlink.txt with these references.
This does not change anything at the _bootstrap_, but can be used for all TargetsDK. In contrast to Android-10 and update flowered, only one Symlink is necessary.
</details>

### MB_Helper in X11 Server
In the following video, the XClients _fluxbox and aterm_ are displayed, the trouchMode **Trackpad** is selected and the device is moto g(7). x11-Version **1e7857c** has a pre+post-MB display, which corresponds to the three mouse buttons 1=L,2=M,3=R. Gboard is used as the KB and the back key is used to turn on the EK bar, in which the EK-KB button turns on the _floating_ KB (covers EK). Then: portrait rotation, which **turns KB off**. Then the two MB helpers are turned on with the first EK button. Post-MB over aterm and pre-MB below and the _floating_ KB is turned on (**covers pre-MB and EK disappears**).

https://github.com/RalfWerner/integrated-process/assets/45426380/a1ad1722-74b3-4b05-8024-0ae0d27a6eb7

Then a landscape rotation is made, which **turns KB off again, post-MB disappears and EK covers pre-MB**. If KB is turned on and changed to _Fixed_, pre-MB also disappears. After another portrait rotation, turning KB on and "Fixed", post-MB disappears but EK is back above the KB.

If the pre/post MB display always appears completely and can be used, this is a great feature.

Actually, I only need Pre-MB. It could also be used for all touchMode inputs (not just stylus) and _multiple_ Pre-MB selections would also be an option. If there was then a _one-time/permanent_ distinction, you wouldn't need a real mouse anymore. I will mainly work with **Direct** because it is the only way to make simple finger gestures.
