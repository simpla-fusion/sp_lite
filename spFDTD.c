//
// Created by salmon on 16-12-18.
//
#include <sp_lite/spConfig.h>
#include "spFDTD.h"

struct spField_s {};
struct spMesh_s {};

int spFDTDInitialValueSin(spField *f, Real const *k, Real const *amp) { return SP_DO_NOTHING; }

int spFDTDUpdate(Real dt,
                 const struct spField_s *fRho,
                 const struct spField_s *fJ,
                 struct spField_s *fE,
                 struct spField_s *fB) { return SP_DO_NOTHING; }

int spFDTDDiv(const spField *fJ, spField *fRho) { return SP_DO_NOTHING; }

int spFDTDMultiplyByScalar(spField *fRho, Real a) { return SP_DO_NOTHING; }