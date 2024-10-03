#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int array[], int N) {
    int index_first = index_first_zero(array);
    int index_last = index_last_zero(array, N);
    int sum_a = 0;
    for (int i = 0; i < index_first; i++) {
        sum_a += abs(array[i]);
    }
    while (index_last < N) {
        sum_a += abs(array[index_last++]);
    }
    return sum_a;

}