#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    char s[1000001];
    scanf("%s", s);
    int countL = 0, countR = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '(') countL++;
        else countR++;
    }
    int minC = countL < countR ? countL : countR;
    printf("%d", 2 * minC);
    return 0;
}