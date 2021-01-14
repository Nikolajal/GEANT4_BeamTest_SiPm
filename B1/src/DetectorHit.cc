#include "DetectorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include <iomanip>

G4ThreadLocal G4Allocator<DetectorHit> *DetectorHitAllocator    = 0;

                        DetectorHit::DetectorHit        ( )
 :  G4VHit()    {
    fEnergyDeposit  =   0.;
    fEnergyDepoSQR  =   0.;
    fEDepPosition   =   G4ThreeVector(0.,0.,0.);
    fEntries=0;
}

                        DetectorHit::~DetectorHit       ( )  {
}

                        DetectorHit::DetectorHit        ( const DetectorHit& right )
  : G4VHit()    {
    fEnergyDeposit  =   right.fEnergyDeposit;
    fEnergyDepoSQR  =   right.fEnergyDepoSQR;
    fEDepPosition   =   right.fEDepPosition;
}

const DetectorHit&      DetectorHit::operator=          ( const DetectorHit& right )    {
    fEnergyDeposit  =   right.fEnergyDeposit;
    fEnergyDepoSQR  =   right.fEnergyDepoSQR;
    fEDepPosition   =   right.fEDepPosition;
    return *this;
}

G4int                   DetectorHit::operator==         ( const DetectorHit& right ) const  {
    return         ( this == &right ) ? 1 : 0;
}

void                    DetectorHit::Add                ( G4double fEDep, G4ThreeVector fEDepPnt )  {
    fEnergyDeposit  +=  fEDep;
    fEnergyDepoSQR  +=  fEDep*fEDep;
    fEDepPosition   +=  fEDep*fEDepPnt;
    fEntries++;
}