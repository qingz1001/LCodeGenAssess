#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 20
#define MAX_C 5

int main(){
    int n, m, cost1, cost2;
    scanf("%d %d %d %d", &n, &m, &cost1, &cost2);
    // Allocate grid
    int **grid = (int **)malloc((m+1) * sizeof(int *));
    for(int y=1; y<=m; y++){
        grid[y] = (int *)malloc((n+1) * sizeof(int));
        for(int x=1; x<=n; x++){
            scanf("%d", &grid[y][x]);
        }
    }
    long long best = -1e18;
    int best_c = 0, best_h = 0;
    for(int h=1; h<=m; h++){
        for(int c=1; c<=MAX_C; c++){
            // Check if h and c can be set without exceeding m
            // During simulation, ensure y <=m
            long long sum =0;
            int y_pos =1;
            int direction =1; // 1 for up, -1 for down
            int steps =0;
            int chains_remaining = c;
            int valid =1;
            int x=1;
            while(x <=n){
                if(direction ==1){
                    y_pos +=1;
                    steps +=1;
                    if(y_pos >m){
                        valid=0;
                        break;
                    }
                    if(grid[y_pos][x] == -1){
                        valid=0;
                        break;
                    }
                    sum += grid[y_pos][x];
                    x++;
                    if(steps ==h){
                        direction = -1;
                        steps =0;
                    }
                }
                else{
                    if(chains_remaining >0){
                        // Chain jump
                        y_pos +=1;
                        chains_remaining--;
                        direction =1;
                        steps =1;
                        if(y_pos >m){
                            valid=0;
                            break;
                        }
                        if(grid[y_pos][x] == -1){
                            valid=0;
                            break;
                        }
                        sum += grid[y_pos][x];
                        x++;
                        if(steps ==h){
                            direction = -1;
                            steps =0;
                        }
                    }
                    else{
                        y_pos -=1;
                        steps +=1;
                        if(y_pos <1){
                            valid=0;
                            break;
                        }
                        if(grid[y_pos][x] == -1){
                            valid=0;
                            break;
                        }
                        sum += grid[y_pos][x];
                        x++;
                        if(steps ==h){
                            direction =1;
                            steps =0;
                        }
                    }
                }
            }
            if(valid){
                long long total = sum - (long long)(cost1)*(h-1) - (long long)(cost2)*(c-1);
                if(total > best){
                    best = total;
                    best_c = c;
                    best_h = h;
                }
                else if(total == best){
                    if(c < best_c){
                        best_c =c;
                        best_h =h;
                    }
                    else if(c == best_c && h < best_h){
                        best_h =h;
                    }
                }
            }
        }
    }
    if(best == -1e18){
        printf("mission failed");
    }
    else{
        printf("%lld %d %d", best, best_c, best_h);
    }
    // Free grid
    for(int y=1; y<=m; y++) free(grid[y]);
    free(grid);
    return 0;
}