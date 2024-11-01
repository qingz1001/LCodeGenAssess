#include <stdio.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    
    long long total = (long long)b - (long long)a + 1;
    
    // Calculate a mod 4 in [0,3]
    int m = a % 4;
    if(m < 0) m += 4;
    
    // Find the first number >=a that is 2 mod 4
    int shift = (2 - m + 4) % 4;
    long long s = (long long)a + shift;
    
    // If s is less than a, move to the next possible number
    if(s < a){
        s += 4;
    }
    
    long long count_f2 = 0;
    if(s <= b){
        count_f2 = ((b - s) / 4) + 1;
    }
    
    long long result = total - count_f2;
    printf("%lld", result);
    
    return 0;
}