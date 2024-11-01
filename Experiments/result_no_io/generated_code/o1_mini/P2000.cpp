#include <stdio.h>
#include <string.h>

int main(){
    char s[100005];
    scanf("%s", s);
    int len = strlen(s);
    int res12 = 0, res40 = 0;
    for(int i=0;i<len;i++){
        res12 = (res12 * 10 + (s[i]-'0')) % 12;
        res40 = (res40 * 10 + (s[i]-'0')) % 40;
    }
    int possible = 0;
    switch(res40){
        case 0: case 1: case 2: case 3: case 4:
        case 8: case 9: case 10: case 11: case 12:
            possible = 1;
            break;
        default:
            possible = 0;
    }
    if(possible) printf("2\n");
    else printf("1\n");
    return 0;
}