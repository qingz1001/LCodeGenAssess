#include <stdio.h>

int matchsticks_per_digit[10] = {6,2,5,5,4,5,6,3,7,6};

int get_matchsticks(int num){
    if(num == 0){
        return matchsticks_per_digit[0];
    }
    int total = 0;
    while(num > 0){
        total += matchsticks_per_digit[num % 10];
        num /= 10;
    }
    return total;
}

int main(){
    int n;
    scanf("%d", &n);
    int target = n - 4;
    if(target < 0){
        printf("0");
        return 0;
    }
    int count = 0;
    for(int A = 0; A <= 99999; A++){
        int match_A = get_matchsticks(A);
        if(match_A > target) continue;
        for(int B = 0; B <= 99999; B++){
            int match_B = get_matchsticks(B);
            if(match_A + match_B > target) continue;
            int C = A + B;
            int match_C = get_matchsticks(C);
            if(match_A + match_B + match_C == target){
                count++;
            }
        }
    }
    printf("%d", count);
    return 0;
}