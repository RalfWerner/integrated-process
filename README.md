# Integrated-Process
Abbreviated **IP**, is an _object-oriented_ (below) assessment tool that exists since the late 80's. Here is however only a part treated, which I designate as **CP** and only the extensions to use **CP** without **W**indows **M**anager (**WM**) in [Termux](https://wiki.termux.com/wiki/Graphical_Environment) and [X11](https://github.com/suhan-paradkar/termux-wayland/wiki/Launching-GUI-applications) on smartphones.

Currently here are sources that I use for X11/X-Client/Server-check. Besides the _**Termux**_ environment, sources are also useable in MobaXterm and Debian. The script [bashrc] could use to update a virgin Termux [APK](https://github.com/termux/termux-packages/issues/3535#issuecomment-489430202) with needed packages for check.

## Control Processes in the IP (based on _xinit*_):
are called **CP**. Besides there are **B**atch **P**rozesses (**BP**/Scripts), which are only edited and started as usual. Both types of processes do essentially the same thing. The **CP** functions _with_ **WM** remain unchanged and will not be treated here. In addition to the **WM** waiver, the portrait/landscape (**p/l**) change of the handy (turn) is part of the extensions that should also work with **WM**.

## Finger control - that's how it should be:
Tap with your finger on the screen/pad and in a window (pointer on touchpad) or hold after tap and move horizontally/vertically and release. The movement can be left, right, up or down (-x, + x, -y, + y). If the value of the movement exceeds a character width or height, one of four gestures will be started and terminated with Release/Lift.
The window can be an **AlfaW** (text including icons) or a graphic (up to 4 windows). It can be smaller or larger (horizontal/x) than the screen or the same size (fullscreen). The lower part of the **AlfaW** can contain a scroll table whose last column **LastC** can contain more characters than displayed in the window.
The four gestures are interpreted differently, depending on the window and position inside. Generally: -x gestures move windows and +x gestures open pop-up menus.
# sources
_touch.c_ should check basics of mutitouch functions standalone (in preparation). Currently there are three _main_ (contolled by `#define TEST <n>` n=1,2,3 in first line) inside, _check.c_ demonstrator of _finger-only_ control (in preparation see [api29](https://github.com/RalfWerner/integrated-process/tree/master/api29)) (use _xcinit*_ too),
_xlunch.c_ application manager and _multi.c_ Multi touch or generic event processing and should mered in _touch.c_ and finally inside _**xcinit***_ and removed.
## check.c
is used to check the **CP** extensions described in _xinitn.c_. If the **bashrc** - script is used, make/run is done with `t <d> c <files>`. The `<files>` (icons/graphics as *.xpm and *.c sources) are predefined and with `<d>=:1` _**Xvnc**_ is used as Xserver. I recommend `:0` or none for `<d>` to use _**Xorg/Xwayland**_ as the Xserver. to use PC-Xserver in _WLAN_ use `<d>=1` All other possible Xserver from **bashrc** are not treated here.

**check** generates an **AlfaW** (basic) with 7 icons, 3 fields, one slider and a table with two (one) columns. Except for _default_ (82 characters in width), the number of characters of **AlfaW** is calculated from the width of screen and font and orientation **p/l**. The _smiley icon_ cyclically switches between three modes from _default_ to _fullscreen_ to _partscreen_ (in pixel or percent) and back.

The table shows the first `<file>` and initially consists of two columns, the last **LastC** has a variable length of 74. This results with current width the first column **LC** and the scrollbar. In order to test all **CP** extensions knowledge of a few functions is necessary: Field-1 is the pop menu via **LC** (line command), field-2 underneath is **CL** (command line), in field-3 the `<file>` is added to the table and with the slider the first 3 characters of field-1 can be changed. Field-2 and 3 have more pop menus, so no keybord events are needed.
If the number of characters is less than width of **AlfaW**, the icons are displayed in two (or more) additional lines above the table and **LastC** can be up to 150 characters (field-1) long. More details to **check** later.
# IP objects
As an _object_ I call the unit of data and functions. The scope of the functions depends on the application and the environment. If the OS is _**not**_ Linux, this is part of it. For Windows: MobaXterm and for Android: Termux, which is then part of the object, as well as all functions to use/make **CP** and BP. The functions can be included as packages, plugins or sources (including make).
