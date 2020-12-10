#include "SiPMHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<SiPMHit>* SiPMHitAllocator = 0;

SiPMHit::SiPMHit()
 :  G4VHit(),
    fEdep(0.),
    fTrackLength(0.),
    fPoint_dE_Vector(G4ThreeVector(0.,0.,0.))
{
    
}

SiPMHit::~SiPMHit()
{
    
}

SiPMHit::SiPMHit( const SiPMHit& right)
  : G4VHit()
{
    fEdep           =   right.fEdep;
    fTrackLength    =   right.fTrackLength;
    fPoint_dE_Vector=   right.fPoint_dE_Vector;
}

const SiPMHit& SiPMHit::operator=(const SiPMHit& right)
{
    fEdep           =   right.fEdep;
    fTrackLength    =   right.fTrackLength;
    fPoint_dE_Vector=   right.fPoint_dE_Vector;
    return *this;
}

G4int SiPMHit::operator==(const SiPMHit& right) const
{
    return         ( this == &right ) ? 1 : 0;
}
