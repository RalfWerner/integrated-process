#include <X11/Xutil.h>
void WinNew(){;};void ColInfo(){;}; int x,y,x4,y4,xd,yd,i9=0,nw=
 PointerMotionMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask ;
#include <X11/cursorfont.h>
#include <X11/extensions/XInput2.h>
Display* dpy; Window wd,wx; XEvent ev; Screen *screen;int i,j,k,l,m=0,n;

int main(int n0,char** A) /* Open Display (connection to X-Server) */
{if (dpy=XOpenDisplay(0)) screen=XDefaultScreenOfDisplay(dpy);
 else{printf("can't open \"%s\"\n",XDisplayName(0)); return 1;} 
 printf("Screen:%dx%d ",XWidthOfScreen(screen),XHeightOfScreen(screen)); 
 int opcode=0,event=0,error,major=3,minor=9; wd=DefaultRootWindow(dpy);
 if (!XQueryExtension(dpy,"XInputExtension",&opcode,&event,&error)) 
  {printf("X Input extension not available.\n"); return 1;}
 if (XIQueryVersion(dpy,&major,&minor)==BadRequest)
  {printf("XI2 not available. Server %d.%d\n",major,minor); return 1;}

/* check devices for "XITouchClass" (8) types */
 XIEventMask masks[64]; unsigned char mask[8][XIMaskLen(XI_LASTEVENT)];
 memset(mask,0,sizeof(mask));
 printf("XI%d.%d opcode:%d ev:%d err:%d ",major,minor,opcode,event,error);
 XIDeviceInfo *info=XIQueryDevice(dpy,XIAllDevices,&n), *dev;
 printf("len=%d i=%d n=%d\n",sizeof(mask),XIAllMasterDevices,n);
 for (i=l=0;i<n;i++)
 {dev=&info[i]; if(m)printf("%2.d Dev-id:%d n/u %d/%d at:%d %s",i+1,
   dev->deviceid,dev->num_classes,dev->use,dev->attachment,dev->name);
  for (j=0;j<dev->num_classes;j++)
  {XITouchClassInfo* t=dev->classes[j];
   if(t->type==XITouchClass)
     {if(m)printf("\n type %d id %d %s %d touches",t->type,
      t->sourceid,(t->mode==XIDirectTouch)?"direct":"depend",k=t->num_touches);
      for(k=18;k<=21;k++) XISetMask(mask,k);/* Begin, Update, End */
      masks[l].deviceid=dev->deviceid;
      masks[l].mask_len=sizeof(mask); masks[l].mask=mask; l++;
     } else if(m)printf(" t(%d)=%d/%d",j+1,t->type,t->mode);
  } if(m)printf("\n");
 } XIFreeDeviceInfo(info);
 if (l) k=XISelectEvents(dpy,wd,masks,l);
  else printf("E=> XITouchClass missing\n");

/* exclusive Mouse pointer with Cursor 34 PointerMotionHintMask| return 1; */
 WinNew(A[1],600,600); j=XC_crosshair; float v;
 printf("\nLoop until point selected with MB3 k/l:%d/%d cursor=%d\n",k,l,j);
 do {if (j>0) {Cursor cursor=XCreateFontCursor(dpy,j); j=-j;
       k=XGrabPointer(dpy,wd,False,nw,GrabModeAsync,
         GrabModeAsync,wd,cursor,CurrentTime);
       if (k != GrabSuccess) {printf("can't grab the mouse %d\n",k); return 1;}}
     XNextEvent(dpy,&ev); xd=x-ev.xbutton.x; yd=y-ev.xbutton.y;
     x=ev.xbutton.x; y=ev.xbutton.y; v=sqrt(xd*xd+yd*yd);
     if (ev.type==6 && v>90.) printf(" v(%d,%d)=%d ", xd,yd,(int)v);
     if (ev.type==GenericEvent) {XGenericEventCookie* genev=&ev.xcookie;
       XGetEventData(dpy,genev); printf(" Gen->%d ext:%d data:%d",genev->evtype,
        ev.xcookie.extension,genev->data); XFreeEventData(dpy,genev);}
     if (i-ev.type) printf(" t->%d,x=%d,y=%d, MB%d/%d\n",ev.type,
     x,y,ev.xbutton.button,ev.xbutton.state);
     if ((i=ev.type)==ButtonPress) {x4=ev.xbutton.x_root; y4=ev.xbutton.y_root;}
     else if (ev.type == ButtonRelease){j=3-j-2*ev.xbutton.button;
      printf("Diff:%d,% x:d, y:%d, j:%d ",i9++,x-x4,y-y4,j);
      ColInfo(dpy,ev.xbutton.x_root,ev.xbutton.y_root); }
    } while (ev.type != ButtonRelease || ev.xbutton.button!=3);
 XUngrabPointer(dpy,CurrentTime); if (i9>7) return 9;
}
