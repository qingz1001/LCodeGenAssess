#include <stdio.h>
#include <stdbool.h>

bool isRunaround(unsigned long n) {
    int digits[10];
    int len = 0;
    unsigned long tmp = n;
    while(tmp > 0){
        digits[len++] = tmp %10;
        tmp /=10;
    }
    if(len ==0) return false;
    int leftDigits[10];
    for(int i=0;i<len;i++) leftDigits[i] = digits[len-1-i];
    bool seen[10] = {false};
    for(int i=0;i<len;i++){
        if(leftDigits[i]==0 || seen[leftDigits[i]]) return false;
        seen[leftDigits[i]] = true;
    }
    bool visited[10] = {false};
    int current =0;
    for(int i=0;i<len;i++){
        if(visited[current]) return false;
        visited[current] = true;
        current = (current + leftDigits[current]) % len;
    }
    return (current ==0);
}

int main(){
    unsigned long m;
    scanf("%lu", &m);
    unsigned long candidate = m+1;
    while(1){
        if(isRunaround(candidate)){
            printf("%lu\n", candidate);
            break;
        }
        candidate++;
    }
    return 0;
}