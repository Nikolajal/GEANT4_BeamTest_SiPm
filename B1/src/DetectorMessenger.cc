#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger    ( DetectorConstruction* Det )
    : G4UImessenger(),  fDetector(Det)
{
    //  Project GUI Commands
    fDir_SiPmProject            = new G4UIdirectory("/SiPm/");
    fDir_SiPmProject            ->SetGuidance("UI commands of this Project");
    
    //  Detector GUI Configuration
    fDir_SiPmProject_Detector   = new G4UIdirectory("/SiPm/Detector/");
    fDir_SiPmProject_Detector   ->SetGuidance("Detector Configuration");
    
    //  Absorber GUI Configuration
    fDir_SiPmProject_Absorber   = new G4UIdirectory("/SiPm/Absorber/");
    fDir_SiPmProject_Absorber   ->SetGuidance("Absorber Configuration");
    
    // -- // Absorber Material
    fCmd_Absorber_Material      = new G4UIcmdWithAString("/SiPm/Absorber/material",this);
    fCmd_Absorber_Material      ->SetGuidance("Select Material of the Absorber");
    fCmd_Absorber_Material      ->SetParameterName("choice",false);
    fCmd_Absorber_Material      ->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    // -- // Absorber X Position
    fCmd_Absorber_MoveXDir      = new G4UIcmdWithADoubleAndUnit("/SiPm/Absorber/movex",this);
    fCmd_Absorber_MoveXDir      ->SetGuidance("Move the Absorber in X");
    fCmd_Absorber_MoveXDir      ->SetParameterName("Size",false);
    fCmd_Absorber_MoveXDir      ->SetUnitCategory("Length");
    fCmd_Absorber_MoveXDir      ->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    // -- // Absorber Y Position
    fCmd_Absorber_MoveYDir      = new G4UIcmdWithADoubleAndUnit("/SiPm/Absorber/movey",this);
    fCmd_Absorber_MoveYDir      ->SetGuidance("Move the Absorber in Y");
    fCmd_Absorber_MoveYDir      ->SetParameterName("Size",false);
    fCmd_Absorber_MoveYDir      ->SetUnitCategory("Length");
    fCmd_Absorber_MoveYDir      ->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    // -- // Absorber Z Position
    fCmd_Absorber_MoveZDir      = new G4UIcmdWithADoubleAndUnit("/SiPm/Absorber/movez",this);
    fCmd_Absorber_MoveZDir      ->SetGuidance("Move the Absorber in Z");
    fCmd_Absorber_MoveZDir      ->SetParameterName("Size",false);
    fCmd_Absorber_MoveZDir      ->SetUnitCategory("Length");
    fCmd_Absorber_MoveZDir      ->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
    // Delete Directories
    delete  fDir_SiPmProject;
    delete  fDir_SiPmProject_Detector;
    delete  fDir_SiPmProject_Absorber;
    
    // Delete Absorber
    delete  fCmd_Absorber_Material;
    delete  fCmd_Absorber_MoveXDir;
    delete  fCmd_Absorber_MoveYDir;
    delete  fCmd_Absorber_MoveZDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(    G4UIcommand* command,   G4String fInputValue   )
{
    if ( command == fCmd_Absorber_Material )    {
        
        fDetector    ->  fSetAbsorberMat( fInputValue );
    }
    if ( command == fCmd_Absorber_MoveXDir )    {
        
        fDetector    ->  fMoveAbsorber( G4ThreeVector(fCmd_Absorber_MoveXDir->GetNewDoubleValue(fInputValue),0.,0.) );
    }
    if ( command == fCmd_Absorber_MoveYDir )    {
        
        fDetector    ->  fMoveAbsorber( G4ThreeVector(0.,fCmd_Absorber_MoveYDir->GetNewDoubleValue(fInputValue),0.) );
    }
    if ( command == fCmd_Absorber_MoveZDir )    {
        
        fDetector    ->  fMoveAbsorber( G4ThreeVector(0.,0.,fCmd_Absorber_MoveZDir->GetNewDoubleValue(fInputValue)) );
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
