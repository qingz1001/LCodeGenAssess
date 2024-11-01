pp
extern "C" int Seniorious(int);

extern "C" int Chtholly(int n, int c) {
    int left = 1, right = n;
    while (left <= right) {
        int mid = (left + right) / 2;
        int result = Seniorious(mid);
        if (result == 0) {
            return mid;
        } else if (result == 1) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1; // 理论上不会到达这里，因为一定能在 c 次内找到 k
}