//
// Created by salmon on 16-9-13.
//

#ifndef SIMPLA_SPPARTICLE_IMPL_H
#define SIMPLA_SPPARTICLE_IMPL_H

#include "../spParticle.h"

int spParticleBucketInitialize_device(spParticle *sp);

int spParticleBucketBuild_device(spParticle *sp);

enum { SP_RAND_GEN_SOBOL };
enum { SP_RAND_UNIFORM = 0x1, SP_RAND_NORMAL = 0x10 };

/**
 *  \f[
 *      f\left(v\right)\equiv\frac{1}{\sqrt{\left(2\pi\sigma\right)^{3}}}\exp\left(-\frac{\left(v-u\right)^{2}}{\sigma^{2}}\right)
 *  \f]
 */

int spParticleInitialize_device(Real **data, int ndims, int const *dist_types, size_type num, size_type offset);

int spParticleBucketSync_device(spParticle *sp);


#endif //SIMPLA_SPPARTICLE_IMPL_H
