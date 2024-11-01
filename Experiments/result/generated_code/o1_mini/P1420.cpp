#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    if(n <=0){
        printf("0");
        return 0;
    }
    long long a;
    scanf("%lld", &a);
    int current =1, max_len=1;
    long long prev = a;
    for(int i=1;i<n;i++){
        scanf("%lld", &a);
        if(a == prev +1){
            current++;
            if(current > max_len){
                max_len = current;
            }
        }
        else{
            current =1;
        }
        prev = a;
    }
    printf("%d", max_len);
    return 0;
}