/*
 * spMesh.h
 *
 *  Created on: 2016年6月15日
 *      Author: salmon
 */

#ifndef SPMESH_H_
#define SPMESH_H_

#include "sp_lite_config.h"
#include "spObject.h"

enum
{
    VERTEX = 0, EDGE = 1, FACE = 2, VOLUME = 3
};
enum
{
    SP_DOMAIN_CENTER = 13, SP_DOMAIN_ALL = 0xFF, SP_DOMAIN_AFFECT_1 = SP_DOMAIN_ALL + 1
};
struct spMesh_s;

typedef struct spMesh_s spMesh;


#define SP_MESH_ATTR_HEAD  SP_OBJECT_HEAD const spMesh *m; uint iform;

typedef struct spMeshAttribute_s
{
    SP_MESH_ATTR_HEAD
    byte_type __others[];
} spMeshAttribute;


int spMeshAttributeCreate(spMeshAttribute **f, size_type size, spMesh const *mesh, uint iform);

int spMeshAttributeDestroy(spMeshAttribute **f);

spMesh const *spMeshAttributeGetMesh(spMeshAttribute const *f);

uint spMeshAttributeGetForm(spMeshAttribute const *f);

int spMeshCreate(spMesh **ctx);

int spMeshDestroy(spMesh **ctx);

int spMeshDeploy(spMesh *self);

int spMeshSetupParam(spMesh *sp);

struct spMPIUpdater_s;

typedef struct spMPIUpdater_s spMPIUpdater;

int spMeshGetMPIUpdater(const spMesh *m, spMPIUpdater **updater);


/** Topology Begin*/

int spMeshGetNDims(spMesh const *m);

Real spMeshCFLDtv(spMesh const *m, Real const *speed);

Real spMeshCFLDt(spMesh const *m, Real const speed);

int spMeshSetDims(spMesh *m, size_type const *);

int spMeshGetGlobalDims(spMesh const *m, size_type *);

int spMeshSetGhostWidth(spMesh *m, size_type const *);

int spMeshGetGhostWidth(spMesh const *m, size_type *);

int spMeshGetStrides(spMesh const *m, size_type *res);

size_type spMeshGetNumberOfEntities(spMesh const *, int domain_tag, int iform);

int spMeshGetDomain(spMesh const *m, int tag, size_type *p_start, size_type *p_end, size_type *p_count);

int spMeshGetDims(spMesh const *m, size_type *v);

//int spMeshGetArrayShape(spMesh const * m, int tag, size_type *min, size_type *max, size_type *stride);

int spMeshGetGlobalStart(spMesh const *m, size_type *start);

int spMeshGetGlobalOffset(spMesh const *m, size_type *dims, ptrdiff_t *offset);

int spMeshGetGlobalArrayShape(spMesh const *m,
                              int domain_tag,
                              int attr_ndims,
                              const size_type *attr_dims,
                              int *array_ndims,
                              int *start_mesh_dim,
                              size_type *g_dims,
                              size_type *g_start,
                              size_type *l_dims,
                              size_type *l_start,
                              size_type *l_count,
                              int is_soa);
/** Topology End*/

/** Geometry Begin*/
int spMeshSetBox(spMesh *m, Real const *lower, Real const *upper);

int spMeshGetBox(spMesh const *m, int tag, Real *lower, Real *upper);

int spMeshGetOrigin(spMesh const *m, Real *origin);

int spMeshGetDx(spMesh const *m, Real *);

int spMeshGetInvDx(spMesh const *m, Real *);

int spMeshGetGlobalOrigin(spMesh const *m, Real *origin);


/** Geometry End */

int spMeshWrite(spMesh const *ctx, const char *name);

int spMeshRead(spMesh *ctx, const char *name);


#endif /* SPMESH_H_ */
