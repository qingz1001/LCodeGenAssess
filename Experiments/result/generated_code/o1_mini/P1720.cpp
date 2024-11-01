#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    
    if(n == 0){
        printf("0.00\n");
        return 0;
    }
    
    long long a = 0, b = 1, c;
    for(int i = 1; i < n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    
    printf("%.2lf\n", (double)b);
    return 0;
}