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
    
    /*
    AbsMaterCmd = new G4UIcmdWithAString("/N03/det/setAbsMat",this);
    AbsMaterCmd->SetGuidance("Select Material of the Absorber.");
    AbsMaterCmd->SetParameterName("choice",false);
    AbsMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
      
    GapMaterCmd = new G4UIcmdWithAString("/N03/det/setGapMat",this);
    GapMaterCmd->SetGuidance("Select Material of the Gap.");
    GapMaterCmd->SetParameterName("choice",false);
    GapMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
        
      AbsThickCmd = new G4UIcmdWithADoubleAndUnit("/N03/det/setAbsThick",this);
      AbsThickCmd->SetGuidance("Set Thickness of the Absorber");
      AbsThickCmd->SetParameterName("Size",false);
      AbsThickCmd->SetRange("Size>=0.");
      AbsThickCmd->SetUnitCategory("Length");
      AbsThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
      
      GapThickCmd = new G4UIcmdWithADoubleAndUnit("/N03/det/setGapThick",this);
      GapThickCmd->SetGuidance("Set Thickness of the Gap");
      GapThickCmd->SetParameterName("Size",false);
      GapThickCmd->SetRange("Size>=0.");
      GapThickCmd->SetUnitCategory("Length");
      GapThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
      
      SizeYZCmd = new G4UIcmdWithADoubleAndUnit("/N03/det/setSizeYZ",this);
      SizeYZCmd->SetGuidance("Set tranverse size of the calorimeter");
      SizeYZCmd->SetParameterName("Size",false);
      SizeYZCmd->SetRange("Size>0.");
      SizeYZCmd->SetUnitCategory("Length");
      SizeYZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
      
      NbLayersCmd = new G4UIcmdWithAnInteger("/N03/det/setNbOfLayers",this);
      NbLayersCmd->SetGuidance("Set number of layers.");
      NbLayersCmd->SetParameterName("NbLayers",false);
      NbLayersCmd->SetRange("NbLayers>0 && NbLayers<500");
      NbLayersCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

      UpdateCmd = new G4UIcmdWithoutParameter("/N03/det/update",this);
      UpdateCmd->SetGuidance("Update calorimeter geometry.");
      UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
      UpdateCmd->SetGuidance("if you changed geometrical value(s).");
      UpdateCmd->AvailableForStates(G4State_Idle);
          
      MagFieldCmd = new G4UIcmdWithADoubleAndUnit("/N03/det/setField",this);
      MagFieldCmd->SetGuidance("Define magnetic field.");
      MagFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
      MagFieldCmd->SetParameterName("Bz",false);
      MagFieldCmd->SetUnitCategory("Magnetic flux density");
      MagFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
     */
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
    
    
    /*
  if( command == AbsMaterCmd )
   { Detector->SetAbsorberMaterial(newValue);}
   
  if( command == GapMaterCmd )
   { Detector->SetGapMaterial(newValue);}
  
  if( command == AbsThickCmd )
   { Detector->SetAbsorberThickness(AbsThickCmd
                                               ->GetNewDoubleValue(newValue));}
   
  if( command == GapThickCmd )
   { Detector->SetGapThickness(GapThickCmd->GetNewDoubleValue(newValue));}
   
  if( command == SizeYZCmd )
   { Detector->SetCalorSizeYZ(SizeYZCmd->GetNewDoubleValue(newValue));}
   
  if( command == NbLayersCmd )
   { Detector->SetNbOfLayers(NbLayersCmd->GetNewIntValue(newValue));}
  
  if( command == UpdateCmd )
   { Detector->UpdateGeometry(); }

  if( command == MagFieldCmd )
   { Detector->SetMagField(MagFieldCmd->GetNewDoubleValue(newValue));}
     
     */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
