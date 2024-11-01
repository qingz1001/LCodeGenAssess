#include <stdio.h>
#include <stdlib.h>

#define MAX_M 21
#define MAX_N 100001

int grid[MAX_M][100001];

int main(){
    int n, m, cost1, cost2;
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    for(int y=1; y<=m; y++){
        for(int x=1; x<=n; x++){
            scanf("%d", &grid[y][x]);
        }
    }
    long long max_sum = -1e18;
    int min_l = 0, min_h = 0;
    for(int h=1; h<m; h++){
        for(int l=1; l<=5; l++){
            if(1 + h > m){
                continue;
            }
            int y = 1;
            int direction = 1; // 1 for up, -1 for down
            int jumps_left = l;
            // Check starting cell
            if(grid[y][1] == -1){
                continue;
            }
            long long sum = grid[y][1];
            int valid = 1;
            for(int x=2; x<=n; x++){
                if(direction ==1){
                    y +=1;
                    if(y ==1 + h){
                        direction = -1;
                    }
                }
                else{
                    y -=1;
                    if(y ==1){
                        if(jumps_left >0){
                            direction =1;
                            jumps_left--;
                        }
                    }
                }
                if(y <1 || y >m || grid[y][x]==-1){
                    valid =0;
                    break;
                }
                sum += grid[y][x];
            }
            if(valid){
                if(sum > max_sum){
                    max_sum = sum;
                    min_l = l;
                    min_h = h;
                }
                else if(sum == max_sum){
                    if(l < min_l){
                        min_l = l;
                        min_h = h;
                    }
                    else if(l == min_l){
                        if(h < min_h){
                            min_h = h;
                        }
                    }
                }
            }
        }
    }
    if(max_sum == -1e18){
        printf("mission failed");
    }
    else{
        printf("%lld %d %d", max_sum, min_l, min_h);
    }
    return 0;
}