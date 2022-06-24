#include <iostream>
#include <cstdlib>
#include <utility>
#include <string>

using namespace std;


int Round, M, N;
char Graph[20][20]={};

bool valid(int x, int y){
    return (
        x >= 0 && x < M && y >=0 && y < N && 
        Graph[x][y] != 'x' && 
        Graph[x][y] != 'A' && Graph[x][y] != 'B'
    );
}

int Max4(int a,int b,int c,int d){
    int max;
    if(a>b)max=a;
    else max=b;
    if(c>max)max=c;
    if(d>max)max=d;
    return max;
}
int Max3(int a,int b,int c){
    int max;
    if(a>b)max=a;
    else max=b;
    if(c>max)max=c;
    return max;
    
}
int Min3(int  a,int b,int c){
    int min;
    if(a==-100)a=INT16_MAX;
    if(b==-100)b=INT16_MAX;
    if(c==-100)c=INT16_MAX;
    if(a==INT16_MAX&&b==INT16_MAX&&c==INT16_MAX){
        return -100;
    }
    if(a<b)min=a;
    else min=b;
    if(c<min)min=c;
    return min;}

int bestdir(int x, int y, int score){
        int up = 0;
        if(score==-100)return score;
        //printf("%d %d is %c\n",x,y,Graph[x][y]);
        switch(Graph[x][y]) {
            case 'b': 
                up=score;
                break;
               
            case 'm':
                up=score+1;
                break;
                
            case 'n': 
                up=score-1;
                break;
                
            case 's': 
                up=score*2;
                break;
                
            case 't':
                up=score/2;
                break;
                
            case '.':
                up=score;
                break;
                
            default:
                up = -100;
            
        }
        return up;
}
int minimaxup(int x,int y,int score){
    int up,left,right;
    if(score==-100)return score;
    
    up = bestdir(x-1,y,score);
    left = bestdir(x,y-1,score);
    right = bestdir(x,y+1,score);
    //printf("%d %d %d\n",up,left,right);
    return Max4(up,left,right,score);
}
int minimaxdown(int x,int y,int score){
    if(score==-100)return score;
    int down,left,right;
    down=bestdir(x+1,y,score);
    left = bestdir(x,y-1,score);
    right = bestdir(x,y+1,score);
    //printf("%d %d %d\n",down,left,right);
    return Max4(down,left,right,score);
}
int minimaxleft(int x,int y,int score){
    if(score==-100)return score;
    int up,down,left;
    up = bestdir(x-1,y,score);
    down = bestdir(x+1,y,score);
    left = bestdir(x,y-1,score);
    //printf("%d %d %d\n",up,down,left);
    return Max4(up,down,left,score);
}
int minimaxright(int x,int y,int score){
    if(score==-100)return score;
    int up,down,right;
    up = bestdir(x-1,y,score);
    down = bestdir(x+1,y,score);
    right = bestdir(x,y+1,score);
    //printf("%d %d %d\n",up,down,right);
    return Max4(up,down,right,score);
}
string next_dir(int x, int y, int score){
        int up,down,left,right;
        string dir[4]={"UP", "DOWN", "LEFT", "RIGHT"};
        int nextdir;
        up = bestdir(x-1,y,score);
        
        down = bestdir(x+1,y,score);
      
        left = bestdir(x,y-1,score);
        
        right = bestdir(x,y+1,score);
             
        //cout << up << ' '<< down <<' '<<left<<' '<<right<<endl;///////////////////////
        int best=Max4(up,down,left,right);
        //printf("up:\n");
        up=Max3(minimaxup(x-2,y,bestdir(x-2,y,up)),minimaxleft(x-1,y-1,bestdir(x-1,y-1,up)),minimaxright(x-1,y+1,bestdir(x-1,y+1,up)));
        
        //printf("down:\n");
        down=Max3(minimaxdown(x+2,y,bestdir(x+2,y,down)),minimaxleft(x+1,y-1,bestdir(x+1,y-1,down)),minimaxright(x+1,y+1,bestdir(x+1,y+1,down)));
        
        //printf("left: \n");
        left=Max3(minimaxleft(x,y-2,bestdir(x,y-2,left)),minimaxdown(x+1,y-1,bestdir(x+1,y-1,left)),minimaxup(x-1,y-1,bestdir(x-1,y-1,left)));
        
        //printf("right:\n");
        right=Max3(minimaxright(x,y+2,bestdir(x,y+2,right)),minimaxdown(x+1,y+1,bestdir(x+1,y+1,right)),minimaxup(x-1,y+1,bestdir(x-1,y+1,right)));
        
       // cout << up << ' '<< down <<' '<<left<<' '<<right<<endl<<endl;///////////////////////////
        best=Max4(up,down,left,right);
        if(best==up)nextdir=0;
        else if(best==down)nextdir=1;
        else if(best==left)nextdir=2;
        else nextdir=3;
           
        return dir[nextdir];
}

int main(void){
    int A, B;
    char me;
    int score;
    cin >> Round >> M >> N;
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            cin >> Graph[i][j];
    cin >> A >> B >> me;
    int x, y, rand_seed;
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            if(Graph[i][j] == me){
                x = i;
                y = j;
            }
    //printf("%d %d\n",x,y);/////////////////////
    if(me=='A')score=A;
    else score =B;
    cout << next_dir(x, y, score) << endl;
    
}
