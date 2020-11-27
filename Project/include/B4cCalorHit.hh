#ifndef B4cCalorHit_h
#define B4cCalorHit_h

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"
#include "G4StepPoint.hh"

class B4cCalorHit : public G4VHit
{
  public:
                        B4cCalorHit         ();
                        B4cCalorHit         (const B4cCalorHit&);
    virtual             ~B4cCalorHit        ();

    const B4cCalorHit&  operator    =       (const B4cCalorHit&);
    G4int               operator    ==      (const B4cCalorHit&) const;

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

extern G4ThreadLocal G4Allocator<B4cCalorHit>* B4cCalorHitAllocator;

inline void*            B4cCalorHit::operator new(size_t)
{
    if (!B4cCalorHitAllocator)
    {
        B4cCalorHitAllocator = new G4Allocator<B4cCalorHit>;
    }
    void *hit;
    hit = (void *) B4cCalorHitAllocator->MallocSingle();
    return hit;
}

inline void             B4cCalorHit::operator delete(void *hit)
{
    if (!B4cCalorHitAllocator)
    {
        B4cCalorHitAllocator = new G4Allocator<B4cCalorHit>;
    }
    B4cCalorHitAllocator->FreeSingle((B4cCalorHit*) hit);
}

inline void             B4cCalorHit::Add(G4double de, G4double dl, G4StepPoint* p)
{
    fEdep += de;
    fTrackLength += dl;
    fPoint_dE_Vector += (p->GetPosition())*de;
}

inline G4double         B4cCalorHit::GetEdep() const
{
    return fEdep;
}

inline G4ThreeVector   B4cCalorHit::GetPoint_dE_Vector() const
{
    return fPoint_dE_Vector*(1/fEdep);
}

inline G4double         B4cCalorHit::GetTrackLength() const
{
    return fTrackLength;
}

#endif
