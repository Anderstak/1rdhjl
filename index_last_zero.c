int index_last_zero(int array[], int N) {
    int index = -1;
    for (int i = N - 1; i >= 0; i--) {
        if (array[i] == 0) {
            index = i;
            break;
        }
    }
    return index;
}