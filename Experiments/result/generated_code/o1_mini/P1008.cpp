#include <stdio.h>

int main(){
    for(int x=100; x<=333; x++){
        int y=2*x, z=3*x;
        // Check if y and z are three-digit
        if(y > 999 || z > 999){
            continue;
        }
        int used = 0, valid = 1;
        int numbers[3] = {x, y, z};
        for(int i=0; i<3 && valid; i++){
            int num = numbers[i];
            for(int j=0; j<3; j++){
                int digit = num % 10;
                if(digit == 0 || (used & (1 << digit))){
                    valid = 0;
                    break;
                }
                used |= (1 << digit);
                num /= 10;
            }
        }
        if(valid){
            printf("%d %d %d\n", x, y, z);
        }
    }
    return 0;
}