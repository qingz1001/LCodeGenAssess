#include <stdio.h>
#include <stdbool.h>

bool is_wave(long N, int B){
    if(N ==0) return true;

    long last_digit = N % B;
    N /= B;
    if(N ==0){
        return true;
    }
    long second_digit = N % B;
    if(second_digit == last_digit){
        return false;
    }
    N /= B;
    bool flag = true;
    while(N >0){
        long current_digit = N % B;
        if(flag){
            if(current_digit != last_digit){
                return false;
            }
        }
        else{
            if(current_digit != second_digit){
                return false;
            }
        }
        flag = !flag;
        N /= B;
    }
    return true;
}

int main(){
    int l, r, k;
    long L, R;
    scanf("%d %d %ld %ld %d", &l, &r, &L, &R, &k);
    for(long N = L; N <= R; N++){
        int count =0;
        for(int B = l; B <= r; B++){
            if(is_wave(N, B)){
                count++;
                if(count > k){
                    break;
                }
            }
        }
        if(count == k){
            printf("%ld\n", N);
        }
    }
    return 0;
}