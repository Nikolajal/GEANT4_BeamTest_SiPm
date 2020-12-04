// !TODO: All set!

/// \file B4cDetectorConstruction.cc
/// \brief Implementation of the B4cDetectorConstruction class

#include "B4cDetectorConstruction.hh"
#include "B4cCalorimeterSD.hh"
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
G4GlobalMagFieldMessenger* B4cDetectorConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorConstruction::B4cDetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4cDetectorConstruction::~B4cDetectorConstruction() {
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4cDetectorConstruction::Construct() {
    
    // Define Materials & Specifics
    DefineMaterials();
    DefineSiPM();
    DefineSubstrate();
    DefineWorld();

    // Define volumes
    return BuildWorld();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::DefineMaterials()
{ 
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_AIR");
    nistManager->FindOrBuildMaterial("G4_Fe");
    nistManager->FindOrBuildMaterial("G4_Si");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::DefineSubstrate() {
    
    // Substrate Definition
    fSubstrateMaterial          =   G4Material::GetMaterial("G4_Si");
    fSubstrateHeight            =   1000.*mm;
    fSubstrateWidth             =   1000.*mm;
    fSubstrateDepth             =   10.*mm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::DefineSiPM() {
    
    // SiPM Cell
    fSiPMCellMaterial           =   G4Material::GetMaterial("G4_Si");
    fSiPMCellHeight             =   10.*mm;
    fSiPMCellWidth              =   10.*mm;
    fSiPMCellDepth              =   10.*mm;
    fSiPMCellGridSpacingX       =   5.*mm;
    fSiPMCellGridSpacingY       =   5.*mm;
    fSiPMCellGridNumberX        =   10;
    fSiPMCellGridNumberY        =   10;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::DefineWorld() {
    
    // SiPM Cell
    fWorldMaterial           =   G4Material::GetMaterial("G4_AIR");
    fWorldWidth              =   10.*m; //X
    fWorldHeight             =   2.*m;  //Y
    fWorldDepth              =   2.*m;  //Z
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::BuildSiPM( G4LogicalVolume *fWorldLogical ) {
    
    auto fSiPMCellSolid     =   new G4Box("SiPMCellSolid",
                                          fSiPMCellWidth/2,
                                          fSiPMCellHeight/2,
                                          fSiPMCellDepth/2);
    
    auto fSiPMCellLogical   =   new G4LogicalVolume(fSiPMCellSolid,
                                                    fSiPMCellMaterial,
                                                    "SiPMCellLogical");
    
    auto fSiPMCellAssembly  =   new G4AssemblyVolume();
    G4RotationMatrix fRotationNull (0,0,0);
    G4ThreeVector fTranslationX (0,0,0);
    G4ThreeVector fTranslationY (0,0,0);
    
    for ( int iRow = 0; iRow < fSiPMCellGridNumberY; ++iRow )   {
        
        fTranslationY.setY(0-(fSiPMCellHeight+fSiPMCellGridSpacingY));
        G4Transform3D f3DTransform ( fRotationNull, fTranslationY );
        fSiPMCellAssembly->AddPlacedVolume( fSiPMCellLogical, f3DTransform );
    }
    for ( int iClm = 0; iClm < fSiPMCellGridNumberX; ++iClm )   {
        
        fTranslationX.setX(0+(fSiPMCellWidth+fSiPMCellGridSpacingX));
        G4Transform3D f3DTransform ( fRotationNull, fTranslationX );
        fSiPMCellAssembly->MakeImprint( fWorldLogical, f3DTransform );
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4cDetectorConstruction::BuildSubstrate( G4LogicalVolume *fWorldLogical ) {
    
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

G4VPhysicalVolume* B4cDetectorConstruction::BuildWorld()
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
    
    /*
  //                               
  // Calorimeter
  //  
  auto calorimeterS
    = new G4Box("Calorimeter",     // its name
                calorSizeXY/2,
                calorSizeXY/2,
                calorThickness/2); // its size
                         
  auto calorLV
    = new G4LogicalVolume(
                 calorimeterS,     // its solid
                 defaultMaterial,  // its material
                 "Calorimeter");   // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 calorLV,          // its logical volume                         
                 "Calorimeter",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
   
  //                                 
  // Layer
  //
  auto layerS 
    = new G4Box("Layer",           // its name
                calorSizeXY/2,
                calorSizeXY/2,
                layerThickness/2); //its size
                         
  auto layerLV
    = new G4LogicalVolume(
                 layerS,           // its solid
                 defaultMaterial,  // its material
                 "Layer");         // its name

  new G4PVReplica(
                 "Layer",          // its name
                 layerLV,          // its logical volume
                 calorLV,          // its mother
                 kZAxis,           // axis of replication
                 fNofLayers,        // number of replica
                 layerThickness);  // witdth of replica
  
  //                               
  // Absorber
  //
  auto absorberS 
    = new G4Box("Abso",            // its name
                calorSizeXY/2,
                calorSizeXY/2,
                absoThickness/2); // its size
                         
  auto absorberLV
    = new G4LogicalVolume(
                 absorberS,        // its solid
                 absorberMaterial, // its material
                 "AbsoLV");        // its name
                                   
   new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., -gapThickness/2), // its position
                 absorberLV,       // its logical volume                         
                 "Abso",           // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 

  //                               
  // Gap
  //
  auto gapS 
    = new G4Box("Gap",             // its name
                 calorSizeXY/2, calorSizeXY/2, gapThickness/2); // its size
                         
  auto gapLV
    = new G4LogicalVolume(
                 gapS,             // its solid
                 gapMaterial,      // its material
                 "GapLV");         // its name
                                   
  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0., 0., absoThickness/2), // its position
                 gapLV,            // its logical volume                         
                 "Gap",            // its name
                 layerLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
 */
  return fWorldPlacement;
}

void B4cDetectorConstruction::ConstructSDandField()
{
    auto absoSD = new B4cCalorimeterSD("AbsorberSD", "AbsorberHitsCollection", fNofLayers);
    G4SDManager::GetSDMpointer()->AddNewDetector(absoSD);
    SetSensitiveDetector("WorldLogical",absoSD);

    auto gapSD = new B4cCalorimeterSD("GapSD", "GapHitsCollection", fNofLayers);
    G4SDManager::GetSDMpointer()->AddNewDetector(gapSD);
    SetSensitiveDetector("SiPMCellLogical",gapSD);

    G4ThreeVector fieldValue;
    fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
    fMagFieldMessenger->SetVerboseLevel(1);

    G4AutoDelete::Register(fMagFieldMessenger);
}
