#pragma once

#include <array>

using std::array;

template <size_t N, typename T>
inline void Add(array<T, N>* dst, const array<T, N>& src)
{
    for (size_t i = 0; i != N; ++i) {
        (*dst)[i] += src[i];
    }
}

template <size_t N, typename T>
inline void Saxpy(array<T, N>* y, const array<T, N>& x, T multiplier)
{
    for (size_t i = 0; i != N; ++i) {
        (*y)[i] += multiplier * x[i];
    }
}
