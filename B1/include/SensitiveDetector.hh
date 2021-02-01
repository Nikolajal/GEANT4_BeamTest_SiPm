#ifndef SensitiveDetector_hh
#define SensitiveDetector_hh

/// \file   SensitiveDetector.hh
/// \brief  Definition of the SensitiveDetector class

#include "G4VSensitiveDetector.hh"
#include "DetectorHit.hh"
#include <vector>

class G4Step;
class G4HCofThisEvent;
class SensitiveDetector : public G4VSensitiveDetector
{
  public:
                                SensitiveDetector     ( const G4String&, const G4String&, G4int );
    virtual                     ~SensitiveDetector    ( );
  
    virtual void                Initialize            ( G4HCofThisEvent* );
    virtual G4bool              ProcessHits           ( G4Step*,          G4TouchableHistory*  );
    virtual void                EndOfEvent            ( G4HCofThisEvent* );

  private:
    DetectorHitsCollection     *fHitsCollection;
};

#endif
