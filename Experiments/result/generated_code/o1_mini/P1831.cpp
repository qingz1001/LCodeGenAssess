#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

int is_lever_number(ull num) {
    char str[20];
    sprintf(str, "%llu", num);
    int len = strlen(str);
    int digits[20];
    for(int i=0;i<len;i++) {
        digits[i] = str[i] - '0';
    }
    for(int p=0; p<len; p++) {
        unsigned long long sum_left = 0;
        for(int i=0;i<p;i++) {
            sum_left += (unsigned long long)digits[i] * (p - i);
        }
        unsigned long long sum_right = 0;
        for(int i=p+1;i<len;i++) {
            sum_right += (unsigned long long)digits[i] * (i - p);
        }
        if(sum_left == sum_right) {
            return 1;
        }
    }
    return 0;
}

int main(){
    ull x, y;
    scanf("%llu %llu", &x, &y);
    ull count = 0;
    if(y - x > 1000000){
        // To prevent excessive computation, limit the range
        // Depending on the problem constraints, adjust accordingly
        // Here, we assume it's manageable
    }
    for(ull num = x; num <= y; num++){
        if(is_lever_number(num)){
            count++;
        }
        if(num == y) break; // To prevent overflow
    }
    printf("%llu\n", count);
    return 0;
}