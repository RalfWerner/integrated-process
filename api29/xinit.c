/* C-Functions for X-Window-management of IP-programs
      SUBROUTINE xcinit
 Author: Ralf. Werner  first.: APR 1992 last Mod 06.19 */
#ifdef VMS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <decw$include/Xlib.h>
#include <decw$include/Xutil.h>
#include <decw$include/Xatom.h>
#include "xpm.h"
#else 
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#define XK_MISCELLANY
#include <X11/keysymdef.h>
/* #include "xpm.h" (#include "/import/prg/own/Tools/include/xpm.h") */
#endif

/* Key-codes to edit Alpha-Windows */
#define Eingabe 13
unsigned char CursorRechts=255;
unsigned char CursorLinks =254;
unsigned char CursorOben  =253;
unsigned char CursorUnten =252;
unsigned char BildOben    =251;
unsigned char BildUnten   =250;
unsigned char Tabulator   =249;
unsigned char DeleteFeld  =248;
unsigned char ZeichenBs   =247;
unsigned char Einfuegen1  =246;
unsigned char ZeichenDel  =245;
unsigned char Suchen      =244;
unsigned char Selektieren =243;
unsigned char Hilfe1      =242;
unsigned char Pf3         =241;
unsigned char TestTaste   =240;
unsigned char SetUpTaste  =239;
unsigned char Hilfe2      =241;
unsigned char Einfuegen2  =242;
unsigned char IconS='ß';

Display *dpy,*dp2,*dpl; XEvent ev;Screen *screen;Window win5[5]={0,0,0,0,0,0},*w;
Pixmap pix5[5]={0,0,0,0,0,0},*p; Drawable *pw; XImage *img; XGCValues xgcv; 
XSetWindowAttributes xswa,xswa4; XWindowAttributes attr; GC gc[15];
Colormap cmap; XPoint pt[300]; Atom lProp; XImage *xpm[]={0,0,0,0};

static int iWin,ngif=1000,winX[5]={0,-1,-1,-1,0}, winY[5]={0,-1,-1,-1,0},
 x06=0,X06=0,W[8]={0,0,0,0,0,0,0,0},H[8]={0,0,0,0,0,0,0,0}, Zfak[4]={1,1,1,1},
 xicon=50,yicon=45,MaxIcon=0,Iicon=-1,SetupLeg=0,demo=0,SetC=1,ASCII,ptAnz,
 Farbe=0,Doppl=0,DopplP[3],Farbel, TypFarbe[]={1,3,0,4,3,4,3,4,5,10},
 WFarbe[]={0,11,12,1},farbig=(-1),ISWAP=0,I82,TF0,TF1, iPS=450,jSp,iSp,
 j,spx,spy,spt,sph,l82=82,i82=82,i24=24,xpl=0,ypl,Pufferl,iSizePos=32,Sp0,x4,y4;
static char *c,delta0[]={30,30,10},cgif[6]={"00000"},test=0,BFarbe=1;
/* External/Public Data */
extern char eacom[176],comwin[120],cfleg[80],clegdf[80],cexcl[2],issyimg[80],
cvers[16];extern struct {int Aktuell,Max,Top; char ATAB[100][160];} ztabl;
extern struct {char TABLE[8],MSG[8]; int W,H,HW[2]; char LMSG[80];} pptab;
extern struct {int LTEST,NPL,KP; float Xmin,Xmax,Ymin,Ymax,Rest;} kontur;
extern struct {float Xmin,Ymin,Xmax,Ymax,Hgrenz; int ZM,RDY;} czoom;
extern struct {int IP,Dick[10],PAT,Gdick,RGB[12][3],Stil[11];} cpunit;
extern struct {int NWIN,IWK,AXLG,SHR,BUH,NERG,N1,N2; float ALF[3];} plparm;

/* Farb-Nummer des Alfa-Foregrounds und Window-Hintergrunds */
float ZoomX,ZoomY, DeltaX,DeltaY,U; /* Graphik-Umrechnungs-Faktor */
static unsigned long PixelRet[110]; static char *Puffer;
XColor Ftab[11][10]; char CellTyp[11][10];
XFontStruct *fs, *font3[3]; int iFont=1, DefaultSchatten=1, Schatten;
static char *FText[]={"-Adobe-Courier-Bold-R-Normal--","*-*-*-M-*-*-*"},
 RCS[40]="Reset     Create >+1Select >+2CATscript ", FontName[3][80]=
  {"-Adobe-Courier-Bold-R-Normal--16-*-*-*-M-*-*-*",  /* small  xFont*/
   "-Adobe-Courier-Bold-R-Normal--20-*-*-*-M-*-*-*",  /* normal xFont*/
   "-Adobe-Courier-Bold-R-*--34-*-*-*-M-*-*-*"}, /* large  xFont*/
 P0P[]="Apply Exit  Copy  Set>+1Img-AlImg-W1Img-W2Img-W3Icons ",
 *FontSize="Small  Normal Large  Gr-->+1Fullsc Partsc Default", *Mg=pptab.LMSG;

/* Field-Amanagement-Structur */
#define MaxFelder 200 /* Maximale Alpha-Feld-Anzahl */
static int Felder,Feld=1,Spalte=0,Einfueg=0,Tabelle,MaxTabelle,Ytab,ModiPos=159;
static struct {unsigned short y,x,len; signed char typ; unsigned char *t;}
  ft[MaxFelder+6],*F=(&ft[1]);
/* External C-Functions */
extern void xcinit(),xcread(),axtdef(),gxpoly(),gxline(),gxgrau(),gxhatch();
extern void winpik(),setupissy(),xcparam(); extern int CXTDEF();
/* Internal C-Functionen for Initialising */
static void TextPos(),SchattenBox(),PopKasten(),LinksShift(),GCaendern();
static int  Farb_Pixel(),FarbeNeu();
/* Internal C-Functionen for Interactive/Event management */
static void FeldPos(); static int MausKlick(),RechteckZiehen();
static int  MausKopie(),WindowModifiziert(),PikWindow(),FeldWechsel();
static int  WertGeber(),PopUpMenu(),TabelleNeu(),TastenKlick(), kdpy=0;
/* ~/u/include/X11/X.h
XEvents (Xlib.h) KeymapNotify     11  ReparentNotify   21
KeyPress      2* Expose           12* ConfigureNotify  22 ClientMessage  33
KeyRelease    3  GraphicsExpose   13  ConfigureRequest 23 GenericEvent   35
ButtonPress   4* NoExpose         14  GravityNotify    24
ButtonRelease 5* VisibilityNotify 15  ResizeRequest    25
MotionNotify  6* CreateNotify     16  CirculateNotify  26
EnterNotify   7  DestroyNotify    17  CirculateRequest 27
LeaveNotify   8  UnmapNotify      18  PropertyNotify   28 XI_TouchBegin  18
FocusIn       9  MapNotify        19  SelectionRequest 30 XI_TouchUpdate 19
FocusOut      10 MapRequest       20  SelectionNotify  31 XI_TouchEnd    20 */
extern void Xtest(Display *dpy,XEvent ev,int i,int *W,int *H,Window *w)
{if (ev.type<6) printf("ev:%d,i=%d\n",ev.type,i);}
static void Ereignis(int i)/* identifier of Event context*/
{do {if (XPending(dpy) && demo<0) return; XNextEvent(dpy,&ev);
 if (test) Xtest(dpy,ev,demo*100+abs(i)*10+iWin,W,H,win5);
 if (ev.xany.window != *w && ev.xany.window != *p) /* active Window changed */
  {int j; for (j=0;j<5&& win5[j]!=ev.xany.window&& pix5[j]!=ev.xany.window;j++);
   if (j>4) continue; w=(&win5[j]); pw=p=(&pix5[j]); if (test) printf
    ("Win-from:%d to:%d ev:%d %dx%d\n",iWin,j,ev.type,W[j],H[j]);iWin=j;}
 if (ev.type==Expose)
  {int we=ev.xexpose.width,he=ev.xexpose.height,x1=(iWin)?0:X06,x2=W[i]-W[6]+x1;
   if(test)printf("%d-Expose:%dx%d e:%dx%d x:%d/%d\n",
      iWin*10+demo,W[7],H[7],we,he,x1,x2);
   if (he>H[7]||we>W[7]||(demo && !iWin))
    {H[7]=XHeightOfScreen(XDefaultScreenOfDisplay(dp2=XOpenDisplay(0)));
     W[7]=XWidthOfScreen(XDefaultScreenOfDisplay(dp2));
     if (test && dpl!=dp2) printf("+Expose:WxH:%dx%d=>%dx%d %d=%d/%d\n",
         W[6],H[6],W[7],H[7],kdpy++,dp2,dpl); if (H[7]!=H[6]||W[7]!=W[6]) return;
     XSetCloseDownMode(dp2,DestroyAll); XCloseDisplay(dp2); dpl=dp2;
    }XCopyArea(dpy,*p,*w,gc[1],
     ev.xexpose.x+x1,ev.xexpose.y,we-x2,he,ev.xexpose.x,ev.xexpose.y);
   if(!iWin && Tabelle && Feld>Tabelle) FeldPos(0,&x1,&x2,&ztabl.Aktuell);
   if (cgif[iWin]=='1' || (cgif[4]=='G' && iWin)) 
    {int iw=*w; sprintf(issyimg,"import -window %d %d.gif ",iw,ngif++);
     system(issyimg); printf("%d-gif:%s\n",iWin,issyimg);cgif[iWin]='0';}
  }}while(ev.type==3||ev.type==13||ev.type==14||ev.type==33);
}
/*=> initialise display, screen and windows */
extern void xcinit(win,OkExitCan) int *win, *OkExitCan;
{char WTxt[140], WText[4][13]={"Alpha Window","Graph1","Graph2","Graph3"};
 char iy[]={3,8,9,4,7,4}, ix[]={10,8,8,6,7,8}, it[]={-2,-2, 2,-2,-2,-2};
 XSizeHints xsh; int PBreit,PHoch,i,k=(-*win);

 if (k>0){if (!demo) l82=i82; if (demo==k){demo=0;i82=l82;} else demo=k;W[0]=-W[0];}
 if (dpy && (H[7]!=H[6]||W[7]!=W[6]))
 {for (j=0;j<110;j++) if (PixelRet[j]) {XFreeColors(dpy,cmap,&PixelRet[j],1,0);PixelRet[j]=0;}
  for (j=0;j<5;j++){if (win5[j]) XDestroyWindow(dpy,win5[j]);
       if (pix5[j]) XFreePixmap(dpy,pix5[j]); win5[j]=pix5[j]=W[j]=0;}
  for (j=0;j<15;j++) if(gc[j]) XFreeGC(dpy,gc[j]); XSync(dpy,False);
  XSetCloseDownMode(dpy,DestroyAll); XCloseDisplay(dpy); dpy=0;}

 Schatten=DefaultSchatten; iWin=(*win<0)?0:(*win>3)?3:*win; if (!dpy)
 {dpy=(dp2)?dp2:XOpenDisplay(0); dp2=czoom.ZM=0; SetC=1;
  if (!dpy) {printf("E=> Display not opened! STOP\n"); exit(-1);}
  screen=XDefaultScreenOfDisplay(dpy);
  W[6]=XWidthOfScreen(screen); H[6]=XHeightOfScreen(screen);
  ft[MaxFelder].t=RCS; if (pptab.HW[1]==2) iFont=2;
  ft[MaxFelder+1].t=(&clegdf[8]); ft[MaxFelder+2].t=(&clegdf[80]);
  ft[MaxFelder+3].t=P0P;
  ft[MaxFelder+4].t=FontSize; ft[MaxFelder+5].t=comwin;
  for (j=MaxFelder;j<=MaxFelder+5;j++)
    {ft[j].y=iy[j-MaxFelder]; ft[j].x=ix[j-MaxFelder];
     ft[j].len=0; ft[j].typ=it[j-MaxFelder];}
  for (j=0;j<=2;j++)
    {font3[j]=XLoadQueryFont(dpy,FontName[j]);
     if (test || !font3[j]) printf("f >%s<\n",FontName[j]);
     if (!font3[j]) {sprintf(FontName[j],"%s-%d-%s",FText[0],
       j*2+14,FText[1]); font3[j]=XLoadQueryFont(dpy,FontName[j]);}
     if (cpunit.RGB[0][j]<delta0[0]) delta0[0]=cpunit.RGB[0][j];
       else if (cpunit.RGB[0][j]>100-delta0[1])delta0[1]=100-cpunit.RGB[0][j];
    }fs=font3[iFont];
 /* ICON/Multi-Window erzeugen PointerMotionMask| */
  xswa4.event_mask=StructureNotifyMask|ExposureMask|PropertyChangeMask|
   EnterWindowMask|LeaveWindowMask|KeyPressMask|KeyReleaseMask|
   ButtonPressMask|ButtonReleaseMask|ButtonMotionMask;
  xswa4.background_pixel=Farb_Pixel(0,0); if (j=win5[4]) XDestroyWindow(dpy,win5[4]);
  win5[4]=XCreateWindow(dpy, XRootWindowOfScreen(screen),0,0,xicon,yicon,0,
          XDefaultDepthOfScreen(screen), InputOutput,
          XDefaultVisualOfScreen(screen),CWEventMask | CWBackPixel, &xswa4);

 /* graphic context xgcv.graphics_exposures=0;*/
  for (j=0;j<=14;j++) gc[j]=XCreateGC(dpy, win5[4], 0, &xgcv);
 }else if (*OkExitCan<0) return;
 if (test) printf("Init Win:%d OEC:%d/%d %dx%d\n",iWin+demo*10,*OkExitCan,iFont,W[iWin],H[iWin]);
 if (SetC) {for (j=0;j<=9;j++) GCaendern(j); SetC=(*OkExitCan<0);}

 /* estimate Window-size */
 if (W[iWin]>0&&win5[iWin]&&(!iWin||cgif[4]!='G')) goto weiter; else if(iWin);
    else if (demo>99){if(H[6]>W[6])
     {W[0]=demo;H[0]=2*demo;} else {H[0]=demo;W[0]=2*demo;}}
    else if (demo){W[0]=W[6]; H[0]=H[6];} if (W[iWin]<0) W[iWin]=(-W[iWin]);
 if (iWin==0)
    {fs=font3[iFont]; spx=fs->max_bounds.width;
     spy=(spt=fs->ascent+fs->descent+2)+Schatten*2+1;
     if (demo){i82=W[0]/fs->max_bounds.width;}
       else {W[iWin]=spx*(l82=i82); if (!H[iWin]) H[iWin]=spy*i24;}}
   else if (demo) {W[iWin]=W[0]; H[iWin]=H[0]; winX[iWin]=winY[iWin]=0;}
   else if (iWin==1)
    {if (!W[1]){W[1]=W[6]-W[0]; if (W[1]>W[0] || W[1]<=0) W[1]=W[0];}
     if (!H[1]) H[1]=H[0];
     if (winX[1]<0) winX[1]=W[0]; if (winY[1]<0) winY[1]=0;}
   else if (iWin==2)
    {if (!W[2]) W[2]=W[6]*0.7;
     if (!H[2]) H[2]=H[6]-H[0]*0.7;
     if (winY[2]<0) winY[2]=H[0]; if (winX[1]<0) winX[1]=0;}
   else if (iWin==3)
    {if (!W[3]) W[3]=spx*i82;
     if (!H[3]) H[3]=spt*i24;
     if (winX[3]<0) winX[3]=W[6]-W[3];
     if (winY[3]<0) winY[3]=H[6]-H[3];}

 /* Window erstellen KeyReleaseMask| */
 if (win5[iWin]){XUnmapWindow(dpy,win5[iWin]);XDestroyWindow(dpy,win5[iWin]);}
 xswa.event_mask=StructureNotifyMask|KeyPressMask|ExposureMask|
  PropertyChangeMask|ButtonPressMask|ButtonReleaseMask|ButtonMotionMask;
 xswa.background_pixel=Farb_Pixel(0,0);
 
 win5[iWin]=XCreateWindow(dpy, XRootWindowOfScreen(screen),winX[iWin],
      winY[iWin],W[iWin],H[iWin],0,XDefaultDepthOfScreen(screen),InputOutput,
      XDefaultVisualOfScreen(screen),CWEventMask | CWBackPixel,&xswa);
 xsh.x=winX[iWin]; xsh.y=winY[iWin]; 
 xsh.width=W[iWin]; xsh.height=H[iWin];
 xsh.flags=PPosition | PSize | USPosition | USSize; 
 XSetNormalHints(dpy, win5[iWin], &xsh);
 
 for (j=32; j<120 && comwin[j]!=' ';j++);
 if (iWin && comwin[iWin*8]) strncpy(WText[iWin],&comwin[(iWin-1)*8],8);
 sprintf(WTxt,"%.*s%.8s%.15s",j-31,&comwin[32],
  &comwin[24],WText[iWin]);XStoreName(dpy, win5[iWin], WTxt);

 weiter:/* Pixmap erstellen mit Background fuellen */
 PBreit=W[iWin]*Zfak[iWin]; ft[MaxFelder+3].y=(test) ? 8 : 4;
 PHoch=(iWin) ? H[iWin]*Zfak[iWin] : XHeightOfScreen(screen);
 if (iWin && xpm[4-iWin]) goto lMap;
 if (pix5[iWin]) XFreePixmap(dpy, pix5[iWin]);
 pix5[iWin]=XCreatePixmap(dpy, XRootWindowOfScreen(screen),
     W[iWin], PHoch, XDefaultDepthOfScreen(screen));
 XFillRectangle(dpy,pix5[iWin],gc[WFarbe[iWin]],0,0,W[iWin],H[iWin]);

 /* Fonts setzen und Window mappen */
 lMap:pw=p=(&pix5[iWin]); w=(&win5[iWin]);
 if (!iWin){if ((x06=W[0]-W[6])<0) x06=0; j=(-2); xcparam(&j,&j,&j);
  for (j=0;j<=11;j++) XSetFont(dpy,gc[j],fs->fid);
  Felder=0; Tabelle=MaxFelder; Ytab=H[0]; I82=TF1=0;TF0=-TF0;
  pptab.W=W[6]; pptab.H=H[6]; pptab.HW[1]=demo;
  pptab.HW[0]=(!demo)?i82:(demo<99)?W[6]/spx:(W[6]<H[6])?demo/spx:demo*2/spx;
  if (*OkExitCan>=1) j=CXTDEF(8,"Exit ",5, 2,(i82-5 ),10);
  if (*OkExitCan>=2) j=CXTDEF(5," Ok ", 4, 2,(i82-10),10);
  if (*OkExitCan>=3) j=CXTDEF(9,"Cancel",6,2,(i82-17),10);}
 XMapWindow(dpy,*w); lProp=XInternAtom(dpy,"__COPY_TEXT",False);
 if (test) printf("Win:%d Shadow:%d Tab:%d, Width:%d, High:%d\n",
     iWin,Schatten,Tabelle,W[iWin],H[iWin]); XMapRaised(dpy,win5[iWin]);
 Puffer=XFetchBytes(dpy, &Pufferl); if (!iWin || *win>3) return;

 /* Graphik-Umrechnungs-Faktoren ermitteln */
 if (czoom.ZM) {DeltaX=czoom.Xmax-czoom.Xmin; DeltaY=czoom.Ymax-czoom.Ymin;
          ZoomX=czoom.Xmin; ZoomY=czoom.Ymax;}
    else {DeltaX=(kontur.Xmax-kontur.Xmin)*1.03;
          DeltaY=(kontur.Ymax-kontur.Ymin)*1.03;
          if (!DeltaX) DeltaX=PBreit; if (!DeltaY) DeltaY=PHoch;
          ZoomX=0.5*(kontur.Xmin+kontur.Xmax-DeltaX);
          ZoomY=kontur.Ymax+0.01*DeltaY;}
 if ((float) PBreit/PHoch > DeltaX/DeltaY) U=(float)PHoch/DeltaY;
    else U=(float)PBreit/DeltaX; czoom.Hgrenz=5.0/U;
 if (test) printf("Delta%d X:%f Y:%f U:%f\n",czoom.ZM,DeltaX,DeltaY,U);
}

/*==> Re-assign/Read *.xpm files for Icons and background Images on Window:4-1 */
extern void XPMRD(char *c,Pixmap *p,Window *w)
{int i=0,j,k,l=0,n=4; for (j=0;j<4;j++) if(xpm[j] && !p[4-j])
 {W[4-j]=xpm[j]->width; H[4-j]=xpm[j]->height; p[4-j]=XCreatePixmap(dpy,
  XRootWindowOfScreen(screen), W[4-j],H[4-j], XDefaultDepthOfScreen(screen));
  XPutImage(dpy,p[4-j],gc[0],xpm[j],0,0,0,0,W[4-j],H[4-j]);
  if (w[4-j]) XDestroyWindow(dpy,w[4-j]);
  w[4-j]=XCreateWindow(dpy,XRootWindowOfScreen(screen),0,0,W[4-j],H[4-j],0,
       XDefaultDepthOfScreen(screen), InputOutput,
       XDefaultVisualOfScreen(screen),CWEventMask | CWBackPixel, &xswa);
  if(j) XSetWindowBackgroundPixmap(dpy,w[4-j],p[4-j]);
 }/* Read *.xpm files into Images and Pixmap */
 if (c[0]!=' ' && c[0]!='*') while (i++<80) if (c[i]==' ')
   {c[i]=0; j=XpmReadFileToImage(dpy,&c[l],&xpm[4-n],NULL,NULL);
    if (j) {printf("\nxpm-Error:%d>%s<%d",j,&c[l],i); return;} if (!n) return;
    c[0]=' ';if (p[n]) XFreePixmap(dpy, p[n]);
    p[n]=XCreatePixmap(dpy, XRootWindowOfScreen(screen),
         W[n]=xpm[4-n]->width, H[n]=xpm[4-n]->height, XDefaultDepthOfScreen(screen));
    XPutImage(dpy,p[n],gc[0],xpm[4-n],0,0,0,0,W[n],H[n]);
    if (w[n]) XDestroyWindow(dpy,w[n]);
    w[n]=XCreateWindow(dpy,XRootWindowOfScreen(screen),0,0,W[n],H[n],0,
         XDefaultDepthOfScreen(screen), InputOutput,
         XDefaultVisualOfScreen(screen),CWEventMask | CWBackPixel, &xswa);
    if(n<5) XSetWindowBackgroundPixmap(dpy,w[n],p[n]); XStoreName(dpy,w[n],&c[l]);
    c[i]=' '; l=i+1; if (c[i+1]==' ' || n--<1) break;
   }return;
}
/*==> Graphic context veraendern */
static void GCaendern(j) int j;
{char Dash_Liste[4][4]={{2,2,2,2},{5,5,5,5},{2,5,2,5},{5,1,2,1}};
 int iStil=(j && j<10) ? cpunit.Stil[j]-1 : 0; if (!dpy) return;
 if (test&&j==1) printf("GC %d dick:%d stil:%d\n",j,cpunit.Dick[j],iStil);
 xgcv.background=xswa.background_pixel;
 xgcv.line_style=LineSolid; xgcv.line_width=1;
 if (j) {if (iStil) xgcv.line_style=LineOnOffDash;
     xgcv.foreground=Farb_Pixel(j,0);
     xgcv.line_width=cpunit.Dick[j];
     xgcv.dashes=2;
     if (iStil)
        {XChangeGC(dpy, gc[j], GCForeground | GCBackground |
                   GCLineWidth | GCLineStyle| GCDashList, &xgcv);
         XSetDashes(dpy, gc[j],0, &Dash_Liste[iStil-1][0],4);}
        else
         XChangeGC(dpy, gc[j], GCForeground | GCBackground |
                   GCLineWidth | GCLineStyle, &xgcv);
     return;
    }

 xgcv.foreground = xswa.background_pixel = Farb_Pixel(0,0); 
 xgcv.background = Farb_Pixel(1,0);
 XChangeGC(dpy, gc[0] , GCForeground | GCBackground, &xgcv);
 xgcv.background = xswa.background_pixel;
 xgcv.foreground = Farb_Pixel(0,1);
 XChangeGC(dpy, gc[10], GCForeground | GCBackground, &xgcv);
 xgcv.foreground = Farb_Pixel(0,2);
 XChangeGC(dpy, gc[11], GCForeground | GCBackground, &xgcv);
 xgcv.foreground = Farb_Pixel(0,3);
 XChangeGC(dpy, gc[12], GCForeground | GCBackground, &xgcv);
 XChangeGC(dpy, gc[14], GCForeground | GCBackground, &xgcv);
 XSetFunction(dpy,gc[14],GXinvert); XSetLineAttributes(dpy,gc[14],3,0,0,0);
}

/*=> Farb-Pixel erstellen /usr/include/X11/X.h */
static int Farb_Pixel(col,d) int col,d;
{static int i,l, Cellen=0;
 if (farbig!=-1) goto weiter;
 if (farbig=(XDefaultVisualOfScreen(screen))->class == TrueColor
         || (XDefaultVisualOfScreen(screen))->class == PseudoColor
         || (XDefaultVisualOfScreen(screen))->class == DirectColor
         || (XDefaultVisualOfScreen(screen))->class == GrayScale
         || (XDefaultVisualOfScreen(screen))->class == StaticGray
         || (XDefaultVisualOfScreen(screen))->class == StaticColor)
    {cmap=XDefaultColormapOfScreen(screen);
     for (i=0;i<=9;i++) for (l=0;l<=9;l++)
         {Ftab[l][i].pixel=0;
          Ftab[l][i].flags=DoRed | DoGreen | DoBlue; PixelRet[l*10+i]=0;}
     XAllocColorCells(dpy,cmap,0,0,0,PixelRet, 110);
     for (i=0;i<=9;i++) for (l=0;l<=9;l++)
          if (CellTyp[l][i]=(PixelRet[l*10+i])!=0) Cellen++;
     if (screen < 0 ||cmap==4 ) farbig=0; 
    }

 /* Hintergrund-Farbe veschieben, so dass 30%-Variation moeglich ist */ 
 weiter: if (!farbig) goto SchwarzWeis;
 if (!col) for (i=0;i<=2;i++)
     {Ftab[0][i].pixel=PixelRet[i];
      if (cpunit.RGB[0][i]<delta0[0]) cpunit.RGB[0][i]=delta0[0];
          else if (cpunit.RGB[0][i]>100-delta0[1])
                   cpunit.RGB[0][i]=100-delta0[1];}
                   
 if (!col && !d) 
    {for (i=0,l=0;i<=2;i++) l+=cpunit.RGB[0][i];
     if (l>150) TypFarbe[9]=10; else TypFarbe[9]=11;}
 if (!d) l=0; else if (d>1) l=delta0[d-1]; else l=(-delta0[0]);
 Ftab[col][d].red  =(cpunit.RGB[col][0]+l)*652.8;
 Ftab[col][d].green=(cpunit.RGB[col][1]+l)*652.8;
 Ftab[col][d].blue =(cpunit.RGB[col][2]+l)*652.8;
 return FarbeNeu(col,d);
 SchwarzWeis:
 if ((col>0 && col<9) || d<0) return XBlackPixelOfScreen(screen);
    else return XWhitePixelOfScreen(screen);
}

/*=> Farb-Zuordnug herstellen */
static int FarbeNeu(col,d) int col,d;
{static int ColMsg=0;
 if (CellTyp[col][d] && Ftab[col][d].pixel)
    {XStoreColor(dpy,cmap, &Ftab[col][d]); return Ftab[col][d].pixel;}
 if (PixelRet[col*10+d]) XFreeColors(dpy,cmap, &Ftab[col][d].pixel,1,0);
 if (XAllocColor(dpy,cmap,&Ftab[col][d]))
    {CellTyp[col][d]=0; return PixelRet[col*10+d]=Ftab[col][d].pixel;}
 if (ColMsg++<10) printf("W=> Insufficient color resouces %d,%d\n",col,d);
 if (!PixelRet[col*10+d]) return Ftab[1][0].pixel; return 0;
}

/*=> Farb-Beispiel im Alpha-Window anzeigen */
static void FarbBeispiel(x,y,hoch,farbe) int x,y, hoch, farbe;
{int i,delta,lg=i82/10,h0=hoch*spy,c0[]={10,11,12}; float Proz=0;
 y=y*spy-fs->ascent-Schatten-1; ptAnz=5;
 pt[0].x=pt[3].x=pt[4].x=x*spx; pt[1].x=pt[2].x=pt[0].x+lg*spx;
 pt[0].y=pt[1].y=pt[4].y=y; pt[2].y=pt[3].y=y+h0-2;
 if (farbe>10) return;

 gxgrau(&farbe, &Proz);
 if (farbe) {pt[3].y-=0.5*hoch*spy;
     for (i=0;i<ptAnz;++i) pt[i].x+=(lg+1)*spx; gxline(&farbe);
     if (farbe<10-plparm.NERG && hoch==1) return;}
   else {gxline(&c0[0]);
     for (i=0;i<ptAnz;++i) pt[i].y+=h0; gxline(&c0[1]);
     for (i=0;i<ptAnz;++i) pt[i].y+=h0; gxline(&c0[2]); return;}

 delta=hoch*spy/(10*((hoch>1) ? 2 : 1));
 if (!farbe) {gxline(&c0[2]); return;}
 for (i=0;i<ptAnz;++i) pt[i].x+=(lg+1)*spx;
 if (hoch>1) farbe--;
 pt[2].y=pt[3].y=pt[0].y+delta;
 while (Proz<1.0) {Proz+=0.1; gxgrau(&farbe, &Proz);
                   for (i=0;i<ptAnz;++i) pt[i].y+=delta;}

 if (hoch>1) {farbe++; Proz=(-0.1); while (Proz<1.0)
    {Proz+=0.1; gxgrau(&farbe, &Proz); for (i=0;i<ptAnz;++i) pt[i].y+=delta;}}
}

/*=> Fenster aktualisieren und evtl. als *.gif Datei ausgeben */
extern void xcpmsg(w) int *w;
{int Wi=(W[*w]<W[6]) ? W[*w]-X06 : W[6]; xpl=-1;
 if (test) printf("MSG Win:%d,%d,%d, X06:%d\n",*w,Wi,H[*w],X06); 
 XCopyArea(dpy,pix5[*w],win5[*w],gc[1],0,0,Wi,H[*w],0,0);
 if (Felder && ! *w) FeldWechsel(Feld,-1);
}

/*=> Window-Parameter vorgeben */
extern void xcparam(Selekt,Xwert,Ywert) int *Selekt, *Xwert,*Ywert;
{int NWIN,IR=0,i, KyCd[17]; char *cfn,*cl;
/* Window-Position vorgeben */
 if (*Selekt>=0 && *Selekt<=3)
    {winX[*Selekt]=XWidthOfScreen(screen)*(*Xwert)*.01; cgif[*Selekt]=eacom[19];
     winY[*Selekt]=XHeightOfScreen(screen)*(*Ywert)*.01;}

/* Window-Groesse vorgeben */
  else if (*Selekt>=5 && *Selekt<=7)
    {W[*Selekt-4]=XWidthOfScreen(screen)*(-*Xwert)*.01;
     H[*Selekt-4]=XHeightOfScreen(screen)*(*Ywert)*.01;}

/* Schrift-Font lesen if (test) */
  else if (*Selekt==(-1) && *Ywert)
    {i=(*Xwert)-1; cl=strstr(eacom,":"); if (cl) {for (i=0;i<3;i++)
     {if (cfn=strstr(FontName[i],"--")) strncpy(cfn+2,cl+1,2); cl+=2;
     }if (cl[1]=='.') sscanf(cl+2,"%d",&demo); if (demo>200) iPS=demo; i=0;}
    else {strncpy(FontName[i],&eacom[8],*Ywert); FontName[i][*Ywert]=0;
     if (dpy) font3[i]=XLoadQueryFont(dpy, &FontName[i][0]);}
     if (test) printf("Font:<%s> d=%d<\n",FontName[i],demo);}

/* Schrift-Farben lesen */
  else if (*Selekt==(-1))
   for (i=0;i<10; i++) {sscanf(&eacom[8+i*3],"%3d",&NWIN); TypFarbe[i]=NWIN;}

/* Icon Datei lesen */
  else if (*Selekt==(-2)){XPMRD(issyimg,pix5,win5);
   MaxIcon=W[4]/xicon; if (test) printf("\nIcon:%d,%d",MaxIcon,xicon);}

/* Tastaturbelegung lesen */
  else if (*Selekt==(-3))
    {for (i=0;i<17; i++) {sscanf(&eacom[8+i*3],"%3d",&KyCd[i]);}
     CursorLinks=KyCd[1];CursorRechts=KyCd[0];
     CursorOben=KyCd[2]; CursorUnten=KyCd[3];
     BildOben  =KyCd[4]; BildUnten  =KyCd[5];
     Tabulator =KyCd[6]; DeleteFeld =KyCd[7]; ZeichenBs=KyCd[8];
     Einfuegen1=Einfuegen2 = KyCd[9]; ZeichenDel=KyCd[10];
     Suchen=KyCd[11]; Selektieren=KyCd[12];Hilfe1=Hilfe2=KyCd[13];
     Pf3=KyCd[14]; TestTaste=KyCd[15]; SetUpTaste=KyCd[16];
     if (test) {printf("\nNew Keys:");
       for (i=0;i<17; i++){ printf(",%d",KyCd[i]);}}}
  else if (*Selekt==(-4)) Doppl=(*Xwert);

/* Image-Datei lesen */
  else if (*Selekt>=11 && *Selekt<=13)
    {issyimg[*Xwert]=0; NWIN=*Selekt-10; 
     if (test) printf("\nREAD Image:%d, file:%s",NWIN,issyimg);
     if (XpmReadFileToImage(dpy, issyimg, &img, NULL, NULL)) return; 
     *Ywert=H[NWIN]=kontur.Xmax=img->height;
     *Xwert=W[NWIN]=kontur.Ymax=img->width;
     czoom.ZM=0; kontur.Xmin=kontur.Ymin=0.0;
     xcinit(&NWIN,&IR);
     if (test) printf("\n Put Image X:%d, Y:%d, W:%d",*Xwert,*Ywert,iWin);
     XPutImage(dpy, pix5[iWin], gc[0], img, 0,0,0,0,*Xwert,*Ywert);
     xcpmsg(&NWIN);}

  else if (*Selekt==99) {test=(*Xwert); Einfueg=(*Ywert);
    if (eacom[0]=='+'){if(++iFont>2)iFont=0; W[0]=0;}}
  else if (*Selekt==4)  
    if (*Xwert < 0) {iFont=(*Ywert); W[0]=0; cgif[4]=eacom[16];}
     else if (*Xwert==0) *Ywert=H[0]/spy;
     else if (*Xwert==99) strcpy(&eacom[7],&FontName[(*Ywert)-1][0]);
     else {i82=(*Xwert); i24=(*Ywert);if (pix5[0]) WindowModifiziert(1);}
}

/*=> ISSY-Parameter-Setup Menu */
extern void setupissy(legp, IR) int *legp, *IR;
{int j,i,l,size,idef,ileg,nleg,col, Nr=0,Ret=0,idem=0;
 static char *leg=clegdf,*cfn,jfn=24, id[10],is[10],icn[11],fn[11],
  DefaultRGB[12][3]={90,90,85, 0,0,0, 80,0,0, 0,50,0, 0,0,100, 60,0,60, 80,0,80,
   0,90,50, 100,100,0, 100,50,0, 0,0,0,0,0,0},FillPAT[6]="fill 0", iDick, iStil,
  InversRGB[5][3]={30,40,40, 80,90,90, 100,50,50, 50,95,50, 40,70,90},
  DreiStufen[3][3]={30,30,100, 100,100,20, 100,30,30}, FarbStufen[9]="0 grades",
  ZweiStufen[2][3]={100,100,100, 10,10,10}, DynInc[10]="Incr rot0",
  *defc="Default Invers  5 Grades3 Grades2 Grades", *dick="normalthick large ",
  *atgc="Alpha  Types  Groups Colors ",defa[32]="Normal  Message Input   Upper   ",
  *stil="solid doted dashed__..___._._.", *RGB, backgr[8]="Backgr. ",
  rgb[3][17]={"C3050000100Red  $","C3050000100Green$","C3050000100Blue $"}, Border[1],
  dlt[3][11]={"I2101030$  ","I2101030$  ","I2101030$  "}; unsigned char SIcon[]={IconS};

 if (*legp<0) 
  {if (*legp==-1) RGB=(&DefaultRGB[0][0]); else RGB=(&InversRGB[0][0]);
   for (i=0; i<=5; i++)
       {cpunit.RGB[i][0]=RGB[0]; cpunit.RGB[i][1]=RGB[1];
        cpunit.RGB[i][2]=RGB[2]; RGB+=3; GCaendern(i);} return;}
 FarbStufen[0]='0'+plparm.NERG;
 Border[0]='0'+DefaultSchatten;
 DynInc[8]=czoom.RDY+'0';
 FillPAT[5]=(cpunit.PAT == -3) ? '1' : '0';

 if (nleg=(*legp)) leg=(&clegdf[(nleg-1)*80]); else leg=defa;
 Beg:j=2; xcinit(&idem,&j); idem=0; pw=p;
 i=CXTDEF(0,"IP",2,1,2,3);
 i=CXTDEF(0,"Setup panel",11,1,5,1);
 size=CXTDEF(11,FontSize,iFont,6,6,9);
 i=CXTDEF(11,&FontSize[iFont*6],6,2,2,10);
 i=CXTDEF(0,"Font size, Border:",18,2,9,1);
 i=CXTDEF(1, Border,1,2,27,1); if (!Nr) Nr=i;
 i=CXTDEF(0, (BFarbe) ? leg+(BFarbe-1)*8: backgr,8,7,2,3);
 i=CXTDEF(0,"thick. style",12,9,11,1);
 i=CXTDEF(0,"Color:",6,l=(i82>51)?2:9,j=(i82>51)?29:10,1);
 idef=CXTDEF(12,defc,0,5,8,9);
 i=CXTDEF(1, FarbStufen,8,l,j+6,1);
 i=CXTDEF(0,"Gif-Win:",8,7,10,1);
 i=CXTDEF(1,cgif,5,7,19,1);

 for (j=0; j<3; j++)
     {sprintf(rgb[j]+2,"%3d",cpunit.RGB[BFarbe][j]); *(rgb[j]+5)='0';
      i=CXTDEF(1,rgb[j]+2,3,j+4,2,7); i=CXTDEF(1,rgb[j], 18,j+4,6,8);}
 if (!BFarbe) for (j=0; j<3; j++) {sprintf(dlt[j]+2,"%2d",delta0[j]);
     *(dlt[j]+4)='1';i=CXTDEF(1,dlt[j],11,j+4,26+i82/10,8);}
 FarbBeispiel(24,4,3,BFarbe);
 ileg=CXTDEF(13,atgc,1,4,7,9);
 i=CXTDEF(13,atgc+(nleg)*7,7,8,2,10);
 i=CXTDEF(1,"Select ",0,1,7,9); i=CXTDEF(1,backgr,8,9,2,1);
 i=CXTDEF(6,FillPAT,6,8,10,10); i=CXTDEF(1,issyimg,48+i82/10,9,31,7);
 i=CXTDEF(6,DynInc, 9,8,16,10); FarbBeispiel(34+i82/5,4,1,0);
 for (j=1; j<10; j++)
     {i=CXTDEF(j+1,"Select A-GroupB-Group",0,3,7,9);
      if (j<5 || nleg) i=CXTDEF(1,&leg[(j-1)*8],8,j+9,2,1);
      iDick=(cpunit.Dick[j]<4) ? cpunit.Dick[j]-1 : 0;
      id[j]=CXTDEF(20+j,dick,iDick,3,6,9);
      i=CXTDEF(20+j,dick+iDick*6,6,j+9,11,10);
      iStil=(cpunit.Stil[j]<5) ? cpunit.Stil[j]-1 : 0;
      is[j]=CXTDEF(30+j,stil,iStil,5,6,9);
      i=CXTDEF(30+j,stil+iStil*6,6,j+9,18,10);
      FarbBeispiel(24,9+j,1,j);
     }
 for (j=0; j<=2; j++)
     {i=CXTDEF(0,FontSize+j*6,6,1, 17+j*7,-j-1);
      i=CXTDEF(1,&FontName[j][0],60,19+j,11,1);
      i=CXTDEF(0,FontSize+j*6,6,19+j,2,-j-1);}
 i=-2;if (issyimg[0]!='*') xcparam(&i,&j,&l);
 if (MaxIcon)    
    {Iicon=-Iicon; sprintf(icn,"I2%2d01%2d",Iicon,MaxIcon);
     i=CXTDEF(1,icn,5,9,25,8);
     for (j=Iicon-1; j<MaxIcon; j++)i=CXTDEF(15,SIcon,j,7,30+5*(j-Iicon),10);}
 if (cfn=strstr(FontName[iFont],"--")) {sscanf(cfn+2,"%d",&jfn);
     sprintf(fn,"I2%2d1444",jfn); i=CXTDEF(1,fn,10,2,9,8);}

 xcread(&Nr,&Ret); if (cfn) {sprintf(cfn+2,"%.2s",fn+2);cfn[4]='-';}
/****************/
 DefaultSchatten=Border[0]-'0'; plparm.NERG = FarbStufen[0]-'0';
 cpunit.PAT=(-3)*(FillPAT[5]-'0'); czoom.RDY=DynInc[8]-'0';
 if (MaxIcon) {if (icn[2]==' ') icn[2]='0';
     sscanf(icn+2,"%2d",&Iicon); Iicon=-Iicon; }  
 for (i=0; i<3; i++)
     {*(rgb[i]+5)=0; sscanf(rgb[i]+2,"%3d",&col);
      if (i-3) {;for (j=0; FontName[i][j] && j<79; j++)
          if (FontName[i][j+1]==' ') FontName[i][j+1]=0;
          font3[i]=XLoadQueryFont(dpy,&FontName[i][0]);}
      if (cpunit.RGB[BFarbe][i] != col)
         {cpunit.RGB[BFarbe][i]  = col; Ret=(-101);}
      if (!BFarbe) {sscanf(dlt[i]+2,"%2d",&col); delta0[i]=col;}
     } j=(-1);
 i=FarbStufen[0]-'0'; if (i>=0 && i<=9) plparm.NERG=i;
 Set:/* Set Font and Window size */ 
 if (Ret==-11 || j>0)
  {if (ft[size].len<5) W[0]=0; if (ft[size].len<3) iFont=ft[size].len;
    else if (ft[size].len>4) {*IR=ft[size+1].len+1; if (*IR>4 || Mg[12]==' ') *IR=0;}
    else {i=-H[6]*.4; l=-W[6]*.4; idem=(ft[size].len==3)?-1:(i>iPS)?i:(l>iPS)?l:iPS;} 
          if (j>0) {if (idem) demo=-idem; *IR=6; return;}}
 else if (Ret== 11) {iFont++;if (iFont==3) iFont=0; W[0]=0;}
 else if (Ret==-12)
  {j=9;
   switch (ft[idef].len)
       {case 0: i=0; RGB=(&DefaultRGB[0][0]); break;
        case 1: i=0; RGB=(&InversRGB [0][0]); j=5; break;
        case 2: i=5; RGB=(&DefaultRGB[i][0]); break;
        case 3: i=7; RGB=(&DreiStufen[0][0]); break;
        case 4: i=8; RGB=(&ZweiStufen[0][0]); break;
       }
   if (ft[idef].len>1) FarbStufen[0]='0'+(plparm.NERG=10-i);
   for (; i<=j; i++)
       {if (!ft[idef].len) cpunit.Stil[i]=cpunit.Dick[i]=1;
        cpunit.RGB[i][0]=RGB[0];
        cpunit.RGB[i][1]=RGB[1];
        cpunit.RGB[i][2]=RGB[2]; RGB+=3;
        if (i) for (l=1; l<10; l++) Ftab[i][l].pixel=0;
        GCaendern(i);
       }
  }
 else if (Ret==-13 || Ret==13)
  {if (SetupLeg=nleg=ft[ileg].len)
           leg=(&clegdf[80*(nleg-1)]); else leg=defa;}
 else if (Ret==15)
  {if (Iicon-- <= -MaxIcon) MaxIcon++;}
 else if (Ret<-100)
  {if (farbig && BFarbe) for (i=1; i<10; i++)
      {Ftab[BFarbe][i].pixel=0;
       if (BFarbe<9) Ftab[BFarbe+1][i].pixel=0;}
   GCaendern(BFarbe); if (BFarbe<9) GCaendern(BFarbe+1);}
 else if ((j=(-Ret-30))>=0) cpunit.Stil[j]=ft[is[j]].len+1;
 else if ((j=(-Ret-20))>=0) cpunit.Dick[j]=ft[id[j]].len+1;
 else if ((j=Ret-30)>=0) {if (++cpunit.Stil[j]>5) cpunit.Stil[j]=1;}
 else if ((j=Ret-20)>=0) {if (++cpunit.Dick[j]>3) cpunit.Dick[j]=1;}
 else if ((j=(-Ret-1) )>=0) {BFarbe=j;
      if (Mg[0] != 'S') cexcl[Mg[0]-'A']='0'-Ret-1;}
 if (j>=0) GCaendern(j); if (Ret!=8) goto Beg; *IR=6;
}

/*========== Funktionen zur Alpha-Window-Initialisierung =============*/
#ifdef VMS
typedef struct SPARM {short len; char typ,cl; unsigned char *t;} SPARM;
typedef union tparm {char *text; SPARM st;} tparm;

extern void axtdef(nr, sparm, lg,yp,xp, ltyp,IR)
 int *nr,*lg,*yp,*xp,*ltyp,*IR; tparm *sparm;
{*IR=CXTDEF(*nr,sparm->st.t,*lg,*yp,*xp,*ltyp);}

#else /* Unix */
extern void axtdef(nr, sparm, lg,yp,xp, ltyp,IR)
 int *nr,*lg,*yp,*xp,*ltyp,*IR; char *sparm;
{*IR=CXTDEF(*nr,sparm,*lg,*yp,*xp,*ltyp);}
#endif

/*=> Bildschirm-Text-Ausgabe (Feld-Definitionen) */
extern int CXTDEF(nr,sparm,lg,yp,xp,ltyp) int nr,lg,yp,xp,ltyp; unsigned char *sparm;
{int i,hoch,lcol,styp=1,xp1=(xp>1)?xp-1:i82+xp;
 if (xp>i82-2 && Tabelle<=Felder) return 0; else if (nr==0 && (ltyp<8 || ltyp>9))
    {if (ltyp<0)
        {XSetFont(dpy, gc[1], font3[-1-ltyp]->fid);
         XDrawImageString(dpy,*p, gc[1],xp1*spx, yp*spy, sparm,lg);
         XSetFont(dpy, gc[1], fs->fid);}
       else if (ltyp) TextPos(sparm,lg,xp1*spx,yp*spy,ltyp==1 ? 9:0,0);
       else {sscanf(sparm,"%1d%2d",&styp,&hoch); 
             if (styp>1) {Felder=0; Ytab=H[0];}
             TextPos(" ",lg,xp1*spx,(yp+1)*spy,20+styp, hoch-2);}
     return 0;
    }
 if (ltyp) {Felder++; j=Felder;} else {Tabelle=Felder+1; j=0; Ytab=xp;}
 ft[j].t=sparm; ft[j].len=lg;
 ft[j].y=((j && j<Tabelle) || lg==0) ? yp : yp-1;
 ft[j].x=xp1;
 if (ltyp==9) {ft[j].typ=nr ? -nr-1 : -1; ft[j].x=xp;}
    else if (ltyp== 0) ft[j].typ=1;
    else if (ltyp>=10 && nr==6) {ft[j].typ=12; if (ft[j].t[0]!=IconS)ft[j].len--;}
    else if (ltyp>=10) ft[j].typ=12+nr;
    else ft[j].typ=(ltyp);
 if (j==Tabelle) {ft[0].x=ft[j].x; return Felder;}
    else if (j>=Tabelle || ltyp==9 || ltyp==0) return Felder;

 if (ltyp>0 && ltyp<6 && ft[j].t[0]==' ') LinksShift(ft[j].t, lg);

 if (ft[j].typ==12 && ft[j].t[0]==IconS) styp=1+(ft[j].t[3]!='1');
    else if (ft[j].typ==12) styp=1+(ft[j].t[lg-1]!='1');
    else if (ltyp>=10 || (j>1 && ft[j-1].typ<0)) styp=2;
 if (ft[j].t[0]==IconS) {if (lg>MaxIcon) ft[j].len=0;}
    else {for (i=0;i<lg;i++) if (sparm[i]==0) sparm[i]=' ';}
 if (ft[j-1].typ<0 && ft[j].typ>=10) lcol=0; else 
    if (ft[j].typ<8) lcol=ltyp; else if (ft[j].typ>12) lcol=8; else lcol=1;
 if (test) printf(" <%.*s,%d,%d,%d,%d>",lg,ft[j].t,lcol,ltyp,ft[j].typ, styp);
 if (ltyp==8) WertGeber(0, p, ft[j].t, lg, ft[j].x*spx, yp*spy);
    else TextPos(ft[j].t, ft[j].len, ft[j].x*spx, yp*spy, lcol,styp);
 return Felder;
}

/*=> Text im Window positionieren */
static void TextPos(text, lg, xp,yp, typ,styp)
unsigned char *text; int lg,xp,yp,typ,styp;
{int breit,xd,yd,d,i12, hoch=spy-3, 
 Rand=(Schatten || typ<9) ? Schatten : 1;
 if (typ>10 && styp!=9)
    {d=spx-Rand-2; breit=lg*spx+2*(Rand+d)+1;
     xd=xp-d-Rand-1; yd=yp-fs->ascent-d-Rand-1;
     i12=(typ>21) ? typ-21 : 12;
     if (typ>=20) hoch+=styp*spy;
     XFillRectangle(dpy,*pw, gc[i12], xd, yd, breit, hoch+2*d);
     SchattenBox(pw, Rand,(typ==20) ? 0: 1, xd, yd, breit, hoch+2*d);
     if (typ>=20) return;}

 if (text[0]!=IconS)
    {if (typ!=6) XDrawImageString
        (dpy,*pw, gc[TypFarbe[(typ>9) ? 9 : typ]], xp,yp,text,lg);
     if (!styp) return; else breit=lg*spx+2*Rand+1;}
   else if (xpm[0])
    {yd=yp-fs->ascent-Rand-1; breit=spx*5-4;hoch=spy*2-2;
     int xi=(xicon>breit)?breit:xicon, yi=(yicon>hoch)?hoch:yicon;
//   if (pix5[4])XPutImage(dpy,*p,gc[0],xpm[0],lg*xicon,0,xp-1,yd,xi,yi);
     if (pix5[4])XCopyArea(dpy,pix5[4],*p,gc[0],lg*xicon,0,xi,yi,xp-1,yd);}

 xp-=Rand+1; yp-=Rand+fs->ascent+1;
 if (test>1) printf(" Box:%.*s x:%d b:%d, lg:%d\n",lg,text,xp,breit,lg);
 if (styp == 1)
     SchattenBox(pw, Rand, 1, xp, yp, breit, hoch);
    else if (styp == 2)
     SchattenBox(pw, Rand, 0, xp, yp, breit, hoch);
    else if (styp == 9)
     XCopyArea(dpy,*pw,*w,gc[1],xp,yp,breit, hoch, xp,yp);
}

/*=> Schatten Box zeichnen */
static void SchattenBox(d, BoxRand, HellDunkel, xpos,ypos, breit,hoch)
int BoxRand, HellDunkel, xpos,ypos, breit,hoch; Drawable *d;
{XPoint Box[3]; int i11=11-HellDunkel, i10=10+HellDunkel;
 if (HellDunkel==2) i11=i10=0;
 Box[0].x=Box[1].x=xpos, Box[2].x=xpos+breit;
 Box[0].y=ypos+hoch, Box[1].y=Box[2].y=ypos;
 while(BoxRand)
   {XDrawLines(dpy,*d,gc[i11],Box,3,0);
    Box[1].x=Box[2].x; Box[1].y=Box[0].y;
    XDrawLines(dpy,*d,gc[i10],Box,3,0); if (!BoxRand--) return;
    Box[0].x++; Box[0].y--; Box[2].x--; Box[2].y++;
    Box[1].x=Box[0].x; Box[1].y=Box[2].y;}
}

/*=> Pop-Up Kasten zeichnen */
static void PopKasten(pop,x,y,text,anz,lg)
int pop, x,y, anz,lg; unsigned char *text;
{static int xp, yp, lang ,hoch;
 if (pop) XCopyArea(dpy,*p,*w,gc[1],xp,yp,lang+1,hoch+1,xp,yp);
 if (pop<0) return;
 xp=x-Schatten-2; yp=y-1; y+=Schatten+fs->ascent+1;
 lang =lg*spx+2*Schatten+2; hoch =anz*spt+2*Schatten+1;
 XFillRectangle(dpy,*w, gc[0], xp,yp, lang, hoch);
 while (anz--)
  {if (text[lg-3]=='>') XDrawImageString(dpy,*w, gc[1], x,y, text,lg-2);
     else XDrawImageString(dpy,*w, gc[1], x,y, text,lg);
   text+=lg; y+=spt;}
 SchattenBox(w,Schatten, 0, xp, yp, lang, hoch);
}

/*=> Text an den linken Feldrand verschieben */
static void LinksShift(text, lg) int lg; unsigned char *text;
{int j,shift;
 for (shift=0; shift<lg && text[shift]==' '; shift++); if (shift==lg) return;
 for (j=0;j<lg;j++){if (shift<lg) text[j]=text[shift];else text[j]=' ';shift++;}
}

/*=================== Funktionen zur graphic-Initialisierung ===========*/
/*=> Poligon Daten-Vorgabe */
extern void gxpoly(X,Y,Ipoint) float *X,*Y; int *Ipoint;
{for (ptAnz=0;ptAnz<*Ipoint;++ptAnz)
   {pt[ptAnz].x=(X[ptAnz]-ZoomX)*U; pt[ptAnz].y=(ZoomY-Y[ptAnz])*U;}}

/*=> Line-Dicke und Line-Typ aendern */
extern void gxltyp(FarbNr,Dick,Typ) int *FarbNr, *Dick, *Typ;
{if (*Typ)  cpunit.Stil[*FarbNr]=(*Typ);
 if (*Dick) cpunit.Dick[*FarbNr]=(*Dick); GCaendern(*FarbNr);}

/*=> Poligon Graphik Ausgabe */
extern void gxline(FarbNr) int *FarbNr;
{int farbe;
 if (*FarbNr<0) farbe=(*FarbNr<-9) ? WFarbe[iWin] : -(*FarbNr);
     else if (*FarbNr && *FarbNr==WFarbe[iWin]) farbe=0;
     else farbe=(*FarbNr); XDrawLines(dpy,*pw,gc[farbe],pt,ptAnz,0);}

/*=> Poligon Farbig ausfuellen */
extern void gxgrau(FarbNr,Prozent) int *FarbNr; float *Prozent;
{int farbe=(*FarbNr && *FarbNr!=WFarbe[iWin]) ? *FarbNr : WFarbe[iWin];
 int rgb[3],col,i,l, ZFarbe, zcol=(*Prozent*10.);
 if (zcol && farbe<9)
    {col=(*FarbNr+1); i=10-zcol; farbe=13;
     if (farbig && !Ftab[col][i].pixel)
        {for (l=0;l<3;l++)
             {rgb[l]=cpunit.RGB[col][l]*(10-i)+cpunit.RGB[col-1][l]*i;
              Ftab[col][i].red  =rgb[0]*65.28;
              Ftab[col][i].green=rgb[1]*65.28;
              Ftab[col][i].blue =rgb[2]*65.28;}

         Ftab[col][i].pixel=PixelRet[col*10+i];
         j=FarbeNeu(col,i);}
     XSetForeground(dpy,gc[13],Ftab[col][i].pixel);
    }
 XFillPolygon(dpy,*pw,gc[farbe],pt,ptAnz,Complex,0);
}

/*=> Poligon schraffiert ausfuellen */
extern void gxhatch(Schraffur) int *Schraffur;{}

/*================== Funktionen zur Interaktiven Bearbeitung ===========*/
/*=> Unterbrechungen bearbeiten */
extern void xcread(Nr, Ret) int *Nr,*Ret;
{int i=0; if (*Ret==4) {*Ret=0; goto Tmod;} Spalte=0; TF0=abs(TF0);
 if (Tabelle<MaxFelder){if (!I82) I82=ft[Felder].len; j=i82-ft[Felder].x-3;
     if (I82>j) {ft[Felder].len=j; TF1=I82-j; sph=(float)j*1.2*spx/I82;}
     if (ztabl.Aktuell-ztabl.Top>(H[0]-Ytab*spy)/spt) ztabl.Top=ztabl.Aktuell-1;
     if (ztabl.Aktuell>0) ztabl.Aktuell--; if (ztabl.Top>0) ztabl.Top--;
 if (*Nr<0) {if (TabelleNeu(0)||win5[0]) xcpmsg(&i); goto EventSchleife;}
 if (*Nr%100>Felder) F=ft; else {F=(&ft[Feld=(*Nr%100)]); if (TF0>TF1) TF0=TF1;
 if (*Nr/100-TF0>j) {TF0=*Nr/100-j+1;Spalte=j-1;} else Spalte=*Nr/100-TF0;}}
  else Spalte=0; if (iWin) xcpmsg(&i); else if (TabelleNeu(0)) xcpmsg(&i);

 EventSchleife: *Ret=0; Sp0=Spalte+TF0;
 if (test) printf("!!! Start Win:%d,%d%s%dx%d%s%d/%d+%d%s%d/%d/%d T:%d\n",*Nr*10+iWin,
     demo," WxH:",W[0],H[0]," i82:",i82,I82,I82-j," TF:",TF0,TF1,Spalte,ztabl.Aktuell);
 while (!*Ret)
  {Ereignis(0); if (ev.type<4 || ev.type>6) DopplP[0]=0;
   if (ev.type==ButtonPress||ev.type==ButtonRelease) 
      {if (*Nr<0) {*Ret=1; return;} else *Ret=MausKlick(ev.xbutton.button);}
     else if (ev.type==ConfigureNotify) *Ret=WindowModifiziert(0);
     else if (ev.type==KeyPress) *Ret=TastenKlick();
     else if (ev.type==SelectionClear) *Ret=MausKopie(0,ev.type);
     else if (ev.type==SelectionRequest)*Ret=MausKopie(0,ev.type);
     else if (ev.type==SelectionNotify) *Ret=MausKopie(0,ev.type);
     else if (ev.type==Expose && (H[7]!=H[6]||W[7]!=W[6])) *Ret=6;
     else if (ev.type==MotionNotify) if (ev.xmotion.x-x4>spx)*Ret=MausKlick(5);
       else if (x4-ev.xmotion.x>spx)*Ret=MausKlick(6);
       else if (i=(ev.xmotion.y-y4)/spt) {ztabl.Top-=i; *Ret=MausKlick(7);}
   if (*Ret) {if (*Ret==5) *Ret=0; break;}
  }if (*Nr>=0) XDrawImageString(dpy, win5[0],gc[2], spx, spy*3,
 "Working ...                                                           ",70);
 XSync(dpy,1); i=0; if (*Nr<0) goto Ende;

 Tmod: i=0; /* estimate modified table record */
 if (Tabelle==MaxFelder) goto Ende;
 if (*Ret>1000 && DopplP[0]>=Tabelle) ztabl.ATAB[DopplP[2]][ModiPos]='!';
 for (j=0; j<ztabl.Max; j++)
     {if (ztabl.ATAB[j][ModiPos]=='!')
         {if (*Ret==4) goto Ende;
          if (pptab.TABLE[0] != ' ')
             {strncpy(eacom+ft[0].y, ft[0].t+160*j, ft[0].len);
              for (i=Tabelle; i<=Felder; i++)
                  strncpy(eacom+ft[i].y, ft[i].t+160*j, ft[i].len);}  
          if (test) printf("Tabellen-update %d >%.*s<%d\n",j,8,pptab.TABLE,i);
          ztabl.ATAB[j][ModiPos]=' '; ztabl.Aktuell=j; if (*Ret>1000) goto Ende;
          if (*Ret>=0 && *Ret<8) *Ret=4;}
     } if  (*Ret==4 && *Nr>=0) *Ret=0; i=Spalte+TF0;
 Ende:if (!iWin) FeldWechsel(Felder+1,0);
 if (*Nr>=0) {*Nr=Feld+i*100; if (!W[0]) *Ret=6;}
 if (Tabelle<MaxFelder) {ztabl.Aktuell++; ztabl.Top++;}
 if (test) printf("xcread Ende %d/%d Tab:%d w:%d\n",*Ret,*Nr,ztabl.Aktuell,iWin);
}

/*=> Window modified */
static int WindowModifiziert(alfa) int alfa;
{int width=ev.xconfigure.width,w=width/i82,height=ev.xconfigure.height,i=iWin;
 if (alfa) {width=i82*spx; height=spy*i24; i=0;}
    else {if (width==W[i] && height==H[i]) return 0;
          winX[i]=ev.xconfigure.x; winY[i]=ev.xconfigure.y;}
 if (i) {W[i]=width; H[i]=height; return i;}
 if (alfa) j=iFont; else if (w >= font3[2]->max_bounds.width) j=2;
    else if (w >= font3[1]->max_bounds.width) j=1; else j=0; H[i]=height;
 if (w < font3[0]->max_bounds.width && iFont == 0 ||
     w > font3[2]->max_bounds.width && iFont == 2 ) iFont=3;
 if (test) printf("Mod %d Width:%d/%d/%d fw:%d/%d f:%d/%d\n",
  i+alfa*10,width,W[i],W[6],w,Felder,j,iFont); X06=0;
 if ((j!=iFont && W[i]<W[6]) || alfa) {W[i]=0; iFont=j; return 6;}
 if (Tabelle<=Felder) return TabelleNeu(0); else xcpmsg(&i); return 0;
}

/*=> Wechsel in ein Alfa-Feld  */
static int FeldWechsel(feld,pos) int feld,pos;
{static int xp,yp,ypos,breit,hoch,TabPos,LetzteFarbe;
 static char *InsOver[]={"<ovr>","<ins>"}; int YF=ft[Feld].y,i;
 for (i=strlen(Mg);i<78;i++) Mg[i]=' ';
 if (demo<0) {XDrawImageString(dpy,pix5[0],gc[2],spx,3*spy,Mg,79);
     TextPos(&cvers[3],5,(i82-6)*spx,3*spy,2,1); Mg[79]=0; return 0;}
   else if (pos>=0) {XDrawRectangle(dpy, win5[0],gc[0],xp,yp,breit,hoch);
     FeldPos(LetzteFarbe,&xp,&yp,&TabPos);
     if (feld>Felder) return 0; else Spalte=pos;}
   else if (pos!=-2)
    {XDrawImageString(dpy,pix5[0],gc[2],spx,3*spy,Mg,80);
     if (Mg[0]!='*') for (j=0;j<80;j++) Mg[j]=' ';
     if (!iWin && Einfueg<2)
         TextPos(InsOver[Einfueg], 5,(i82-6)*spx, 3*spy,2,1+Einfueg);
     XCopyArea(dpy,pix5[0],win5[0],gc[1],0,2*spy,W[0],2*spy,0,2*spy);}
 if (feld==0) while (Feld<Felder)
     {if (Feld++>Tabelle) break; 
        else if (ft[Feld].typ<1 || ft[Feld].typ>7);
        else if (ft[Feld].y != YF) break;}
    else if (feld>0) Feld=feld;
    else if (feld<0 && Feld==1) Feld=Felder;
    else if (feld<0) while (Feld>1) 
      if (ft[--Feld].typ<8 && ft[Feld].typ>0) break;
 while (Feld<Felder && (ft[Feld].typ>7 || ft[Feld].typ<0)) Feld++;
 F=(&ft[Feld]); LetzteFarbe=Farbe=TypFarbe[(F->typ>9) ? 9 : F->typ];
 if (Spalte>=F->len) Spalte=1;
 FeldPos(0,&xp,&yp,&ztabl.Aktuell);

 if (Feld>=Tabelle) {breit=F->len*spx+2*Schatten; hoch=spt;
     xp=F->x*spx-Schatten; yp-=Schatten+fs->ascent;
     TabPos=ztabl.Aktuell;
     SchattenBox(&win5[0],1,0,xp,yp,breit,hoch);}
   else {breit=F->len*spx+2*Schatten+3; hoch=spy-1;
     xp=F->x*spx-Schatten-2; yp-=Schatten+fs->ascent+2;
     XDrawRectangle(dpy,win5[0],gc[2],xp,yp,breit,hoch);}
 return 0;
}

/*=> X,Y-Position des Aktuellen Feldes im Alfa-Window ermitteln */
static void FeldPos(farbe,x,y,TabPos) int farbe, *x,*y,*TabPos;
{int Relativ=(*TabPos-ztabl.Top);
 if (Feld>=Tabelle)
    {if (Relativ>=MaxTabelle) *TabPos=ztabl.Top+MaxTabelle-1;
        else if (Relativ<0) *TabPos=ztabl.Top;
     c=F->t+(*TabPos*160); if (Feld==Felder) c+=TF0;
     *y=Ytab*spy+(*TabPos-ztabl.Top)*spt;}
  else {c=F->t; *y=F->y*spy;}
 *x=(F->x+Spalte)*spx; if (F->typ<1 || F->typ>7) return;
 if (F->typ==6) XDrawImageString(dpy,win5[0],gc[farbe],*x,*y,"*",1);
    else XDrawImageString(dpy,win5[0],gc[farbe],*x,*y,&c[Spalte],1);
}

/*=> Farben mit Wert-Geber veraendert */
extern void FarbenMod(rgb, wert) int rgb, wert;
{cpunit.RGB[BFarbe][rgb]=wert;
 Ftab[0][9].red  =(cpunit.RGB[BFarbe][0])*652.8;
 Ftab[0][9].green=(cpunit.RGB[BFarbe][1])*652.8;
 Ftab[0][9].blue =(cpunit.RGB[BFarbe][2])*652.8;
 j=FarbeNeu(0,9);

 FarbBeispiel(24, 4, 3, 13);
 XSetForeground(dpy,gc[13],Ftab[0][9].pixel);
 XFillPolygon(dpy,*w,gc[13],pt,ptAnz,Complex,0);
}

/*=> Achsen-Kreuz Graphik Ausgabe */
extern void xpline(X,Y,ixyz) float X[2],Y[2]; int *ixyz;
{static char xyz[3]={'X','Y','Z'};
 pt[0].x=X[0]; pt[1].x=X[1];
 pt[0].y=Y[0]; pt[1].y=2*Y[0]-Y[1];
 XDrawLines(dpy,*pw,gc[1],pt,2,0);
 XDrawImageString(dpy,*pw, gc[*ixyz+2], pt[1].x,pt[1].y, &xyz[*ixyz], 1);
}

/*=> Wert eines Sliders ermitteln */
static int WertGeber(nach,d,text, lg,xp,yp)
char *text; int nach,lg,xp,yp; Drawable *d;
{int i,x,breit,knopf,wert,von,bis,xyz,Rand=(Schatten)?Schatten:1,
 move=nach, xwt,xw,yw,ywOU, xa,ya,hoch,wcopy=0, ybox=yp-fs->ascent-1;
 char fmtl=text[1]-'0', fbeg=2+3*fmtl,z,fmt[10]="%*d%*d%*d",
 fmtw[4]="%*d",*tknopf=(&text[fbeg]); float xbeg,ybeg;

 for (knopf=lg-fbeg; knopf && *(tknopf+knopf)!='$'; knopf--);
 if (!knopf) knopf=3;
 fmtw[1]=fmt[1]=fmt[4]=fmt[7]=text[1];
 for (i=2; i<fbeg; i++) if (text[i]=='-' && i<2+fmtl)
     {text[i]='0'; text[2]='-';} else if (text[i]==' ') text[i]='0';
 sscanf(&text[2],fmt,&wert,&von,&bis);

 /* Wert-Ausgabe-Position ermitteln */
 if (nach || text[0]=='I' || text[0]=='A') switch (text[0])
    {case 'O': ywOU=yw=yp-fs->ascent-Rand-spy; move=(-1); break;
     case 'U': ywOU=yw=yp+fs->descent+Rand+1;  move=(-1); break;
     case 'I': yw=yp; knopf=fmtl; tknopf=(&text[2]); move=(-1); break;
     case 'C': Feld=nach; FeldWechsel(-1,0);
       if (tknopf[0]=='R') move=(-4);
          else if (tknopf[0]=='G') move=(-3);
          else if (tknopf[0]=='B') move=(-2); break;
     case 'A': if (nach) {Feld=nach; FeldWechsel(-1,0);}
       xa=50*spx; ya=9.2*spy+2; hoch=spy*4+Rand;
       SchattenBox(p, 1, 1, xa,ya, hoch, hoch);
       xbeg=(xa--)+2*spy; ybeg=(ya--)+2*spy+2; hoch+=2;
       if (tknopf[0]=='X') move=(-5);
          else if (tknopf[0]=='Y') move=(-6);
          else if (tknopf[0]=='Z') move=(-7);
       if (nach) xyz=4+move; else xyz=0; break;
     case 'N': Feld=nach; FeldWechsel(Feld,0); break;
     case 'L': Feld=nach; FeldWechsel(-1,0); break;
    }
 if (!nach) SchattenBox(p, Rand, 1,
      xp-Rand,ybox-Rand, lg*spx+2*Rand+3, spt+2*Rand-1);

 x=ev.xbutton.x; z=text[2+fmtl]; 
 if (text[0]!='O' && text[0]!='U' && text[0]!='I') wcopy=move!=(-1);
 if (nach) {xw=F->x*spx; yw=F->y*spy;
     if (wcopy && c[fmtl]==' ') for (i=fmtl; i<F->len; i++) c[i]=' ';
     if (Feld>=Tabelle) FeldPos(Farbe,&xwt,&yw,&ztabl.Aktuell);}
 do {if (nach) wert=von+(bis-von)*(x-xp)/(((float)lg-.5*knopf)*spx);
     if (wert<von) wert=von; else if (wert>bis) wert=bis;
     x=xp+(wert-von)*((float)(lg-knopf)*spx)/(bis-von)+3;
     XFillRectangle(dpy,*d, gc[12], xp+1, ybox, lg*spx+3,spt);
     if (nach) {sprintf(&text[2],fmtw,wert); text[2+fmtl]=z;}
     XDrawImageString(dpy, *d, gc[1], x, yp, tknopf, knopf);
     SchattenBox(d, 2, 0, x-1,ybox, knopf*spx+1, spt-2);
     if (move==(-7)) winpik(&xbeg, &ybeg, &xyz, &wert);
     if (!nach) return 0;
     if (move<-4)
        {XFillRectangle(dpy, *p, gc[0], xa+2,ya+2, hoch-4,hoch-4);
         if (ev.xbutton.button==3) xyz-=10;
         winpik(&xbeg, &ybeg, &xyz, &wert);
         XCopyArea(dpy, *p,*w, gc[1], xa,ya, hoch,hoch, xa,ya);}
      else if (move<-1) FarbenMod(4+move,wert);
      else if (text[0]=='O' || text[0]=='U')
        {PopKasten(1, x, ywOU, &text[2], 1,fmtl); wcopy=0;}
     if (wcopy) {for (i=0;i<fmtl;i++){c[i]=text[i+2];if (c[i]==' ')c[i]='0';}
         if (F->typ>0 && F->typ<6) LinksShift(c, F->len);
         XDrawImageString(dpy, *d, gc[Farbe], xw, yw, c, F->len);}
     Ereignis(1); x=ev.xmotion.x;
    } while(ev.type==MotionNotify);
 if (text[0]=='O' || text[0]=='U') PopKasten(-1, 0,0," ",0,0);
 XCopyArea(dpy,*w,*p,gc[1], xp,ybox, lg*spx, spt-1, xp,ybox);
 if (move<-1 && move>-5) return move-100; else return 0;
}

/*=> Pop-Up-Menue anzeigen */
static int PopUpMenu(pos,xp,yp,m) int pos,xp,yp,m;
{int next=0,ret=0,xpi,ypi=yp,top,ytop=0,ypop=ft[m].y,shift=ev.xmotion.x>xp,
 ymax=H[iWin]*((shift)?.8:.9)/spt,tmax=ft[m].y-ymax, xnext,l,lg,xl=0,line=(-1);
 char *tn; float scale=(float)(ft[m].y-ymax+2)/(ymax*spt); static int n=0; n++;

 if (W[iWin]<xp+(lg=ft[m].x*spx-1) && lg<W[iWin]/2) xp=W[iWin]-lg-1;
    else if (ev.xmotion.x+3*spx<xp) xp=ev.xmotion.x+3*spx;
 if ((xnext=xp+0.5*ft[m].x*spx)>W[iWin]-lg) xnext=spx; xl=xp/spx;
 if (pos<0) {pos=0; yp+=spt; xp+=1; goto Anf;}
    else if (!shift) {j=(yp/spt>ft[m].len) ? ft[m].len : yp/spt; yp-=spt*j;
     if (ft[m].len>j && tmax<0) ft[m].len=j; ytop=ft[m].len-j; ypop=ft[m].y-ytop;
     if (spt*ypop>H[iWin]) goto Anf;}
    else if (ft[m].y <= ymax) yp-=ft[m].len*spt;
    else {ypop=ymax; yp-=ft[m].len/scale;}
 if (yp > (j=H[iWin]-ypop*spt)) yp=j; else if (yp<0) yp=0;
 if (ft[m].y > ymax && (ytop=(ypi-yp)*scale)>tmax) ytop=tmax;
 Anf: xpi=xp-1; ypi=yp+1; PopKasten(0,xp,yp,ft[m].t+ytop*ft[m].x,ypop,ft[m].x);
 if (ev.type==ButtonRelease) goto Ret;
 do {if (line != -1) SchattenBox(w,2,2, xpi,ypi+line*spt, lg,spt-1);
     if (pos && ev.xmotion.x<xpi) goto Ret;
     if ((l=ev.xmotion.x/spx)>xl) xl=l;
     if (ev.xmotion.y<ypi||ev.xmotion.y>ypi+ypop*spt-1||
         ev.xmotion.x<xpi) {line=(-1); if (pos) goto Ret;}
        else if (ft[m].y > ypop && (top=(ev.xmotion.y-yp)*scale) != ytop
                 && top<=tmax && shift) {ytop=top; line=(-1); goto Anf;}
        else line=(ev.xmotion.y-ypi)/spt;
     if (l<xl-2 && n-1){line=(-1); if (pos) goto Ret;}
     if (line != -1) SchattenBox(w,2,0, xpi,ypi+line*spt, lg,spt-1);
     if (*(tn=ft[m].t+(ytop+line+1)*ft[m].x-3)=='>' && ev.xmotion.x>xnext && n<9) 
        {if (*(++tn)=='+') next=m+(*(++tn)-'0');
            else if (*tn=='-') next=m-(*(++tn)-'0');
            else {sscanf(tn, "%2d", &next);if (!next||next>Felder) goto Ret;}
         if (ret=PopUpMenu(pos+ft[m].x, xnext, yp+line*spt, next)) goto Ret;
         if (ev.type!=ButtonRelease) Ereignis(2);
         xl=ev.xmotion.x/spx; goto Anf;
        } Ereignis(2);
    } while(ev.type==MotionNotify);
 Ret: PopKasten(-1,xp,yp," ",0,0); if (n) n--;
 if (test) printf(" PopMen:%d/%d,%d,y:%d\n",m,ft[m].typ,ft[m].len,ft[m].y);
 if (line == -1) return ret; else ft[m].len=line+ytop;
 if (ev.type==ButtonRelease) strncpy
  (Mg+pos, ft[m].t+ft[m].len*ft[m].x, ft[m].x);
 if (test) printf(" T:%d, %.*s",ft[m].len,20,Mg);
 if (pos) return ret; else if (ft[m].typ<-1) return ft[m].typ;
 Feld=m+1; F=&ft[Feld]; lg=F->len; Spalte=0;
 if (F->typ>7) {strncpy(F->t, Mg, lg); 
     TextPos(F->t, lg, F->x*spx, F->y*spy,1,9);}
 else {FeldPos(0,&xp,&yp,&ztabl.Aktuell); strncpy(c, Mg, lg);
     TextPos(c, lg, xp, yp, F->typ, 0);}
 for (j=0; j<80; j++) Mg[j]=' ';
 if (Feld>=Tabelle) ztabl.ATAB[ztabl.Aktuell][ModiPos]='!';
 j=0; xcpmsg(&j); return FeldWechsel(Feld,-2);
}

/*=> Tabellen Texte ausgeben */
static void TabellenText(MaxT,ypos,pos) int MaxT,ypos,pos;
{while(MaxT){int i,j,k,tpos;
   for (j=Tabelle;j<=Felder;j++)if (ft[j].typ>0)
        {if (ft[j].typ>0 && ft[j].typ<6) 
             if (j>Tabelle) LinksShift(ft[j].t+pos, ft[j].len);
           else if (ft[j].typ>=8 || ft[j].typ<0) continue;
         if (j==Felder) tpos=pos+TF0; else tpos=pos;
         if ((k=j)==Tabelle)
            {for (i=ft[j].len; i && *(ft[j].t+pos+i-1)==' '; i--);
             if (!i && ft[j].len<=ft[0].len) {k=0;tpos=pos+ft[k].len-ft[j].len;}}
         TextPos(ft[k].t+tpos, ft[j].len, ft[k].x*spx, ypos, ft[k].typ,0);
        }ypos+=spt; MaxT--; pos+=160;
   } return;  
}

/*=> Tabelle neu aufbauen */
static int TabelleNeu(offset) int offset;
{static int i=0,j,delta,Opos,MaxT,xp,yp,pos,BarBreite=0,hoch,lang,yBar;
 int x,y,ypos=Ytab*spy,sp=(offset-5)?sph:spx, Rand=(Schatten)?Schatten:1;
 MaxTabelle=MaxT=(H[0]-ypos)/spt;
 if (MaxT<1) {if (!offset) return 1; else return -offset;}
 if (!BarBreite && offset==2) return 0;

 /* Tabellen-Anfang vom Scroll-Balken ermitteln */
 if (offset==2)
    {delta=ev.xbutton.y-yBar; lang+=1;
     if (delta<0) delta=0; else if (delta>BarBreite) delta=BarBreite;
     pos=ev.xbutton.y-delta; pw=w; Opos=ztabl.Top;
     if (ztabl.Top+MaxT>ztabl.Max) MaxTabelle=MaxT=ztabl.Max-ztabl.Top;
     do {if (pos >= yp && pos <= yp+hoch)
           {ztabl.Top=(ztabl.Max-MaxT)*(pos-yp)/hoch;
            if (ztabl.Top < 0) ztabl.Top=0;
            if (ztabl.Top != Opos) {Opos=ztabl.Top;
               TabellenText(MaxT,ypos,pos=ztabl.Top*160);
               XFillRectangle(dpy,*pw,gc[12],xp,yp,lang,hoch+BarBreite+1);
               yBar=yp+hoch*ztabl.Top/(ztabl.Max-MaxT);
               XFillRectangle(dpy,*pw,gc[2], xp,yBar, lang, BarBreite);
               SchattenBox(pw, Rand, 0, xp, yBar, lang, BarBreite);}}
         Ereignis(3);
         if ((j=ev.xmotion.y-delta) < yp && j != yp) pos=yp;
            else if (j > yp+hoch && j != yp+hoch) pos=yp+hoch;
            else pos=j;
        } while(ev.type==MotionNotify);
     pw=p; MaxTabelle=MaxT=(H[0]-ypos)/spt;
    }
  else if (offset>4 && ev.xbutton.button<4)
  {if (ypos-spt>y4 && offset==6) return -offset;
   if (offset<7) {if (abs(ev.xmotion.x-x4)<sp) return 0;
      if (!TF1 || Feld!=Felder) return -offset;}
   if (offset==7) {if (abs(ev.xmotion.y-y4)<spt) return 0;
       ztabl.Top+=(y4-ev.xmotion.y)/spt;}
   i=(x4-ev.xmotion.x)/sp; x4=ev.xmotion.x; y4=ev.xmotion.y;
   if (offset<7) {j=TF0+i; if ((Spalte-=i)<0) Spalte=0;
      if (test) printf(" TB-o=%d x:%d,%d, i=%d/%d\n",offset,Spalte,TF0,i,j);
      if (offset==5) j=(Spalte<=0)?TF0-1:(Spalte>=ft[Felder].len)?TF0+1:TF0;
        else i=0; if (Spalte>=ft[Felder].len) Spalte=ft[Felder].len-1;
   if (offset<7) TF0=(j>TF1)?TF1:(j<1)?0:j;}}
  else if (offset>3) ztabl.Top+=ev.xbutton.button*2-9;
  else if (offset<-1); else if (offset) ztabl.Top+=offset*(1+hoch/spt*0.75);
 if (ztabl.Top<0 || ztabl.Top>=ztabl.Max) ztabl.Top=0;
  else if (ztabl.Top>ztabl.Aktuell) ztabl.Aktuell=ztabl.Top;
  else if (ztabl.Aktuell-ztabl.Top>MaxT) ztabl.Aktuell=ztabl.Top;
 if (ztabl.Top+MaxT>ztabl.Max) MaxTabelle=MaxT=ztabl.Max-ztabl.Top;
 if (offset>3) {sprintf(Mg,"Pos:%d/%d [%d to %d of %d] ",
     Spalte+TF0+1,ztabl.Aktuell+1,TF0+1,ft[Felder].len+TF0,I82);}
 hoch=MaxT*spt+2*Rand;

 /* Tabellen-Relief erstellen */
 yp=ypos-Rand-fs->ascent-1;
 XFillRectangle(dpy, *p, gc[0], 0,yp, W[0], H[0]-yp);
 for (j=Tabelle;j<=Felder;j++)
       if(ft[j].typ<8 && ft[j].typ>=0) SchattenBox(p,Rand,(ft[j-1].typ>=0),
          ft[j].x*spx-Rand-1, yp, ft[j].len*spx+2*Rand+2, hoch);
 
 /* Scroll-Balken erstellen */
 if (MaxT < ztabl.Max)
    {BarBreite=hoch*MaxT/ztabl.Max;
     if (BarBreite<spx) BarBreite=spx;
     xp=(i82-2)*spx+Rand-2; lang=2*(spx-Rand);
     XFillRectangle(dpy,*p,gc[12], xp,yp, lang, hoch);
     SchattenBox(p, Rand, 1, xp-Rand, yp, lang+2*Rand, hoch);
     yp+=Rand; hoch-=2*Rand+BarBreite;
     yBar=yp+hoch*ztabl.Top/(ztabl.Max-MaxT);
     XFillRectangle(dpy,*p,gc[0], xp,yBar, lang, BarBreite);
     SchattenBox(p, Rand, 0, xp, yBar, lang, BarBreite);
    } else BarBreite=0;

 /* Tabelle mit Daten fuellen */
 if (offset==5 && i) {if ((i=j=Spalte+TF0-Sp0)<0) i=-j; if (j<0) j=0;
     sprintf(&Mg[strlen(Mg)],"CP:%d-%d (%d)",Spalte-j+1,Spalte-j+i,i);} else i=0;
 TabellenText(MaxT,ypos,pos=ztabl.Top*160); xcpmsg(&iWin);
 if (i) {FeldPos(9,&x,&y,&ztabl.Aktuell); iSp=i; jSp=j;
     XDrawImageString(dpy,*w,gc[0],x-jSp*spx,y,&c[Spalte-jSp],iSp);}
 return FeldWechsel(Feld,-2);
}

/*=> Tastatur-Eingabe verarbeiten ?*/
static int TastenKlick()
{char z; int j,xp,yp,lg,offset=0,IR,KC=0;
 KeySym keys; XComposeStatus comp;
 if (iWin) {iWin=0; w=(&win5[0]); pw=p=(&pix5[0]);}
 ASCII=XLookupString(&ev.xkey,&z,1,&keys,&comp);
 FeldPos(Farbe,&xp,&yp,&ztabl.Aktuell); lg=F->len;
 ASCII=XLookupString(&ev.xkey,&z,1,&keys,&comp);
 if (CursorRechts == 255 && (keys=XLookupKeysym(&ev.xkey,0))) 
  switch (keys & XK_VoidSymbol)
    {case XK_Left     : KC=CursorLinks; break;
     case XK_Right    : KC=CursorRechts; break;
     case XK_Up       : KC=CursorOben; break;
     case XK_Down     : KC=CursorUnten; break;
     case XK_Page_Up  : KC=BildOben; break;
     case XK_Page_Down: KC=BildUnten; break;
     case XK_Tab      : KC=Tabulator; break;
     case XK_Insert   : KC=Einfuegen1; break;
     case XK_End      : KC=DeleteFeld; break;
     case XK_Home     : KC=Selektieren; break;
     case XK_Escape   : KC=Suchen; break;
     case XK_Delete   : KC=ZeichenDel; break;
     case XK_F1       : KC=Hilfe1; break;
     case XK_F2       : KC=SetUpTaste; break;
     case XK_F3       : KC=Pf3; break;
     case XK_F4       : KC=TestTaste; break;
     case XK_BackSpace: KC=ZeichenBs; break;}
 if (KC==0) KC=ev.xkey.keycode;
 if (test) printf("Key code:%d state:%d AscII:%d/%d Sp:%d c=<%.*s>%d %s\n",
    KC,ev.xkey.state,ASCII,z,Spalte,lg,c,Farbe,XKeysymToString(keys));

 /* Taste mit gedruecktem Umschalter (z.B. Ctrl) */
 if (ev.xkey.state>1) {
   if (KC==Tabulator || KC==CursorLinks){Feld--; return FeldWechsel(Feld,0);}
   if (KC==CursorRechts && Feld<Felder) {Feld++; return FeldWechsel(Feld,0);}}

 if (KC==CursorRechts) {if (Spalte<lg-1) Spalte++; goto Ok;}
 if (KC==CursorLinks) {if (Spalte) Spalte--; goto Ok;}
 if (KC==ZeichenBs) {if (Spalte==0) goto Ok; Spalte--;
      for (j=Spalte; j<lg; j++) c[j]=c[j+1];
           xp-=spx; c[lg-1]=' '; lg-=Spalte; goto Pop;}
 if (KC==BildOben)  return TabelleNeu(-1);
 if (KC==BildUnten) return TabelleNeu( 1);
 if (KC==Pf3) return 8;
 if (KC==Hilfe1 || KC==Hilfe2) return 7;
 if (KC==SetUpTaste) {setupissy(&SetupLeg,&IR); return IR;}
 if (KC==TestTaste) {test=1-test; goto Ok;}
 if (KC==DeleteFeld)
     {for (j=Spalte; j<lg; j++) c[j]=' ';lg-=Spalte; goto Pop;}
 if (KC==Suchen) {while(Spalte<lg) if (c[++Spalte]==' ') goto Ok;}
 if (KC==Selektieren) return FeldWechsel(1,0);
 if (KC==ZeichenDel)
     {for (j=Spalte; j<lg; j++) c[j]=c[j+1];
           F->t[lg-1]=' '; lg-=Spalte; goto Pop;}
 if (KC==CursorOben)
     {if (Feld<Tabelle) return FeldWechsel(-1,0);
          else if (ztabl.Aktuell>ztabl.Top) ztabl.Aktuell--;
          else ztabl.Aktuell=ztabl.Top+MaxTabelle;
       return FeldWechsel(Feld,Spalte);}
 if (KC==CursorUnten)
     {if (Feld<Tabelle) return FeldWechsel(0,0);
          else if (ztabl.Aktuell+1<ztabl.Top+MaxTabelle) ztabl.Aktuell++;
          else ztabl.Aktuell=ztabl.Top;
       return FeldWechsel(Feld,Spalte);}
 if (KC==Tabulator) {if (Feld<Felder) Feld++; return FeldWechsel(Feld,0);}
 if (KC==Einfuegen1 || KC==Einfuegen2)
     {if (Einfueg<2) Einfueg=1-Einfueg; return FeldWechsel(Feld,-1);}

 if (z==Eingabe) return 5;
 if (!ASCII) goto Ok;
 if (!Einfueg) lg=1;
    else {for (j=lg-1; j>Spalte; j--) c[j]=c[j-1]; lg-=Spalte;}
 if (F->typ>2 && F->typ<5) c[Spalte]=toupper(z); else c[Spalte]=z;
 if (F->typ>0 && F->typ<6 && c[0]==' ')
    {lg=F->len; Spalte=0; xp=F->x*spx; LinksShift(c, lg);}
 if (Spalte<F->len-1) offset=1;

 Pop:/* Teil-Kette in Window und Pixmax ausgeben */
 if (Feld>=Tabelle) ztabl.ATAB[ztabl.Aktuell][ModiPos]='!';
 if (F->typ==6) XDrawImageString(dpy, *w, gc[Farbe], xp, yp, "*", 1);
  else {XDrawImageString(dpy, *w, gc[Farbe], xp, yp, &c[Spalte], lg);
        XDrawImageString(dpy, *p, gc[Farbe], xp, yp, &c[Spalte], lg);}
 Spalte+=offset;
 Ok: FeldPos(0,&xp,&yp,&ztabl.Aktuell); return 0;
}

/*=> Maus-Taste gedrueckt */
static int MausKlick(int button)
{static int i,j,l,n=1,Ja,JaNein,IR,breit,hoch,PopRet,PopTyp;
 int k=button,xp=ev.xbutton.x,yp=ev.xbutton.y,yl=(yp-5)/spy+1,xl=xp/spx,
  J01=0,m=ztabl.Top+(yp-5-(Ytab-1)*spy)/spt;
 float xleg,yleg; XWindowAttributes aXWAtt; static char XPM[]="issy0.xpm";

 if (ev.type==ButtonPress) {x4=xp; y4=yp;}
 if (iWin) /* Maus-Taste in einem Graphik-Window gedrueckt */
    {if (abs(x4-ev.xmotion.x)<spx && k==1) return 0; n=iWin;
     if (k<3||k==7) return RechteckZiehen(); if (k==6) goto Ok;
     xleg=ZoomX+(float)xp/U; yleg=ZoomY-(float)yp/U;
     xp-=2*spx; yp-=Schatten+fs->ascent;
     if (czoom.ZM) strncpy(ft[MaxFelder].t, "Reset    ",9);
        else strncpy(ft[MaxFelder].t, "Plot Outp",9);
     if (!PopUpMenu(0,xp,yp, MaxFelder)) return 0;
     if (ft[MaxFelder].len) return PikWindow(xleg, yleg,
         ft[MaxFelder+ft[MaxFelder].len].len+1);
        else if (czoom.ZM) czoom.ZM=0;
        else {plparm.NWIN=(-plparm.NWIN); plparm.IWK=0;} return iWin;}
   else if (ev.type==ButtonRelease && (k>1 || !j));
   else if (ev.type==ButtonRelease) {DopplP[0]=j; DopplP[1]=xl-ft[j].x;
     DopplP[2]=ztabl.Aktuell=m; return FeldWechsel(j,DopplP[1]);}

 /*  Maus-Taste im Alpha-Window gedrueckt */
 if (yl==3 && xl>=(i82-7) && Einfueg<2) {Einfueg=1-Einfueg;
     if (button>=3) test=1-test; return FeldWechsel(Feld,-1);}
 if (yl>=Ytab && xl>=(i82-2)) return TabelleNeu(2);
    else if (yl>=Ytab && ev.type==4 && (j=ev.xbutton.button)>3) return TabelleNeu(j);
 for (j=1;j<=Felder;j++) 
   {if (xl<ft[j].x || ft[j].typ<0) continue;
    if (ft[j].t[0]==IconS) {if (xl>=ft[j].x+4) continue;
        if (yl==ft[j].y || yl==ft[j].y+1) goto Ok; continue;}
    if (xl>=ft[j].x+ft[j].len) continue; if (yl<Ytab && j>=Tabelle) break; 
    if (j<Tabelle) {if (yl==ft[j].y) goto Ok;} else goto Ok;
   } j=0; if (button<3) return 0; if (button>5) goto Ok;

 /* Apply/Exit/Setup etc.Knopf-Feld selektiert */
 if (PopUpMenu(0,xp,yp, i=MaxFelder+3))
    {n=ft[i+1].len; if (test) printf("Pop>%.12s<%.6s>%d,%d\n",Mg,P0P,ft[i].len,n);
     switch (ft[i].len){case 0: return 5; 
     case 1: return (P0P[6]=='E')?8:0; 
     case 2: {if (P0P[0]=='A') strncpy(P0P,"Copy  Paste Find  ",18);
      else if (P0P[0]=='C') strncpy(P0P,"Erase Find  Apply ",18);
      else strncpy(P0P,"Apply Exit  Copy  ",18); return 0;}
     case 3: if (Mg[6]==' ' || iFont==n) setupissy(&SetupLeg,&IR);
      else {IR=6;if (Mg[13]!=' ') IR=ft[i+2].len+1;
            else if (n<3) iFont=n; else if (n>5) {i82=l82; demo=0;}
            else {k=-H[6]*.4; l=-W[6]*.4; demo=(n==4)?1:(k>iPS)?k:(l>iPS)?l:iPS;}
           } if (IR==6) W[0]=0; return IR;}
     if (pix5[k])
       {if (test) printf("Get Image Win:%d %d %d\n",k,W[k],H[k]);
        if (!XGetWindowAttributes (dpy, win5[k], &aXWAtt)) return 0;
        if (k==4) aXWAtt.width=MaxIcon*xicon;
        img=XGetImage(dpy,pix5[k],0,0,aXWAtt.width,aXWAtt.height,AllPlanes,ZPixmap);
        if (test) printf("I.xpm:%d %d %d\n",k,aXWAtt.width,aXWAtt.height);
        XpmWriteFileFromImage (dpy, XPM, img, NULL, NULL); XPM[4]++;
       } 
    } return 0;

 /* finger/mouse management of windows 0-3 MotionNotify=6 */
 Ok: if (k<4 && (j!=Feld || ft[j-1].typ<0)) 
 {if (j>Tabelle) ztabl.Aktuell=m; FeldWechsel(j,xl-ft[j].x);}
 if (k>5 || (k==5 && j==Felder /*&& P0P[0]=='C'*/))
 {XMapRaised(dpy,win5[iWin]); if(j==Felder) Feld=j; Sp0=Spalte+TF0;
  if (TF0>TF1) TF0=TF1; i=l=n; xleg=1.-(float)(W[0]-x4)/W[0];
  if (iWin) n=iWin; else if (button==6) while(W[n]<=0||l==n)
   {if (++n>3) n=1; if (n==l)break;} i=n; if (!W[l]) l=i;
  do{Ereignis(k); if (ev.type==6) if (!iWin && k>=0) k=TabelleNeu(button); else
     {j=W[6]-W[iWin]; XTranslateCoordinates(dpy,win5[iWin],DefaultRootWindow(dpy),
      ev.xmotion.x-x4,ev.xmotion.y-y4-spy,&xp,&yp,&m);
      if (iWin) {j=0;goto G;}
      if(j<0) {if(xp<j) xp=j; else if(xp>0) xp=0;}
         else {if(xp<0) xp=0; else if(xp+W[0]>W[6]) xp=j;} j=H[6]-H[0];
      if(j<0) {if(yp<j) yp=j; else if(yp>0) yp=0;}
         else {if(yp<0) yp=0; else if(yp+H[0]>H[6]) yp=j;} j=0;
      if(xp==0 && k==-6) {if (TF0==TF1 && TF0) {k=-6;x4=ev.xmotion.x;}
         else if (W[n]>0) j=W[0]-(float)(x4-ev.xmotion.x)/xleg;}
      if(l!=n && (j>W[0]&&i==n || j<W[0]&&i==l))
        {XUnmapWindow(dpy,win5[i]); i=(i==l)?n:l;}
      if (j>W[0]) {j-=W[0]+W[i]; if(j>0) j=(-1);}
    G:if(!j) XMoveResizeWindow(dpy,win5[iWin],xp,yp,W[iWin],H[iWin]);
       else {XMapRaised(dpy,win5[i]);XMoveResizeWindow(dpy,win5[i],j,0,W[i],H[i]);}
      if (k==-6 && x4-ev.xmotion.x>spx*5 && TF0>0) TF0=TF0;
    }}while(ev.type!=ButtonRelease);
  if (k==-6 && W[n]>0 && abs(j)*2>W[0]) XUnmapWindow(dpy,win5[i]);
//printf("1=>j/Feld:%d/%d k=%d %d = %d\n",j,Feld,k,button,ft[j-1].typ);
  if (k<0 && !iWin) XLowerWindow(dpy,win5[0]); return 0;
 }

 /* Pop-Menue des Alfa-Feldes selektiert */
 if (ft[j].t[0]==IconS) l=3; else l=ft[j].len;
 if (ft[j].typ==12 && ft[j].t[ft[j].len]=='P') PopTyp=(-1);
    else PopTyp=ft[j-1].typ<0 && k>=3;
 if (test) printf("MB>%.*s<j/k:%d/%d t=%d %d\n",l,ft[j].t,j,k,ft[j].typ,PopTyp);
 if (PopTyp)
    {if (j<Tabelle) yp=ft[j].y*spy;
        else yp=Ytab*spy+(ztabl.Aktuell-ztabl.Top)*spt;
     xp=(ft[j].x+(PopTyp+1)*0.25*ft[j].len)*spx;
     if ((PopRet=PopUpMenu(PopTyp-1,xp,yp-Schatten-fs->ascent, j-1))
         && j>=Tabelle) ztabl.ATAB[ztabl.Aktuell][ModiPos]='!';
     return (PopRet < -1) ? PopRet+1 : 0;
    }
 else if (ft[j].typ>=10) /* Buttom selected */
    {xp=ft[j].x*spx-Schatten-1; yp=ft[j].y*spy-Schatten-fs->ascent-1;
     if (ft[j].t[0]==IconS) {breit=spx*5-4;hoch=spy*2-2;}
         else {breit=ft[j].len*spx+2*Schatten+1; hoch=spy-3;}
     if (ft[j].typ==12 && ft[j].t[l]!='1') J01=1;
     do {Ja=1-J01;
         if (xl<ft[j].x || yl<ft[j].y) Ja=J01;
            else if (ft[j].t[0]==IconS) 
             {if (xl>ft[j].x+4 || yl>ft[j].y+1) Ja=J01;}
            else if (xl>=ft[j].x+ft[j].len || yl != ft[j].y) Ja=J01;
         if (ft[j].typ==12) JaNein=1-Ja; else JaNein=Ja;
         SchattenBox(w, Schatten, JaNein, xp,yp, breit, hoch);
         Ereignis(4); xl=ev.xbutton.x/spx; yl=(ev.xbutton.y-5)/spy+1;
         if (!JaNein && ft[j-1].typ<0) {k=3; goto Ok;}
        }while(ev.type == MotionNotify);
     if (ft[j].t[0]==IconS && ft[j].t[2]=='.') 
         strncpy(Mg,&ft[j].t[3],2);
     if (ft[j].typ==12) ft[j].t[l]='1'-Ja; 
     if (Ja) return ft[j].typ-12; else return 0;
    }
 else if (ft[j].typ==8) /* Slider selected */
    return WertGeber(j,w,ft[j].t,ft[j].len,ft[j].x*spx-1,ft[j].y*spy); 

 else if (ev.xbutton.button>1) return MausKopie(j,xl-ft[j].x);

 /* Alpha-Input selected */
 if (DopplP[0]!=j || DopplP[1]!=xl-ft[j].x || DopplP[2]!=ztabl.Aktuell) 
    {DopplP[0] =j;   DopplP[1] =xl-ft[j].x;   DopplP[2] =ztabl.Aktuell;}
    else if (Doppl) {strncpy(Mg,c,ft[j].len);
         for (k=ft[j].len; k<80; k++) Mg[k]=' '; return 1000+j;}
    else {XDrawImageString(dpy,win5[0],gc[2], spx,3*spy,
        "Double click not supported   ", 28);} return 0;
}

/*=> cut/past by mouse (MB2/MB3) or past from external window */
static int MausKopie(j,pos) int j,pos;
{static int xp,yp,lg,i,lFmt; Atom lType,lLeft;
 if (j) {FeldWechsel(j,pos);
         FeldPos(0,&xp,&yp,&ztabl.Aktuell);lg=F->len-Spalte;}
 if (test) printf("C/P MB%d len:%d %d\n",ev.xbutton.button,lg,j);

/* copy to clipboard */
 if (j && ev.xbutton.button == 2) {XConvertSelection
    (dpy, XA_PRIMARY,XA_STRING,lProp,*w, ev.xbutton.time); return 0;}

  else if (j && ev.xbutton.button == 3)              
    {for (; lg>0 && c[Spalte+lg-1] == ' '; lg--); if (lg <= 0) return 0;
     if (XGetSelectionOwner(dpy, XA_PRIMARY) == *w && Pufferl && xpl>0)
         XDrawImageString(dpy, *w, gc[Farbel], xpl, ypl, Puffer, Pufferl);
     XSetSelectionOwner(dpy, XA_PRIMARY, *w, ev.xbutton.time);
     XStoreBytes(dpy,Puffer=&c[Spalte],Pufferl=lg); Farbel=Farbe;
     if (test) printf("cut <%.*s>\n",lg,&c[Spalte]);
     XDrawImageString(dpy, *w, gc[0], xpl=xp, ypl=yp, &c[Spalte], lg);
    }
/* copy from clipboard */
  else if (ev.type==SelectionNotify) /* 31 */
   {if (xpl && (Puffer=XFetchBytes(dpy, &Pufferl)) && Pufferl > 0);
     else if (ev.xselection.selection == XA_PRIMARY &&
        ev.xselection.property == lProp &&
        (XGetWindowProperty(dpy, *w, lProp,0 ,1024,False, XA_STRING,
              &lType, &lFmt, (unsigned long*) &Pufferl, &lLeft, 
              (unsigned char **) &Puffer) == Success) &&
              lType == XA_STRING && Pufferl > 0);
     else if (Pufferl == 0) return 0; 
     if (Pufferl > lg) Pufferl=lg;
     if (Einfueg) 
        {for (i=Spalte+lg-1; i>=Spalte+Pufferl; i--) c[i]=c[i-Pufferl]; 
        if (Pufferl < lg) XDrawImageString(dpy, *w,
            gc[Farbe], xp, yp, &c[Spalte], lg);}      
     for (i=0; i<Pufferl; i++) c[i+Spalte]=Puffer[i]; 
     if (test) printf("paste:<%.*s> %d\n",Pufferl,Puffer,Pufferl);
     XSetSelectionOwner(dpy, XA_PRIMARY, None,CurrentTime);
     XDrawImageString(dpy, *w, gc[2], xp, yp, &c[Spalte], lg);
     XDrawImageString(dpy, *p, gc[Farbe], xp, yp, &c[Spalte], lg);
     if (Feld>=Tabelle) ztabl.ATAB[ztabl.Aktuell][ModiPos]='!';
   }

  else if (ev.type==SelectionClear) /* 29 */
   {if (ev.xselectionclear.window == *w &&
        ev.xselection.selection == XA_PRIMARY && Pufferl && xpl>0)
    XDrawImageString(dpy,*w,gc[Farbel],xpl,ypl,Puffer,Pufferl);
    xpl=0;}

  else if (ev.type==SelectionRequest) /* 30 */
   {XSelectionEvent lSE;
    lSE.type      = SelectionNotify;
    lSE.requestor = ev.xselectionrequest.requestor;
    lSE.selection = ev.xselectionrequest.selection;
    lSE.target    = ev.xselectionrequest.target;
    lSE.time      = ev.xselectionrequest.time;
    lSE.property  = ev.xselectionrequest.property;
    if (ev.xselectionrequest.selection == XA_PRIMARY)
        XChangeProperty(dpy, lSE.requestor, lSE.property, lSE.target, 8,
                        PropModeReplace, (unsigned char *) &c[Spalte],lg);
      else lSE.property = None;
    XSendEvent(dpy, lSE.requestor, False, 0, (XEvent *) &lSE);
   }
 return 0;
}

/*=> Rechteck mit der Maus ziehen */
static int RechteckZiehen()
{static int IJx[3]={1,2,2},IJy[3]={0,0,1};
 int ret=0, bewegt=0, MB12=ev.xbutton.button,xbb=x4,ybb=y4;
 float win1,win2,dx=kontur.Xmax-kontur.Xmin,dy=kontur.Ymax-kontur.Ymin,
  alfx=plparm.ALF[IJx[plparm.N1-1]]/90.,alfy=plparm.ALF[IJy[plparm.N1-1]]/90.;
 pt[0].x=pt[2].x=pt[1].x=pt[4].x=xbb; pt[0].y=pt[2].y=pt[3].y=pt[4].y=ybb;
 czoom.Xmin=ZoomX+(float)pt[2].x/U; czoom.Ymin=ZoomY-(float)pt[2].y/U;

 while (ev.type != ButtonRelease)
    {Ereignis(5); if (MB12==1 && ev.xbutton.button==2) bewegt=-4-iWin;
     if (ev.xbutton.button==3) bewegt=-4;
     if (ev.type !=  MotionNotify) continue;
     if (bewegt==1) XDrawLines(dpy,*w,gc[14],pt,5,0);
     pt[3].x=pt[2].x=ev.xmotion.x;
     pt[1].y=pt[2].y=ev.xmotion.y;

/* Dynamische Rotation */
     if (bewegt==-4) 
        {czoom.Xmax=ZoomX+(float)pt[2].x/U;
         czoom.Ymax=ZoomY-(float)pt[2].y/U;
         if (MB12==1) 
           {win1=(ev.xmotion.x*2-W[iWin])/((float)W[iWin]);
            win2=(ev.xmotion.y*2-H[iWin])/((float)H[iWin]);}
          else
           {win1=((pt[2].x-xbb)/((float)W[iWin])*2.+alfx);
            if (win1>2.) win1-=4; else if (win1<-2.) win1+=4;
            win2=((pt[2].y-ybb)/((float)H[iWin])*2.+alfy);
            if (win2>2.) win2-=4; else if (win2<-2.) win2+=4;}
         winpik(&win1, &win2, &bewegt, &ret);}

/* Translation im gezoomten Zustand 
        else if (bewegt<=-5 && czoom.RDY==0) 
        {win1=(ev.xmotion.x-xbb)/(W[iWin]*.9);
         win2=(ev.xmotion.y-ybb)/(H[iWin]*.9);
         czoom.Xmin=ZoomX-win1*DeltaX*.1; czoom.Ymin=ZoomY+win2*DeltaY*.1;
         czoom.Xmin=ZoomX; czoom.Ymin=ZoomY;
         czoom.Xmax=czoom.Xmin+DeltaX; czoom.Ymax=czoom.Ymin+DeltaY;
 printf("ZA:%f,%f >> %f,%f\n",win1*DeltaX,win2*DeltaY,DeltaX,DeltaY);
        if (fabs(win1)+fabs(win2)>.05) {xgrneu(&bewegt,&ret); if (ret) return 0;}
         }*/
        else if (bewegt<=-5) 
        {win1=dx*(W[iWin]-ev.xmotion.x)/(W[iWin]*.9);
         win2=dy*(H[iWin]-ev.xmotion.y)/(H[iWin]*.9); 
         czoom.Xmin=kontur.Xmax-win1; czoom.Ymin=kontur.Ymin+win2;
         czoom.Xmax=czoom.Xmin+DeltaX; czoom.Ymax=czoom.Ymin+DeltaY;
         xgrneu(&bewegt,&ret); if (ret) return 0;}

        else {XDrawLines(dpy,*w,gc[14],pt,5,0); bewegt=1;}
     if (Iicon>0) XCopyArea(dpy,*p,win5[0],gc[1],
         pt[2].x+X06,pt[2].y, xicon,yicon, 36*spx, 6*spy+8);
    }
 if (bewegt<=-4) return 0; if (bewegt) XDrawLines(dpy,*w,gc[14],pt,5,0);
 if (ev.xbutton.button==1 &&
    (pt[0].x==pt[2].x || pt[0].y==pt[2].y)) return 0;
 if (Iicon>0) {XCopyArea(dpy,*p,pix5[4],gc[1],
     pt[2].x,pt[2].y,xicon,yicon,(Iicon-1)*xicon,0); return 0;}

 /* Zoom-Koordinaten-Bereich ermitteln */
 if (pt[0].x < pt[2].x) j=0; else j=2;
 czoom.Xmin=ZoomX+(float)pt[j].x/U; czoom.Xmax=ZoomX+(float)pt[2-j].x/U;

 if (pt[0].y > pt[2].y) j=0; else j=2;
 czoom.Ymin=ZoomY-(float)pt[j].y/U; czoom.Ymax=ZoomY-(float)pt[2-j].y/U;
 if (ev.xbutton.button>1) return PikWindow(czoom.Xmin, czoom.Ymin, 24);
 if ((czoom.Ymax-czoom.Ymin)*U < H[iWin]*.05 &&
     (czoom.Xmax-czoom.Xmin)*U < W[iWin]*.05) return 0;
 czoom.ZM=1; return iWin;
}

/*=> Maus im Graphik-Window  */
static int PikWindow(xpik,ypik,MausTaste) int MausTaste; float xpik,ypik;
{int ret; if (test) printf("PikWI:%d,x/y=%.1f/%.1f\n",MausTaste,xpik,ypik);
 winpik(&xpik,&ypik,&MausTaste, &ret);
 XCopyArea(dpy,*p,*w,gc[1],0,0,W[iWin],H[iWin],0,0);
 if (Mg[0] != ' ' && !ret)
    {XDrawImageString(dpy,win5[0],gc[2], spx,3*spy, Mg, 74);
     for (j=0; j<80; j++) Mg[j]=' ';}
 if (test) printf("WinPik Ok:%d, %.*s>\n", ret,20,Mg);
 return ret;
}
/*=> LITTLE/BIG ENDIAN-Pruefung */
extern void checkconvert(char* DSN, char* cw, int* len, int* Ret)
{int16_t w; FILE* fd; DSN[*len]=0; fd=fopen(DSN,"r");*Ret=0;if (!fd) return;
 if (*cw == '!') {c=0;fread(&c,1,1,fd);w=c;} else fread(&w,sizeof(w),1,fd); 
 *Ret=ISWAP=(w)?1:2; fclose(fd); DSN[*len]=' ';
 if (test) printf("==>%.*s => %d,%d\n",*len,DSN,w,*Ret);}
extern void swapint(int *num, int *n)
{int j=*n,*m=num,tmp; char *i=(char*) &tmp, *o; if (ISWAP != 2) return;
 while (j){tmp=*m; o=(char*) m;
 o[0]=i[3]; o[1]=i[2]; o[2]=i[1]; o[3]=i[0];
 if (test) printf("==>%d %d %d %d\n",j,tmp,*m,ISWAP); j--; *m++;};}
