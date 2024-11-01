#include <stdio.h>
#include <string.h>

int count_VK(char s[], int n){
    int count = 0;
    for(int i=0;i<n-1;i++){
        if(s[i]=='V' && s[i+1]=='K') count++;
    }
    return count;
}

int main(){
    int n;
    char s[101];
    scanf("%d", &n);
    scanf("%s", s);
    int max_count = count_VK(s, n);
    for(int i=0;i<n;i++){
        char original = s[i];
        char new_char = (s[i] == 'V') ? 'K' : 'V';
        if(new_char != original){
            s[i] = new_char;
            int current = count_VK(s, n);
            if(current > max_count) max_count = current;
            s[i] = original;
        }
    }
    printf("%d\n", max_count);
    return 0;
}