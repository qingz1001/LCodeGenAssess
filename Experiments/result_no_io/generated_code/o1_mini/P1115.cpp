#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a, current_sum, max_sum;
    scanf("%d", &a);
    current_sum = max_sum = a;
    for(int i = 1; i < n; i++){
        scanf("%d", &a);
        if(current_sum < 0){
            current_sum = a;
        }
        else{
            current_sum += a;
        }
        if(current_sum > max_sum){
            max_sum = current_sum;
        }
    }
    printf("%d\n", max_sum);
    return 0;
}