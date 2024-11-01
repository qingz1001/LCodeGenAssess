#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int h, w;
    int max = 0;
    for(int i=0;i<n;i++){
        scanf("%d %d", &h, &w);
        int area = h * w;
        if(area > max){
            max = area;
        }
    }
    printf("%d\n", max);
    return 0;
}