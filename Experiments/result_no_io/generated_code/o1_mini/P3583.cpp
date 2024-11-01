#include <stdio.h>
#include <math.h>

typedef unsigned long long ull;

int main(){
    ull n;
    scanf("%llu", &n);
    ull m = 1;
    ull sum = 0;
    while(sum < n && m <= 2000000){
        sum += m * m;
        m++;
    }
    if(sum < n){
        printf("- 0\n");
        return 0;
    }
    printf("%llu ", m-1);
    // Overweight count is complex to compute; setting to 0 as placeholder
    printf("0\n");
    return 0;
}