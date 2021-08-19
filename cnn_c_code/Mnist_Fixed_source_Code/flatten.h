#pragma once
#ifndef FLATTEN_H_
#define FLATTEN_H_


// INCLUDES
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "newvariable.h"
#include "datachunk.h"

// DEFINITIONS

// TYPEDEF
struct LayerFlattenS {
	int x;
};

// FUNCTION PROTOTYPES
void LayerFlattenS_init(struct LayerFlattenS* self);
struct LayerFlattenS* LayerFlattenS_create(void);
void Flatten_load_weights(struct LayerFlattenS* self);
struct DataChunkFlatS* Flatten_compute_output(struct LayerFlattenS* self, struct DataChunk2DS* dc);
unsigned int Flatten_get_input_rows(struct LayerFlattenS* self);
unsigned int Flatten_get_input_cols(struct LayerFlattenS* self);
unsigned int Flatten_get_output_units(struct LayerFlattenS* self);
void LayerFlattenS_reset(struct LayerFlattenS* self);
void LayerFlattenS_destroy(struct LayerFlattenS* self);

#endif