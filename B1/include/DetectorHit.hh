#ifndef DetectorHit_hh
#define DetectorHit_hh

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"
#include "G4StepPoint.hh"

class DetectorHit : public G4VHit
{
  public:
                                DetectorHit         ();
                                DetectorHit         (const DetectorHit&);
    virtual                    ~DetectorHit         ();

    const DetectorHit&          operator    =       (const DetectorHit&);
    G4int                       operator    ==      (const DetectorHit&) const;

    inline void*                operator    new     (size_t);
    inline void                 operator    delete  (void*);

    virtual void                Draw                () {}
    virtual void                Print               () {}
    
    void                        Add                 ( G4double, G4ThreeVector );
    
    G4double                    GetEdep             () const    { return fEnergyDeposit;    };
    G4double                    GetESQR             () const    { return fEnergyDepoSQR;    };
    G4ThreeVector               GetEPos             () const    { return fEDepPosition;     };
    G4int                       GetEntr             () const    { return fEntries;          };
      
  private:
    G4double                    fEnergyDeposit;     // Energy deposit in the sensitive volume
    G4double                    fEnergyDepoSQR;     // Energy deposit in the sensitive volume
    G4ThreeVector               fEDepPosition;      // Point in the sensitive volume
    G4int                       fEntries;           // Entries   
};

using                                       DetectorHitsCollection  = G4THitsCollection<DetectorHit>;
extern G4ThreadLocal G4Allocator<DetectorHit>*  DetectorHitAllocator;

inline void*            DetectorHit::operator new( size_t )   {
    if (!DetectorHitAllocator)
    {
        DetectorHitAllocator = new G4Allocator<DetectorHit>;
    }
    void *hit;
    hit = (void *) DetectorHitAllocator->MallocSingle();
    return hit;
}

inline void             DetectorHit::operator delete(void *hit) {
    if (!DetectorHitAllocator)
    {
        DetectorHitAllocator = new G4Allocator<DetectorHit>;
    }
    DetectorHitAllocator->FreeSingle((DetectorHit*) hit);
}

#endif
