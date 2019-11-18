# Example to check api 29
I have not finished a handy Android-10/api29 solution for my _example_. It can be started with the [script t]() (loop in line 8 with environment) for Android-8/9, works on my two phones and does a little bit more than "hello world" (prerequisite: OTS with PID1+2+3 ). @xeffyr says:
- will work, but with _additional steps_.

If I understand your suggestion correctly, the _additional steps_ refer to `$s` and `make $s; $s` and should be described in the _makefile_.
Can you look at it and adjust it so that it also changes the APK?

If your suggestion also includes _bash, make, gfortran, ssh Xwayland etc._ as well as `$s` in `/bin`, then 
`PATH=./:/bin:./:~/u/bin` with (ln -s ~/../usr ~/u) and is the _native lib_ then`ln -s /system/lib ~/n`?

For the example minimum required _pkg install_ I have described in the script.
Currently my termux size is (~/u) on _armv7l/Android-9 is 794Mb (t.tgz) + 185 in ~/n.

If I only use my t77.apk (PID1) and x11.apk (PID2) or create a _virgin termux_ (39Mb/60Mb with ssh + mc) with `rm -rf ../*`, the first start will be a termux size 402Mb installed (multiple confirms required and need 15 minutes).
## Install APK and start XClient ($s) with _t_.
Before the APK (my*.apk) are installed, all other Termux/Plugins must be _uninstalled_ on the phone.
- The data from this path should then be stored in path _/storage/emulated/0/api29_ (`a=d/api29`).
- Tap on the two APK to install them on phone.
- open the termux app (contains all boot packages)
- with `termux-setup-storage` you get access to `$a`
- with `bash $a/t` the packages are installed, and set alias _ll,pp,dd,t_ and links to_**d,u** and **.bashrc** ($a/t).
