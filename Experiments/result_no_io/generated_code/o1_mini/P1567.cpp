#include <stdio.h>

int main(){
    int N;
    if(scanf("%d", &N)!=1) return 0;
    int temp, prev, current_len=1, max_len=1;
    if(N ==0){
        printf("0");
        return 0;
    }
    if(scanf("%d", &prev)!=1){
        printf("1");
        return 0;
    }
    for(int i=1;i<N;i++){
        if(scanf("%d", &temp)!=1){
            break;
        }
        if(temp > prev){
            current_len++;
            if(current_len > max_len){
                max_len = current_len;
            }
        }
        else{
            current_len =1;
        }
        prev = temp;
    }
    printf("%d", max_len);
    return 0;
}