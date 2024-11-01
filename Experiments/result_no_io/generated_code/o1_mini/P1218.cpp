#include <stdio.h>
#include <math.h>

int is_prime(int n){
    if(n < 2) return 0;
    if(n ==2 || n==3) return 1;
    if(n %2 ==0 || n%3 ==0) return 0;
    int i;
    int sqrt_n = sqrt(n);
    for(i=5;i<=sqrt_n;i+=6){
        if(n%i ==0 || n%(i+2) ==0) return 0;
    }
    return 1;
}

int n;

void backtrack(int current, int length){
    if(length == n){
        printf("%d\n", current);
        return;
    }
    int next;
    for(next=1; next<=9; next++){
        int new_num = current *10 + next;
        if(is_prime(new_num)){
            backtrack(new_num, length+1);
        }
    }
}

int main(){
    scanf("%d", &n);
    if(n >=1){
        int first;
        for(first=2; first<=9; first++){
            if(is_prime(first)){
                backtrack(first, 1);
            }
        }
    }
    return 0;
}