#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 100005
#define MAXLEN 16

int cmp_ignore_case(const char *s1, const char *s2) {
    while(*s1 && *s2){
        char c1 = tolower(*s1);
        char c2 = tolower(*s2);
        if(c1 != c2){
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    char words[MAXN][MAXLEN];
    for(int i=0;i<N;i++){
        scanf("%s", words[i]);
    }
    while(M--){
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--; // Convert to 0-based index
        int max_idx = x;
        for(int i=x+1;i<=y;i++){
            int cmp = cmp_ignore_case(words[i], words[max_idx]);
            if(cmp > 0){
                max_idx = i;
            }
            else if(cmp == 0){
                max_idx = i;
            }
        }
        printf("%s\n", words[max_idx]);
    }
    return 0;
}