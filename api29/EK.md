/* XPM this `*.md` file is an valid **xpm image** matrix with this headline but **not** in _Imlib2_
# Extrakeys/Toolbox
contains special buttons in Termux that are not included in the AOSP-KB or are self-defined. The same are used in Terminal (app) and X11-02.04, but in the current X11 version there are only 4 button + 4 cursor that are in a conflict block (overlapping X11 screen).
In X11 are additional keys necessary and some are to be treated differently as in the terminal.

As discussed [here](https://github.com/termux/termux-x11/discussions/46#discussioncomment-3279888), no processing of the errors and functions is to be expected. That is why I've prepared an Xlib solution (in `config.h`) for some important keys and **MB** = mouse button that is integrated in the event management.

The optical basis is a `*xpm` file with icons (Nx50x45) that are placed and scaled on the screen or can be part of an Xclient. I use `touch.c` (TEST=0-4) with one or two windows with XLIB/XCB) and `check.c` (several windows including text/tables/icon processing in XLIB) for demonstrating the finger functions.
Use is of course only possible if the Xclients also contains the source config.c and not in `aterm` or `fluxbox`. If several application is used, each of their own icons also has an exchange of the settings via the file: `ek.tmp` is possible.
## The Mouse/Tab Icon
If **MBn** keys are used to emulate the three mouse buttons with n=1-3. So applications can also use several MB at the same time and order of the mouse clicks is important, which then color (red, blue, green = 1+2+3 or red, green = 3+1). With a real USB/BT mouse, it's also displayed regardless of the pointer position and set back on MB1 when it is released. With finger or Pen, the setting is done with gestures after the first tab-on-icon and remains with all tabs/gestures outside the icons). The setting gestures are: Horizontal selection of the next/last MB and Vertical: Select additional MB/Toggle keys.
## The Ctrl/Alt/Shift/Ins*-icon
On the left, the 4 specified Toggle keys, which are mostly significant together with key events, can also be used in MB campaigns. Real KB often have several same keys or not treated to-do-making keys here.
On the right are the touch campaign and three other actions that
## The Curcor,PG*,Home,End,Enter icon
## XPM file
Is readable by two functions. In case of available _Imlib2_ (headline strictly like here) with `imlib_load_image` to an scalable **image**. Additional with `XpmReadFileToImage` as **xpm** matrix, possibly unscalable, headline could be extend here and dpy must known. Here are several comment (as in C) in line 2-8 but that is not a problem.
``` c
/* XPM */
static char *EK.xpm[]={"150 45 16 1",/* width (50xN) hight (45 for icons) color (16x1)
bash bashrc t E*& # to start touch.c - see TEST in first line of source of N=3 icons */
". c None   ",/* None   is transparent  #002030<-dark*/,/* white */
"  c #EEEECE",/* backgr.  */"@ c #FFFF00","- c #FEFE00",/* yellow   */
"+ c #007F00",/* green 1-4*/"= c #00E57F","; c #00FF00",
"* c #CB0000",/* red   1-3*/"$ c #CB00CB","% c #FF00FF","< c #FFFFFF",
"# c #0000FF",/* blue  1-2*/", c #0000FE","> c #00FFFF",/* turquoise*/
"& c #212121","' c #BDBDBD",/* black gray  --50 --><--    --><--    --><--    --><--    --><-- 100--><--    --><--    --><--    --><--    --><-- 150-->*/
"+                                                 +                                                 +                        +                        ",
"                                                                                                    ''''''''''''''''''''''''''                        ",
"                     ,,,,,,,,                       &&&&&&&&&&&&           &          &&&&&   &&&&& ''####'####'#####''##'''''       &           &    ",
"              +++++ ,        , *****                &                     &&&         &&&&&& &&&&&& '#####'####'######'##'''''      &             &   ",
"          ++++    + ,   ,,   , *    ****            & &&&&&&&            & & &        &&  && &&     '##'''''##''##''##'##'''''     &&&&&&&&&&&&&&&&&  ",
"       +++        + ,  ,  ,  , *        ***         & &&                &  &  &       &&&&&  && &&& '##'''''##''#####''##'''''    &&               && ",
"    +++           + ,    ,   , *           ***      & & &              &   &   &      &&     &&  && '##'''''##''##'##''##'''''     &&&&&&&&&&&&&&&&&  ",
"  ++              + ,   ,    , *              **    & &  &                 &          &&     &&&&&& '#####''##''##''##'####'''      &             &   ",
"  +               + ,  ,,,,  , *               *    & &   &                &          &&      &&&&& ''####''##''##''##'####'''       &           &    ",
"  +      +        + ,        , *     ***       *    & &    &               &                        ''''''''''''''''''''''''''                        ",
"  +      +        + ,  * *   , *     *  *      *    & &     &              &          &&  && &&&&&  ''''''''''''''''''''''''''                        ",
"  +      +        + , * * *  , *     ***       *    &                      &          &&  && &&&&&& ''''''''''''''''''''''''''                        ",
"  +      +        + , * * *  , *     * *       *                           &          &&  && &&  && ''''''''''''''''''''''''''                        ",
"  +      ++++     + , *   *  , *     *  *      *                                      &&  && &&&&&  ''####''##''####''''''''''    #####  #####  ##### ",
"  +               + , *   *  , *               *                                      &&  && &&     '######'##''####''''''''''    ##### ###### ###### ",
"  +               + ,        , *               *                                      &&&&&& &&     '##''##'##'''##'''''''''''    ##     ##    ##     ",
"  + ''''''''''''' + ,  ***   , * ''''''''''''' *                                       &&&&  &&     '######'##'''##'''''''''''    ###     ##   ##     ",
"  +               + , *   *  , *               *                                                    '##''##'##'''##'''''''''''    ##       ##  ##     ",
"  + &    &        + , *   *  , *        &    & *        &            **  *** *** &            &     '##''##'####'##'''''''''''    ##### ###### ###### ",
"  + &   &         + , *   *  , *         &   & *       &             * * *    *  &             &    '##''##'####'##'''''''''''    ##### #####   ##### ",
"  + &  &          + ,  ***   , *          &  & *      &              **  ***  *  &              &   ''''''''''''''''''''''''''                        ",
"  + & &           + ,        , *           & & *     &               * * *    *  &               &  ''''''''''''''''''''''''''                        ",
"  + &&&&&&&&&&&&  + , *   *  , *  &&&&&&&&&&&& *    &&&&&&&&&&&&     * * ***  *  &     &&&&&&&&&&&& ''''''''''''''''''''''''''                        ",
"  + & &           + , *   *  , *           & & *     &                  &        &               &  ''''''''''''''''''''''''''                        ",
"  + &  &          + , *   *  , *          &  & *      &                &         &              &   ''''''''''''''''''''''''''                        ",
"  + &   &         + , *   *  , *         &   & *       &              &&&&&&&&&&&&             &    ''#####'##'##'##'####'####    #####   ##### ##### ",
"  + &    &        + ,  ***   , *        &    & *        &              &                      &     '######'##'##'##'####'####    ###### ###### ######",
"  +               + ,        , *               *                        &                           ''##''''##'##'##'##''''##'    ##  ##  ##    ##  ##",
"  + ''''''''''''' + ,  ****  , * ''''''''''''' *                                                    '''##'''#####'##'###'''##'    #####    ##   ##### ",
"  +               + , *      , *               *                                                    ''''##''##'##'##'###'''##'    ##  ##    ##  ##    ",
"  +      & &      + ,  ***   , *       &       *                                                    '######'##'##'##'##''''##'    ###### ###### ##    ",
"  +      & &      + ,     *  , *      &&&      *    &&&   &&& &  &                                  '#####''##'##'##'##''''##'    #####  #####  ##    ",
"  +      & &      + , ****   , *     && &&     *    &  & &    &  &         &                      & ''''''''''''''''''''''''''                        ",
"  +      & &      + ,        , *    & & & &    *    &&&  & && &  &         &                      & ''''''''''''''''''''''''''                        ",
"  +  &   & &   &  + , *****  , *   &  & &  &   *    &    &  & &  &         &              &     & & ''''''''''''''''''''''''''                        ",
"  +   &  & &  &   + , *      , *  &   & &   &  *    &     &&&  &&          &               &    & & ''''''''''''''''''''''''''                        ",
"  +    & & & &    + , ****   , *      & &      *                           &                &   & & '##'##''##''#####'''''''''    #####  ###### ##    ",
"  +     && &&     + , *      , *      & &      *    &&&  &  &              &                 &  & & '##'##''##'######'''''''''    ###### ###### ##    ",
"  +      &&&      + , *****  , *      & &      *    &  & && &          &   &   &              & & & '##'###'##''##''''''''''''    ##  ## ##     ##    ",
"  +       &       + ,        , *      & &      *    &  & & &&           &  &  &                && & '##'######'''##'''''''''''    ##  ## ####   ##    ",
"  +               + ,        , *               *    &  & &  &            & & &            &&&&&&& & '##'##'###''''##''''''''''    ##  ## ##     ##    ",
"  +               + ,        , *               *    &&&  &  &             &&&                     & '##'##''##'######'''''''''    ###### ###### ######",
"  +               + ,        , *               *                           &            &&&&&&&&&&& '##'##''##'#####''''''''''    #####  ###### ######",
"  +++++++++++++++++ ,,,,,,,,,, *****************                                                                                                      ",
"                                                                                                                                                      "}/*
```
## edit and check `*.xpm`
The file can also be **edited** with nedit or [check.c](https://github.com/RalfWerner/integrated-process/blob/master/check.c) (use `t c *md`) or [mc](https://github.com/RalfWerner/integrated-process/blob/master/videos.md#mc). to check use newest version of [touch.c](https://github.com/RalfWerner/integrated-process/blob/master/touch.c).*/
