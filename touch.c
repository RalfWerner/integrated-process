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
}
