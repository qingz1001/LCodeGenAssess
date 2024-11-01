#include <stdio.h>
#include <string.h>

int main() {
    char word[101];
    scanf("%s", word);
    
    int len = strlen(word);
    for (int i = 0; i < len; ) {
        if (word[i] == 'C' || word[i] == 'A' || word[i] == 'M' || 
            word[i] == 'B' || word[i] == 'R' || word[i] == 'I' || 
            word[i] == 'D' || word[i] == 'G' || word[i] == 'E') {
            for (int j = i; j < len - 1; j++) {
                word[j] = word[j + 1];
            }
            len--;
        } else {
            i++;
        }
    }
    
    printf("%s\n", word);
    return 0;
}