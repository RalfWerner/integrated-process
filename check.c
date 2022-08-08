/* TEST head -n 9 check.c|grep -v grep >makefile gfortran needed for issy.f
LDFLAGS= -lX11 -lXpm -lXi -lxcb -lX11-xcb -lImlib2 -lm
.c.o: # rules to create executables (*.exe) from source (*.c) with "config"
	gcc -c -w -std=c99 $< -o $@ # libaries X11, xcb and Xpm are always expected
$U/check.exe: config.h check.o xinitn.o
	gcc check.o xinitn.o -lX11 -lXpm -lXi -lImlib2 -lm -o $@
$U/touch.exe: config.h touch.o #/home/.termux/termux.properties - here only TEST=1/2
	gcc touch.o -lX11 -lXpm -lXi -lxcb -lX11-xcb -lImlib2 -lm -o $@
config.h: # solve restrictions of environment= pkg i make clang xorgproto libxpm libxi -y
	printf '#define WITH_%s\n' 'XI2 // need Xi' 'IM2 // need Imlib2'> $@

$U/multi.exe: multi.o
	gcc multi.o -lX11 -lXi -lcairo -o $@
tkdiff check.c ../check.c
# see 
# files above and xinitn.c are needed to make *.exe with config=everything */
#define X_MAX 100000
#define X_MAX1 43
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xutil.h>
extern char issyimg[80]="-PMOD.xpm  ",cvers[16]="Setup ",cexcl[2]=" ",cfleg[80]=" ",
 eacom[176]=" ",comwin[120]="1.Grafic2.Grafic3.Graficcheck.c ",clegdf[3][80]=
 {"Lines   Points  Quad/RecTrias   Circles Text    Main->-1Sel.->+1Last >-0",
  "1/A gr. 2/B gr. 3/C gr. 4/D gr. 5/E gr. Cre.->-1Main->-2Last >+0Rotate  "};
extern struct {int LTEST,NPL,KP; float XY[4],Rest;} kontur={0,0,0,0,0,0,0,0,0};
extern struct {char TABLE[16];int WH[4];unsigned char LMSG[80];} pptab={" ",0,0,0,1," "};
extern struct {float XY[4],Hgrenz; int ZM,MaxI;} czoom={0,0,0,0,0,0,0};
extern struct {int IP,Dick[10],PAT,Gdick,RGB[12][3],Stil[11];} cpunit=
 {10,1,1,1,1,1,1,1,1,1,1,1,1, 90,90,80,0,0,0,80,0,0,0,50,0,0,0,100,60,0,60,
  80,0,80,0,90,50,100,100,0,100,50,0,0,100,100,0,0,0, 1,1,1,1,1,1,1,1,1,1,1};
extern struct {int NWIN,IWK; float AXLG,SHR,BUH; int NERG,N1,N2; float ALF[3];}
 plparm={1,1, 0,0,0, 0,0,0, 1,1,1}; unsigned char ICN[]="ß8 0", TO[9]="TMP/Tlog";
extern struct {int Aktuell,Max,Top; unsigned char TAB[X_MAX*160]} ztabl={0,0,0,0};
extern void xDir(c,r,l)char* c,r;int l;
{char ELF[5];int n;static char T[4]={226,134,144,0},*t;
 if(t=strstr(c,T)){n=t-(int)(c);t[l-n]=0; FILE *o=fopen(t+3,"r");ELF[0]=1;
    if(o) {fgets(ELF,5,o);fclose(o); if (ELF[1]==69&&ELF[3]==70) ELF[0]-=127;}}
  else if (t=strstr(c,"->")){n=t-(int)c;printf("link:%.*s/%d",l-n-3,t+3,n);}
 return;strncpy(c,r-l,l);static int i=0;
printf("%s=%d,j=%d>%.*s<%d,%d\n",T,l,t-(int)c,l-1,c,ELF[0]++,i);
}
/* check of xinit basic function. A is a file table with sources and images */
main(int n,char** A){/*ztabl.TAB=malloc(X_MAX*160);*TAB;*/ return xEdit(A,n);}
extern xEdit(char** A,int n)
{int Nr=1,i,j,k,l=strlen(A[1]),m,ii,Ret=0,L,L5,L3,L2,l3,nA; FILE *f=fopen(A[1],"r"),*o;
 unsigned char cmd[]="X-FindLC+>-2Gra>-4Cmd>+4+size ReReadDIR   Setup ", *h=getenv("HOME"),
 lc[]="900+>-6Ins+3  Cmd->-4122040.File>-2",ll[]="N3099070150len",*DT="DIR Tlogdiffsave",
 c1,*c,*t,*r,*rc, *Mg=pptab.LMSG, DSN[900]; for(i=0;i<900;i++) DSN[i]=(i>l)?' ':A[1][i];
 for (i=j=1,k=1;i<n;i++)
  {if (A[i][0]==':'){sprintf(eacom,"%s",A[i]); l=-1;xcparam(&l,&l,&l);}
      else if (j<99){strncpy(DSN+9*j++,A[i],strlen(A[i]));
/*strncpy(Mg,A[i],strlen(A[i]));printf("MG=%s< i/n=%d/%d, A=%s\n",Mg,i,n,A[i]);*/}
   if (c=strstr(A[i],"xpm")){sprintf(issyimg+k,"%s ",A[i]); k+=1+strlen(A[i]);}
  } nA=j; if (!f) {printf("%.9s invalid file",DSN); return 1;} c=ztabl.TAB; rc=c+X_MAX*160;

/* Read file for table/pop functions */
 B0:t=strstr(Mg,"TMP/DIR"); L3=lc[11]-'0';l3=pow(10,L3);c[L5=156-(L2=(L3>3)?2*L3:L3+4)]=0;
 if (t) L=9999;else if (lc[0]<'2') L=L5+2;else sscanf(lc,"%3d",&L); r=rc; ztabl.Max=i=k=m=0;
 while(fgets(c+i,L,f) && c+i+(l=strlen(c+i))<r-l-160)
 {j=i+l;while(c[j-1]==' '||c[j-1]==10||c[j-1]==13)--j; c[i+(l=(j-i)+1)]=0; if (k<l) k=l;
  strncpy(r-l,c+i,l);if (t) xDir(c+i,r,l);sprintf(c+i+L5+2,"%*.d",157-L5,(ztabl.Max+1)%l3);
  if (l<L5 || lc[0]<'2') {if (l>=L5) m++;}
   else {r-=l; unsigned int *ir=&c[i+154];*ir=rc-r;c[i+158]=r[l-1]=0;}
  if (l>L5)l=L5; else for (;j-i<L5;j++) if (j-i<L5) c[j]=' ';c[i+L5+1]=l-1;
  ztabl.Max++; i+=160; c[i+L5]=0; c[i-1]=' ';
 }Mg[strlen(Mg)]=' '; sprintf(strchr(Mg,' '),",%d lines m=%d>%d/%d/%d",ztabl.Max,m,L,L5,L3);
 sprintf(lc,"%03d",k+1); lc[3]=cmd[8]; fclose(f); f=i=0; for (j=0;j<80;j++) eacom[j]=' ';

/* describe Alfa screen */
 B1:j=ICN[3]-'0';c=ztabl.TAB;k=99;m=-19;xcparam(&k,&j,&m);eacom[0]=' ';
 sprintf(ll,"N3%.3s%03d%03dlen",lc,pptab.WH[2]-((lc[3]!='-')?5+L3:4),150);j=1;xcinit(&i,&j);
 k=((m=pptab.WH[2]-72)>0)?32:4;if (m>4) i=CXTDEF(1,eacom+5,m-4,1,35,3);l=0; j=czoom.MaxI;
 for (m=-11;j--;m-=5) {if(pptab.WH[2]+m-9<((l)?0:(k<5)?22:k)){m=-5; l=(l)?l+2:3;}
  if (j==4) i=CXTDEF(9,DT,0,4,4,9); i=CXTDEF((j-4)?12-j:13,ICN,j,1+l,m,10);}
 j=ztabl.Top-1; i=CXTDEF(9,comwin,0,4,8,9); i=CXTDEF(1,ll,12,(k<7)?1:2,(k<7)?9:22,8);
 i=CXTDEF(11,c,(j<0)?0:j,ztabl.Max,160,9); i=CXTDEF(1,lc,k,1,2,1); i=CXTDEF(9,cmd,0,8,6,9);
 i=CXTDEF(1,eacom,4,2,2,1);i=CXTDEF(0,"File:",5,2,7,3); i=CXTDEF(12,DSN,0,nA,9,9);
 i=CXTDEF(1,DSN,9,2,12,1); i=CXTDEF(10,lc,0,5,7,9); ii=CXTDEF(6,c+153,6,1,(l)?l+3:4,0);
 printf("WxH:%dx%d n=%d/%d, d=%d/%d\n",pptab.WH[0],pptab.WH[1],pptab.WH[2],k,pptab.WH[3],Nr);
 k=2; if (lc[3]!='-'){i=CXTDEF(6,c+L5+2,L3,L5,2,3); k=3+L3;}
 sscanf(lc,"%3d",&j); i=CXTDEF(6,c,j,1,k,7);

/* analyse screen input */
 B2:xcread(&Nr,&Ret); j=Ret; k=(lc[11]-'0'); i=2+L2;t=c+(l=ztabl.Aktuell)*160-i;
 printf(">>>%d,%d/%d WH:%d/%d\n",j,i,L2,pptab.WH[0],pptab.WH[2]);
 if (m=(c[l*160-2])?0:*((int*)&c[l*160-6])) strncpy(rc-m,c+(l-1)*160,L5); c1=Mg[0]; i=0;
 if (j==-9 && c1=='G'){i=Mg[6]-'0';if (i<1||i>3) goto B2;}
  else if (eacom[0]=='L'||c1=='L') {cmd[8]=(cmd[8]-'-')?'-':'+';lc[3]=cmd[8]; goto B1;}
  else if (Ret<0) {eacom[0]=c1; Ret=6;} else if (Ret==4) goto E1; else if (Ret==12)
  {i=(pptab.WH[3])?(k-7)*100:(pptab.WH[0]<4000)?-1:-80;} else if (Ret==13) eacom[0]='+';
  else if (Ret>1000){sprintf(Mg,"C-double click on %d",j=ii-Ret+991); if (j!=-10)goto B2;}
  else if (Ret>8) i=Ret-8; else if (Ret>7) i=-1; else if (Ret>6) return 9*(8-Ret);
  else if (Ret<4) i=Ret; else if (Ret==6) goto E1; else goto B2; k=l*160-160+L5;
 if(!c[k]){for (m=k-1;c[m-1]==' ';m--);c[k+1]=m-k+L5;}; k=strchr(Mg,' ');
 if (i<0||!k) goto E1; Mg[k-(int)Mg]=0;
 printf("%c/%c-Ret:%d/%d/%d/%d>%s\n",c1,eacom[0],Ret,j,k-(int)Mg,ii,Mg);
 if (j==-9){if (c1=='R' && (f=fopen(A[1],"r"))) goto B0; if (strchr("SCL",c1)) goto B2;
     j=(c1=='s')?22:(c1=='d')?21:20; if (j==20)strncpy(&TO[4],Mg,4);}
   else if (j==-10 && c1=='1'){sprintf(eacom,":%s",Mg); l=-1; xcparam(&l,&l,&l);i=0;}
   else if (j==-10||t[0]=='C'){t[l=t[-1]-L5]=0; system(t-L5-2); strncpy(&TO[4],"DIR ",4);
    if (strstr(t-L5-2,TO)) j=20; t[0]=t[l]=' ';}
   else if (j==-12 && (f=fopen(Mg,"r"))) {strncpy(DSN,Mg,9);}
 if (j>19){sprintf(Mg,"%s/%s ",h,TO); Mg[(unsigned char*)strchr(Mg,' ')-Mg]=0;}
/* save table and compare by diff */
 if (j>20 && (o=fopen(Mg,"w"))){printf("write:%d lines to %s %d/%d\n",ztabl.Max,Mg,L5,c[L5+1]);
  for (l=i=0,t=c+ztabl.Max*160; l<ztabl.Max; l++,c+=160)
   if (!c[158]) fprintf(o,"%s\n",rc-*((int*)&c[154])); else if (c[L5])
    {strncpy(t+i,c,L5+1); i+=L5+1;} else {fprintf(o,"%.*s%.*s\n",i,t,c[L5+1],c);i=0;}
   fclose(o); sprintf(Mg,"%s %s/%s %.9s&",(j==22)?"cp -p":"xterm -e mcdiff",h,TO,DSN);
  printf("\n>%c=%s< j=%d\n",cmd[0],Mg,j); system(Mg); c=ztabl.TAB; goto B2; return 9;}
 printf("%c-Cmd:%d i=%d/%d/%d dsn=%.20s TO=%s\n",c1,Ret,i,j,strchr("TSCL",c1),Mg,TO);
 if (j>19) f=fopen(Mg,"r"); if (f) goto B0; if (k=strlen(Mg)) sprintf(Mg+k," missing");
 if (i){xcinit(&i,&j); xgrneu(&i,&j);goto B2;} i=0;
 E1:if(r=strchr(eacom+5,' '))r[0]=0;/* X-exclude and find actions by primary/line commands*/
printf("%c%cMg>%s<%.*s>%s<%d,k=%d,Ret:%d/%d/%d l=%d\n",eacom,t[0],Mg,L3,t,eacom,Nr,k-(int)Mg,Ret,j,i,l);
 if(eacom[0]=='X')for(j=k=0;j<ztabl.Max;j++,k+=160) 
  if(eacom[5]){c[k+159]=' ';if(!strstr(c+k,eacom+5)) c[k+159]=0;}
  else if(DSN[5]=='f'){if(!strstr(c+k,"SUBR"))c[k+159]=0;}
  else if(DSN[7]=='c'){if(!strstr(c+k,"*=>"))c[k+159]=0;}
  else if(c[k+L5+1]<=14||c[k+22]=='@')c[k+159]=0;//printf("l(%d)=%d/%d\n",j,c[k+L5+1],c[k+159]=0);
 if(eacom[0]=='F')for(j=k=0;j<ztabl.Max;j++,k+=160) if(strstr(c+k,eacom+5)) c[k+159]=1;
 if(t[0]=='X')for(;l<=ztabl.Max && c[l*160-1];l++) c[l*160-1]=0;
 if(t[0]=='F')for(;l && !c[(--l)*160-1];) //c[l*160-1]=' ';
 printf("l(%d)=%d/%d\n",l,c[l*160-161],c[l*160-1]=' ');
 if(!strchr("ABCM",t[0])) t[0]=' ';if (Ret==4) goto B2; if (Ret != 8) goto B1;
}
/* extern int xEdit();extern xcparam();*/
extern winpik(x,y,i,w)float *x,*y;int *i,*w;{float d=sqrt(pow(*x,2)+pow(*y,2));
int f=3,n=2; gxpoly(&czoom.XY[0],&czoom.XY[1],&n);gxline(&f);
printf("P:%.1f/%0.f v:%1.f i=%d/%d ",*x,*y,d,*i,*w);
printf("Z:%f/%f, %f/%f\n",czoom.XY[0],czoom.XY[1],czoom.XY[2],czoom.XY[3]);}
extern xgrneu(b,i)int *b,*i;{printf("resize:%d/%d\n",*b,*i);}
