#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 101
#define MAXY 201

int N, M;
int available[MAXN][MAXY];
int dp_max[MAXN][MAXY];

// Function to compute the maximum triangle size on the current available grid
int compute_max_triangle() {
    // Initialize dp_max to 0
    memset(dp_max, 0, sizeof(dp_max));
    int max_size = 0;
    for(int x = N; x >=1; x--){
        for(int y =1; y <= 2*x-1; y++){
            if(available[x][y]){
                if(x == N){
                    dp_max[x][y] =1;
                }
                else{
                    if(y-1 >=1 && y+1 <= 2*(x+1)-1){
                        int min_val = dp_max[x+1][y-1];
                        if(dp_max[x+1][y] < min_val) min_val = dp_max[x+1][y];
                        if(dp_max[x+1][y+1] < min_val) min_val = dp_max[x+1][y+1];
                        dp_max[x][y] = 1 + min_val;
                    }
                    else{
                        dp_max[x][y] =1;
                    }
                }
                if(dp_max[x][y] > max_size) max_size = dp_max[x][y];
            }
        }
    }
    return max_size;
}

int main(){
    scanf("%d", &N);
    scanf("%d", &M);
    // Initialize available grid to 1
    for(int x=1; x<=N; x++){
        for(int y=1; y<=2*x-1; y++) available[x][y] =1;
    }
    // Mark bad cells
    for(int i=0; i<M; i++){
        int X, Y;
        scanf("%d %d", &X, &Y);
        if(X >=1 && X <=N && Y >=1 && Y <=2*X-1){
            available[X][Y] =0;
        }
    }
    int max_sum =0;
    // Iterate over all possible s1 from N downto1
    for(int s1 =N; s1 >=1; s1--){
        // Iterate over possible x
        for(int x=1; x<=N - s1 +1; x++){
            // Iterate over possible y
            for(int y=1; y<=2*x-1; y++){
                // Check if a triangle of size s1 can be placed at (x,y)
                int can_place =1;
                for(int t=0; t<s1 && can_place; t++){
                    int current_x = x + t;
                    int start_y = y - t;
                    int end_y = y + t;
                    if(start_y <1 || end_y > 2*current_x -1){
                        can_place =0;
                        break;
                    }
                    for(int dy = start_y; dy <= end_y; dy++){
                        if(!available[current_x][dy]){
                            can_place =0;
                            break;
                        }
                    }
                }
                if(can_place){
                    // Mark the cells as blocked
                    for(int t=0; t<s1; t++){
                        int current_x = x + t;
                        int start_y = y - t;
                        int end_y = y + t;
                        for(int dy = start_y; dy <= end_y; dy++){
                            available[current_x][dy] =0;
                        }
                    }
                    // Compute the maximum triangle size on the remaining grid
                    int s2 = compute_max_triangle();
                    // Update max_sum
                    int current_sum = s1 * s1 + s2 * s2;
                    if(current_sum > max_sum){
                        max_sum = current_sum;
                        // Early exit if maximum possible is achieved
                        if(max_sum == 2 * N * N){
                            printf("%d", max_sum);
                            return 0;
                        }
                    }
                    // Unmark the cells
                    for(int t=0; t<s1; t++){
                        int current_x = x + t;
                        int start_y = y - t;
                        int end_y = y + t;
                        for(int dy = start_y; dy <= end_y; dy++){
                            available[current_x][dy] =1;
                        }
                    }
                }
            }
        }
    }
    printf("%d", max_sum);
    return 0;
}