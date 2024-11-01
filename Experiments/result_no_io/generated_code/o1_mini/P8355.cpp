#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char s[n+1];
    scanf("%s", s);
    int count_open = 0, count_close = 0;
    for(int i=0;i<n;i++){
        if(s[i]=='(') count_open++;
        else if(s[i]==')') count_close++;
    }
    int min_count = count_open < count_close ? count_open : count_close;
    printf("%d\n", 2 * min_count);
    return 0;
}