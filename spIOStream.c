//
// Created by salmon on 16-12-18.
//

#include "spIOStream.h"

struct spIOStream_s {};


int spIOStreamCreate(spIOStream **os) { return SP_DO_NOTHING; }

int spIOStreamDestroy(spIOStream **os) { return SP_DO_NOTHING; }

int spIOStreamPWD(spIOStream *os, char *url) { return SP_DO_NOTHING; }

int spIOStreamOpen(spIOStream *os, const char *url) { return SP_DO_NOTHING; }

int spIOStreamClose(spIOStream *os) { return SP_DO_NOTHING; }

//int spIOStreamWrite(spIOStream *, const char *name, spDataSet const *, int tag);
//
//int spIOStreamRead(spIOStream *, const char *name, spDataSet const *, int tag);

struct spDataType_s {};

int spIOStreamWriteSimple(spIOStream *os,
                          const char *name,
                          int data_type_tag,
                          void *d,
                          int ndims,
                          size_type const *dims,
                          size_type const *start,
                          size_type const *stride,
                          size_type const *count,
                          size_type const *block,
                          size_type const *g_dims,
                          size_type const *g_start,
                          int flag) { return SP_DO_NOTHING; };