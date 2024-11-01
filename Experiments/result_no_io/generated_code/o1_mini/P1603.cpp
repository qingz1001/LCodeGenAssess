#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char words[6][21];
    // Read 6 words
    for(int i=0;i<6;i++){
        scanf("%20s", words[i]);
        // Remove trailing punctuation
        int len = strlen(words[i]);
        if(words[i][len-1]=='.') words[i][len-1]='\0';
        // Convert to lowercase
        for(int j=0; j<strlen(words[i]); j++) words[i][j] = tolower(words[i][j]);
    }

    // Mapping function
    int get_number(char *word){
        // Standard numbers
        const char *standard[] = {"one","two","three","four","five","six","seven","eight","nine",
                                 "ten","eleven","twelve","thirteen","fourteen","fifteen",
                                 "sixteen","seventeen","eighteen","nineteen","twenty"};
        int std_size = 20;
        for(int i=0;i<std_size;i++) if(strcmp(word, standard[i])==0) return i+1;
        // Non-standard
        if(strcmp(word, "a")==0) return 1;
        if(strcmp(word, "both")==0) return 2;
        if(strcmp(word, "another")==0) return 1;
        if(strcmp(word, "first")==0) return 1;
        if(strcmp(word, "second")==0) return 2;
        if(strcmp(word, "third")==0) return 3;
        return 0;
    }

    char digits[25];
    int d_idx=0;
    for(int i=0;i<6;i++){
        int num = get_number(words[i]);
        if(num >0 && num <=20){
            int sq = (num * num) % 100;
            digits[d_idx++] = '0' + (sq / 10);
            digits[d_idx++] = '0' + (sq % 10);
        }
    }

    if(d_idx ==0){
        printf("0\n");
        return 0;
    }

    // Count digit frequencies
    int freq[10] = {0};
    for(int i=0;i<d_idx;i++) freq[digits[i]-'0']++;

    // Find smallest non-zero digit
    int first = -1;
    for(int i=1;i<=9;i++) {
        if(freq[i]>0){
            first = i;
            freq[i]--;
            break;
        }
    }
    if(first == -1){
        // All digits are zero
        printf("0\n");
        return 0;
    }

    // Build minimal number
    char result[25];
    int r =0;
    result[r++] = '0' + first;
    // Append zeros
    while(freq[0] >0){
        result[r++] = '0';
        freq[0]--;
    }
    // Append remaining digits in order
    for(int i=1;i<=9;i++) {
        while(freq[i]>0){
            result[r++] = '0' + i;
            freq[i]--;
        }
    }
    result[r] = '\0';

    // Print as number
    printf("%s\n", result);
    return 0;
}