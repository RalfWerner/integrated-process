# to the script s
It is divided in different sections but could use outside of termux as _bash_ script (partially) too.
## virgin Termux update with pkg ...
This requires a `*.apk` (for example, lorie) and a first open (bash prompt) from Termux.
To perform this section, there must be _no_ **.ssh** path (generated here) and the required data must be available on the phone in `~/sd`. (including **s** itself).
This can be an sdcard or internal memory (sd=d) that can be used with `termux-setup-storage` in the script. For this are set up symlinks in `~/`.
Alternatively, a **tar update** can be used (below) if a _*.tgz_ of a previous installation exists. This is much faster (15 seconds) than **pkg**.
## ~/.bashrc
Is also a symlink to **s** itself (~/sd/ip/s) and _checks_ the state of the installation before the first prompt:
- start some processes (PID): sshd, Xvnc and possibly Xorg
- and set some aliases: pp to _check_ PID, ll=`ls -la` to list files, dd=`du -hd 1` to _check_ space
## various test functions with ~/t
since PATH also contains `:.`, **t** is enough to call `bash ~.bashrc $@`. Without parameter, the _usage help_ is displayed or else the described function is executed.
The two scripts parts listed above are ignored. **s** is legible, so here are just a few special features:
- API dialogs/functions (need the installation of _api_ plugin) started with `t d` (termux only)
- LAN/DISPLAY adresses is estimated by the second parameter (without is **DISPLAY=:1** and Xvnc as Xserver the default)
- The third (second) parameter (above) identify a keychar like **d** (above) or **tgz** or files
## tgz backup of termux installation
With `t tgz` you see a separat _usage help_.The most important function is to produce `~/sd/t.tgz` from`~/..`. The process can take up to 80 minutes. Subsequently, however, the Termux state can be quickly restored (above) if another Virgin-Termux is used or reinitialized after `rm -r ../*`. 
Since then **~/sd** is no longer known you have to use the 
path _t=storage/6533-6333/t.tgz_ in `tar -xzf $t -C ..`.
