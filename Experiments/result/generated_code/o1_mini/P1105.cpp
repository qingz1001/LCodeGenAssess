#include <stdio.h>

typedef struct {
    int H;
    int L;
    int R;
} Platform;

int main(){
    int N;
    scanf("%d", &N);
    Platform platforms[N+1];
    for(int i=1;i<=N;i++){
        scanf("%d %d %d", &platforms[i].H, &platforms[i].L, &platforms[i].R);
    }
    for(int i=1;i<=N;i++){
        // Left drop
        int x_left = platforms[i].L;
        int best_left = 0;
        int best_h_left = -1;
        for(int j=1;j<=N;j++){
            if(j == i) continue;
            if(platforms[j].L < x_left && x_left < platforms[j].R && platforms[j].H < platforms[i].H){
                if(platforms[j].H > best_h_left || (platforms[j].H == best_h_left && j < best_left)){
                    best_left = j;
                    best_h_left = platforms[j].H;
                }
            }
        }
        // Right drop
        int x_right = platforms[i].R;
        int best_right = 0;
        int best_h_right = -1;
        for(int j=1;j<=N;j++){
            if(j == i) continue;
            if(platforms[j].L < x_right && x_right < platforms[j].R && platforms[j].H < platforms[i].H){
                if(platforms[j].H > best_h_right || (platforms[j].H == best_h_right && j < best_right)){
                    best_right = j;
                    best_h_right = platforms[j].H;
                }
            }
        }
        printf("%d %d\n", best_left, best_right);
    }
    return 0;
}