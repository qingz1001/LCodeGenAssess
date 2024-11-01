#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    // Define the values and corresponding symbols
    int values[] = {1000, 900, 500, 400, 100, 90, 50,40,10,9,5,4,1};
    const char *symbols[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int num_symbols = sizeof(values)/sizeof(values[0]);
    
    // Initialize counts for 'I','V','X','L','C','D','M'
    int counts[7] = {0};
    
    // Function to map character to index
    // 'I'->0, 'V'->1, 'X'->2, 'L'->3, 'C'->4, 'D'->5, 'M'->6
    for(int number=1; number<=n; number++){
        int temp = number;
        for(int i=0;i<num_symbols;i++){
            while(temp >= values[i]){
                temp -= values[i];
                const char *sym = symbols[i];
                for(int j=0; sym[j]!='\0'; j++){
                    char c = sym[j];
                    switch(c){
                        case 'I': counts[0]++; break;
                        case 'V': counts[1]++; break;
                        case 'X': counts[2]++; break;
                        case 'L': counts[3]++; break;
                        case 'C': counts[4]++; break;
                        case 'D': counts[5]++; break;
                        case 'M': counts[6]++; break;
                    }
                }
            }
        }
    }
    
    // Define the order of characters
    char order[7] = {'I','V','X','L','C','D','M'};
    for(int i=0;i<7;i++){
        if(counts[i] > 0){
            printf("%c %d\n", order[i], counts[i]);
        }
    }
    return 0;
}