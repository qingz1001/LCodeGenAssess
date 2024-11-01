#include <stdio.h>

int main(){
    unsigned int X;
    scanf("%u", &X);
    
    unsigned int current = 1;
    int dir = 1;
    for(unsigned int i =1; i <= X; i++){
        if(i == X){
            printf("%u\n", current);
            return 0;
        }
        
        int flag = 0;
        if(i % 7 == 0){
            flag =1;
        }
        else{
            unsigned int temp = i;
            while(temp){
                if(temp %10 ==7){
                    flag=1;
                    break;
                }
                temp /=10;
            }
        }
        
        if(flag){
            dir = -dir;
        }
        
        if(dir ==1){
            current++;
            if(current > 1337){
                current =1;
            }
        }
        else{
            if(current ==1){
                current =1337;
            }
            else{
                current--;
            }
        }
    }
    return 0;
}