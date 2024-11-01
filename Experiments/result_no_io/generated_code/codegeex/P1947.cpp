pp
#include <cstdio>

extern "C" int Seniorious(int x);

extern "C" int Chtholly(int n, int c) {
    int l = 1, r = n, mid;
    int count = 0;
    while (l <= r) {
        mid = (l + r) >> 1;
        int response = Seniorious(mid);
        count++;
        if (response == 0) {
            return mid;
        } else if (response == 1) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1; // 如果无法在指定次数内猜中，返回-1（实际不会发生）
}