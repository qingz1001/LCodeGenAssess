#include <stdio.h>
#include <ctype.h>

int main(){
    int c;
    long long freq[26] = {0};
    while((c = getchar()) != '\n' && c != EOF){
        if(c >= 'a' && c <= 'z'){
            freq[c - 'a']++;
        }
    }
    long long max = 0;
    for(int i = 0; i < 26; i++) {
        if(freq[i] > max){
            max = freq[i];
        }
    }
    printf("%lld\n", max);
    return 0;
}