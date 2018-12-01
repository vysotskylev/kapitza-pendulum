#pragma once

#include <array>

using std::array;

template <typename N, typename T>
inline void Add(array<N,T>* dst, const array<N,T>& src)
{
    for (size_t i = 0; i != N; ++i) {
        (*dst)[i] += src[i];
    }
}

template <typename N, typename T>
inline void Saxpy(array<N,T>* y, const array<N,T>& x, T multiplier)
{
    for (size_t i = 0; i != N; ++i) {
        (*dst)[i] += multiplier * src[i];
    }
}
