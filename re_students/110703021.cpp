#include<stdio.h>
char p,*D[4]={"UP","LEFT","RIGHT","DOWN"};
int d[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
int xA,xB,yA,yB,i=0,j=-1,k,x,y,R,C,sA,sB,T,r=1,f=0;
int main(){scanf("%d%d%d%*c",&k,&R,&C);
char M[R][C];int v[R][C],q[R*C-2][3];
for(;R-i;){scanf("%1c ",&M[i][++j]);v[i][j]=0;
if(M[i][j]=='A')xA=i,yA=j;else if(M[i][j]=='B')xB=i,yB=j;
if(C-j==1)++i,j=-1;}  scanf("%d%d%*c%1c",&sA,&sB,&p);
if(p^'A'){x=q[0][0]=xB;y=q[0][1]=yB;q[0][2]=sB;sB=sA;
  for(k=0;r-f;){if(k==4)k=0,x=q[++f][0],y=q[f][1];
            i=x+d[k][0],j=y+d[k++][1];
     if(i+1&&j+1&&R-i&&C-j)if(!f&&M[i][j]=='A');
    else if(M[i][j]^'x'&&!v[i][j]){v[i][j]=f?v[x][y]:k;
       switch(M[i][j]){case'm':q[r][2]=-~q[f][2];break;
    case'n':q[r][2]=~-q[f][2];break;
    case's':q[r][2]=q[f][2]<<1;break;
    case't':q[r][2]=q[f][2]>>1;break;
    default:q[r][2]=q[f][2];break;}
     if(M[i][j]^'b'){if(q[r][2]>sB)sB=q[r][2],T=v[i][j];
                       q[r][0]=i,q[r++][1]=j;
                     if(M[i][j]=='A'){x=i,y=j;break;}}
     else if(q[r][2]>sB<<1)q[r][0]=i,q[r++][1]=j;}}
        puts(sB>sA?D[~-T]:D[~-v[x][y]]);}
else{x=q[0][0]=xA,y=q[0][1]=yA,q[0][2]=sA,sA=sB;
   for(k=3;r-f;){if(k==-1)k=3,x=q[++f][0],y=q[f][1];
            i=x+d[k][0],j=y+d[k--][1];
     if(i+1&&j+1&&R-i&&C-j)if(!f&&M[i][j]=='B');
      else if(M[i][j]^'x'&&!v[i][j]){v[i][j]=f?v[x][y]:k+2;
       switch(M[i][j]){case'm':q[r][2]=-~q[f][2];break;
       case'n':q[r][2]=~-q[f][2];break;
       case's':q[r][2]=q[f][2]<<1;break;
       case't':q[r][2]=q[f][2]>>1;break;
       default:q[r][2]=q[f][2];break;}
       if(M[i][j]^'b'){if(q[r][2]>sA)sA=q[r][2],T=v[i][j];
                            q[r][0]=i,q[r++][1]=j;
                       if(M[i][j]=='B'){x=i,y=j;break;}}
      else if(q[r][2]>sA<<1)q[r][0]=i,q[r++][1]=j;}}
       puts(sA>sB?D[~-T]:D[~-v[x][y]]);}}
