/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "SensitiveDetector.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4AssemblyVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"


G4ThreadLocal 
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true) {
  fDetMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction() {
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct() {
    
    // Define Materials & Specifics
    DefineMaterials();
    DefineSiPM();
    DefineSubstrate();
    DefineAbsorber();
    DefineWorld();

    // Define volumes
    return BuildWorld();
}

void DetectorConstruction::ConstructSDandField()
{
  SensitiveDetector ***fSensitive_SiPM = new SensitiveDetector **[fSiPMCellGridNumberX];
    
  char* fName = new char[256];
  char* fNam2 = new char[256];
    
  for ( int iClm = 0; iClm < fSiPMCellGridNumberX; ++iClm )   {
    
    fSensitive_SiPM[iClm]  = new SensitiveDetector  *[fSiPMCellGridNumberY];

    for ( int iRow = 0; iRow < fSiPMCellGridNumberY; ++iRow )   {
          
    std::sprintf(fName,"Sensitive_SiPM_%i_%i",iClm,iRow);
    std::sprintf(fNam2,"SiPMHitsCollection_%i_%i",iClm,iRow);
    fSensitive_SiPM[iClm][iRow]   =   new SensitiveDetector ( fName, fNam2, 1);
    G4SDManager::GetSDMpointer()->AddNewDetector(fSensitive_SiPM[iClm][iRow]);
    
    std::sprintf(fName,"SiPMCellLogical_%i_%i",iClm,iRow);
    SetSensitiveDetector( fName, fSensitive_SiPM[iClm][iRow]);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_Galactic");
    nistManager->FindOrBuildMaterial("G4_Fe");
    nistManager->FindOrBuildMaterial("G4_Al");
    nistManager->FindOrBuildMaterial("G4_Si");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineSiPM() {
    
    // SiPM Cell
    fSiPMCellMaterial           =   G4Material::GetMaterial("G4_Si");
    fSiPMCellWidth              =   3.*mm;
    fSiPMCellHeight             =   3.*mm;
    fSiPMCellDepth              =   2.*mm;
    fSiPMCellGridSpacingX       =   0.3*mm;
    fSiPMCellGridSpacingY       =   0.3*mm;
    fSiPMCellGridNumberX        =   8;
    fSiPMCellGridNumberY        =   4;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineAbsorber() {
    
    // Substrate Definition
    fAbsorberMaterial           =   G4Material::GetMaterial("G4_Al");
    fAbsorberWidth              =   20*cm;
    fAbsorberHeight             =   20*cm;
    fAbsorberDepth              =   4*cm;
    auto fXDisplace             =   -10.3*cm;
    auto fYDisplace             =   -10.*cm;
    auto fZDisplace             =   - fWorldDepth/2. + fSubstrateDepth + fSiPMCellDepth/2. + 1.*cm + 0.5*fAbsorberDepth;
    fAbsorberPosition           =   G4ThreeVector (fXDisplace,fYDisplace,fZDisplace);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineSubstrate() {
    
    // Substrate Definition
    fSubstrateMaterial          =   G4Material::GetMaterial("G4_Si");
    fSubstrateWidth             =   4.5*cm;
    fSubstrateHeight            =   3.5*cm;
    fSubstrateDepth             =   fSiPMCellDepth;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineWorld() {
    
    // SiPM Cell
    fWorldMaterial           =   G4Material::GetMaterial("G4_Galactic");
    fWorldWidth              =   1.*m; //X
    fWorldHeight             =   1.*m;  //Y
    fWorldDepth              =   4.*m;  //Z
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::BuildSiPM( G4LogicalVolume *fWorldLogical ) {
    
  G4Box            ***fSiPMCellSolid      =   new G4Box           **[fSiPMCellGridNumberX];
    
  fSiPMCellLogical    =   new G4LogicalVolume **[fSiPMCellGridNumberX];
    
  auto fSiPMCellAssembly  =   new G4AssemblyVolume();
  G4RotationMatrix    fRotationNull   (0,0,0);
    
  char* fName = new char[256];
    
  for ( int iClm = 0; iClm < fSiPMCellGridNumberX; ++iClm )   {

    fSiPMCellSolid[iClm]    = new G4Box            *[fSiPMCellGridNumberY];
    fSiPMCellLogical[iClm]  = new G4LogicalVolume  *[fSiPMCellGridNumberY];

    for ( int iRow = 0; iRow < fSiPMCellGridNumberY; ++iRow )   {

    std::sprintf(fName,"SiPMCellSolid_%i_%i",iClm,iRow);
    fSiPMCellSolid[iClm][iRow]      =   new G4Box(fName,
                                                  fSiPMCellWidth/2,
                                                  fSiPMCellHeight/2,
                                                  fSiPMCellDepth/2);
    
    std::sprintf(fName,"SiPMCellLogical_%i_%i",iClm,iRow);
    fSiPMCellLogical[iClm][iRow]    =   new G4LogicalVolume(fSiPMCellSolid[iClm][iRow],
                                                            fSiPMCellMaterial,
                                                            fName);

    auto fXDisplace = -0.5*(fSiPMCellGridNumberX-2*iClm)*(fSiPMCellGridSpacingX+fSiPMCellWidth);
    auto fYDisplace = -0.5*(fSiPMCellGridNumberY-2*iRow)*(fSiPMCellGridSpacingY+fSiPMCellHeight);
    auto fZDisplace = -fWorldDepth/2.+fSubstrateDepth+fSiPMCellDepth/2.;
    fSiPMPosition = G4ThreeVector(fXDisplace,fYDisplace,fZDisplace);

    std::sprintf(fName,"SiPMCellPlacement_%i_%i",iClm,iRow);
    auto fSiPMPlacement =   new G4PVPlacement(0,                // no rotation
                                                  fSiPMPosition,  // at (0,0,0)
                                                  fSiPMCellLogical[iClm][iRow], // its logical volume
                                                  fName, // its name
                                                  fWorldLogical,    // its mother  volume
                                                  false,            // no boolean operation
                                                  0,                // copy number
                                                  fCheckOverlaps);  // checking overlaps
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::BuildAbsorber( G4LogicalVolume *fWorldLogical ) {
    
    fAbsorberSolid     =   new G4Box("AbsorberSolid",
                                          fAbsorberWidth/2,
                                          fAbsorberHeight/2,
                                          fAbsorberDepth/2);
    
    fAbsorberLogical   =   new G4LogicalVolume(fAbsorberSolid,
                                                    fAbsorberMaterial,
                                                    "AbsorberLogical");

    fAbsorberPlacement =   new G4PVPlacement(0,                // no rotation
                                                  fAbsorberPosition,  // at (0,0,0)
                                                  fAbsorberLogical, // its logical volume
                                                  "fAbsorberPlacement", // its name
                                                  fWorldLogical,    // its mother  volume
                                                  false,            // no boolean operation
                                                  0,                // copy number
                                                  fCheckOverlaps);  // checking overlaps
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::BuildSubstrate( G4LogicalVolume *fWorldLogical ) {
    
    auto fSubstrateSolid    =   new G4Box("SubstrateSolid",
                                          fSubstrateWidth/2,
                                          fSubstrateHeight/2,
                                          fSubstrateDepth/2);
    
    auto fSubstrateLogical  =   new G4LogicalVolume(fSubstrateSolid,
                                                    fSubstrateMaterial,
                                                    "SubstrateLogical");
    
    auto fWorldPlacement    =   new G4PVPlacement(0,                    // no rotation
                                                  G4ThreeVector(0,0,-fWorldDepth/2+fSubstrateDepth/2),      // at (0,0,0)
                                                  fSubstrateLogical,    // its logical volume
                                                  "SubstratePlacement", // its name
                                                  fWorldLogical,        // its mother  volume
                                                  false,                // no boolean operation
                                                  0,                    // copy number
                                                  fCheckOverlaps);      // checking overlaps
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::BuildWorld()
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
    
    fWorldLogical  =   new G4LogicalVolume(fWorldSolid,
                                                fWorldMaterial,
                                                "WorldLogical");
                                   
    auto fWorldPlacement=   new G4PVPlacement(0,                // no rotation
                                              G4ThreeVector(0.,0.,0.),  // at (0,0,0)
                                              fWorldLogical,    // its logical volume
                                              "WorldPlacement", // its name
                                              0,                // its mother  volume
                                              false,            // no boolean operation
                                              0,                // copy number
                                              fCheckOverlaps);  // checking overlaps
    
    BuildSiPM       ( fWorldLogical );
    BuildSubstrate  ( fWorldLogical );
    BuildAbsorber   ( fWorldLogical );
    
    return fWorldPlacement;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void    DetectorConstruction::fMoveAbsorber     ( G4ThreeVector fTranslation )  {
    if ( fTranslation == G4ThreeVector(0,0,0) ) return;
    fAbsorberPosition  +=   fTranslation;
    fAbsorberPlacement  ->  SetTranslation( fAbsorberPosition );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void    DetectorConstruction::fSetAbsorberMat   ( G4String fMaterialChoice )    {
    
    G4Material* fNewMaterial = G4Material::GetMaterial ( fMaterialChoice );
    if ( fNewMaterial ) {
        fAbsorberLogical->SetMaterial(fNewMaterial);
    }   else    {
        G4ExceptionDescription msg;
        msg << "The material passed is not available, the default will be used" << G4endl;
        G4Exception("DetectorConstruction::fSetAbsorberMat(G4String fMaterialChoice)","W_absorber_material", JustWarning, msg);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume*    DetectorConstruction::GetSiPMLogicalVolume   ( G4int iClm, G4int iRow )  const  {
    
    return fSiPMCellLogical[iClm][iRow];
    
}



/*

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 30*cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* PhysicalWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //     
  // Shape 1
  //  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4ThreeVector pos1 = G4ThreeVector(0, 2*cm, -7*cm);
        
  // Conical section shape       
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
  G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
  G4double shape1_hz = 3.*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Cons* solidShape1 =    
    new G4Cons("Shape1", 
    shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    shape1_phimin, shape1_phimax);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Shape 2
  //
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
  G4ThreeVector pos2 = G4ThreeVector(0, -1*cm, 7*cm);

  // Trapezoid shape       
  G4double shape2_dxa = 12*cm, shape2_dxb = 12*cm;
  G4double shape2_dya = 10*cm, shape2_dyb = 16*cm;
  G4double shape2_dz  = 6*cm;      
  G4Trd* solidShape2 =    
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb, 
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return PhysicalWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
 {
   // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  
   // 
   // Sensitive detectors
   //
   auto absoSD 
     = new B4cCalorimeterSD("AbsorberSD", "AbsorberHitsCollection", fNofLayers);
   G4SDManager::GetSDMpointer()->AddNewDetector(absoSD);
   SetSensitiveDetector("AbsoLV",absoSD);
  
   auto gapSD 
     = new B4cCalorimeterSD("GapSD", "GapHitsCollection", fNofLayers);
   G4SDManager::GetSDMpointer()->AddNewDetector(gapSD);
   SetSensitiveDetector("GapLV",gapSD);
  
   // 
   // Magnetic field
   //
   // Create global magnetic field messenger.
   // Uniform magnetic field is then created automatically if
   // the field value is not zero.
   G4ThreeVector fieldValue;
   fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
   fMagFieldMessenger->SetVerboseLevel(1);
   
   // Register the field messenger for deleting
   G4AutoDelete::Register(fMagFieldMessenger);
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
*/
