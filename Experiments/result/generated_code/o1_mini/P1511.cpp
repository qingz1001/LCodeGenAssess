#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_A 201
#define BUFFER_SIZE 100

int main(){
    char A[MAX_A];
    scanf("%s", A);
    int lenA = strlen(A);
    
    // Compute lps array
    int lps[MAX_A];
    lps[0] = 0;
    for(int i=1;i<lenA;i++){
        int len = lps[i-1];
        while(len >0 && A[i] != A[len]){
            len = lps[len-1];
        }
        if(A[i] == A[len]){
            len++;
        }
        lps[i] = len;
    }
    
    unsigned long long n=1;
    int current_length=0;
    unsigned long long position=0;
    char buffer[BUFFER_SIZE];
    
    while(1){
        sprintf(buffer, "%llu", n);
        int len = strlen(buffer);
        for(int i=0;i<len;i++){
            char c = buffer[i];
            position++;
            while(current_length >0 && c != A[current_length]){
                current_length = lps[current_length-1];
            }
            if(c == A[current_length]){
                current_length++;
            }
            if(current_length == lenA){
                printf("%llu\n", position - lenA +1);
                return 0;
            }
        }
        n++;
    }
}