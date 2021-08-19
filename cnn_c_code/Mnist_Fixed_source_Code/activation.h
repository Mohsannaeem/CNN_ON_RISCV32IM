#pragma once
#ifndef ACTIVATION_H_
#define ACTIVATION_H_

// INCLUDES
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "newvariable.h"
#include "datachunk.h"

// DEFINITIONS

// TYPEDEF
struct LayerActivationS{
	char  m_activation_type;
};

// FUNCTION PROTOTYPES
void LayerActivationS_init(struct LayerActivationS* self);
struct LayerActivationS* LayerActivationS_create();
void Activation_load_weights(struct LayerActivationS* self);
struct DataChunkFlatS* Activation_compute_output1D(struct LayerActivationS* self, struct  DataChunkFlatS* dc);
struct DataChunk2DS* Activation_compute_output3D(struct LayerActivationS* self, struct  DataChunk2DS* dc);
unsigned int Activation_get_input_rows(struct LayerActivationS* self);
unsigned int Activation_get_input_cols(struct LayerActivationS* self);
unsigned int Activation_get_output_units(struct LayerActivationS* self);
void LayerActivationS_reset(struct LayerActivationS* self);
void LayerActivationS_destroy(struct LayerActivationS* self);

#endif