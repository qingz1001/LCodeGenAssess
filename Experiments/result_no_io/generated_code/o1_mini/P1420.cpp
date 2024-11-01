#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    if(n <=0 ){
        printf("0");
        return 0;
    }
    long long a;
    scanf("%lld", &a);
    long long prev = a;
    int current_len =1, max_len=1;
    for(int i=1;i<n;i++){
        scanf("%lld", &a);
        if(a == prev +1){
            current_len++;
            if(current_len > max_len){
                max_len = current_len;
            }
        }
        else{
            current_len =1;
        }
        prev = a;
    }
    printf("%d", max_len);
    return 0;
}