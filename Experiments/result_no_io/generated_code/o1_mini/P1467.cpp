#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_runaround(unsigned long n) {
    char s[20];
    sprintf(s, "%lu", n);
    int len = strlen(s);
    bool used[10] = {false};
    
    // Check for non-zero and unique digits
    for(int i = 0; i < len; i++) {
        if(s[i] == '0') return false;
        if(used[s[i]-'0']) return false;
        used[s[i]-'0'] = true;
    }
    
    bool visited[10] = {false};
    int pos = 0;
    for(int i = 0; i < len; i++) {
        if(visited[pos]) return false;
        visited[pos] = true;
        int step = s[pos] - '0';
        pos = (pos + step) % len;
    }
    return pos == 0;
}

int main(){
    unsigned long m;
    scanf("%lu", &m);
    unsigned long n = m + 1;
    while(1){
        if(is_runaround(n)){
            printf("%lu\n", n);
            break;
        }
        n++;
    }
    return 0;
}