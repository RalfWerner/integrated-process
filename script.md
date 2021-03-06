# to the [script s](https://github.com/RalfWerner/integrated-process/edit/master/s)
It is divided in different sections but could use outside of termux as _bash_ script (partially) too. The first Termux update contains 11 widget scripts (`~/.shortcuts` lines 22-25). In order to display this on the start screen (_Long Tap_) this must be set in the widget management of the mobile phone. The corresponding functions are somewhat different on my two devices.
## Virgin Termux (vt) update with pkg ... (pu) or *.tgz (tu)
This requires a `*.apk` (for example, termux_73) and a first open (bash prompt) from Termux.
To perform this section, there must be _no_ **t** file (generated here) and the required data must be available on the phone in `~/sd`. (including **s** itself).
This can be an sdcard or internal memory (sd=d) that can be used with `termux-setup-storage` in the script. For this are set up symlinks in `~/`.
Alternatively, a **tar/*.tgz update** can be used (below) if a _*.tgz_ of a previous installation exists. This is much faster (15 seconds) than **pkg**.

Is _$d_ assigned (see below) the update could start with:`bash $d/ip/s $t`.
## ~/.bashrc
Is also a symlink to **s** itself (~/sd/ip/s) and _checks_ the state of the installation before the first prompt:
- start some processes (PID): sshd, Xvnc and possibly Xwayland (Xorg)
- and set some aliases: pp to _check_ PID, ll=`ls -la` to list files, dd=`du -hd 1` to _check_ space
## various test functions with ~/t
since PATH also contains `:.`, **t** is enough to call `bash ~.bashrc $@`. Without parameter, the _usage help_ is displayed or else the described function is executed.
The two scripts parts listed above are ignored. **s** is legible, so here are just a few special features:
- API dialogs/functions (need the installation of _api_ plugin) started with `t d` (termux only)
- LAN/DISPLAY adresses is estimated by the second parameter (without is **DISPLAY=:1** and Xvnc as Xserver the default)
- The third (second) parameter (above) identify a keychar like **d** (above) or **tgz** or files
## tgz backup of termux installation
With `t tgz` you see a separat _usage help_.The most important function is to produce `~/sd/t.tgz` from`~/..`. The process can take 8 to 80 minutes. Subsequently, however, the Termux state can be quickly restored (above) if another Virgin-Termux is used or reinitialized after `rm -r ../*`. 
Since then **~/sd** is no longer known you have to use the 
path _d=/storage/6533-6333/; t=t_ in `tar -xzf $d/$t.tgz -C ..`.
