#ifndef B4cCalorimeterSD_h
#define B4cCalorimeterSD_h

#include "G4VSensitiveDetector.hh"
#include "B4cCalorHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;
class B4cCalorimeterSD : public G4VSensitiveDetector
{
  public:
                                B4cCalorimeterSD(const G4String& name, const G4String& hitsCollectionName,G4int nofCells);
    virtual                     ~B4cCalorimeterSD();
  
    virtual void                Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool              ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void                EndOfEvent(G4HCofThisEvent* hitCollection);

  private:
    B4cCalorHitsCollection*     fHitsCollection;
    G4int                       fNofCells;
};

#endif
