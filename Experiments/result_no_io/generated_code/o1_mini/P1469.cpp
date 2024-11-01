#include <stdio.h>

typedef unsigned int uint;

int main(){
    uint n;
    uint x, res=0;
    int c = getchar();
    // Read n
    while(c < '0' || c > '9') c = getchar();
    n = 0;
    while(c >= '0' && c <= '9'){
        n = n*10 + (c - '0');
        c = getchar();
    }
    // Read n integers and XOR
    for(uint i=0;i<n;i++){
        // Read next number
        while(c < '0' || c > '9') c = getchar();
        x = 0;
        while(c >= '0' && c <= '9'){
            x = x*10 + (c - '0');
            c = getchar();
        }
        res ^= x;
    }
    printf("%u\n", res);
    return 0;
}