#include <stdio.h>
#include <limits.h>

int main(){
    int n;
    scanf("%d", &n);
    if(n <=0){
        printf("0");
        return 0;
    }
    long long a;
    scanf("%lld", &a);
    long long max_so_far = a;
    long long current_max = a;
    for(int i = 1; i < n; i++){
        scanf("%lld", &a);
        if(current_max < 0){
            current_max = a;
        }
        else{
            current_max += a;
        }
        if(current_max > max_so_far){
            max_so_far = current_max;
        }
    }
    printf("%lld", max_so_far);
    return 0;
}