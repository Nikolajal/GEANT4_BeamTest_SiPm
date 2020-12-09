/// \file   PrimaryGeneratorAction.cc
/// \brief  Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction    ()
    :   G4VUserPrimaryGeneratorAction(),
        fParticleGun(nullptr),
        fParticleSource(nullptr)
{
    fParticleSource = new G4GeneralParticleSource();
    
    // default particle kinematic
    //
    auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("proton");
    fParticleSource->SetParticleDefinition(particleDefinition);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction   ()  {
    
    delete fParticleSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void    PrimaryGeneratorAction::GeneratePrimaries   ( G4Event* fCurrent_Event )
{
    // Check the World Volume is there and set the source
    G4double worldZHalfLength = 0.;
    auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("WorldLogical");
    
    // Check that the world volume has box shape
    G4Box* worldBox = nullptr;
    if (  worldLV ) {
    
        worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
    }

    if ( worldBox ) {
    
        worldZHalfLength = worldBox->GetZHalfLength();
    }
    else  {
    
        G4ExceptionDescription msg;
        msg << "The World Volume does not have a box shape: cannot place it in standard position" << G4endl;
        msg << "The gun will be place in the center.";
        G4Exception("B4PrimaryGeneratorAction::GeneratePrimaries()","W_world_no_box", JustWarning, msg);
    }
    
    // Set gun position
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -worldZHalfLength));
    fParticleGun->GeneratePrimaryVertex(fCurrent_Event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

