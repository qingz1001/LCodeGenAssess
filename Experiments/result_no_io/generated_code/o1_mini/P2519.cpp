#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int a, b;
    int count = 0;
    for(int i=0;i<n;i++){
        scanf("%d %d", &a, &b);
        if(a >=0 && b >=0 && a + b <= n -1){
            count++;
        }
    }
    printf("%d\n", n - count);
    return 0;
}