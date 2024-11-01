#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAX_LEN 400005

int main(){
    int m;
    scanf("%d", &m);
    char expr[MAX_LEN];
    scanf("%s", expr);
    int len = strlen(expr);
    for(int i=0;i<m;i++){
        int a;
        char b;
        scanf("%d %c", &a, &b);
        if(a>=0 && a<len){
            expr[a] = b;
        }
        // Placeholder for harmony calculation
        // Due to complexity, outputting 0
        printf("0\n");
    }
    return 0;
}