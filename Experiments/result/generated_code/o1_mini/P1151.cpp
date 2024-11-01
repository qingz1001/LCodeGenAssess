#include <stdio.h>

int main(){
    int K;
    scanf("%d", &K);
    int found = 0;
    for(int n=10000; n<=30000; n++){
        int sub1 = n / 100;
        int sub2 = (n / 10) % 1000;
        int sub3 = n % 1000;
        if(sub1 % K ==0 && sub2 % K ==0 && sub3 % K ==0){
            printf("%d\n", n);
            found =1;
        }
    }
    if(!found){
        printf("No\n");
    }
    return 0;
}