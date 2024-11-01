#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *word;
    int value;
} WordMap;

int main(){
    WordMap mappings[] = {
        // Standard
        {"one",1},{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},
        {"seven",7},{"eight",8},{"nine",9},{"ten",10},{"eleven",11},
        {"twelve",12},{"thirteen",13},{"fourteen",14},{"fifteen",15},
        {"sixteen",16},{"seventeen",17},{"eighteen",18},{"nineteen",19},
        {"twenty",20},
        // Non-standard
        {"a",1},{"both",2},{"another",1},{"first",1},{"second",2},{"third",3},
        // Zero
        {"zero",0}
    };
    int mapping_size = sizeof(mappings)/sizeof(mappings[0]);
    char word[50];
    int numbers[6];
    int n = 0;
    for(int i=0;i<6;i++){
        scanf("%s", word);
        // Remove possible punctuation
        int len = strlen(word);
        if(word[len-1]=='.') word[len-1] = '\0';
        // Search mapping
        int found = -1;
        for(int j=0;j<mapping_size;j++){
            if(strcmp(word, mappings[j].word)==0){
                found = mappings[j].value;
                break;
            }
        }
        if(found != -1){
            numbers[n++] = found;
        }
    }
    if(n ==0){
        printf("0");
        return 0;
    }
    // Calculate squared mod 100
    int sq_mod[6];
    for(int i=0;i<n;i++) {
        sq_mod[i] = (numbers[i]*numbers[i])%100;
    }
    // Generate permutations
    int min_val = -1;
    // Using Heap's algorithm for permutations
    int *perm = malloc(n * sizeof(int));
    for(int i=0;i<n;i++) perm[i] = sq_mod[i];
    // Initialize c array
    int c_arr[n];
    for(int i=0;i<n;i++) c_arr[i] =0;
    // Start permutation
    while(1){
        // Concatenate numbers
        char concat[20] = "";
        for(int i=0;i<n;i++){
            char temp[3];
            sprintf(temp, "%02d", perm[i]);
            strcat(concat, temp);
        }
        // Convert to integer, ignoring leading zeros
        int num = atoi(concat);
        if(min_val == -1 || num < min_val){
            min_val = num;
        }
        // Generate next permutation
        int i;
        for(i=0;i<n;i++) c_arr[i] =0;
        i=0;
        while(i < n){
            if(c_arr[i] < i){
                if(i%2 ==0){
                    // swap perm[0] and perm[i]
                    int temp = perm[0];
                    perm[0] = perm[i];
                    perm[i] = temp;
                }
                else{
                    // swap perm[c_arr[i]] and perm[i]
                    int temp = perm[c_arr[i]];
                    perm[c_arr[i]] = perm[i];
                    perm[i] = temp;
                }
                c_arr[i]++;
                i=0;
                continue;
            }
            else{
                c_arr[i] =0;
                i++;
            }
        }
        if(i >=n) break;
    }
    printf("%d", min_val);
    free(perm);
    return 0;
}