#pragma once

#include "runge_kutta.h"

#include <cmath>

constexpr double FREE_FALL_ACC = 9.8;

struct TModelParams
{
    double BarLength;
    double SupportMagnitude;
    double SupportFrequency;
};

struct TInitialConditions
{
    double Angle;
    double AngularVelocity;
    double SupportPhase;
};

class TIntegrator
{

private:
    using TState = std::array<double, 2ul>;

    class Fun
    {
    public:
        Fun(const TIntegrator& integrator)
            : Integrator_(integrator)
        { }

        void operator() (double time, const TState& y, TState* res)
        {
            const auto& phi = y[0];
            const auto& psi = y[1];
            const auto& freq = Integrator_.Params_.SupportFrequency;
            const auto& mag = Integrator_.Params_.SupportMagnitude;
            auto supportPhase = sin(freq * time + Integrator_.SupportPhase_);

            (*res)[0] = psi;
            (*res)[1] = sin(phi) / Integrator_.Params_.BarLength *
                (freq * freq * mag * supportPhase - FREE_FALL_ACC);
        }

    private:
        const TIntegrator& Integrator_;
    };

public:
    TIntegrator(
        const TModelParams& params,
        const TInitialConditions& init,
        double timeStep)
        : Fun_(*this)
        , Params_(std::move(params))
        , TimeStep_(timeStep)
    {
        State_[0] = init.Angle;
        State_[1] = init.AngularVelocity;
        SupportPhase_ = init.SupportPhase;
    }

    double GetAngle() const
    {
        return State_[0];
    }

    double GetTime() const
    {
        return Time_;
    }

    void NextStep()
    {
        RungeKuttaStep(Fun_, Time_, TimeStep_, &State_);
        Time_ += TimeStep_;
    }

private:
    Fun Fun_;
    TModelParams Params_;
    TState State_;
    double SupportPhase_ = 0;
    double Time_ = 0;
    double TimeStep_ = 0;
};
