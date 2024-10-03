int index_first_zero(int array[]) {
    int index = -1;
    for (int i = 0; i < 100; i++) {
        if (array[i] == 0) {
            index = i;
            break;
        }
    }
    return index;
}