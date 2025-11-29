EcoMug is the tool to produce muons which mimics the cosmic ray muons. Here is the code for plane based generation of cosmic ray muons.

```bash
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

ostream & operator<<(ostream & os, const MuonPosition& m) {
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
```

Here the data for 1,00,000 muons is recorded in csv file. Later on the momentum distribution, theta distribution and phi distribution is made using python. In the momentum distribution graph it can be seen that most of the particles having the momentum between 1GeV/c to 5GeV/c are being produced. Which is comparable with the observed muon energy 3GeV. Theta and Phi distribution are the angualar distribution of the cosmic ray muons.


EcoMug reference - 
   https://www.bing.com/ck/a?!&&p=0c5c4bb690f8fe415ce3bd6dd0e57e4fe437bf6993d4af051e487d050f0c231fJmltdHM9MTc2NDI4ODAwMA&ptn=3&ver=2&hsh=4&fclid=195e9c6f-e4c2-684f-0e45-88b8e5bd6932&psq=ecomug+cosmic+ray+muon+generator&u=a1aHR0cHM6Ly93d3cuc2NpZW5jZWRpcmVjdC5jb20vc2NpZW5jZS9hcnRpY2xlL3BpaS9TMDE2ODkwMDIyMTAwNzE3OA
