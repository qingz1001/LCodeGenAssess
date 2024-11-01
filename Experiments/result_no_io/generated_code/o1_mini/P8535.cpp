#include <stdio.h>
#include <string.h>

int main(){
    long long n;
    scanf("%lld", &n);
    int p_star[10] = {5,8,15,30,23,11,16,10,18,24};
    int min_cost = 5;
    long long max_digits = n / min_cost;
    if(max_digits ==0){
        // Not possible, as n>=5, but just in case
        printf("0");
        return 0;
    }
    char *result = (char*)malloc(max_digits +1);
    long long remaining = n;
    for(long long i=0;i<max_digits;i++){
        for(int d=9; d>=0; d--){
            if(remaining >= p_star[d] && (remaining - p_star[d]) >= min_cost * (max_digits - i -1)){
                result[i] = '0' + d;
                remaining -= p_star[d];
                break;
            }
        }
    }
    result[max_digits] = '\0';
    printf("%s", result);
    free(result);
    return 0;
}