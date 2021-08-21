#pragma once
#ifndef DENSE_H_
#define DENSE_H_

// INCLUDES
#include <stdint.h>
#include "newvariable.h"
#include "datachunk.h"
#include "conv.h"
#include "orca_malloc.h"
#include "orca_printf.h"

// DEFINITIONS

// TYPEDEF
struct LayerDenseS {
	int16_t* m_weights; //input, neuron
	int16_t* m_bias;
	int m_row;
	int m_col;
	int m_input_cnt;
	int m_neurons;
};

// FUNCTION PROTOTYPES
void LayerDenseS_init(struct LayerDenseS* self);
struct LayerDenseS* LayerDenseS_create();
void Dense_load_weights(struct LayerDenseS* self);
struct DataChunkFlatS* Dense_compute_output(struct LayerDenseS* self, struct DataChunkFlatS* dc);
unsigned int Dense_get_input_rows(struct LayerDenseS* self);
unsigned int Dense_get_input_cols(struct LayerDenseS* self);
unsigned int Dense_get_output_units(struct LayerDenseS* self);
void LayerDenseS_reset(struct LayerDenseS* self);
void LayerDenseS_destroy(struct LayerDenseS* self);

#endif
