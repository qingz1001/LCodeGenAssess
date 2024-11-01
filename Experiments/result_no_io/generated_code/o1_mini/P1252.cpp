#include <stdio.h>
#include <limits.h>

int main(){
    int times[5][11];
    for(int i=0;i<5;i++) {
        for(int j=1;j<=10;j++) {
            scanf("%d", &times[i][j]);
        }
    }
    int min_time = INT_MAX;
    int best_d[5] = {0};
    for(int d1=1;d1<=10;d1++) {
        for(int d2=1;d2<=10;d2++) {
            for(int d3=1;d3<=10;d3++) {
                for(int d4=1;d4<=10;d4++) {
                    for(int d5=1;d5<=10;d5++) {
                        if(d1+d2+d3+d4+d5 == 25){
                            int total = times[0][d1] + times[1][d2] + times[2][d3] + times[3][d4] + times[4][d5];
                            if(total < min_time){
                                min_time = total;
                                best_d[0] = d1;
                                best_d[1] = d2;
                                best_d[2] = d3;
                                best_d[3] = d4;
                                best_d[4] = d5;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", min_time);
    printf("%d %d %d %d %d\n", best_d[0], best_d[1], best_d[2], best_d[3], best_d[4]);
    return 0;
}