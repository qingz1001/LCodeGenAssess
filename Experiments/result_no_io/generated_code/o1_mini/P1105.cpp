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
    for(int i=1;i<=N;i++) {
        scanf("%d %d %d", &platforms[i].H, &platforms[i].L, &platforms[i].R);
    }
    for(int i=1;i<=N;i++) {
        // Left edge
        int left_x = platforms[i].L;
        int maxH_left = -1;
        int result_left = 0;
        for(int j=1;j<=N;j++) {
            if(platforms[j].H < platforms[i].H && platforms[j].L < left_x && platforms[j].R > left_x){
                if(platforms[j].H > maxH_left || (platforms[j].H == maxH_left && j < result_left)){
                    maxH_left = platforms[j].H;
                    result_left = j;
                }
            }
        }
        // Right edge
        int right_x = platforms[i].R;
        int maxH_right = -1;
        int result_right = 0;
        for(int j=1;j<=N;j++) {
            if(platforms[j].H < platforms[i].H && platforms[j].L < right_x && platforms[j].R > right_x){
                if(platforms[j].H > maxH_right || (platforms[j].H == maxH_right && j < result_right)){
                    maxH_right = platforms[j].H;
                    result_right = j;
                }
            }
        }
        printf("%d %d\n", result_left, result_right);
    }
    return 0;
}