# Integrated-Process
Abbreviated **IP**, is an assessment tool that exists since the late 80's. Here, however, only a part is treated, which I designate as **CP** and only the extensions, to use **CP** without **W**indows **M**anager (**WM**) in _Termux_ on smartphones.

Currently here are sources that I use for X11/Xorg-check. Besides the _**Termux**_ environment, sources are also useable in MobaXterm and Debian 9.2. The script **s** could use to update a virgin Termux [APK](https://github.com/termux/termux-packages/issues/3535#issuecomment-489430202) with needed packages for check.

## Control Processes in the IP:
are called **CP**. Besides there are **B**atch **P**rozesse (**BP**/Scripts), which are only edited and started as usual. Both types of processes do essentially the same thing. The **CP** functions _with_ **WM** remain unchanged and will not be treated here. In addition to the **WM** waiver, the portrait/landscape (**p/l**) change of the handy (turn) is part of the extensions that should also work with **WM**.

## Finger control - that's how it should be:
Tap with your finger on the screen/pad and in a window (pointer on touchpad) or hold after tap and move horizontally/vertically and release. The movement can be left, right, up or down (-x, + x, -y, + y). If the value of the movement exceeds a character width or height, one of four gestures will be started and terminated with Release/Lift.
The window can be an **AlfaW** (text including icons) or a graphic (up to 4 windows). It can be smaller or larger (horizontal/x) than the screen or the same size (fullscreen). The lower part of the **AlfaW** can contain a scroll table whose last column **LastC** can contain more characters than displayed in the window.
The four gestures are interpreted differently, depending on the window and position inside. Generally: -x gestures move windows and +x gestures pop-up menus.
# sources
_touch.c_ should check basics of mutitouch functions standalone (just not valid)
_check.c_ demonstrator of _finger-only_ control (in preparation)
## check.c
is used to test the extensions described in _xinitn.c_. If the **s** - script is used, make/run is done with `t <d> c <files>`. The `<files>` (icons/graphics as *.xpm and *.c sources) are predefined and without `<d>` _**Xvnc**_ is used as the server. I recommend `:0` as `<d>` to use _**Xorg**_ as the server. All other possible Xserver from **s** are not treated here.

**check** generates an **AlfaW** (basic) with 7 icons, 3 fields, one slider and a table with two columns. Except for _basic_ (82 characters in width), the number of characters of **AlfaW** is calculated from the width of screen, font and **p/l**. The _smiley icon_ cyclically switches between three modes from _basic_ to _fullscreen_ to _partscreen_ (400/800 or 800/400) and back.

The _basic_ table shows the first `<file>` and initially consists of two columns, the last **LastC** is 73 characters long. This results in the first column **LC** and the scrollbar 82. In order to test all **CP** extensions knowledge of a few functions is necessary: Field-1 is the pop menu via **LC** (line command), field-2 underneath is **CL** (command line), in field-3 the `<file>` is added to the table and with the slider the first 3 characters of field-1 can be changed. Field-2 and 3 have more pop menus, so no keybord events are needed (currently failed in _**Xorg**_).
If the number of characters is less than 80, the icons are displayed in two additional lines above the table and **LastC** can be up to 150 characters (field-1) long.
