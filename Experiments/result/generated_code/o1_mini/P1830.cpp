#include <stdio.h>

int main(){
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    int rect[x][4];
    for(int i=0;i<x;i++) {
        scanf("%d %d %d %d", &rect[i][0], &rect[i][1], &rect[i][2], &rect[i][3]);
    }
    for(int i=0;i<y;i++) {
        int px, py;
        scanf("%d %d", &px, &py);
        int count=0, last=0;
        for(int j=0;j<x;j++) {
            if(px >= rect[j][0] && px <= rect[j][2] && py >= rect[j][1] && py <= rect[j][3]){
                count++;
                last = j+1;
            }
        }
        if(count > 0){
            printf("Y %d %d\n", count, last);
        }
        else{
            printf("N\n");
        }
    }
    return 0;
}