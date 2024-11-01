#include <stdio.h>
#include <limits.h>

int main(){
    int runner[5][10];
    for(int i=0;i<5;i++) {
        for(int j=0;j<10;j++) {
            scanf("%d", &runner[i][j]);
        }
    }
    int min_time = INT32_MAX;
    int best[5];
    for(int a=1;a<=10;a++) {
        for(int b=1;b<=10;b++) {
            for(int c=1;c<=10;c++) {
                for(int d=1;d<=10;d++) {
                    for(int e=1;e<=10;e++) {
                        if(a + b + c + d + e == 25){
                            int total = runner[0][a-1] + runner[1][b-1] + runner[2][c-1] + runner[3][d-1] + runner[4][e-1];
                            if(total < min_time){
                                min_time = total;
                                best[0]=a;
                                best[1]=b;
                                best[2]=c;
                                best[3]=d;
                                best[4]=e;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", min_time);
    printf("%d %d %d %d %d\n", best[0], best[1], best[2], best[3], best[4]);
    return 0;
}