/// \file ActionInitialization.hh
/// \brief Definition of the ActionInitialization class

#ifndef B4cActionInitialization_h
#define B4cActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
    
public:
    
    // Constructors and destructors
                    ActionInitialization    ();
    virtual         ~ActionInitialization   ();

    // Methods
    virtual void    BuildForMaster          () const;
    virtual void    Build                   () const;
    
};

#endif

    
