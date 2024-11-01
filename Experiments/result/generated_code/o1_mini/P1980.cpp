#include <stdio.h>

int main(){
    int n, x, count = 0;
    scanf("%d %d", &n, &x);
    for(int i =1; i <=n; i++){
        int num = i;
        if(num ==0 && x==0){
            count++;
        }
        while(num >0){
            if(num %10 ==x){
                count++;
            }
            num /=10;
        }
    }
    printf("%d", count);
    return 0;
}