/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "RunAction.hh"
#include "SensitiveDetector.hh"
#include "DetectorHit.hh"
#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"
#include "G4SDManager.hh"
#include "globals.hh"

class RunAction;

/// Event action class
///

class DetectorConstruction;
class EventAction : public G4UserEventAction
{
  public:
                              EventAction           ( );
    virtual                  ~EventAction           ( );

    virtual void              BeginOfEventAction    ( const G4Event* event);
    virtual void              EndOfEventAction      ( const G4Event* event);
    
  private:
    DetectorHitsCollection*   GetHitsCollection     ( G4int, const G4Event* );
    RunAction* fRunAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
