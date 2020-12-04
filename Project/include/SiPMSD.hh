#ifndef SiPMSD_hh
#define SiPMSD_hh

/// \file   SiPMSD.hh
/// \brief  Definition of the SiPMSD class

#include "G4VSensitiveDetector.hh"
#include "B4cCalorHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;
class SiPMSD : public G4VSensitiveDetector
{
  public:
                                SiPMSD      (const G4String& name, const G4String& hitsCollectionName,G4int nofCells);
    virtual                     ~SiPMSD     ();
  
    virtual void                Initialize  (G4HCofThisEvent* hitCollection);
    virtual G4bool              ProcessHits (G4Step* step, G4TouchableHistory* history);
    virtual void                EndOfEvent  (G4HCofThisEvent* hitCollection);

  private:
    B4cCalorHitsCollection*     fHitsCollection;
    G4int                       fNofCells;
};

#endif
