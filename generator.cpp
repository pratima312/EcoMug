#include <iostream>
#include <fstream>
#include <array>
#include <cmath>
#include <iomanip>    
using namespace std;

#include "EcoMug.h"

struct MuonPosition {
    double x, y, z;
};

ostream& operator<<(ostream& os, const MuonPosition& m) {
    os << "(" << m.x << ", " << m.y << ", " << m.z << ")";
    return os;
}

struct muonmomentum {
    double px, py, pz;
};

ostream& operator<<(ostream& os, const muonmomentum& m) {
    os << "(" << m.px << ", " << m.py << ", " << m.pz << ")";
    return os;
}

int main() {
    ofstream csv("muon_1l.csv");
    if (!csv) {
        cerr << "Error: cannot open muon.csv for writing\n";
        return 1;
    }

    csv << "x,y,z,px,py,pz,phi,theta,charge\n";

    EcoMug gen;
    gen.SetUseSky();
    gen.SetSkySize({{10., 10.}});
    gen.SetSkyCenterPosition({{0., 0., 20.}});

    std::array<double, 3> muon_position;

    csv << std::fixed << std::setprecision(6);

    const int nEvents = 100000;
    for (auto event = 0; event < nEvents; ++event) {
        gen.Generate();

        muon_position = gen.GetGenerationPosition();
        double muon_p      = gen.GetGenerationMomentum();
        double muon_theta  = gen.GetGenerationTheta();
        double muon_phi    = gen.GetGenerationPhi();
        double muon_charge = gen.GetCharge();

        double px = muon_p * sin(muon_theta) * cos(muon_phi);
        double py = muon_p * sin(muon_theta) * sin(muon_phi);
        double pz = muon_p * cos(muon_theta);

        
        csv << muon_position[0] << ","
            << muon_position[1] << ","
            << muon_position[2] << ","
            << px << ","
            << py << ","
            << pz << ","
            << muon_phi << ","
            << muon_theta << ","
            << muon_charge << "\n";
    }

    csv.close();
    return 0;
}
