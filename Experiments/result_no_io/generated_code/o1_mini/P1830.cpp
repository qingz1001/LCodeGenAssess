#include <stdio.h>

int main(){
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    
    int x1[x], y1_[x], x2[x], y2[x];
    for(int i=0;i<x;i++){
        scanf("%d %d %d %d", &x1[i], &y1_[i], &x2[i], &y2[i]);
    }
    
    for(int i=0;i<y;i++){
        int px, py;
        scanf("%d %d", &px, &py);
        int count=0, last=0;
        for(int j=0;j<x;j++){
            if(px >= x1[j] && px <= x2[j] && py >= y1_[j] && py <= y2[j]){
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