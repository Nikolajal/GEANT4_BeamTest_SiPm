// !TODO: check static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;

/// \file B4cDetectorConstruction.hh
/// \brief Definition of the B4cDetectorConstruction class

#ifndef SiPMDetectorConstruction_h
#define SiPMDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

class SiPMDetectorConstruction : public G4VUserDetectorConstruction  {

    // -- // Public methods & variables
public:
    
    // Constructors
                                    SiPMDetectorConstruction();

    // Destructors
    virtual                        ~SiPMDetectorConstruction();
    
    // Build the Physical and Logical Volume
    virtual G4VPhysicalVolume*      Construct();
    virtual void                    ConstructSDandField();
    
    // Setters for the GUI Command
    void                            fMoveAbsorber   ( G4ThreeVector fTranslation );
    void                            fSetAbsorberMat ( G4String fMaterialChoice );
    
    // -- // Private methods & variables
private:
    
    // Volumes Definition
    void                            DefineMaterials();
    
    // SiPM Cell Specifics
    void                            DefineSiPM();
    G4Material                     *fSiPMCellMaterial;
    G4double                        fSiPMCellHeight,    fSiPMCellDepth,     fSiPMCellWidth,    fSiPMCellGridSpacingX,  fSiPMCellGridSpacingY;
    G4int                           fSiPMCellGridNumberX,   fSiPMCellGridNumberY;
    
    // Substrate Specifics
    void                            DefineSubstrate();
    G4Material                     *fSubstrateMaterial;
    G4double                        fSubstrateHeight,   fSubstrateDepth,    fSubstrateWidth;
    
    // Absorber Specifics
    void                            DefineAbsorber();
    G4Material                     *fAbsorberMaterial;
    G4double                        fAbsorberHeight,   fAbsorberDepth,    fAbsorberWidth;
    G4ThreeVector                   fAbsorberPosition;
    
    // World Specifics
    void                            DefineWorld();
    G4Material                     *fWorldMaterial;
    G4double                        fWorldHeight,   fWorldDepth,    fWorldWidth;
    
    // Volumes Building
    G4VPhysicalVolume*              BuildWorld();
    void                            BuildSiPM ( G4LogicalVolume *fWorldLogical );
    void                            BuildSubstrate ( G4LogicalVolume *fWorldLogical );
    void                            BuildAbsorber ( G4LogicalVolume *fWorldLogical );
    
    // Utility
    G4bool                          fCheckOverlaps; // option to activate checking of volumes overlaps
    
    // !TODO: Check usefulness
    // -- // Example legacy (TBD if useful)
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
};

#endif

