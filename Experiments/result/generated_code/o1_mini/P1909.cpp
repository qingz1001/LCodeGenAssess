#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int count, price;
    int min_cost = 100000000;
    for(int i = 0; i < 3; i++){
        scanf("%d %d", &count, &price);
        int packages = (n + count - 1) / count;
        int total = packages * price;
        if(total < min_cost){
            min_cost = total;
        }
    }
    printf("%d\n", min_cost);
    return 0;
}