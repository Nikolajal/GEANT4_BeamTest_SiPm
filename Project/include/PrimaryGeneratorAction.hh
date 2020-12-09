/// \file   PrimaryGeneratorAction.hh
/// \brief  Definition of the PrimaryGeneratorAction class

#ifndef B4PrimaryGeneratorAction_h
#define B4PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4ParticleGun;
class G4ParticleSource;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

public:
                                PrimaryGeneratorAction          ();
    virtual                     ~PrimaryGeneratorAction         ();
    virtual void                GeneratePrimaries               (G4Event* fCurrent_Event);
    
    // set methods
    void                        SetRandomFlag                   (G4bool value);

private:
    G4ParticleGun*              fParticleGun; // G4 particle gun
    G4GeneralParticleSource*    fParticleSource; // G4 particle source
};

#endif
