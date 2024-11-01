#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_T 20
#define MAX_MASK (1<<20)
#define INF 1000000

int main(){
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);
    int P[21][21];
    for(int i=1;i<=M;i++) {
        for(int j=1;j<=N;j++) {
            scanf("%d",&P[i][j]);
        }
    }
    // List plants
    int T=0;
    int plants_x[MAX_T], plants_y[MAX_T], plants_p[MAX_T];
    for(int i=1;i<=M;i++) {
        for(int j=1;j<=N;j++) {
            if(P[i][j]>0){
                if(T >= MAX_T){
                    // Exceed maximum allowed plants
                    // Handle accordingly, here we limit to MAX_T
                    continue;
                }
                plants_x[T]=i;
                plants_y[T]=j;
                plants_p[T]=P[i][j];
                T++;
            }
        }
    }
    // Compute distance matrix
    int d[MAX_T+1][MAX_T+1];
    // Node 0 is road
    for(int a=0;a<=T;a++) {
        for(int b=0;b<=T;b++) {
            if(a==0 && b==0){
                d[a][b]=0;
            }
            else if(a==0){
                // road to b
                int min_d = INF;
                for(int j=1;j<=N;j++) {
                    int tmp = 1 + abs(plants_x[b-1]-1) + abs(plants_y[b-1]-j);
                    if(tmp < min_d) min_d = tmp;
                }
                d[a][b]=min_d;
            }
            else if(b==0){
                // a to road
                int min_d = INF;
                for(int j=1;j<=N;j++) {
                    int tmp = abs(plants_x[a-1]-1) + abs(plants_y[a-1]-j) +1;
                    if(tmp < min_d) min_d = tmp;
                }
                d[a][b]=min_d;
            }
            else{
                d[a][b]=abs(plants_x[a-1]-plants_x[b-1]) + abs(plants_y[a-1]-plants_y[b-1]);
            }
        }
    }
    // Initialize DP
    int DP[MAX_MASK][MAX_T];
    for(int m=0;m<(1<<T);m++) {
        for(int l=0;l<T;l++) {
            DP[m][l] = INF;
        }
    }
    // Starting from road, mask=0
    // No last node, handled separately
    // Iterate through all masks
    for(int m=0;m<(1<<T);m++) {
        for(int last=0; last<T; last++) {
            if( (m & (1<<last)) ){
                // Current mask includes last
                int prev_mask = m ^ (1<<last);
                if(prev_mask ==0){
                    // From road to last
                    if(d[0][last+1] +1 <= K){
                        if(DP[m][last] > d[0][last+1] +1){
                            DP[m][last] = d[0][last+1] +1;
                        }
                    }
                }
                else{
                    for(int pre=0; pre<T; pre++) {
                        if(pre != last && (prev_mask & (1<<pre))){
                            if(DP[prev_mask][pre] + d[pre+1][last+1] +1 <= K){
                                if(DP[m][last] > DP[prev_mask][pre] + d[pre+1][last+1] +1){
                                    DP[m][last] = DP[prev_mask][pre] + d[pre+1][last+1] +1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Now find the maximum P with DP[m][last] + d[last][0] <=K
    int max_P=0;
    for(int m=0;m<(1<<T);m++) {
        int sum_P=0;
        for(int i=0;i<T;i++) if(m & (1<<i)) sum_P += plants_p[i];
        for(int last=0; last<T; last++) {
            if( m & (1<<last) ){
                if(DP[m][last] + d[last+1][0] <= K){
                    if(sum_P > max_P){
                        max_P = sum_P;
                    }
                }
            }
        }
    }
    printf("%d\n", max_P);
}