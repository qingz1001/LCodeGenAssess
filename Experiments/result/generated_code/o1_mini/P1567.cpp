#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    
    if (N <= 0){
        printf("0");
        return 0;
    }
    
    int temp, prev, current_length = 1, max_length = 1;
    scanf("%d", &prev);
    
    for(int i = 1; i < N; i++){
        scanf("%d", &temp);
        if(temp > prev){
            current_length++;
            if(current_length > max_length){
                max_length = current_length;
            }
        }
        else{
            current_length = 1;
        }
        prev = temp;
    }
    
    printf("%d", max_length);
    return 0;
}