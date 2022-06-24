#include<bits/stdc++.h>
using namespace std;
int main()
{
        int t=0,m=0,n=0,p=0,q=0,ma=0,na=0,mb=0,nb=0;
        char map[20][20]={0},x[20][20]={0},a[20][20]={0},b[20][20]={0};
        char se,c;
        scanf("%d",&t);
        scanf("%d %d%c",&m,&n,&se);
        for(int i=0;i<m;++i)
        {
                for(int j=0;j<n;++j)
                {
                        scanf("%c%c",&map[i][j],&se);
                        if(map[i][j]=='x')
                        {
                                x[i][j]=1;
                        }
                        else if(map[i][j]=='A')
                        {
                                ma=i;
                                na=j;
                                a[i][j]=1;
                        }
                        else if(map[i][j]=='B')
                        {
                                mb=i;
                                nb=j;
                                b[i][j]=1;
                        }
                }
        }
        scanf("%d%c",&p,&se);
        scanf("%d%c",&q,&se);
        scanf("%c%c",&c,&se);
        if(c=='A')
        {
                if(ma==0)
                {
                        if(na==0)
                        {
                                if(x[0][1]==1||b[0][1]==1)
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(x[1][0]==1||b[1][0]==1)
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else
                                {
                                        if(p<=0)
                                        {
                                                if(map[0][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[0][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else if(na==n-1)
                        {
                                if(x[0][n-2]==1||b[0][n-2]==1)
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(x[1][n-1]==1||b[1][n-1]==1)
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else
                                {
                                        if(p<=0)
                                        {
                                                if(map[0][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[0][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else
                        {
                                if(p<=0)
                                {
                                        if(map[0][na+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='m')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='t')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='.')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='n')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='s')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[0][na+1]!=1&&b[0][na+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(x[1][na]!=1&&b[1][na]!=1)
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(x[0][na-1]!=1&&b[0][na-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                                else
                                {
                                        if(map[0][na+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='s')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='m')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='.')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='n')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][na+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][na]=='t')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][na-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[0][na+1]!=1&&b[0][na+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(x[1][na]!=1&&b[1][na]!=1)
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(x[0][na-1]!=1&&b[0][na-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                }
                else if(ma==m-1)
                {
                        if(na==n-1)
                        {
                                if(x[m-2][n-1]==1||b[m-2][n-1]==1)
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(x[m-1][n-2]==1||b[m-1][n-2]==1)
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else
                                {
                                        if(p<=0)
                                        {
                                                if(map[m-1][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[m-1][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else if(na==0)
                        {
                                if(x[m-1][1]==1||b[m-1][1]==1)
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(x[m-2][0]==1||b[m-2][0]==1)
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else
                                {
                                        if(p<=0)
                                        {
                                                if(map[m-1][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[m-1][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else
                        {
                                if(p<=0)
                                {
                                        if(map[m-1][na-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='m')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='t')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='.')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='n')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='s')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[m-1][na-1]!=1&&b[m-1][na-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(x[m-2][na]!=1&&b[m-2][na]!=1)
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(x[m-1][na+1]!=1&&b[m-1][na+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                                else
                                {
                                        if(map[m-1][na-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='s')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='m')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='.')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='n')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][na]=='t')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][na+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[m-1][na-1]!=1&&b[m-1][na-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(x[m-2][na]!=1&&b[m-2][na]!=1)
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(x[m-1][na+1]!=1&&b[m-1][na+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                }
                else
                {
                        if(p<=0)
                        {
                                if(map[ma][na+1]=='m')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='m')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='m')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='m')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='t')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='t')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='t')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='t')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='.')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='.')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='.')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='.')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='n')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='n')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='n')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='n')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='s')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='s')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='s')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='s')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else
                                {
                                        if(x[ma][na+1]!=1&&b[ma][na+1]!=1&&na+1<=n-1)
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(x[ma+1][na]!=1&&b[ma+1][na]!=1&&ma+1<=m-1)
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(x[ma][na-1]!=1&&b[ma][na-1]!=1&&na-1>=0)
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(x[ma-1][na]!=1&&b[ma-1][na]!=1&&ma-1>=0)
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                }
                        }
                        else
                        {
                                if(map[ma][na+1]=='s')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='s')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='s')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='s')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='m')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='m')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='m')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='m')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='.')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='.')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='.')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='.')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='n')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='n')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='n')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='n')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[ma][na+1]=='t')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[ma+1][na]=='t')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[ma][na-1]=='t')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[ma-1][na]=='t')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else
                                {
                                        if(x[ma][na+1]!=1&&b[ma][na+1]!=1&&na+1<=n-1)
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(x[ma+1][na]!=1&&b[ma+1][na]!=1&&ma+1<=m-1)
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(x[ma][na-1]!=1&&b[ma][na-1]!=1&&na-1>=0)
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(x[ma-1][na]!=1&&b[ma-1][na]!=1&&ma-1>=0)
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                }
                        }
                }
        }
        else
        {
                if(mb==0)
                {
                        if(nb==0)
                        {
                                if(x[0][1]==1||a[0][1]==1)
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(x[1][0]==1||a[1][0]==1)
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else
                                {
                                        if(q<=0)
                                        {
                                                if(map[0][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[0][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[1][0]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else if(nb==n-1)
                        {
                                if(x[0][n-2]==1||a[0][n-2]==1)
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(x[1][n-1]==1||a[1][n-1]==1)
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else
                                {
                                        if(q<=0)
                                        {
                                                if(map[0][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[0][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='s')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='m')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='.')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='n')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(map[0][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[1][n-1]=='t')
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else
                        {
                                if(q<=0)
                                {
                                        if(map[0][nb+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='m')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='t')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='.')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='n')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='s')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[0][nb+1]!=1&&a[0][nb+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(x[1][nb]!=1&&a[1][nb]!=1)
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(x[0][nb-1]!=1&&a[0][nb-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                                else
                                {
                                        if(map[0][nb+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='s')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='m')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='.')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='n')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[0][nb+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[1][nb]=='t')
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                        else if(map[0][nb-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[0][nb+1]!=1&&a[0][nb+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(x[1][nb]!=1&&a[1][nb]!=1)
                                                {
                                                        printf("DOWN\n");
                                                        return 0;
                                                }
                                                else if(x[0][nb-1]!=1&&a[0][nb-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                }
                else if(mb==m-1)
                {
                        if(nb==n-1)
                        {
                                if(x[m-2][n-1]==1||a[m-2][n-1]==1)
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(x[m-1][n-2]==1||a[m-1][n-2]==1)
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else
                                {
                                        if(q<=0)
                                        {
                                                if(map[m-1][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[m-1][n-2]=='s')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='m')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='.')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='n')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][n-2]=='t')
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][n-1]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else if(nb==0)
                        {
                                if(x[m-1][1]==1||a[m-1][1]==1)
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(x[m-2][0]==1||a[m-2][0]==1)
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else
                                {
                                        if(q<=0)
                                        {
                                                if(map[m-1][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                        else
                                        {
                                                if(map[m-1][1]=='s')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='s')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='m')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='m')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='.')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='.')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='n')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='n')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(map[m-1][1]=='t')
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                                else if(map[m-2][0]=='t')
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                        else
                        {
                                if(q<=0)
                                {
                                        if(map[m-1][nb-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='m')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='t')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='.')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='n')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='s')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[m-1][nb-1]!=1&&a[m-1][nb-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(x[m-2][nb]!=1&&a[m-2][nb]!=1)
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(x[m-1][nb+1]!=1&&a[m-1][nb+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                                else
                                {
                                        if(map[m-1][nb-1]=='s')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='s')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='s')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='m')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='m')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='m')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='.')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='.')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='.')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='n')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='n')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='n')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb-1]=='t')
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(map[m-2][nb]=='t')
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(map[m-1][nb+1]=='t')
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else
                                        {
                                                if(x[m-1][nb-1]!=1&&a[m-1][nb-1]!=1)
                                                {
                                                        printf("LEFT\n");
                                                        return 0;
                                                }
                                                else if(x[m-2][nb]!=1&&a[m-2][nb]!=1)
                                                {
                                                        printf("UP\n");
                                                        return 0;
                                                }
                                                else if(x[m-1][nb+1]!=1&&a[m-1][nb+1]!=1)
                                                {
                                                        printf("RIGHT\n");
                                                        return 0;
                                                }
                                        }
                                }
                        }
                }
                else
                {
                        if(q<=0)
                        {
                                if(map[mb][nb-1]=='m')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='m')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='m')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='m')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='t')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='t')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='t')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='t')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='.')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='.')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='.')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='.')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='n')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='n')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='n')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='n')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='s')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='s')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='s')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='s')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else
                                {
                                        if(x[mb][nb-1]!=1&&a[mb][nb-1]!=1&&nb-1>=0)
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(x[mb-1][nb]!=1&&a[mb-1][nb]!=1&&mb-1>=0)
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(x[mb][nb+1]!=1&&a[mb][nb+1]!=1&&nb+1<=n-1)
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(x[mb+1][nb]!=1&&a[mb+1][nb]!=1&&mb+1<=m-1)
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                }
                        }
                        else
                        {
                                if(map[mb][nb-1]=='s')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='s')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='s')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='s')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='m')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='m')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='m')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='m')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='.')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='.')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='.')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='.')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='n')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='n')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='n')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='n')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else if(map[mb][nb-1]=='t')
                                {
                                        printf("LEFT\n");
                                        return 0;
                                }
                                else if(map[mb-1][nb]=='t')
                                {
                                        printf("UP\n");
                                        return 0;
                                }
                                else if(map[mb][nb+1]=='t')
                                {
                                        printf("RIGHT\n");
                                        return 0;
                                }
                                else if(map[mb+1][nb]=='t')
                                {
                                        printf("DOWN\n");
                                        return 0;
                                }
                                else
                                {
                                        if(x[mb][nb-1]!=1&&a[mb][nb-1]!=1&&nb-1>=0)
                                        {
                                                printf("LEFT\n");
                                                return 0;
                                        }
                                        else if(x[mb-1][nb]!=1&&a[mb-1][nb]!=1&&mb-1>=0)
                                        {
                                                printf("UP\n");
                                                return 0;
                                        }
                                        else if(x[mb][nb+1]!=1&&a[mb][nb+1]!=1&&nb+1<=n-1)
                                        {
                                                printf("RIGHT\n");
                                                return 0;
                                        }
                                        else if(x[mb+1][nb]!=1&&a[mb+1][nb]!=1&&mb+1<=m-1)
                                        {
                                                printf("DOWN\n");
                                                return 0;
                                        }
                                }
                        }
                }
        }

        return 0;
}
