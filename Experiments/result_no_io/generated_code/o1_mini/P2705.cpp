#include <stdio.h>
#include <limits.h>

int main(){
    int R, B, C, D, E;
    scanf("%d %d %d %d %d", &R, &B, &C, &D, &E);
    int x_start = (R > B) ? (R - B) : 0;
    int max_score = INT32_MIN;
    for(int x = x_start; x <= R; x++){
        int y = B + x - R;
        if(y < 0 || y > B) continue;
        int score = x * C + (R - x) * E + y * D + (B - y) * E;
        if(score > max_score){
            max_score = score;
        }
    }
    printf("%d\n", max_score);
    return 0;
}