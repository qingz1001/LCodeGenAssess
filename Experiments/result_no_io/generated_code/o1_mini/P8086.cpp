#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_X 10000000
#define BUFFER_SIZE 1 << 20

unsigned char bitmap[(MAX_X >> 3) + 2];
char buffer[BUFFER_SIZE];
size_t data_size = 0, data_pos = 0;

int get_char() {
    if (data_pos >= data_size) {
        data_size = fread(buffer, 1, BUFFER_SIZE, stdin);
        if (data_size == 0) return EOF;
        data_pos = 0;
    }
    return buffer[data_pos++];
}

uint32_t read_uint() {
    uint32_t x = 0;
    int c = get_char();
    while(c < '0' || c > '9') {
        if(c == EOF) return x;
        c = get_char();
    }
    while(c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = get_char();
    }
    return x;
}

int main(){
    uint32_t n, x, t;
    unsigned long long sum = 0;
    n = read_uint();
    for(uint32_t i=0;i<n;i++){
        x = read_uint();
        t = read_uint();
        if(t >1){
            uint32_t byte_idx = x >> 3;
            uint8_t bit_idx = x & 7;
            if(!(bitmap[byte_idx] & (1 << bit_idx))){
                sum += t;
                bitmap[byte_idx] |= (1 << bit_idx);
            }
        }
    }
    printf("%llu\n", sum);
    return 0;
}