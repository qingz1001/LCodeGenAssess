#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int k[3], p[3];
    for(int i=0;i<3;i++) scanf("%d %d", &k[i], &p[i]);
    int min_cost = 2147483647;
    for(int i=0;i<3;i++){
        int m = (n + k[i] -1) /k[i];
        int cost = m * p[i];
        if(cost < min_cost) min_cost = cost;
    }
    printf("%d", min_cost);
    return 0;
}