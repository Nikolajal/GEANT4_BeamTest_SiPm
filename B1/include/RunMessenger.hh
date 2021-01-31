#ifndef RunMessenger_h
#define RunMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "RunAction.hh"

class RunAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunMessenger: public G4UImessenger
{
  public:
    RunMessenger( RunAction* );
   ~RunMessenger();
    
    void SetNewValue( G4UIcommand*, G4String );
    
  private:
    RunAction*                  fRunAction;
    G4UIdirectory*              fDir_SiPmProject;
    G4UIdirectory*              fDir_RunAction;
    G4UIcmdWithAString*         fCmd_Outputfile_Name;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

