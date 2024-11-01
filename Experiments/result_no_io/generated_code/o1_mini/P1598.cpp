#include <stdio.h>
#include <string.h>

#define MAX_LINE 101
#define LETTERS 26

int main(){
    int freq[LETTERS] = {0};
    char line[MAX_LINE];
    for(int i=0;i<4;i++){
        if(fgets(line, sizeof(line), stdin)){
            for(int j=0; line[j]!='\n' && line[j]!='\0'; j++){
                if(line[j]>='A' && line[j]<='Z'){
                    freq[line[j]-'A']++;
                }
            }
        }
    }
    // Collect letters with freq >0
    char letters[LETTERS];
    int k=0;
    int max=0;
    for(int i=0;i<LETTERS;i++){
        if(freq[i]>0){
            letters[k++] = 'A' + i;
            if(freq[i]>max) max = freq[i];
        }
    }
    // Print rows from max to 1
    for(int row=max; row>=1; row--){
        char output[LETTERS*2];
        int idx=0;
        for(int i=0;i<k;i++){
            output[idx++] = (freq[letters[i]-'A']>=row)? '*' : ' ';
            if(i != k-1){
                output[idx++] = ' ';
            }
        }
        output[idx] = '\0';
        // Trim trailing spaces
        int len = strlen(output);
        while(len >0 && output[len-1]==' ') len--;
        output[len] = '\0';
        printf("%s\n", output);
    }
    // Print letters
    for(int i=0;i<k;i++){
        printf("%c", letters[i]);
        if(i != k-1) printf(" ");
    }
    printf("\n");
    return 0;
}