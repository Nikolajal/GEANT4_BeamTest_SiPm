// !TODO: check static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;

/// \file B4cDetectorConstruction.hh
/// \brief Definition of the B4cDetectorConstruction class

#ifndef B4cDetectorConstruction_h
#define B4cDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

class B4cDetectorConstruction : public G4VUserDetectorConstruction  {

    // -- // Public methods & variables
public:
    
    // Constructors
                                    B4cDetectorConstruction();
    
    // Destructors
    virtual                        ~B4cDetectorConstruction();
    
    // Build the Physical and Logical Volume
    virtual G4VPhysicalVolume*      Construct();
    virtual void                    ConstructSDandField();

    
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
    
    // World Specifics
    void                            DefineWorld();
    G4Material                     *fWorldMaterial;
    G4double                        fWorldHeight,   fWorldDepth,    fWorldWidth;
    
    // Volumes Building
    G4VPhysicalVolume*              BuildWorld();
    void                            BuildSiPM();
    
    // Utility
    G4bool                          fCheckOverlaps; // option to activate checking of volumes overlaps
    
    // !TODO: Check usefulness
    // -- // Example legacy (TBD if useful)
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
    G4int   fNofLayers;     // number of layers
};

#endif

