# Example to check api 29
I've just **not** finished a mobile Android-10/api29 solution for in this _example_ but [prepared](#discussion) - last state [bootstrap loop](https://github.com/RalfWerner/integrated-process/issues/2#issuecomment-780625381). It can be started with the [bashrc](https://github.com/RalfWerner/integrated-process/blob/master/api29/bashrc#L178#L186) (loop in **line 8** with environment) for Android-8/9, works on my two phones and does a little bit more than "hello world" (prerequisite: **OTS**=_One Touch Start_ of Termux and X-Server with PID1+2+3 ). [Leonid](#abbr) says:
> will work, but with _additional steps_, running custom executables _**not**_ possible but generally environment will be same.

If I understand your suggestion correctly, the _additional steps_ refer to `$s` (**line 3**) and `make $s; $s` and should be described in the _makefile_ (create in **line 15**). Can you look at it and adjust it so that it also _**changes the APK?**_

If your suggestion also includes _bash, make, gfortran, ssh Xwayland etc._ as well as `$s` in `/bin` or NL, then 
`PATH=./:/bin:./:~/u/bin` with (ln -s ~/../usr ~/u) and is the _native lib_ (export NL) then a wrapper of`/system/bin/pm` right?

For the example minimum required _pkg install_ I have described in `t`.
Currently my (full) termux size is (~/u) on _armv7l/Android-9_ is 794Mb (t.tgz) + 38Mb in $NL.
I've omitted Xvnc (second X server), window manager (WM) and everything else that is not needed for check, with the exception of ssh, mc and xterm, to have minimal comfort.

If I only use my t82.apk (PID1) and x11.apk (PID2) or create a _virgin termux_ (39Mb and 60Mb with ssh+mc) with `rm -rf ../*`, the first start (_**pu**_=package update) will be a termux size 402Mb installed (multiple confirms required and need 15 minutes).
## Install APK and start XClient (`t c`) with _c=check_.
Before the APK (`*.apk`) are installed, all other Termux/Plugins must be _uninstalled_ on the phone.
- The data from this path should then be stored in path _/storage/emulated/0/api29_ (`a=d/api29` or `sd/`).
- Tap on the APK (more in [dropbox](https://www.dropbox.com/s/ug071qoox8gwf1c/ip.zip?dl=0) (zip version) to install them on your phone strep with **Xvnc** see [here](https://github.com/bk138/multivnc/issues/176). Next steps are ommited than
- [old](https://www.dropbox.com/sh/e34d0nnwingz2c6/AACVbPuTkvXxFgf-LtYy0Ml9a?dl=0) - the ARCHs of t82/t84(t64:aarch64 only) are treated _separately_.
- open the termux app (contains all boot packages)
- with `termux-setup-storage` you get access to `$f and ~/sd`
- with `bash ~i/bashrc` set alias _ll,pp,dd,c_ and links to_**d,u** and **.bashrc** ($a/t) or creates _makefile_ and install the packages.
## discussion
and Shots/FAQ in [#2](https://github.com/RalfWerner/integrated-process/issues/2). Github is limit that my-t95.apk (68Mb) can not be saved but is also [here](https://www.dropbox.com/sh/e34d0nnwingz2c6/AACVbPuTkvXxFgf-LtYy0Ml9a?dl=0) and created with private _apksigner_. But this version is outdated. Currently I use last version 118 see [here](https://github.com/termux/termux-app/issues/2155) and [there](https://github.com/termux/termux-app/issues/1072) together 371 commits oly in this two issues.
## Package update _**pu**_ here (api29) and complete and with _uu*)._
can also be done with *.tgz files (_**tu**_) if the files exist and were updated with `pkg up` before creation. The *.tgz are then (on gigaset) here: 131Mb and complete: 355Mb in size and _**tu**_ is much faster than _**pu**_. Steps to install [uu](#abbr).
- First steps decribed [here](https://github.com/RalfWerner/integrated-process/issues/2#issuecomment-572552197) ff - to use ubuntu in proot
- update of [script t](https://github.com/RalfWerner/integrated-process/blob/master/api29/EK.md#edit-and-check) in progress - will test the process `ln -s /sdcard/api29/t .bashrc` and both _**pu**_ (termux+ubuntu).

### abbr
uu=ubuntu (double u) another possibility would be triple u (so many u's contain this linux variant) is used as`alias uu=uu/uu.sh`and path, because this can be easily entered on the on-screen KB.

Leonid: One of the famous Termux Developers (@xeffyr or @sylirre)
