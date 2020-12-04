#ifndef SiPMHit_hh
#define SiPMHit_hh

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"
#include "G4StepPoint.hh"

class SiPMHit : public G4VHit
{
  public:
    SiPMHit         ();
    SiPMHit         (const B4cCalorHit&);
    virtual             ~SiPMHit        ();

    const SiPMHit&  operator    =       (const SiPMHit&);
    G4int               operator    ==      (const SiPMHit&) const;

    inline void*        operator    new     (size_t);
    inline void         operator    delete  (void*);

    virtual void        Draw                () {}
    virtual void        Print               () {}
    
    void                Add                 (G4double de, G4double dl, G4StepPoint* p);
    
    G4double            GetEdep             () const;
    G4double            GetTrackLength      () const;
    G4ThreeVector       GetPoint_dE_Vector  () const;
      
  private:
    G4double            fEdep;              ///< Energy deposit in the sensitive volume
    G4double            fTrackLength;       ///< Track length in the sensitive volume
    G4ThreeVector       fPoint_dE_Vector;   ///< Point in the sensitive volume
};

using B4cCalorHitsCollection = G4THitsCollection<B4cCalorHit>;

extern G4ThreadLocal G4Allocator<SiPMHit>* SiPMHitAllocator;

inline void*            SiPMHit::operator new(size_t)
{
    if (!B4cCalorHitAllocator)
    {
        B4cCalorHitAllocator = new G4Allocator<B4cCalorHit>;
    }
    void *hit;
    hit = (void *) B4cCalorHitAllocator->MallocSingle();
    return hit;
}

inline void             SiPMHit::operator delete(void *hit)
{
    if (!B4cCalorHitAllocator)
    {
        B4cCalorHitAllocator = new G4Allocator<B4cCalorHit>;
    }
    B4cCalorHitAllocator->FreeSingle((B4cCalorHit*) hit);
}

inline void             SiPMHit::Add(G4double de, G4double dl, G4StepPoint* p)
{
    fEdep += de;
    fTrackLength += dl;
    fPoint_dE_Vector += (p->GetPosition())*de;
}

inline G4double         SiPMHit::GetEdep() const
{
    return fEdep;
}

inline G4ThreeVector   SiPMHit::GetPoint_dE_Vector() const
{
    return fPoint_dE_Vector*(1/fEdep);
}

inline G4double         SiPMHit::GetTrackLength() const
{
    return fTrackLength;
}

#endif
