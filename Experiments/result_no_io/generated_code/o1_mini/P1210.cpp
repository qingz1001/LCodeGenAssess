#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char S[20020];
    int len =0;
    while (fgets(S + len, 20020 - len, stdin)){
        len += strlen(S + len);
    }
    S[len] = '\0';
    char letters[2000];
    int positions[2000];
    int m=0;
    for(int p=0; p<len && m <2000; p++){
        if(isalpha(S[p])){
            letters[m] = S[p];
            positions[m] = p;
            m++;
        }
    }
    if(m ==0){
        printf("0\n");
        return 0;
    }
    int maxlen =1, start=0;
    for(int i=0;i<m;i++){
        // odd length
        int l =i, r=i;
        while(l >=0 && r <m && letters[l] == letters[r]){
            int current = r-l+1;
            if(current > maxlen){
                maxlen = current;
                start = l;
            }
            l--;
            r++;
        }
        // even length
        l =i;
        r =i+1;
        while(l >=0 && r <m && letters[l] == letters[r]){
            int current = r-l+1;
            if(current > maxlen){
                maxlen = current;
                start = l;
            }
            l--;
            r++;
        }
    }
    printf("%d\n", maxlen);
    if(maxlen ==0){
        return 0;
    }
    int left = positions[start];
    int right = positions[start + maxlen -1];
    for(int p=left; p <= right; p++){
        putchar(S[p]);
    }
    return 0;
}