#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_ORIG 20000
#define MAX_LETTER 20000

int main(){
    char original[MAX_ORIG];
    int orig_len = 0;
    int c;
    while((c = getchar()) != EOF && orig_len < MAX_ORIG){
        original[orig_len++] = c;
    }

    char letters[MAX_LETTER];
    int indices[MAX_LETTER];
    int N = 0;
    for(int i = 0; i < orig_len; i++){
        if( (original[i] >= 'A' && original[i] <= 'Z') || (original[i] >= 'a' && original[i] <= 'z') ){
            letters[N] = toupper(original[i]);
            indices[N] = i;
            N++;
        }
    }

    if(N == 0){
        printf("0\n");
        return 0;
    }

    int max_len = 1;
    int max_start = 0;

    for(int i = 0; i < N; i++){
        // Odd length
        int l = i - 1;
        int r = i + 1;
        int count = 1;
        while(l >=0 && r < N && letters[l] == letters[r]){
            count +=2;
            if(count > max_len){
                max_len = count;
                max_start = l;
            }
            l--;
            r++;
        }

        // Even length
        if(i+1 < N && letters[i] == letters[i+1]){
            l = i;
            r = i+1;
            count =2;
            while(l-1 >=0 && r+1 < N && letters[l-1] == letters[r+1]){
                count +=2;
                l--;
                r++;
            }
            if(count > max_len){
                max_len = count;
                max_start = l;
            }
        }
    }

    int orig_start = indices[max_start];
    int orig_end = indices[max_start + max_len -1];

    // Print the length
    printf("%d\n", max_len);

    // Print the substring, handling possible newlines
    for(int i = orig_start; i <= orig_end; i++){
        putchar(original[i]);
    }

    return 0;
}