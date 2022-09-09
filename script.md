# OTS means One Touch Start
I use [OTS](https://github.com/termux/termux-float/issues/37#issuecomment-916777123) to _Start_ 
[objects](https://github.com/RalfWerner/integrated-process/tree/master/README.md#IP-objects) all processes (sshd, x11 ... and installs) with _One Touch_ on Termux environment. So that it also works with a virgin app installation, are mainly two scripts ([uu.sh](#uu-sh) and [bashrc](#bashrc) that are outside of **Termux** and a symlink: `ln -s  /storage... sd`) needet.

After download/[installation](https://github.com/termux/termux-app/blob/master/README.md#Installation) of App+Plugin (APK) and bootstrap, will [uu.sh](#uu-sh) with the file App copied to `~`. Start there with **`. uu.sh .`**.
Thereafter should the following symlinks exist: `u,sd,i,.bashrc`. The environment can be checked with alias `pp;ll`. If a backup extist (`~/sd/t*.tgz`), this will restored. The useage of the two scripts is displayed with aliases: `u` and `t` (without arguments).
# to the script [~/.bashrc](#bashrc)
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
