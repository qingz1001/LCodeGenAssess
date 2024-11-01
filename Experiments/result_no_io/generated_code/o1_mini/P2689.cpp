#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_T 50
#define OFFSET 50
#define INF 1000

int main(){
    int x1, y1, x2, y2, T;
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    scanf("%d", &T);
    
    char wind_char;
    int winds[MAX_T][2];
    for(int i=0;i<T;i++){
        scanf(" %c", &wind_char);
        if(wind_char == 'N'){
            winds[i][0] = 0;
            winds[i][1] = 1;
        }
        else if(wind_char == 'S'){
            winds[i][0] = 0;
            winds[i][1] = -1;
        }
        else if(wind_char == 'E'){
            winds[i][0] = 1;
            winds[i][1] = 0;
        }
        else if(wind_char == 'W'){
            winds[i][0] = -1;
            winds[i][1] = 0;
        }
    }
    
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    // Check if target is achievable within T moves
    if(abs(dx) > T || abs(dy) > T){
        printf("-1\n");
        return 0;
    }
    
    // Initialize min_steps array
    int min_steps[101][101];
    for(int i=0;i<=100;i++) {
        for(int j=0;j<=100;j++) {
            min_steps[i][j] = INF;
        }
    }
    min_steps[OFFSET][OFFSET] = 0;
    
    // Process each wind vector
    for(int i=0;i<T;i++){
        int wind_dx = winds[i][0];
        int wind_dy = winds[i][1];
        
        // Iterate from high to low to prevent reuse
        for(int x = MAX_T; x >= -MAX_T; x--){
            for(int y = MAX_T; y >= -MAX_T; y--){
                int current_x = x;
                int current_y = y;
                if(current_x < -MAX_T || current_x > MAX_T || current_y < -MAX_T || current_y > MAX_T){
                    continue;
                }
                if(min_steps[current_x + OFFSET][current_y + OFFSET] < INF){
                    int new_x = current_x + wind_dx;
                    int new_y = current_y + wind_dy;
                    if(new_x >= -MAX_T && new_x <= MAX_T && new_y >= -MAX_T && new_y <= MAX_T){
                        if(min_steps[new_x + OFFSET][new_y + OFFSET] > min_steps[current_x + OFFSET][current_y + OFFSET] +1){
                            min_steps[new_x + OFFSET][new_y + OFFSET] = min_steps[current_x + OFFSET][current_y + OFFSET] +1;
                        }
                    }
                }
            }
        }
    }
    
    if(dx < -MAX_T || dx > MAX_T || dy < -MAX_T || dy > MAX_T){
        printf("-1\n");
    }
    else{
        int result = min_steps[dx + OFFSET][dy + OFFSET];
        if(result <= T){
            printf("%d\n", result);
        }
        else{
            printf("-1\n");
        }
    }
    
    return 0;
}