/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4GlobalMagFieldMessenger;
class DetectorMessenger;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction  {

    // -- // Public methods & variables
public:
    
    // Constructors
                                    DetectorConstruction    ();

    // Destructors
    virtual                        ~DetectorConstruction    ();
    
    // Build the Physical and Logical Volume
    virtual G4VPhysicalVolume*      Construct               ();
    virtual void                    ConstructSDandField     ();
    
    // Setters for the GUI Command
    void                            fMoveAbsorber           ( G4ThreeVector fTranslation    );
    void                            fSetAbsorberMat         ( G4String      fMaterialChoice );
    G4LogicalVolume*                GetSiPMLogicalVolume    ( G4int iClm, G4int iRow ) const;
    
    // -- // Private methods & variables
private:
    
    // Volumes Definition
    void                            DefineMaterials();
    
    // SiPM Cell Specifics
    void                            DefineSiPM();
    G4LogicalVolume              ***fSiPMCellLogical;
    G4Material                     *fSiPMCellMaterial;
    G4double                        fSiPMCellHeight,    fSiPMCellDepth,     fSiPMCellWidth,    fSiPMCellGridSpacingX,  fSiPMCellGridSpacingY;
    G4int                           fSiPMCellGridNumberX,   fSiPMCellGridNumberY;
    G4ThreeVector                   fSiPMPosition;
    
    // Substrate Specifics
    void                            DefineSubstrate();
    G4Material                     *fSubstrateMaterial;
    G4double                        fSubstrateHeight,   fSubstrateDepth,    fSubstrateWidth;
    G4ThreeVector                   fSubstratePosition;

    // Absorber Specifics
    void                            DefineAbsorber();
    G4Material                     *fAbsorberMaterial;
    G4double                        fAbsorberHeight,   fAbsorberDepth,    fAbsorberWidth;
    G4ThreeVector                   fAbsorberPosition;
    G4Box                          *fAbsorberSolid;
    G4LogicalVolume                *fAbsorberLogical;
    G4PVPlacement                  *fAbsorberPlacement;
    
    // World Specifics
    void                            DefineWorld();
    G4Material                     *fWorldMaterial;
    G4double                        fWorldHeight,   fWorldDepth,    fWorldWidth;
    G4LogicalVolume                *fWorldLogical;
    
    // Volumes Building
    G4VPhysicalVolume*              BuildWorld();
    void                            BuildSiPM ( G4LogicalVolume *fWorldLogical );
    void                            BuildSubstrate ( G4LogicalVolume *fWorldLogical );
    void                            BuildAbsorber ( G4LogicalVolume *fWorldLogical );
    
    // Utility
    G4bool                          fCheckOverlaps; // option to activate checking of volumes overlaps
    DetectorMessenger              *fDetMessenger;  // Detector messenger
    
    // !TODO: Check usefulness
    // -- // Example legacy (TBD if useful)
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
};

#endif