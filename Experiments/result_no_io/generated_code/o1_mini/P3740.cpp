#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long start;
    long end;
} Interval;

int main(){
    long N, M;
    scanf("%ld %ld", &N, &M);
    Interval posters[M];
    for(long i=0;i<M;i++) {
        scanf("%ld %ld", &posters[i].start, &posters[i].end);
    }
    // Initialize union intervals
    Interval unionIntervals[M*2];
    long unionCount = 0;
    long visible = 0;
    // Iterate from last to first
    for(long i=M-1;i>=0;i--){
        long A = posters[i].start;
        long B = posters[i].end;
        long current = A;
        // Check coverage
        for(long j=0; j<unionCount && current <= B; j++){
            if(unionIntervals[j].end < current){
                continue;
            }
            if(unionIntervals[j].start > current){
                break;
            }
            if(unionIntervals[j].start <= current && unionIntervals[j].end >= current){
                if(unionIntervals[j].end >= B){
                    current = B +1;
                    break;
                }
                if(unionIntervals[j].end +1 > current){
                    current = unionIntervals[j].end +1;
                }
            }
        }
        if(current <= B){
            visible++;
        }
        // Merge [A,B] into unionIntervals
        // Find the position to insert
        long newStart = A;
        long newEnd = B;
        // Find the first interval that might overlap
        long startPos = 0;
        while(startPos < unionCount && unionIntervals[startPos].end < A){
            startPos++;
        }
        // Merge overlapping intervals
        long endPos = startPos;
        while(endPos < unionCount && unionIntervals[endPos].start <= B){
            if(unionIntervals[endPos].start < newStart){
                newStart = unionIntervals[endPos].start;
            }
            if(unionIntervals[endPos].end > newEnd){
                newEnd = unionIntervals[endPos].end;
            }
            endPos++;
        }
        // Shift intervals to remove overlapped
        long shift = endPos - startPos;
        for(long j=startPos; j<unionCount - shift; j++){
            unionIntervals[j] = unionIntervals[j + shift];
        }
        unionCount -= shift;
        // Insert the new merged interval
        // Shift to make space
        for(long j=unionCount; j>startPos; j--){
            unionIntervals[j] = unionIntervals[j-1];
        }
        unionIntervals[startPos].start = newStart;
        unionIntervals[startPos].end = newEnd;
        unionCount++;
    }
    printf("%ld\n", visible);
    return 0;
}