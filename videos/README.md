# videos and pictures to processes
Here are examples of controlling Termux / X11 apps as `* .mp4` and` '* .jpg` related to programs of this repo.
An app in Termux can be portrait or landscape depending on the rotation of the phone in your hand, which in the current case is 1440x720 or vice versa.
Partially the examples are also on my pad and PC (unrotatable but different resolutions)
## xserver XSDL
If there is a better Xserver, XSDL should _**not**_ be used because it is based out of service and an old xorg. the rotation is _not really_ supported and pinch/multitouch is impossible. in `xserver.mp4` are examples of xterm, display, nedit shown.
## Termux_mc (midnight commander)
The **mc** functions with the Termux pinch are exemplary for X11 clients with _text/cursor functions_ and finger control on phones.
## TV (Team Viewer) and Xvnc
the recommended Xvnc server for Termux is similar to the TV, behaving like a finger/screen. in `TVpad_phone.mp4`. The external App **Real-VNC** and the **Xvnc** start (tigervnc package) needet. In t(s) start is it done in Termux-start and use of of none as display reference.
## Xorg_wayland & Co
The two attempts (sparkle, lorie) to use Xorg under Termux have been abandoned. the sparkle version was the best so far, but unfortunately had segfaults that could not be fixed. A third attempt was started with [Xwayland](https://en.wikipedia.org/wiki/X.Org_Server#XWayland). in the video current bugs but also benefits are shown.
Mouse, pointer and keyboard are not supported in the current version, so at the end (1:21ff) of the video, the target functionality is demonstrated on a pad with MobaX
