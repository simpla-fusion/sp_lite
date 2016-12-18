//
// Created by salmon on 16-6-11.
//

#ifndef SIMPLA_BORISYEE_H
#define SIMPLA_BORISYEE_H

#include "sp_lite_config.h"
#include "spParticle.h"


typedef struct boris_particle_s
{
    SP_PARTICLE_HEAD
    SP_PARTICLE_ATTR(vx)
    SP_PARTICLE_ATTR(vy)
    SP_PARTICLE_ATTR(vz)
    SP_PARTICLE_ATTR(f)
    SP_PARTICLE_ATTR(w)

} boris_particle;

struct spMesh_s;
struct spField_s;

int spParticleCreateBorisYee(spParticle **sp, struct spMesh_s const *m);

int spParticleDestroyBorisYee(spParticle **sp);

int spParticleInitializeBorisYee(spParticle *sp, Real n0, Real T0);

int spParticleUpdateBorisYee(spParticle *sp,
                             Real dt,
                             const struct spField_s *fE,
                             const struct spField_s *fB,
                             struct spField_s *fRho,
                             struct spField_s *fJ);



#endif //SIMPLA_BORISYEE_H
