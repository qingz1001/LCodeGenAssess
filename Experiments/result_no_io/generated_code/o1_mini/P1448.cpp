#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int s;
} Triangle;

int main(){
    int N,M;
    scanf("%d",&N);
    scanf("%d",&M);
    // Maximum y per row is 2*N
    int blocked[N+2][2*N+2];
    memset(blocked, 0, sizeof(blocked));
    for(int i=0;i<M;i++){
        int X,Y;
        scanf("%d %d",&X,&Y);
        blocked[X][Y] =1;
    }
    // dp[x][y] = max size of triangle with top at (x,y)
    int dp[N+2][2*N+2];
    memset(dp, 0, sizeof(dp));
    for(int x=N;x>=1;x--){
        for(int y=1;y<=2*x-1;y++){
            if(!blocked[x][y]){
                if(x ==N){
                    dp[x][y]=1;
                }
                else{
                    if(y+2 >2*(x+1)-1){
                        dp[x][y]=1;
                    }
                    else{
                        int min = dp[x+1][y] < dp[x+1][y+2] ? dp[x+1][y] : dp[x+1][y+2];
                        dp[x][y] = min +1;
                    }
                }
            }
            else{
                dp[x][y]=0;
            }
        }
    }
    // Collect all possible triangles
    Triangle list[1000000];
    int count=0;
    for(int s=1;s<=N;s++){
        for(int x=1;x<=N-s+1;x++){
            for(int y=1;y<=2*x-1;y++){
                if(dp[x][y] >=s){
                    list[count].x =x;
                    list[count].y =y;
                    list[count].s =s;
                    count++;
                }
            }
        }
    }
    // Sort list descending by s
    for(int i=0;i<count-1;i++){
        for(int j=i+1;j<count;j++){
            if(list[j].s > list[i].s){
                Triangle temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    int max_sum=0;
    for(int i=0;i<count;i++){
        Triangle A = list[i];
        int areaA = A.s * A.s;
        for(int j=i+1;j<count;j++){
            Triangle B = list[j];
            int areaB = B.s * B.s;
            if(areaA + areaB <= max_sum){
                break;
            }
            // Check overlap
            int overlap=0;
            // Rows occupied by A
            for(int a=0;a<A.s && !overlap;a++){
                int rowA = A.x +a;
                int yA_start = A.y;
                int yA_end = A.y + 2*a;
                // Rows occupied by B
                for(int b=0;b<B.s && !overlap;b++){
                    int rowB = B.x +b;
                    if(rowB < rowA || rowB > rowA){
                        continue;
                    }
                    if(rowB != rowA){
                        continue;
                    }
                    int yB_start = B.y;
                    int yB_end = B.y + 2*b;
                    if(!(yA_end < yB_start || yB_end < yA_start)){
                        overlap=1;
                    }
                }
            }
            if(!overlap){
                if(areaA + areaB > max_sum){
                    max_sum = areaA + areaB;
                }
                break;
            }
        }
    }
    printf("%d",max_sum);
}