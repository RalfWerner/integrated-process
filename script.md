# OTS means One Touch Start
I use OTS to start all processes (SSH, X11 ... and installs) with _One Touch_. So that it also works with a virgin app installation, I use mainly two scripts (`uu.sh` and `~/i/bashrc`) that are outside of **Termux** and a symlink: `ln -s  /storage... sd`).

After download/installation of App+Plugin (APK) and boatstrap, copy `uu.sh` with the file app to `~`. Start there with `. uu.sh .`
Then following symlinks exist: `u, sd, i, .bashrc`. The environment can be checked with the commands: `alias; pp; ll`. If `~/sd/t*.tgz` a backup contains, this is restored. The use of the two scripts is displayed with `i` and `t` (alias without arguments).
# to the [script s](https://github.com/RalfWerner/integrated-process/edit/master)
It is divided in different sections but could use outside of termux as _bash_ script (partially) too. The first Termux update contains 11 widget scripts (`~/.shortcuts` lines 22-25). In order to display this on the start screen (_Long Tap_) this must be set in the widget management of the mobile phone. The corresponding functions are somewhat different on my two devices.
## Virgin Termux (vt) update with pkg ... (pu) or *.tgz (tu)
This requires a `*.apk` (for example, termux_73) and a first open (bash prompt) from Termux.
To perform this section, there must be _no_ **t** file (generated here) and the required data must be available on the phone in `~/sd`. (including **s** itself).
This can be an sdcard or internal memory (sd=d) that can be used with `termux-setup-storage` in the script. For this are set up symlinks in `~/`.
Alternatively, a **tar/*.tgz update** can be used (below) if a _*.tgz_ of a previous installation exists. This is much faster (15 seconds) than **pkg**.

Is _$d_ assigned (see below) the update could start with:`bash $d/ip/s $t`.
## ~/.bashrc
Is also a symlink to **s** itself (`~/sd/ip/bashrc`) and _checks_ the state of the installation before the first prompt:
- start some processes (PID): sshd, Xvnc and possibly Xwayland (Xorg)
- and set some aliases: pp to _check_ PID, ll=`ls -la` to list files, d=`du -hd 1` to _check_ space
## various test functions with alias t
since PATH also contains `:.`, **t** is enough to call `bash ~.bashrc $@`. Without parameter, the _usage help_ is displayed or else the described function is executed.
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
