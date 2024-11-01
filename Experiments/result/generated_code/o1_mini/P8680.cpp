#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int sum = 0;
    for(int i = 1; i <= n; i++){
        int num = i;
        while(num > 0){
            int d = num % 10;
            if(d == 0 || d == 1 || d == 2 || d == 9){
                sum += i;
                break;
            }
            num /= 10;
        }
    }
    printf("%d\n", sum);
    return 0;
}