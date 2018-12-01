#pragma once

#include <array>

#include "fixed_valarray.h"

// f must have signature void(double time, const array<N, double>& y, array<N, double>* res).
template <typename Fun, int N>
RungeKuttaStep(
    Fun f,
    double time,
    double step,
    std::array<N, double>* y)
{
    using TArray = std::array<N, double>;
    TArray k1, k2, k3, k4;

    f(time, y, &k1);

    TArray tmp = y;
    Saxpy(&tmp, k1, step / 2);
    f(time + step / 2, tmp, &k2);

    tmp = y;
    Saxpy(&tmp, k2, step / 2);
    f(time + step / 2, tmp, &k3);

    tmp = y;
    Saxpy(&tmp, k3, step);
    f(time + step, tmp, &k4);

    tmp = k1;
    Add(&tmp, k2);
    Add(&tmp, k2);
    Add(&tmp, k3);
    Add(&tmp, k3);
    Add(&tmp, k4);

    Saxpy(y, tmp, step / 6);
}


