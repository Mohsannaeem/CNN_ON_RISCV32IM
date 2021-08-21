#pragma once
#ifndef DATACHUNK_H_
#define DATACHUNK_H_

// INCLUDES
#include <stdint.h>
#include "orca_malloc.h"
#include "orca_printf.h"
#include "newvariable.h"
#include "conv.h"
// DEFINITIONS

// TYPEDEF
struct DataChunk2DS {
	int16_t* y_ret_3D;
	int m_dept;
	int m_row;
	int m_col;
};

struct DataChunkFlatS
{
	int32_t m_size;
	int16_t* f;
};

// FUNCTION PROTOTYPES
void DataChunk2DS_init(struct DataChunk2DS* self);
struct DataChunk2DS* DataChunk2DS_create(void);
void DataChunk2DS_reset(struct DataChunk2DS* self);
void DataChunk2DS_destroy(struct DataChunk2DS* self);
int16_t* Chunk2D_get_3d1(struct DataChunk2DS* self);
void Chunk2D_set_data1(struct DataChunk2DS* self, int16_t* y_ret, int depth, int row, int col);
size_t Chunk2D_get_data_dim(void);
void chunk_showvalues(struct DataChunk2DS* self);
int Chun2D_read_from_file1Dep(struct DataChunk2DS* self);
void DataChunkFlatS_init(struct DataChunkFlatS* self, int size);
struct DataChunkFlatS* DataChunkFlatS_create(int size);
void DataChunkFlatS_reset(struct DataChunkFlatS* self);
void DataChunkFlatS_destroy(struct DataChunkFlatS* self);
int16_t* Flat_get_1d_rw(struct DataChunkFlatS* self);
void Flat_set_data1(struct DataChunkFlatS* dc, int16_t* d);
size_t Flat_get_data_dim(void);
void Flat_show_values(struct DataChunkFlatS* self);

#endif
