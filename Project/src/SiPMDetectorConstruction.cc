// !TODO: All set!

/// \file B4cDetectorConstruction.cc
/// \brief Implementation of the B4cDetectorConstruction class

#include "SiPMDetectorConstruction.hh"
#include "SiPMSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4AssemblyVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* SiPMDetectorConstruction::fMagFieldMessenger = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMDetectorConstruction::SiPMDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SiPMDetectorConstruction::~SiPMDetectorConstruction() {
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* SiPMDetectorConstruction::Construct() {
    
    // Define Materials & Specifics
    DefineMaterials();
    DefineSiPM();
    DefineSubstrate();
    DefineAbsorber();
    DefineWorld();

    // Define volumes
    return BuildWorld();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMDetectorConstruction::DefineMaterials()
{ 
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_Galactic");
    nistManager->FindOrBuildMaterial("G4_Fe");
    nistManager->FindOrBuildMaterial("G4_Si");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMDetectorConstruction::DefineSiPM() {
    
    // SiPM Cell
    fSiPMCellMaterial           =   G4Material::GetMaterial("G4_Si");
    fSiPMCellWidth              =   3.*mm;
    fSiPMCellHeight             =   3.*mm;
    fSiPMCellDepth              =   2.*mm;
    fSiPMCellGridSpacingX       =   0.*mm;
    fSiPMCellGridSpacingY       =   0.*mm;
    fSiPMCellGridNumberX        =   8;
    fSiPMCellGridNumberY        =   4;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMDetectorConstruction::DefineAbsorber() {
    
    // Substrate Definition
    fAbsorberPosition           =   G4ThreeVector (0,0,0);
    fSubstrateMaterial          =   G4Material::GetMaterial("G4_Si");
    fSubstrateWidth             =   4.5*cm;
    fSubstrateHeight            =   3.5*cm;
    fSubstrateDepth             =   fSiPMCellDepth;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMDetectorConstruction::DefineSubstrate() {
    
    // Substrate Definition
    fSubstrateMaterial          =   G4Material::GetMaterial("G4_Si");
    fSubstrateWidth             =   4.5*cm;
    fSubstrateHeight            =   3.5*cm;
    fSubstrateDepth             =   fSiPMCellDepth;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMDetectorConstruction::DefineWorld() {
    
    // SiPM Cell
    fWorldMaterial           =   G4Material::GetMaterial("G4_Galactic");
    fWorldWidth              =   fSubstrateWidth*3; //X
    fWorldHeight             =   fSubstrateHeight*3;  //Y
    fWorldDepth              =   2.*m;  //Z
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMDetectorConstruction::BuildSiPM( G4LogicalVolume *fWorldLogical ) {
    
    auto fSiPMCellSolid     =   new G4Box("SiPMCellSolid",
                                          fSiPMCellWidth/2,
                                          fSiPMCellHeight/2,
                                          fSiPMCellDepth/2);
    
    auto fSiPMCellLogical   =   new G4LogicalVolume(fSiPMCellSolid,
                                                    fSiPMCellMaterial,
                                                    "SiPMCellLogical");
    
    auto fSiPMCellAssembly  =   new G4AssemblyVolume();
    G4RotationMatrix    fRotationNull   (0,0,0);
    G4ThreeVector       fTranslationX   (0,0,fWorldDepth-fSubstrateDepth);
    G4ThreeVector       fTranslationY   (0,0,fWorldDepth-fSubstrateDepth);
    
    for ( int iRow = 0; iRow < fSiPMCellGridNumberY; ++iRow )   {
        
        G4Transform3D f3DTransform ( fRotationNull, fTranslationY );
        fSiPMCellAssembly->AddPlacedVolume( fSiPMCellLogical, f3DTransform );
        fTranslationY.setY(0-(fSiPMCellHeight+fSiPMCellGridSpacingY));
    }
    for ( int iClm = 0; iClm < fSiPMCellGridNumberX; ++iClm )   {
        
        fTranslationX.setX(0+(fSiPMCellWidth+fSiPMCellGridSpacingX));
        G4Transform3D f3DTransform ( fRotationNull, fTranslationX );
        fSiPMCellAssembly->MakeImprint( fWorldLogical, f3DTransform );
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SiPMDetectorConstruction::BuildSubstrate( G4LogicalVolume *fWorldLogical ) {
    
    auto fSubstrateSolid    =   new G4Box("SubstrateSolid",
                                          fSubstrateWidth/2,
                                          fSubstrateHeight/2,
                                          fSubstrateDepth/2);
    
    auto fSubstrateLogical  =   new G4LogicalVolume(fSubstrateSolid,
                                                    fSubstrateMaterial,
                                                    "SubstrateLogical");
    
    auto fWorldPlacement    =   new G4PVPlacement(0,                    // no rotation
                                                  G4ThreeVector(),      // at (0,0,0)
                                                  fSubstrateLogical,    // its logical volume
                                                  "SubstratePlacement", // its name
                                                  fWorldLogical,        // its mother  volume
                                                  false,                // no boolean operation
                                                  0,                    // copy number
                                                  fCheckOverlaps);      // checking overlaps
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* SiPMDetectorConstruction::BuildWorld()
{
    if ( !(fWorldMaterial&&fSiPMCellMaterial&&fSubstrateMaterial) ) {
        G4ExceptionDescription msg;
        msg << "Have you fetched all Materials in DefineMaterial()?";
        G4Exception("B4DetectorConstruction::DefineMaterials()","MyCode0001", FatalException, msg);
    }
   
    auto fWorldSolid    =   new G4Box("WorldSolid",
                                      fWorldWidth/2,    //X
                                      fWorldHeight/2,   //Y
                                      fWorldDepth/2);   //Z
    
    auto fWorldLogical  =   new G4LogicalVolume(fWorldSolid,
                                                fWorldMaterial,
                                                "WorldLogical");
                                   
    auto fWorldPlacement=   new G4PVPlacement(0,                // no rotation
                                              G4ThreeVector(),  // at (0,0,0)
                                              fWorldLogical,    // its logical volume
                                              "WorldPlacement", // its name
                                              0,                // its mother  volume
                                              false,            // no boolean operation
                                              0,                // copy number
                                              fCheckOverlaps);  // checking overlaps
    
    BuildSiPM       ( fWorldLogical );
    BuildSubstrate  ( fWorldLogical );
    //BuildAbsorber   ( fWorldLogical );
    
    return fWorldPlacement;
}

void SiPMDetectorConstruction::ConstructSDandField()
{
    auto fSensitive_SiPM = new SiPMSD ("Sensitive_SiPM", "SiPMHitsCollection", 1);
    G4SDManager::GetSDMpointer()->AddNewDetector(fSensitive_SiPM);
    SetSensitiveDetector("WorldLogical",fSensitive_SiPM);

    G4ThreeVector fieldValue;
    fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
    fMagFieldMessenger->SetVerboseLevel(1);

    G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void    SiPMDetectorConstruction::fMoveAbsorber     ( G4ThreeVector fTranslation )  {
    
    fAbsorberPosition  +=   fTranslation;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void    SiPMDetectorConstruction::fSetAbsorberMat   ( G4String fMaterialChoice )    {
    
    G4Material* fNewMaterial = G4Material::GetMaterial ( fMaterialChoice );
    if ( fNewMaterial ) {
        
        fAbsorberMaterial = fNewMaterial;
    }   else    {
        
        G4ExceptionDescription msg;
        msg << "The material passed is not available, the default will be used" << G4endl;
        G4Exception("SiPMDetectorConstruction::fSetAbsorberMat(G4String fMaterialChoice)","W_absorber_material", JustWarning, msg);
    }
}
