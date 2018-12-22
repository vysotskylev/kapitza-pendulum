#include "integrator.h"

#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char** argv)
{
    using std::cerr;
    using std::cout;
    using std::endl;

    if (argc != 10) {
        cerr <<
            "USAGE: " << argv[0] << " " <<
            "<mag> <freq> <init-phase> <barlen> " <<
            "<init-angle> <init-angular-speed> <step> <step-count> " <<
            "<format>\n";
        exit(1);
    }

    TModelParams params;
    TInitialConditions init;
    double timeStep;
    size_t stepCount;
    bool binary;

    {
        std::stringstream ss;
        std::string formatStr;
        for (int i = 1; i < argc; ++i) {
            ss << argv[i] << ' ';
        }
        ss >>
            params.SupportMagnitude >> params.SupportFrequency >> init.SupportPhase >>
            params.BarLength >>
            init.Angle >> init.AngularVelocity >>
            timeStep >> stepCount >>
            formatStr;

        if (formatStr == "text") {
            binary = false;
        } else if (formatStr == "binary") {
            binary = true;
        } else {
            cerr << "Unknown format: " << formatStr << endl;
            exit(1);
        }
    }


    cerr <<
        "RUNNING MODELLING:\n" <<
        "  Support point:\n" <<
        "    Magnitude: " << params.SupportMagnitude << "\n" <<
        "    Frequency: " << params.SupportFrequency << "\n" <<
        "    Initial phase: " << init.SupportPhase << "\n" <<
        "  Initial state:\n" <<
        "    Angle: " << init.Angle << "\n" <<
        "    Angular velocity: " << init.AngularVelocity << "\n" <<
        "  Bar length: " << params.BarLength << "\n" <<
        "  Time step: " << timeStep << "\n" <<
        "  Binary: " << binary << endl;

    TIntegrator integr(params, init, timeStep);

    for (size_t i = 0; i != stepCount; ++i) {
        double angle = integr.GetAngle();
        if (binary) {
            cout.write((char*)&angle, sizeof(angle));
        } else {
            cout << angle << ' ';
        }
        integr.NextStep();
    }
    if (!binary) {
        cout << endl;
    }

    return 0;
}
