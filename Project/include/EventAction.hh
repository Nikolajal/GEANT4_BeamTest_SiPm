#ifndef B4cEventAction_h
#define B4cEventAction_h

#include "G4UserEventAction.hh"
#include "B4cCalorHit.hh"
#include "globals.hh"

class B4cEventAction : public G4UserEventAction
{
public:
                            B4cEventAction();
  virtual                   ~B4cEventAction();

  virtual void              BeginOfEventAction(const G4Event* event);
  virtual void              EndOfEventAction(const G4Event* event);
    
private:
  B4cCalorHitsCollection*   GetHitsCollection(G4int hcID,const G4Event* event) const;
  G4int                     fAbsHCID;
  G4int                     fGapHCID;
};

#endif
