#include <bits/stdc++.h>
using namespace std ;
float bfs( vector<vector<char> > arr , int x , int y , float score , int len , char player2 , int time ){
        if( time <= 1  ){
                return score ;
        }
        time -= 1 ;
        if( arr[y][x] == 's' ){
                if( score >= 0 ){
                        score =  score + 1000  ;
                }else{
                        score = score - 700 ;
                }
        }else if( arr[y][x] == 'm' ){
                score = score + 800 ;
        }else if( arr[y][x] == 'n' ){
                score = score - 300  ;  // 500
        }else if( arr[y][x] == 't' ){
                if( score == 0 ){
                        score += 200 ;   // 300
                }else{
                        score = score/2 - 700  ;  //   /2
                }
        }
        if( ( x != 0 )  && ( x != len-1 ) && ( y != 0 )  && ( y != len-1 )  ){
                score += 200 ;
        }
        char record = arr[y][x] ;
        arr[y][x] = '.' ;
        double result = score ;
        if( ( y != 0 ) && ( arr[y-1][x] != 'x' ) && ( arr[y-1][x] != player2 ) ){
                score = bfs( arr, x , y-1 , result , len , player2  , time );
        }
        if( ( y != len-1 ) && ( arr[y+1][x] != 'x' ) && ( arr[y+1][x] != player2 )  ){
                score = bfs( arr, x , y+1, result , len , player2 , time );
        }
        if( ( x != 0 ) && ( arr[y][x-1] != 'x' ) && ( arr[y][x-1] != player2 ) ){
                score = bfs( arr, x-1 , y , result , len , player2 , time );
        }
        if( ( x != len-1 )  && ( arr[y][x+1] != 'x' ) && ( arr[y][x+1] != player2 ) ){
                score = bfs( arr, x+1 , y , result , len , player2 , time );
        }
        arr[y][x] = record ;
        return score ;
}
int main( void ){
        int n ;
        scanf( "%d\n" , &n ) ;
        int len1 , len2 ;
        scanf( "%d %d\n" ,&len1 , &len2 );
        vector<vector<char> > arr( len1 , vector<char>(len2) ) ;
        for( int i = 0 ; i < len1 ; ++i ){
                for( int j = 0 ; j < len2 ; ++j ){
                        char tem ;
                        cin >> tem ;
                        arr[i][j] = tem ;
                }
        }
        float a_score , b_score ;
        scanf( "%f\n" , &a_score );
        scanf( "%f\n" , &b_score );
        char player1 , player2 ;
        float my_score ;
        scanf( "%c\n" , &player1 );
        if( player1 == 'A' ){
                player2 = 'B' ;
                my_score = a_score ;
        }
        if( player1 == 'B' ){
                player2 = 'A' ;
                my_score = b_score ;
        }
        int ax , ay ;
        int bx , by ;
        for( int i = 0 ; i < len1 ; ++i ){
                for( int j = 0 ; j < len2 ; ++j ){
                        if( arr[i][j] == player1 ){
                                ax = j ;
                                ay = i ;
                        }
                        if( arr[i][j] == player2 ){
                                bx = j ;
                                by = i ;
                        }
                }
        }
        int max_step = 0 ;
        if( ax > bx ){
                max_step += ( ax - bx );
        }else{
                max_step += ( bx - ax );
        }
        if( ay > by ){
                max_step += ( ay - by );
        }else{
                max_step += ( by - ay );
        }
        float dir[4] ;
        if( max_step > 7 ){
                max_step = 6 ;
        }else if( max_step < 2 ){
                max_step = 5 ;
        }
        if( ( ay == 0 ) || ( arr[ay-1][ax] == 'x' ) || ( arr[ay-1][ax] == player2 )){
                dir[0] = INT_MIN;
        }else{
                dir[0] = bfs( arr, ax , ay-1 , my_score , len1 , player2 , max_step  );   // up
        }
        if( ( ay == len1 - 1 ) || ( arr[ay+1][ax] == 'x' ) || ( arr[ay+1][ax] == player2 ) ){
                dir[1] = INT_MIN;
        }else{
                dir[1] = bfs( arr, ax , ay+1 , my_score , len1 , player2 , max_step );    // down
        }
        if( ( ax == 0 ) || ( arr[ay][ax-1] == 'x' ) || ( arr[ay][ax-1] == player2 ) ){
                dir[2] = INT_MIN;
        }else{
                dir[2] = bfs( arr ,  ax-1 ,  ay ,  my_score , len1 , player2 , max_step  );  //left
        }
        if( ( ax == len2 - 1 ) || ( arr[ay][ax+1] == 'x' ) || ( arr[ay][ax+1] == player2 ) ){
                dir[3] = INT_MIN;
        }else{
                dir[3] = bfs( arr, ax+1 ,  ay , my_score , len1 , player2 , max_step  );  //right
        }
        float max = -999999999 ;
        int max_place = -1 ;
        if( player1 == 'A' ){
                for( int i = 0 ; i < 4 ; ++i ){
                        if( dir[i] != INT_MIN ){
                                if( max <= dir[i] ){
                                        max = dir[i] ;
                                        max_place =  i ;
                                }
                        }
                }
        }
        if( player1 == 'B' ){
                for( int i = 0 ; i < 4 ; ++i ){
                        if( dir[i] != INT_MIN ){
                                if( max < dir[i] ){
                                        max = dir[i] ;
                                        max_place = i ;
                                }
                        }
                }
        }
        if( max_place == 0 ){
                printf( "UP\n");
        }else if( max_place == 1 ){
                printf( "DOWN\n" );
        }else if( max_place == 2 ){
                printf( "LEFT\n" );
        }else{
                printf( "RIGHT\n" );
        }
        return 0 ;
}