#include <stdio.h>

long long X;

long long next_number_with7(long long n){
    while(1){
        long long temp = n;
        while(temp > 0){
            if(temp % 10 == 7){
                return n;
            }
            temp /= 10;
        }
        n++;
    }
}

int main(){
    scanf("%lld", &X);
    long long pos = 1;
    int dir = 1;
    long long prev_special = 0;
    long long next_multiple7 = 7;
    long long next_contains7 = 7;
    long long next_special_num;
    
    while(1){
        if(next_multiple7 < next_contains7){
            next_special_num = next_multiple7;
        }
        else if(next_contains7 < next_multiple7){
            next_special_num = next_contains7;
        }
        else{
            next_special_num = next_multiple7;
        }
        if(next_special_num > X){
            break;
        }
        long long len = next_special_num - prev_special -1;
        pos = (pos + dir * len) % 1337;
        if(pos <=0){
            pos +=1337;
        }
        dir *= -1;
        prev_special = next_special_num;
        if(next_special_num == next_multiple7){
            next_multiple7 +=7;
        }
        if(next_special_num == next_contains7){
            next_contains7 = next_number_with7(next_contains7 +1);
        }
    }
    long long remaining = X - prev_special;
    pos = (pos + dir * remaining) % 1337;
    if(pos <=0){
        pos +=1337;
    }
    printf("%lld\n", pos);
    return 0;
}