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
    gen.SetSkySize({{0.5, 0.5}});
    gen.SetSkyCenterPosition({{0., 0., 0.5}});

    // // Cylindrical generation
    // EcoMug gen; // initialization of the class
    // gen.SetUseCylinder(); // cylindrical surface generation
    // gen.SetCylinderRadius(0.15); // cylinder radius
    // gen.SetCylinderHeight(0.4); // cylinder height
    // // (x,y,z) position of the center of the cylinder
    // gen.SetCylinderCenterPosition({{0., 0., 0.1}});


    // // Half-spherical generation
    // EcoMug gen; // initialization of the class
    // gen.SetUseHSphere(); // half-spherical surface generation
    // gen.SetHSphereRadius(0.4); // half-sphere radius
    // // (x,y,z) position of the center of the half-sphere
    // gen.SetHSphereCenterPosition({{0., 0., 0.3}});


    // //Constraints on generated muons
    // gen.SetMinimumMomentum(00.);
    // gen.SetMaximumMomentum(00.);
    // gen.SetMinimumTheta(0.);
    // gen.SetMaximumTheta(M_PI/4);
    // gen.SetMinimumPhi(0.);
    // gen.SetMaximumPhi(M_PI);

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
