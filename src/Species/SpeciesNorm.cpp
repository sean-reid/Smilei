#include "SpeciesNorm.h"

#include <iostream>

#include "Particles.h"
#include "Interpolator.h"
#include "Projector.h"
#include "Pusher.h"

using namespace std;

// ---------------------------------------------------------------------------------------------------------------------
// Creator for SpeciesNorm
// ---------------------------------------------------------------------------------------------------------------------
SpeciesNorm::SpeciesNorm( Params& params, Patch* patch )
  : SpeciesV( params, patch )
{
    DEBUG("Species is being created as norm");
}


// ---------------------------------------------------------------------------------------------------------------------
// Destructor for SpeciesNorm
// ---------------------------------------------------------------------------------------------------------------------
SpeciesNorm::~SpeciesNorm()
{
    DEBUG("Species norm deleted ");
}
