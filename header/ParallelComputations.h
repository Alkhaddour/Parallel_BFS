#ifndef PARALLEL_BFS_OPENMP_PARALLELCOMPUTATIONS_H
#define PARALLEL_BFS_OPENMP_PARALLELCOMPUTATIONS_H

#include <functional>
#include "utils.h"

template<typename I, typename O>
void map(I *input, O *output, LL first, LL last, std::function<O(I)> &mapping_fun) {
#pragma omp parallel for num_threads(N_THREADS) default(none) shared(first, last, mapping_fun, input, output)
    for(LL i=first; i < last; i++) {
        output[i] = mapping_fun(input[i]);
    }
}

template<typename T>
T scan(const T *input, T* output, LL first, LL last) {
    T cumulative = 0;
#pragma omp simd reduction(inscan, +: cumulative)
    for(int i = first; i < last; i++) {
        output[i] = cumulative;
#pragma omp scan exclusive(cumulative)
        cumulative += input[i];
    }
    return cumulative;
}

template<typename T>
LL filter(T *input, T *output, LL* buf1, LL* buf2, LL first, LL last, std::function<LL(T)> &filter_func) {
    // find size of next front
    map(input, buf1, first, last, filter_func);
    LL size = scan(buf1, buf2, first, last);

    // update front
#pragma omp parallel for num_threads(N_THREADS) default(none) shared(first, last, buf1, buf2, input, output)
    for (LL i = first; i < last; i++) {
        if (buf1[i]) {
            output[first + buf2[i]] = input[i];
        }
    }
    return size;
}

#endif //PARALLEL_BFS_OPENMP_PARALLELCOMPUTATIONS_H
