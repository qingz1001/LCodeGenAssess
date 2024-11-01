#include <stdio.h>
#include <string.h>

int main(){
    char s[9];
    scanf("%8s", s);
    int count = 0;
    for(int i=0;i<8;i++) {
        if(s[i] == '1') count++;
    }
    printf("%d\n", count);
    return 0;
}