#include <stdio.h>
#include <string.h>

#define MAX 210

int main(){
    int n;
    scanf("%d", &n);
    char s[MAX];
    s[0] = '1';
    s[1] = '\0';
    for(int i = 0; i < n; i++){
        int carry = 0;
        int len = strlen(s);
        for(int j = 0; j < len; j++){
            int num = (s[j]-'0') * 2 + carry;
            s[j] = (num % 10) + '0';
            carry = num / 10;
        }
        if(carry) {
            s[len] = carry + '0';
            s[len+1] = '\0';
        }
    }
    // Reverse the string
    int len = strlen(s);
    for(int i = 0; i < len/2; i++){
        char tmp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = tmp;
    }
    printf("%s\n", s);
    return 0;
}