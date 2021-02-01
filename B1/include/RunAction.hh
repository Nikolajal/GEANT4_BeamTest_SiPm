/// \file RunAction.hh
/// \brief Definition of the RunAction class

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "RunMessenger.hh"
#include "G4Accumulable.hh"
#include "RunMessenger.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class RunAction : public G4UserRunAction
{
  public:
                    RunAction();
    virtual        ~RunAction();

    // virtual G4Run* GenerateRun();
    virtual void    BeginOfRunAction  ( const G4Run*  );
    virtual void    EndOfRunAction    ( const G4Run*  );

    void            AddEdep           ( G4double edep );
    void            fSetFileName      ( G4String fNewFileName ) { fFileName = fNewFileName; };

    void            fSetIndex           ( G4int edep ) { fCollectionIndex = edep; };
    void            fSetEDepMap         ( std::map<G4String,G4int> edep ) { fMapOfEDepHistograms = edep; };
    std::map<G4String,G4int>  fGetEDepMap (  ) { return fMapOfEDepHistograms;};
    G4int            fGetIndex        (  ) { return fCollectionIndex ;};
    
    
    std::map<G4String,G4int>  fGetCntrMap (  ) { return fMapOfHistograms;};
    void            fSetCntrMap         ( std::map<G4String,G4int> edep ) { fMapOfHistograms = edep; };
    
    
  private:
    G4String        fFileName;
    RunMessenger   *fRunMessenger;
    G4int                       fCollectionIndex;
    std::map<G4String,G4int>    fMapOfEDepHistograms;
    std::map<G4String,G4int>    fMapOfHistograms;
};

#endif

