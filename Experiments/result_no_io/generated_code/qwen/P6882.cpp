#include <stdio.h>
#include <ctype.h>

int main() {
    int N;
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        char sentence[1001];
        scanf(" %[^\n]", sentence);
        
        int count = 0;
        int inWord = 0;
        int hasUpper = 0;
        
        for (int j = 0; sentence[j] != '\0'; j++) {
            if (isalpha(sentence[j])) {
                if (!hasUpper && isupper(sentence[j])) {
                    hasUpper = 1;
                }
                inWord = 1;
            } else if (sentence[j] == '.' || sentence[j] == '?' || sentence[j] == '!') {
                if (inWord && hasUpper) {
                    count++;
                }
                inWord = 0;
                hasUpper = 0;
            } else {
                if (inWord) {
                    count++;
                    inWord = 0;
                    hasUpper = 0;
                }
            }
        }
        
        printf("%d\n", count);
    }
    
    return 0;
}