//
// Created by salmon on 16-7-28.
//

#ifndef SIMPLA_FDTD_H
#define SIMPLA_FDTD_H

#include "spMacro.h"
#include "spPhysicalConstants.h"

struct spField_s;
struct spMesh_s;

typedef struct spField_s spField;

int spFDTDInitialValueSin(spField *, Real const *k, Real const *amp);

int spFDTDUpdate(Real dt,
                 const spField *fRho,
                 const spField *fJ,
                 spField *fE,
                 spField *fB);

int spFDTDDiv(const spField *fJ, spField *fRho);

int spFDTDMultiplyByScalar(spField *fRho, Real a);


#endif //SIMPLA_FDTD_H
