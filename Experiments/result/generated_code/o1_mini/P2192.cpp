#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int count5=0, count0=0;
    for(int i=0; i<n; i++){
        int digit;
        scanf("%d", &digit);
        if(digit ==5) count5++;
        else if(digit ==0) count0++;
    }
    if(count0 ==0){
        printf("-1");
        return 0;
    }
    int x = count5 - (count5 % 9);
    if(x ==0){
        printf("0");
        return 0;
    }
    // Build the number
    for(int i=0; i<x; i++) printf("5");
    for(int i=0; i<count0; i++) printf("0");
    return 0;
}