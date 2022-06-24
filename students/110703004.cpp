#include <stdio.h>
#include <limits.h>

//debug
#define DEBUG_INITIALIZE 0
#define DEBUG_CLOSED 0
#define DEBUG_ZONIFY 0
#define DEBUG_GREEDY_REPEATABLE_DFS 0
#define DEBUG_SHOWDOWN 0
#define DEBUG_DECIDE_WINNER 0
#define DEBUG_GREEDY_SINGLE_DFS 0
#define DEBUG_STEP_SORT 0
#define RUNTIME 1

//parameter
#define DEPTH_LIMIT_HEURISTIC_SINGLE_DFS 5
#define DEPTH_LIMIT_ALPHA_BETA_PRUNE 3
#define SHOWDOWN_GREED_DEPTH 10
#define DANGER_DISTENCE 3
#define ORIGIN_SCORE_SCALING 35
#define DISTANCE_PARAMETER 100

//const
#define ME 0
#define OPPONENT 1
#define ROW 0
#define COL 1
const int MOVING_EFFECT[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
const char DIR_NAME[4][10] = {"UP","DOWN","LEFT","RIGHT"};

typedef enum _HeuristicVersion{
        SINGLE_DFS = 0,
        REPEATABLE_DFS,
}HeuristicVersion;

//given variable
int turnStarted;
int mapSize[2];
int map[21][21];
int playerPosition[2][2];
int playerScore[2];

//variable generated by func
int dangerZone[21][21] = {};
int repeatableDFSRecord[21][21] = {};
int singleDFSRecord[21][21] = {};
int leaveRecord[100][100] = {};
int leaveCnt[100]={};

//variable generated by given variable
int chaser;
int objectLeftSum = 0;
int objectLeftProduct = 1;
int playerStuned[2] = {};
int lastStep[2];
int nowScore[2];

//tools func
int abs(int a);
int max(int a, int b);
int min(int a, int b);
void swap(int* a, int* b);
int valid(int row, int col);
int get_distence();
int apply_item_effect_score(int score, char item);
int apply_item_effect_board(int score, char item);

//unique func
void initialize();
int closed(int row, int col, int originDirection);
void encoding(int row, int col, int gap, int distance);
void zonify();
int greed_single_DFS(int row, int col, int score, int depth, int limit, int initialScore);
int showdown();
int decide_winner();
void step_sort(int* decisionEval, int* order);
int alpha_beta_prune(int identity, int depth, int alpha, int beta);
int greed_repeatable_DFS(int row, int col, int score, int depth, int limit);

int main(){
    if(RUNTIME == 1){
        initialize();
        zonify();
        int winningMove = showdown();
        if(winningMove != -1&&valid(playerPosition[ME][ROW]+MOVING_EFFECT[winningMove][ROW],playerPosition[ME][COL]+MOVING_EFFECT[winningMove][COL]) == 1)
            printf("%s\n", DIR_NAME[winningMove]);
        else{
            int bestDicision = 0;
            int maxEval = INT_MIN;
            int flag = 0;
            map[playerPosition[ME][ROW]][playerPosition[ME][COL]] = '.';
            for(int i=0;i<4;++i){
                lastStep[OPPONENT] = -1;
                lastStep[ME] = i;
                if(valid(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW],playerPosition[ME][COL]+MOVING_EFFECT[i][COL])){
                    nowScore[ME] = playerScore[ME];
                    nowScore[OPPONENT] = playerScore[OPPONENT];
                    playerPosition[ME][ROW]+=MOVING_EFFECT[i][ROW];
                    playerPosition[ME][COL]+=MOVING_EFFECT[i][COL];
                    int tmp = alpha_beta_prune(ME, 0, maxEval, INT_MAX);
                    if(tmp > maxEval){
                        flag = 1;
                        maxEval = tmp;
                        bestDicision = i;
                    }
                    playerPosition[ME][ROW]-=MOVING_EFFECT[i][ROW];
                    playerPosition[ME][COL]-=MOVING_EFFECT[i][COL];
                }
            }
            map[playerPosition[ME][ROW]][playerPosition[ME][COL]] = '0';
            if(flag == 1&&valid(playerPosition[ME][ROW] + MOVING_EFFECT[bestDicision][ROW],playerPosition[ME][COL] + MOVING_EFFECT[bestDicision][COL]) == 1)
                    printf("%s\n", DIR_NAME[bestDicision]);
            else{
                int worseDecision = 0;
                int max = INT_MIN;
                for(int i=0;i<4;++i){
                    int tmp = greed_single_DFS(playerPosition[ME][ROW] + MOVING_EFFECT[i][ROW],playerPosition[ME][COL] + MOVING_EFFECT[i][COL],playerScore[ME],0,10000,playerScore[ME]);
                    if(tmp > max){
                        max = tmp;
                        worseDecision = i;
                    }
                }
                printf("%s\n", DIR_NAME[worseDecision]);
            }
        }
    }
    if(DEBUG_INITIALIZE == 1){
        initialize();
        printf("turnStarted:%d\n", turnStarted);
        printf("mapSize[ROW]:%d mapSize[COL]:%d\n",mapSize[ROW],mapSize[COL]);
        for(int i=0;i<mapSize[ROW];++i){
            for(int j=0;j<mapSize[COL];++j)
                printf("%c ", map[i][j]);
            printf("\n");
        }
        printf("playerPosition[ME][ROW]:%d playerPosition[ME][COL]:%d\n", playerPosition[ME][ROW], playerPosition[ME][COL]);
        printf("playerPosition[OPPONENT][ROW]:%d playerPosition[OPPONENT][COL]:%d\n", playerPosition[OPPONENT][ROW], playerPosition[OPPONENT][COL]);
        printf("playerScore[ME]:%d playerScore[OPPONENT]:%d\n",playerScore[ME] ,playerScore[OPPONENT]);
        printf("chaser:%d\n", chaser);
        printf("objectLeftSum:%d objectLeftProduct:%d\n", objectLeftSum, objectLeftProduct);
    }
    if(DEBUG_CLOSED == 1){
        initialize();
        zonify();
        int row, col, dir;
        scanf("%d %d %d",&row, &col, &dir);
        printf("%d\n", closed(row, col, dir));
    }
    if(DEBUG_ZONIFY == 1){
        initialize();
        zonify();
        for(int i=0;i<mapSize[ROW];++i){
            for(int j=0;j<mapSize[COL];++j)
                printf("%5d ", dangerZone[i][j]);
            printf("\n");
        }
    }
    if(DEBUG_GREEDY_REPEATABLE_DFS == 1){
        initialize();
        zonify();
        int greedyMe = INT_MIN;
        int greedyOpponent = INT_MIN;
        for(int i=0;i<4;++i){
            int tmpMe;
            int tmpOpponent;
            tmpMe = greed_repeatable_DFS(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW], playerPosition[ME][COL]+MOVING_EFFECT[i][COL], playerScore[ME], 0, SHOWDOWN_GREED_DEPTH);
            tmpOpponent = greed_repeatable_DFS(playerPosition[OPPONENT][ROW]+MOVING_EFFECT[i][ROW], playerPosition[OPPONENT][COL]+MOVING_EFFECT[i][COL], playerScore[OPPONENT], 0, SHOWDOWN_GREED_DEPTH);
            greedyMe = max(greedyMe,tmpMe);
            greedyOpponent = max(greedyOpponent,tmpOpponent);
            printf("score:%d %d\n", playerScore[ME], playerScore[OPPONENT]);
            printf("position:ME:(%d,%d) position:OPPONENT:(%d,%d)\n",playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW],playerPosition[ME][COL]+MOVING_EFFECT[i][COL],playerPosition[OPPONENT][ROW]+MOVING_EFFECT[i][ROW],playerPosition[OPPONENT][COL]+MOVING_EFFECT[i][COL]);
            printf("greedy:%d %d\n", tmpMe,tmpOpponent);
        }
        printf("ME:%d\n",greedyMe);
        printf("OPPONENT:%d\n", greedyOpponent);
    }
    if(DEBUG_SHOWDOWN == 1){
        initialize();
        zonify();
        printf("step:%d\n",showdown());
        if(chaser == ME){
            int dangerousityMe = dangerZone[playerPosition[ME][ROW]][playerPosition[ME][COL]];
            int dangerousityOpponent = dangerZone[playerPosition[OPPONENT][ROW]][playerPosition[OPPONENT][COL]];
            if(dangerousityMe>dangerousityOpponent && abs(dangerousityMe-dangerousityOpponent)<51)
                    printf("zoned out\n");
        }
        if(playerScore[ME]>(playerScore[OPPONENT]+objectLeftSum)*objectLeftProduct){
            int bestDicision = 0;
            int maxEval;
            for(int i=0;i<4;i++){
                int greedyMax = INT_MIN;
                for(int j=0;j<4;++j){
                    greedyMax = max(greedyMax,greed_repeatable_DFS(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW]+MOVING_EFFECT[j][ROW], playerPosition[ME][COL]+MOVING_EFFECT[i][COL]+MOVING_EFFECT[j][COL], playerScore[ME], 0, SHOWDOWN_GREED_DEPTH));
                }
                int tmp = greedyMax;
                printf("%d:%d ",i, tmp);
                if(tmp > maxEval){
                    maxEval = tmp;
                    bestDicision = i;
                }
            }
            printf("\nbest decision:%d\n", bestDicision);
        }
    }
    if(DEBUG_DECIDE_WINNER == 1){
        initialize();
        zonify();
        printf("winner:%d\n", decide_winner());
    }
    if(DEBUG_GREEDY_SINGLE_DFS == 1){
        initialize();
        zonify();
        int greedyMe = INT_MIN;
        int greedyOpponent = INT_MIN;
        int best = -1;
        for(int i=0;i<4;++i){
            printf("score:%d %d\n", playerScore[ME], playerScore[OPPONENT]);
            printf("position:ME:(%d,%d) position:OPPONENT:(%d,%d)\n",playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW],playerPosition[ME][COL]+MOVING_EFFECT[i][COL],playerPosition[OPPONENT][ROW]+MOVING_EFFECT[i][ROW],playerPosition[OPPONENT][COL]+MOVING_EFFECT[i][COL]);
            if(greedyMe<greed_single_DFS(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW], playerPosition[ME][COL]+MOVING_EFFECT[i][COL], playerScore[ME], 0, DEPTH_LIMIT_HEURISTIC_SINGLE_DFS, playerScore[ME]))
                    best = i;
            greedyMe = max(greedyMe,greed_single_DFS(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW], playerPosition[ME][COL]+MOVING_EFFECT[i][COL], playerScore[ME], 0, DEPTH_LIMIT_HEURISTIC_SINGLE_DFS, playerScore[ME]));
            greedyOpponent = max(greedyOpponent,greed_single_DFS(playerPosition[OPPONENT][ROW]+MOVING_EFFECT[i][ROW], playerPosition[OPPONENT][COL]+MOVING_EFFECT[i][COL], playerScore[OPPONENT], 0, DEPTH_LIMIT_HEURISTIC_SINGLE_DFS, playerScore[OPPONENT]));
            printf("greedy:%d %d\n", greedyMe,greedyOpponent);
        }
        printf("ME:%d\n", greedyMe);
        printf("OPPONENT:%d\n", greedyOpponent);
    }
    if(DEBUG_STEP_SORT == 1){
        int val[4];
        int index[4];
        for(int i=0;i<4;++i){
            scanf("%d %d",&index[i], &val[i]);
        }
        step_sort(val, index);
        for(int i=0;i<4;++i)
            printf("%d index%d:%d\n",i,index[i],val[i]);
    }
    return 0;
}

int alpha_beta_prune(int identity, int depth, int alpha, int beta){
    int nowScoreRecird = nowScore[identity];
    int stunMe =  playerStuned[ME];
    int stunOppenent = playerStuned[OPPONENT];
    char item = map[playerPosition[identity][ROW]][playerPosition[identity][COL]];
    int recordScore = playerScore[identity];
    int recordChaser = chaser;
    int stunedDuration = 0;
    if(item == 'b'){
        chaser = (chaser+1)%2;
        playerStuned[identity] = 3;
    }
    else
        playerScore[identity] = apply_item_effect_board(playerScore[identity], item);
    int winner = decide_winner();
    nowScore[identity] += playerScore[identity];
    if(winner == ME)
        return INT_MAX;
    if(winner == OPPONENT)
        return INT_MIN;
    if(depth >= DEPTH_LIMIT_ALPHA_BETA_PRUNE||(depth/2+1)+turnStarted>1000){
        if(DEPTH_LIMIT_HEURISTIC_SINGLE_DFS == -1)
            return (playerScore[ME]-playerScore[OPPONENT])*ORIGIN_SCORE_SCALING;
        int greedyMe = INT_MIN;
        int greedyOpponent = INT_MIN;
        int flagM = 0;
        int flagO = 0;
        for(int i=0;i<4;++i){
            if(valid(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW],playerPosition[ME][COL]+MOVING_EFFECT[i][COL]) == 1){
                flagM = 1;
                greedyMe = max(greedyMe,greed_single_DFS(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW], playerPosition[ME][COL]+MOVING_EFFECT[i][COL], playerScore[ME], 0, DEPTH_LIMIT_HEURISTIC_SINGLE_DFS,playerScore[ME]));
            }
            if(valid(playerPosition[OPPONENT][ROW]+MOVING_EFFECT[i][ROW],playerPosition[OPPONENT][COL]+MOVING_EFFECT[i][COL]))
                flagO = 1;
            greedyOpponent = max(greedyOpponent,greed_single_DFS(playerPosition[OPPONENT][ROW]+MOVING_EFFECT[i][ROW], playerPosition[OPPONENT][COL]+MOVING_EFFECT[i][COL], playerScore[OPPONENT], 0, DEPTH_LIMIT_HEURISTIC_SINGLE_DFS,playerScore[OPPONENT]));
        }
        return (greedyMe*flagM - greedyOpponent*flagO) + ((nowScore[ME]-nowScore[OPPONENT])*ORIGIN_SCORE_SCALING);
    }
    int opposite = (identity+1)%2;
    if(playerStuned[opposite]>0){
        --playerStuned[opposite];
        if(identity == ME){
            map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = '0';
            int tmp = alpha_beta_prune(opposite, depth+1, alpha, beta);
            map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = item;
            if(item == 'm')
                    ++objectLeftSum;
            if(item == 's')
                    objectLeftProduct *= 2;
            playerScore[identity] = recordScore;
            chaser = recordChaser;
            playerStuned[ME] = stunMe;
            playerStuned[OPPONENT] = stunOppenent;
            nowScore[identity] = nowScoreRecird;
            return tmp;
        }
        else{
            map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = '1';
            int tmp = alpha_beta_prune(opposite, depth+1, alpha, beta);
            map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = item;
            if(item == 'm')
                    ++objectLeftSum;
            if(item == 's')
                    objectLeftProduct *= 2;
            playerScore[identity] = recordScore;
            chaser = recordChaser;
            playerStuned[ME] = stunMe;
            playerStuned[OPPONENT] = stunOppenent;
            nowScore[identity] = nowScoreRecird;
            return tmp;
        }
    }
    int order[4];
    int decisionEval[4] = {};
    for(int i=0;i<4;++i){
        int rowCurrentStep = playerPosition[opposite][ROW]+MOVING_EFFECT[i][ROW];
        int colCurrentStep = playerPosition[opposite][COL]+MOVING_EFFECT[i][COL];
        order[i] = i;
        if(valid(rowCurrentStep, colCurrentStep) == 0){
            decisionEval[i] = INT_MIN;
            continue;
        }
        switch(map[rowCurrentStep][colCurrentStep]){
            case 'm':
                decisionEval[i] = 10;
                break;
            case 'n':
                decisionEval[i] = -10;
                break;
            case 's':
                decisionEval[i] = 20;
                break;
            case 't':
                decisionEval[i] = -20;
                break;
            case 'b':
                decisionEval[i] = -15;
                break;
        }
        if((i-1+(1-i%2)*2) == lastStep[opposite])
            decisionEval[i] -= 12;
        if(dangerZone[rowCurrentStep][colCurrentStep]!=0){
            decisionEval[i]-=4;
            if(get_distence() <=DANGER_DISTENCE){
                    decisionEval[i] -= abs(dangerZone[rowCurrentStep][colCurrentStep]);
            }
        }
    }

    step_sort(decisionEval, order);

    if(identity == ME){
        map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = '0';
        map[playerPosition[opposite][ROW]][playerPosition[opposite][COL]] = '.';
        int minEval = INT_MAX;
        for(int i=0;i<4;++i){
            if(decisionEval[i] != INT_MIN){
                lastStep[opposite] = i;
                playerPosition[opposite][ROW] += MOVING_EFFECT[order[i]][ROW];
                playerPosition[opposite][COL] += MOVING_EFFECT[order[i]][COL];
                int tmp = alpha_beta_prune(OPPONENT, depth+1, alpha, beta);
                minEval = min(minEval, tmp);
                beta = min(beta, minEval);
                playerPosition[opposite][ROW] -= MOVING_EFFECT[order[i]][ROW];
                playerPosition[opposite][COL] -= MOVING_EFFECT[order[i]][COL];
                if(beta<alpha)
                        break;
            }
        }
        map[playerPosition[opposite][ROW]][playerPosition[opposite][COL]] = '1';
        map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = item;
        if(item == 'm')
            ++objectLeftSum;
        if(item == 's')
            objectLeftProduct *= 2;
        playerScore[identity] = recordScore;
        chaser = recordChaser;
        playerStuned[ME] = stunMe;
        playerStuned[OPPONENT] = stunOppenent;
        nowScore[identity] = nowScoreRecird;
        return minEval;
    }
    else{
        map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = '1';
        map[playerPosition[opposite][ROW]][playerPosition[opposite][COL]] = '.';
        int maxEval = INT_MIN;
        for(int i=0;i<4;++i){
            if(decisionEval[i] != INT_MIN){
                lastStep[opposite] = i;
                playerPosition[opposite][ROW] += MOVING_EFFECT[order[i]][ROW];
                playerPosition[opposite][COL] += MOVING_EFFECT[order[i]][COL];
                int tmp = alpha_beta_prune(ME, depth+1, alpha, beta);
                maxEval = max(maxEval, tmp);
                alpha = max(alpha, maxEval);
                playerPosition[opposite][ROW] -= MOVING_EFFECT[order[i]][ROW];
                playerPosition[opposite][COL] -= MOVING_EFFECT[order[i]][COL];
                if(beta<alpha)
                        break;
            }
        }
        map[playerPosition[opposite][ROW]][playerPosition[opposite][COL]] = '0';
        map[playerPosition[identity][ROW]][playerPosition[identity][COL]] = item;
        if(item == 'm')
            ++objectLeftSum;
        if(item == 's')
            objectLeftProduct *= 2;
        playerScore[identity] = recordScore;
        chaser = recordChaser;
        playerStuned[ME] = stunMe;
        playerStuned[OPPONENT] = stunOppenent;
        nowScore[identity] = nowScoreRecird;
        return maxEval;
    }
}

void initialize(){
    scanf("%d", &turnStarted);
    scanf("%d %d", &mapSize[ROW], &mapSize[COL]);
    int APosition[2];
    int BPosition[2];
    for(int i=0;i<mapSize[ROW];++i)
        for (int j=0;j<mapSize[COL];++j){
            scanf(" %c", &map[i][j]);
            switch(map[i][j]){
                case'A':
                    APosition[ROW] = i;
                    APosition[COL] = j;
                    break;
                case'B':
                    BPosition[ROW] = i;
                    BPosition[COL] = j;
                    break;
                case'm':
                    ++objectLeftSum;
                    break;
                case's':
                    objectLeftProduct *= 2;
                    break;
            }
        }
    int AScore ,BScore;
    scanf(" %d %d", &AScore, &BScore);
    char authority;
    scanf(" %c", &authority);
    if(authority == 'A'){
        playerScore[ME] = AScore;
        playerScore[OPPONENT] = BScore;
        playerPosition[ME][ROW] = APosition[ROW];
        playerPosition[ME][COL] = APosition[COL];
        playerPosition[OPPONENT][ROW] = BPosition[ROW];
        playerPosition[OPPONENT][COL] = BPosition[COL];
    }
    else{
        playerScore[ME] = BScore;
        playerScore[OPPONENT] = AScore;
        playerPosition[ME][ROW] = BPosition[ROW];
        playerPosition[ME][COL] = BPosition[COL];
        playerPosition[OPPONENT][ROW] = APosition[ROW];
        playerPosition[OPPONENT][COL] = APosition[COL];
    }
    map[playerPosition[ME][ROW]][playerPosition[ME][COL]] = '0';
    map[playerPosition[OPPONENT][ROW]][playerPosition[OPPONENT][COL]] = '1';
    chaser = get_distence()%2;
    return;
}

int closed(int row, int col, int originDirection){
    int flag = -1;
    for(int i=0;i<4;++i){
        if(i == originDirection)
            continue;
        if(row+MOVING_EFFECT[i][ROW] < 0||row+MOVING_EFFECT[i][ROW] >= mapSize[ROW]||col+MOVING_EFFECT[i][COL]< 0||col+MOVING_EFFECT[i][COL] >= mapSize[COL])
            continue;
        if(map[row+MOVING_EFFECT[i][ROW]][col+MOVING_EFFECT[i][COL]]!='x')
            if(flag!=-1)
                return -1;
        else
            flag = i;
    }
    return flag;
}

void encoding(int row, int col, int gap, int distance){
    static int code = 0;
    if(distance == 1)
        code++;
    if(dangerZone[row][col]!=0)
        return;
    dangerZone[row][col] = code*100 + distance;
    dangerZone[mapSize[ROW]-row-1][mapSize[COL]-col-1] = code*(-100) + distance;
    if(gap == -1)
        return;
    int closion = closed(row+MOVING_EFFECT[gap][ROW], col+MOVING_EFFECT[gap][COL], gap-1+(1-gap%2)*2);
    encoding(row+MOVING_EFFECT[gap][ROW], col+MOVING_EFFECT[gap][COL], closion, distance+1);
    return;
}

void zonify(){
    for(int i = 0;i<(min(mapSize[ROW], mapSize[COL])+1)/2;++i){
        for(int j = i;j<mapSize[COL]-i;++j){
            if(dangerZone[i][j] == 0 && map[i][j] != 'x'){
                int closion = closed(i, j, -1);
                if(closion != -1)
                    encoding(i, j, closion, 1);
            }
        }
        for(int j = i+1;j<mapSize[ROW]-i-1;++j){
            if(dangerZone[j][mapSize[COL]-i-1] == 0 && map[j][mapSize[COL]-i-1] != 'x'){
                int closion = closed(j, mapSize[COL]-i-1, -1);
                if(closion != -1)
                    encoding(j, mapSize[COL]-i-1, closion, 1);
            }
        }
    }
}

int greed_repeatable_DFS(int row, int col, int score, int depth, int limit){
    if(depth >= limit)
        return score;
    if(valid(row, col) == 0)
        return INT_MIN;
    int newScore = score;
    int stunedDuration = 0;
    int flag = 0;
    if(repeatableDFSRecord[row][col] == 0){
        if(map[row][col] == 'b')
            stunedDuration = 3;
        else
            newScore = apply_item_effect_score(newScore, map[row][col]);
        repeatableDFSRecord[row][col] = 1;
        flag =1;
    }
    int maxL = INT_MIN;
    for(int i=0;i<4;++i)
        maxL = max(maxL, greed_repeatable_DFS(row+MOVING_EFFECT[i][ROW], col+MOVING_EFFECT[i][COL], newScore, depth+1+stunedDuration, limit));
    if(flag == 1)
        repeatableDFSRecord[row][col] = 0;
    return maxL;
}

int showdown(){
    if(chaser == ME){
        int dangerousityMe = dangerZone[playerPosition[ME][ROW]][playerPosition[ME][COL]];
        int dangerousityOpponent = dangerZone[playerPosition[OPPONENT][ROW]][playerPosition[OPPONENT][COL]];
        if(dangerousityMe>dangerousityOpponent && abs(dangerousityMe-dangerousityOpponent)<51){
            for(int i=0;i<4;++i){
                if(dangerZone[playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW]][playerPosition[ME][COL]+MOVING_EFFECT[i][COL]] < dangerousityMe){
                    if(valid(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW], playerPosition[ME][COL]+MOVING_EFFECT[i][COL]) == 1)
                        return i;
                }
            }
        }
    }
    if(playerScore[ME]>(playerScore[OPPONENT]+objectLeftSum)*objectLeftProduct){
        int bestDicision = -1;
        int maxEval = INT_MIN;
        for(int i=0;i<4;i++){
            int tmp = greed_single_DFS(playerPosition[ME][ROW]+MOVING_EFFECT[i][ROW], playerPosition[ME][COL]+MOVING_EFFECT[i][COL], playerScore[ME], 0, 10,playerScore[ME]);
            if(tmp > maxEval){
                maxEval = tmp;
                bestDicision = i;
            }
        }
        if(valid(playerPosition[ME][ROW]+MOVING_EFFECT[bestDicision][ROW], playerPosition[ME][COL]+MOVING_EFFECT[bestDicision][COL]) == 1)
            return bestDicision;
    }
    return -1;
}

int decide_winner(){
    int dangerousity = dangerZone[playerPosition[chaser][ROW]][playerPosition[chaser][COL]]-dangerZone[playerPosition[(chaser+1)%2][ROW]][playerPosition[(chaser+1)%2][COL]];
    if(dangerousity>0&&dangerousity<50)
        return chaser;
    if(playerScore[ME]>(playerScore[OPPONENT]+objectLeftSum)*objectLeftProduct)
        return ME;
    if(playerScore[OPPONENT]>(playerScore[ME]+objectLeftSum)*objectLeftProduct)
        return OPPONENT;
    return -5;
}

int greed_single_DFS(int row, int col, int score, int depth, int limit, int initialScore){
    if(depth >= limit||singleDFSRecord[row][col] == 1)
        return (score - initialScore)*DISTANCE_PARAMETER/(depth+1);
    if(valid(row, col) == 0)
        return INT_MIN;
    singleDFSRecord[row][col] = 1;
    int newScore = score;
    int stunedDuration = 0;
    if(map[row][col] == 'b')
        stunedDuration = 3;
    else
        newScore = apply_item_effect_score(newScore, map[row][col]);
    int maxL = INT_MIN;
    for(int i=0;i<4;++i)
        maxL = max(maxL, greed_single_DFS(row+MOVING_EFFECT[i][ROW], col+MOVING_EFFECT[i][COL], newScore, depth+1+stunedDuration, limit, initialScore));
    maxL = max(maxL, (score - initialScore)*DISTANCE_PARAMETER/(depth+1));
    singleDFSRecord[row][col] = 0;
    return maxL;
}

void step_sort(int* decisionEval, int* order){
    for(int i=0;i<3;++i){
        for(int j=0;j<3-i;++j){
            if(decisionEval[j]<decisionEval[j+1]){
                swap((decisionEval+j),(decisionEval+j+1));
                swap((order+j),(order+j+1));
            }
        }
    }
}

int abs(int a){
    if(a<0)
        return -a;
    return a;
}

int max(int a, int b){
    if(a>b)
        return a;
    return b;
}

int min(int a, int b){
    if(a<b)
        return a;
    return b;
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int valid(int row, int col){
    if(row<0||row>=mapSize[ROW]||col<0||col>=mapSize[COL])
        return 0;
    if(map[row][col] == 'x'||map[row][col] == '0'||map[row][col] =='1')
        return 0;
    return 1;
}

int get_distence(){
    return abs(playerPosition[ME][ROW]-playerPosition[OPPONENT][ROW])+abs(playerPosition[ME][COL]-playerPosition[OPPONENT][COL]);
}


int apply_item_effect_score(int score, char item){
    switch(item){
        case'm':
            return score+1;
        case'n':
            return score-1;
        case's':
            return score*2;
        case't':
            return score/2;
    }
    return score;
}

int apply_item_effect_board(int score, char item){
    switch(item){
        case'm':
            --objectLeftSum;
            return score+1;
        case'n':
            return score-1;
        case's':
            objectLeftProduct/=2;
            return score*2;
        case't':
            return score/2;
    }
    return score;
}