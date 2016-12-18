//
// Created by salmon on 16-12-18.
//

#include <sp_lite/spConfig.h>
#include "spAlogorithm.h"


int sort_by_key(size_type const *p0, size_type const *p1, size_type *s0) { return SP_DO_NOTHING; }

/**
 *   dest[n]=src[index[n]]
 *   0<=n<num
 * @param dest
 * @param src
 * @param num
 * @param index
 * @return
 */
int spMemoryCopyIndirect(Real *dest, Real const *src, size_type num, size_type const *index) { return SP_DO_NOTHING; }

int
spMemoryCopyInvIndirect(Real *dest, Real const *src, size_type num, size_type const *index) { return SP_DO_NOTHING; }


int spMemoryCopySubArray(void *dest, void const *src, int type_tag, size_type const *strides, size_type const *start,
                         size_type const *count) { return SP_DO_NOTHING; }

int spMemoryCopyInvSubArray(void *dest, void const *src, int type_tag, size_type const *strides, size_type const *start,
                            size_type const *count) { return SP_DO_NOTHING; }

/**
 * v[n]=min+n
 * 0<= n < num
 * @param index
 * @param num
 * @param min
 * @return
 */
int spFillSeq(void *v, int type_tag, size_type num, size_type min, size_type step) { return SP_DO_NOTHING; }

int spTransformMinus(size_type *v, size_type const *a, size_type const *b, size_type num) { return SP_DO_NOTHING; }

int spTransformAdd(size_type *v, size_type const *a, size_type const *b, size_type num) { return SP_DO_NOTHING; }

int spExclusiveScan(size_type const *b, size_type const *e, size_type *out) { return SP_DO_NOTHING; }

int spInclusiveScan(size_type const *b, size_type const *e, size_type *out) { return SP_DO_NOTHING; }


int spPackInt(size_type **dest, size_type *num, size_type const *src,
              size_type num_of_cell, size_type const *start, size_type const *count) { return SP_DO_NOTHING; }

