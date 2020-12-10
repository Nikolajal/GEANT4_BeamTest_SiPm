#include "DetectorMessenger.hh"

#include "SiPMDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
DetectorMessenger::DetectorMessenger    ( SiPMDetectorConstruction* Det )
    :Detector(Det)
{
    //  Project GUI Commands
    fDir_SiPMProject            = new G4UIdirectory("/SiPM/");
    fDir_SiPMProject            ->SetGuidance("UI commands of this Project");
    
    //  Detector GUI Configuration
    fDir_SiPMProject_Detector   = new G4UIdirectory("/SiPM/detector/");
    fDir_SiPMProject_Detector   ->SetGuidance("Detector Configuration");
    
    //  Absorber GUI Configuration
    fDir_SiPMProject_Absorber   = new G4UIdirectory("/SiPM/absorber/");
    fDir_SiPMProject_Absorber   ->SetGuidance("Absorber Configuration");
    
    // -- // Absorber Material
    fCmd_Absorber_Material      = new G4UIcmdWithAString("/SiPM/absorber/material",this);
    fCmd_Absorber_Material      ->SetGuidance("Select Material of the Absorber");
    fCmd_Absorber_Material      ->SetParameterName("choice",false);
    fCmd_Absorber_Material      ->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    // -- // Absorber X Position
    fCmd_Absorber_MoveXDir      = new G4UIcmdWithADoubleAndUnit("/SiPM/absorber/move_x",this);
    fCmd_Absorber_MoveXDir      ->SetGuidance("Move the absorber in X");
    fCmd_Absorber_MoveXDir      ->SetParameterName("Size",false);
    fCmd_Absorber_MoveXDir      ->SetUnitCategory("Length");
    fCmd_Absorber_MoveXDir      ->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    // -- // Absorber Y Position
    fCmd_Absorber_MoveYDir      = new G4UIcmdWithADoubleAndUnit("/SiPM/absorber/move_y",this);
    fCmd_Absorber_MoveYDir      ->SetGuidance("Move the absorber in Y");
    fCmd_Absorber_MoveYDir      ->SetParameterName("Size",false);
    fCmd_Absorber_MoveYDir      ->SetUnitCategory("Length");
    fCmd_Absorber_MoveYDir      ->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    // -- // Absorber Z Position
    fCmd_Absorber_MoveZDir      = new G4UIcmdWithADoubleAndUnit("/SiPM/absorber/move_z",this);
    fCmd_Absorber_MoveZDir      ->SetGuidance("Move the absorber in Z");
    fCmd_Absorber_MoveZDir      ->SetParameterName("Size",false);
    fCmd_Absorber_MoveZDir      ->SetUnitCategory("Length");
    fCmd_Absorber_MoveZDir      ->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
    // Delete Directories
    delete  fDir_SiPMProject;
    delete  fDir_SiPMProject_Detector;
    delete  fDir_SiPMProject_Absorber;
    
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
        
        Detector    ->  fSetAbsorberMat( fInputValue );
    }
    
    if ( command == fCmd_Absorber_MoveXDir )    {
        
        Detector    ->  fMoveAbsorber( G4ThreeVector(fCmd_Absorber_MoveXDir->GetNewDoubleValue(fInputValue),0.,0.) );
    }
    
    if ( command == fCmd_Absorber_MoveYDir )    {
        
        Detector    ->  fMoveAbsorber( G4ThreeVector(0.,fCmd_Absorber_MoveXDir->GetNewDoubleValue(fInputValue),0.) );
    }
    
    if ( command == fCmd_Absorber_MoveZDir )    {
        
        Detector    ->  fMoveAbsorber( G4ThreeVector(0.,0.,fCmd_Absorber_MoveXDir->GetNewDoubleValue(fInputValue)) );
    }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
