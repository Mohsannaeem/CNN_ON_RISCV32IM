#pragma once
#ifndef POOLING_H_
#define POOLING_H_

// INCLUDES
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "newvariable.h"
#include "datachunk.h"
#include "vector.h"

// DEFINITIONS

// TYPEDEF
struct LayerMaxPoolingS {
	int m_pool_x;
	int m_pool_y;
};

// FUNCTION PROTOTYPES
void LayerMaxPoolingS_init(struct LayerMaxPoolingS* self, int m_pool_x, int m_pool_y);
struct LayerMaxPoolingS* LayerMaxPoolingS_create(void);
void MaxPooling_load_weights(struct LayerMaxPoolingS* self);
struct DataChunk2DS* MaxPooling_compute_output(struct LayerMaxPoolingS* self, struct DataChunk2DS* dc);
unsigned int MaxPooling_get_input_rows(struct LayerMaxPoolingS* self);
unsigned int MaxPooling_get_input_cols(struct LayerMaxPoolingS* self);
unsigned int MaxPooling_get_output_units(struct LayerMaxPoolingS* self);
void LayerMaxPoolingS_reset(struct LayerMaxPoolingS* self);
void LayerMaxPoolingS_destroy(struct  LayerMaxPoolingS* self);

#endif