#include <stdio.h>
#include <string.h>

int matchsticks[10] = {6,2,5,5,4,5,6,3,7,6};

int count_matches(int num) {
    if(num == 0) return matchsticks[0];
    int cnt = 0;
    while(num > 0){
        cnt += matchsticks[num % 10];
        num /= 10;
    }
    return cnt;
}

int has_leading_zero(int num, int digits) {
    if(digits == 1) return 0;
    int temp = num;
    for(int i=1;i<digits;i++) {
        temp /=10;
    }
    return temp == 0;
}

int main(){
    int n;
    scanf("%d",&n);
    int count =0;
    for(int A=0; A<=9999; A++){
        int B_min=0, B_max=9999;
        for(int B=B_min; B<=B_max; B++){
            int C = A + B;
            if(C > 9999) continue;
            // Count digits
            int digitsA = (A ==0)?1:0, tempA = A;
            while(tempA >0){ digitsA++; tempA /=10;}
            int digitsB = (B ==0)?1:0, tempB = B;
            while(tempB >0){ digitsB++; tempB /=10;}
            int digitsC = (C ==0)?1:0, tempC = C;
            while(tempC >0){ digitsC++; tempC /=10;}
            if(has_leading_zero(A, digitsA) || has_leading_zero(B, digitsB) || has_leading_zero(C, digitsC)) continue;
            int total = count_matches(A) + count_matches(B) + count_matches(C) + 4;
            if(total ==n){
                if(A != B){
                    count +=2;
                }
                else{
                    count +=1;
                }
            }
        }
    }
    printf("%d",count);
}