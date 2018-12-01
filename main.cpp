#include "integrator.h"

#include <iostream>

int main(int argc, char** argv)
{
    using std::cerr;
    using std::cout;
    using std::endl;

    if (argc != 6) {
        cerr << "USAGE: " << argv[0] << " <mag> <freq> <phase> <barlen> <step>" << endl;
        exit(1);
    }

    TModelParams params;
    TInitialConditions init;
    double timeStep;

    {
        stringstream ss;
        for (int i = 1; i < argc; ++i) {
            ss << argv[i];
        }
        ss >> params.SupportMagnitude >> params.SupportFrequency >> init.SupportPhase >>
            params.BarLength >> timeStep;
    }

    TIntegrator integr(params, init, timeStep);

    const int stepCount = 100;

    for (int i = 0; i < stepCount; ++i) {
        cout << integr.GetTime() << ": " << integr.GetAngle << endl;
        integr.NextStep();
    }

    return 0;
}
