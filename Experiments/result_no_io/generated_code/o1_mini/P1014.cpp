#include <stdio.h>

int main(){
    int N;
    scanf("%d",&N);
    int k=1;
    long long total=1;
    while(total < N){
        k++;
        total +=k;
    }
    int pos = N - (total - k);
    int sum = k +1;
    int num, den;
    if(sum %2 ==0){
        num = sum - pos;
        den = pos;
    }
    else{
        num = pos;
        den = sum - pos;
    }
    printf("%d/%d\n", num, den);
    return 0;
}