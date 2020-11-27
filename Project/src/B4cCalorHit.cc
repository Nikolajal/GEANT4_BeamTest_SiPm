#include "B4cCalorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<B4cCalorHit>* B4cCalorHitAllocator = 0;

B4cCalorHit::B4cCalorHit()
 :  G4VHit(),
    fEdep(0.),
    fTrackLength(0.),
    fPoint_dE_Vector(G4ThreeVector(0.,0.,0.))
{
    
}

B4cCalorHit::~B4cCalorHit()
{
    
}

B4cCalorHit::B4cCalorHit(const B4cCalorHit& right)
  : G4VHit()
{
    fEdep           =   right.fEdep;
    fTrackLength    =   right.fTrackLength;
    fPoint_dE_Vector=   right.fPoint_dE_Vector;
}

const B4cCalorHit& B4cCalorHit::operator=(const B4cCalorHit& right)
{
    fEdep           =   right.fEdep;
    fTrackLength    =   right.fTrackLength;
    fPoint_dE_Vector=   right.fPoint_dE_Vector;
    return *this;
}

G4int B4cCalorHit::operator==(const B4cCalorHit& right) const
{
    return         ( this == &right ) ? 1 : 0;
}
