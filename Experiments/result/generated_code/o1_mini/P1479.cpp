#include <stdio.h>
#include <stdint.h>

int main(){
    int n;
    scanf("%d", &n);
    // Define the 12 line masks
    unsigned int lines[12] = {
        // Rows
        (1U<<0)|(1U<<1)|(1U<<2)|(1U<<3)|(1U<<4),
        (1U<<5)|(1U<<6)|(1U<<7)|(1U<<8)|(1U<<9),
        (1U<<10)|(1U<<11)|(1U<<12)|(1U<<13)|(1U<<14),
        (1U<<15)|(1U<<16)|(1U<<17)|(1U<<18)|(1U<<19),
        (1U<<20)|(1U<<21)|(1U<<22)|(1U<<23)|(1U<<24),
        // Columns
        (1U<<0)|(1U<<5)|(1U<<10)|(1U<<15)|(1U<<20),
        (1U<<1)|(1U<<6)|(1U<<11)|(1U<<16)|(1U<<21),
        (1U<<2)|(1U<<7)|(1U<<12)|(1U<<17)|(1U<<22),
        (1U<<3)|(1U<<8)|(1U<<13)|(1U<<18)|(1U<<23),
        (1U<<4)|(1U<<9)|(1U<<14)|(1U<<19)|(1U<<24),
        // Diagonals
        (1U<<0)|(1U<<6)|(1U<<12)|(1U<<18)|(1U<<24),
        (1U<<4)|(1U<<8)|(1U<<12)|(1U<<16)|(1U<<20)
    };
    // Initialize k_possible
    unsigned char k_possible[13] = {0};
    // Iterate all combinations
    if(n <0 || n >25){
        // Do nothing, invalid input
    } else{
        if(n ==0){
            // k=0 is possible
            k_possible[0] =1;
        } else{
            if(n >25) n =25;
            unsigned int c = (n == 25) ? 0x1FFFFFF : (1U <<n) -1;
            while(1){
                int k =0;
                for(int i=0;i<12;i++) {
                    if( (c & lines[i]) == lines[i] ){
                        k++;
                    }
                }
                if(k <=12){
                    k_possible[k] =1;
                }
                // Generate next combination
                if(n ==25) break;
                unsigned int smallest = c & -c;
                unsigned int ripple = c + smallest;
                if(ripple ==0){
                    break;
                }
                unsigned int new_smallest = c ^ ripple;
                new_smallest = (new_smallest >> 2)/smallest;
                c = ripple | new_smallest;
                if(__builtin_popcount(c) != n){
                    break;
                }
            }
        }
        // Now, compute sum
        int sum =0;
        for(int k=0;k<=12;k++) if(k_possible[k]) sum +=k;
        printf("%d\n", sum);
    }
}