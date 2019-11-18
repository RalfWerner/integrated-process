/* head -n 5 check.c|grep -v grep >makefile
.c.o :
	gcc -c -w $< -o $@
~/TMP/check.exe: check.o xinitn.o
	gfortran check.o xinitn.o -lXpm -lX11 -o $@
~/TMP/touch.exe: touch.o
	gcc touch.o -lX11 -lXpm -lXi -lcairo -lxcb -o $@
*/
#define X_MAX 100000
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xutil.h>
extern char issyimg[80]="PMOD.xpm  ",cvers[16]="Setup ",cexcl[2]=" ",cfleg[80]=" ",
 eacom[176]=" ",comwin[120]="1.Grafic2.Grafic3.Graficcheck.c ",clegdf[3][80]=
 {"Lines   Points  Quad/RecTrias   Circles Text    Main->-1Sel.->+1Last >-0",
  "1/A gr. 2/B gr. 3/C gr. 4/D gr. 5/E gr. Cre.->-1Main->-2Last >+0Rotate  "};
extern struct {int LTEST,NPL,KP; float XY[4],Rest;} kontur={0,0,0,0,0,0,0,0,0};
extern struct {char TABLE[16];int WH[4];unsigned char LMSG[80];} pptab={" ",0,0,0,1," "};
extern struct {float XY[4],Hgrenz; int ZM,RDY;} czoom={0,0,0,0,0,0,0};
extern struct {int IP,Dick[10],PAT,Gdick,RGB[12][3],Stil[11];} cpunit=
 {10,1,1,1,1,1,1,1,1,1,1,1,1, 90,90,80,0,0,0,80,0,0,0,50,0,0,0,100,60,0,60,
  80,0,80,0,90,50,100,100,0,100,50,0,0,100,100,0,0,0, 1,1,1,1,1,1,1,1,1,1,1};
extern struct {int NWIN,IWK; float AXLG,SHR,BUH; int NERG,N1,N2; float ALF[3];} 
 plparm={1,1, 0,0,0, 0,0,0, 1,1,1}; unsigned char ICN[]="ß8 0", TO[9]="TMP/Tlog";
extern struct {int Aktuell,Max,Top; unsigned char TAB[X_MAX*160]} ztabl={0,0,0,0};

/* check of xinit basic function. A is a file table with sources and images */
main(int n,char** A){/*ztabl.TAB=malloc(X_MAX*160);*TAB;*/ return xEdit(A,n);}
extern int xEdit(char** A,int n) 
{int Nr=1,i,j,k,l=strlen(A[1]),m,Ret=0,L5,L3; FILE *f=fopen(A[1],"r"),*o;
 unsigned char *cmd="+ sizeReReadCmd>+4Debug LC->-2Setup Test  ",*h=getenv("HOME"),
 lc[]="173->-6Ins+3  Cmd->-4122040.File>-2",ll[]="N3099070150len",
 *c,*t, *Mg=pptab.LMSG, DSN[160]; for(i=0;i<160;i++) DSN[i]=(i>l)?' ':A[1][i];
 for (i=j=1,k=0;i<n;i++) 
  {if (A[i][0]==':'){sprintf(eacom,"%s",A[i]); l=-1;xcparam(&l,&l,&l);}
      else if (j<18) strncpy(DSN+9*j++,A[i],strlen(A[i]));
   if (c=strstr(A[i],"xpm")){sprintf(issyimg+k,"%s ",A[i]); k+=1+strlen(A[i]);}
  }n=j; sprintf(Mg,"*Invalid file:%.9s",DSN); if (!f) return 1;

/* Read file for table/pop functions */
 B0:L3=lc[11]-'0'; c=ztabl.TAB; c[L5=156-2*L3]=ztabl.Max=i=k=m=0;
 while(fgets(c+i,L5+2,f) && ztabl.Max<X_MAX)
 {ztabl.Max+=1; j=i+(l=strlen(c+i)-1); if (k<l) k=l; 
  if(l>=L5) m++; else while(c[i+l-1]==' ') l--; for (;j-i<152;j++) if (j-i!=L5)c[j]=' ';
  c[i+L5+1]=l; sprintf(c+i+152,"%7.d",ztabl.Max); i+=160; c[i+L5]=0;
 }sprintf(Mg,"%.9s,%d lines m=%d>%d ",DSN,ztabl.Max,m,L5);
 sprintf(lc,"%03d",k);lc[3]='-'; fclose(f); f=i=0;
/* describe Alfa screen */ 
 B1:j=ICN[3]-'0'; k=99; xcparam(&k,&j,&j); j=1; xcinit(&i,&j);
 if ((k=(pptab.WH[2]-35)/5)>7) k=7; l=1; m=-11; 
 printf("WxH:%dx%d n=%d/%d, d=%d/%d ",pptab.WH[0],pptab.WH[1],pptab.WH[2],k,pptab.WH[3],Nr);
 c=ztabl.TAB; eacom[0]=' '; if (k<5){l=4;m=-5;k=7;} for (j=0;j<k;j++)
 {if (j==4) i=CXTDEF(9,"LC+ LC- fulldiffsaveTlogDIR ",0,7,4,9);
  i=CXTDEF((j-4)?12-j:13,ICN,j,l,m-5*j,10);} j=ztabl.Top-1;
 i=CXTDEF(1,ll,12,2,22,8); i=CXTDEF(11,c,(j<0)?0:j,ztabl.Max,160,9);
 i=CXTDEF(1,lc,32,1,2,1);  i=CXTDEF(9,cmd,0,7,6,9);
 i=CXTDEF(1,eacom,4,2,2,1);i=CXTDEF(0,"File:",5,2,7,3);
 i=CXTDEF(12,DSN,0,n,9,9); i=CXTDEF(1,DSN,9,2,12,1);
 i=CXTDEF(10,lc, 0,5,7,9); i=CXTDEF(6,c+153,6,1,3+l,0);
 k=2; if (lc[10]!='-'){i=CXTDEF(6,c+L5+3,L3,6,2,3); k=3+L3;}
 sscanf(lc,"%3d", &j); i=CXTDEF(6,c,j,6,k,7);

/* analyse input */
 B2:xcread(&Nr,&Ret); i=0; k=(lc[11]-'0'); l=ztabl.Aktuell; t=c+l*160-1-2*L3; j=Ret;
//if (Ret==13){setupissy(&i,&k); goto B1;}
 if (Ret<0) {eacom[0]=Mg[0]; Ret=6;} else if (Ret==12) 
  {i=(pptab.WH[3])?(k-7)*100:(pptab.WH[0]<4000)?-1:-800;} else if (Ret==13) eacom[0]='+';
  else if (Ret>8) i=Ret-8; else if (Ret>6) return 9*(8-Ret); else if (Ret>7) i=-1;
  else if (Ret<4) i=Ret; else if (Ret==6) goto B1; else goto B2; k=l*160-160+L5;
 if (Mg[0]=='L') lc[10]=Mg[2];
 if(!c[k]){for (m=k-1;c[m-1]==' ';m--);c[k+1]=m-k+L5;};k=strchr(Mg,' ');
 if (Mg[0]=='f') i=-1; if (i<0||!k) goto B1; Mg[k-(int)Mg]=0;// l=0;
 if (Mg[0]=='D'||Mg[0]=='T'){j=20;strncpy(&TO[4],Mg,4);} else if (Mg[0]=='s') j=21;
   else if (Mg[0]=='1'){sprintf(eacom,":%s",Mg); l=-1; xcparam(&l,&l,&l);i=0;}
   else if (j==-12 && (f=fopen(Mg,"r"))) {strncpy(DSN,Mg,9); j=19;}
printf("%.8s<%.*s><%4s>,%d,k=%d,Ret:%d/%d/%d\n",Mg,L3,t,eacom,Nr,k-(int)Mg,Ret,j,i);
 if (j>19){sprintf(Mg,"%s/%s ",h,TO); Mg[(unsigned char*)strchr(Mg,' ')-Mg]=0;}
 if (j>20 && (o=fopen(Mg,"w"))){printf("write:%d lines to %s %d\n",ztabl.Max,Mg,L5);
  for (l=i=0,t=c+ztabl.Max*160; l<ztabl.Max; l++,c+=160) if (c[L5]) 
  {strncpy(t+i,c,L5+1); i+=L5+1;} else {fprintf(o,"%.*s%.*s\n",i,t,c[L5+1],c);i=0;}
  fclose(o); sprintf(Mg,"%s %s/%s %.9s&","xterm -e mcdiff",h,TO,DSN);
  system(Mg); goto B2;strncpy(Mg,"cp -p",5); system(Mg); return 9;}
 if (j>19) f=fopen(Mg,"r"); if (f)goto B0; if (i){xcinit(&i,&j); goto B2;} i=0; goto B1;
}
/* extern int xEdit();extern xcparam();*/
extern winpik(x,y,i,w)float *x,*y;int *i,*w;{float d=sqrt(pow(*x,2)+*y**y);
int f=3,n=2; gxpoly(&czoom.XY[0],&czoom.XY[1],&n);gxline(&f);
printf("P:%.1f/%0.f v:%1.f i=%d/%d ",*x,*y,d,*i,*w);
printf("Z:%f/%f, %f/%f\n",czoom.XY[0],czoom.XY[1],czoom.XY[2],czoom.XY[3]);}
extern long tasini(){;} extern long tasexe(){;};extern xgrneu(){;};
extern void propelt(long *ip,long *ptyp,long *n,long *typ,long *p){;}
extern long getspnt (long *np, long *pt, long *vn, long *ier){;}
extern long simple (long *npts, long *eid, long *plist, long *ier){;}
/*
logcat -s termux:* termux-api:*/
