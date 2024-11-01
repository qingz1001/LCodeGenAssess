#include <stdio.h>

#define MAX 20000

int sum_of_proper_divisors(int n) {
    if(n <=1) return 0;
    int sum =1;
    for(int i=2;i*i<=n;i++) {
        if(n%i ==0){
            if(i != n/i)
                sum += i + n/i;
            else
                sum += i;
        }
    }
    return sum;
}

int main(){
    int s;
    scanf("%d", &s);
    int a, b;
    for(a = s; a <= MAX; a++){
        b = sum_of_proper_divisors(a);
        if(b != a && b >=1 && b <= MAX){
            if(sum_of_proper_divisors(b) == a){
                printf("%d %d\n", a, b);
                return 0;
            }
        }
    }
    return 0;
}