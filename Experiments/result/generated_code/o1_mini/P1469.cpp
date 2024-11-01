#include <stdio.h>

int main(){
    int n;
    // Read n
    int c = getchar();
    while(c < '0' || c > '9') c = getchar();
    n =0;
    while(c >= '0' && c <= '9'){
        n = n*10 + (c - '0');
        c = getchar();
    }
    unsigned int res=0, x;
    for(int i=0;i<n;i++){
        // Read next number
        while(c < '0' || c > '9') c = getchar();
        x=0;
        while(c >= '0' && c <= '9'){
            x = x*10 + (c - '0');
            c = getchar();
        }
        res ^=x;
    }
    printf("%u\n", res);
    return 0;
}