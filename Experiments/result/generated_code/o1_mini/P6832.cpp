#include <stdio.h>
#include <stdlib.h>

int main(){
    // Allocate memory for the string, 10^7 + 1
    char *s = (char*)malloc(10000001 * sizeof(char));
    if(!s){
        return 1;
    }
    // Read the string
    if(!fgets(s, 10000001, stdin)){
        free(s);
        return 1;
    }
    // Initialize count array
    unsigned int count[26] = {0};
    // Iterate over the string
    for(int i=0; s[i] != '\n' && s[i] != '\0'; i++){
        char c = s[i];
        if(c >= 'a' && c <= 'z'){
            count[c - 'a']++;
        }
    }
    free(s);
    // Find the maximum count
    unsigned int max = 0;
    for(int i=0; i<26; i++){
        if(count[i] > max){
            max = count[i];
        }
    }
    // Print the result
    printf("%u\n", max);
    return 0;
}