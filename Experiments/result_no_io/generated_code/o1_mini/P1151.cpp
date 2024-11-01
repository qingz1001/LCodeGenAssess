#include <stdio.h>

int main(){
    int K;
    scanf("%d", &K);
    int found = 0;
    for(int N=10000; N<=30000; N++){
        int sub1 = (N / 100) % 1000;
        int sub2 = (N / 10) % 1000;
        int sub3 = N % 1000;
        if(sub1 % K ==0 && sub2 % K ==0 && sub3 % K ==0){
            printf("%d\n", N);
            found =1;
        }
    }
    if(!found){
        printf("No\n");
    }
    return 0;
}