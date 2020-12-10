#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class SiPMDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(SiPMDetectorConstruction* );
   ~DetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    SiPMDetectorConstruction* Detector;
    
    G4UIdirectory*             fDir_SiPMProject;
    G4UIdirectory*             fDir_SiPMProject_Detector;
    G4UIdirectory*             fDir_SiPMProject_Absorber;
    G4UIcmdWithAString*        fCmd_Absorber_Material;
    G4UIcmdWithADoubleAndUnit* fCmd_Absorber_MoveXDir;
    G4UIcmdWithADoubleAndUnit* fCmd_Absorber_MoveYDir;
    G4UIcmdWithADoubleAndUnit* fCmd_Absorber_MoveZDir;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

