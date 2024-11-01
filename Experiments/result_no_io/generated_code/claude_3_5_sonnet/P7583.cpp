#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int main() {
    char word[MAX_LEN];
    char result[MAX_LEN];
    int j = 0;
    
    scanf("%s", word);
    
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] != 'C' && word[i] != 'A' && word[i] != 'M' && 
            word[i] != 'B' && word[i] != 'R' && word[i] != 'I' && 
            word[i] != 'D' && word[i] != 'G' && word[i] != 'E') {
            result[j++] = word[i];
        }
    }
    result[j] = '\0';
    
    printf("%s\n", result);
    
    return 0;
}