#ifndef B4cEventAction_h
#define B4cEventAction_h

#include "G4UserEventAction.hh"
#include "SiPMHit.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction
{
public:
                            EventAction();
  virtual                   ~EventAction();

  virtual void              BeginOfEventAction  ( const G4Event* event );
  virtual void              EndOfEventAction    ( const G4Event* event );
    
private:
  SiPMHitsCollection*       GetHitsCollection   ( G4int hcID, const G4Event* event ) const;
  G4int                    *fCollectionHitsID;
};

#endif
