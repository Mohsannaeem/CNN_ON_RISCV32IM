#pragma once
#ifndef ACTIVATION_H_
#define ACTIVATION_H_

// INCLUDES
#include <stdint.h>
#include "newvariable.h"
#include "datachunk.h"
#include "orca_malloc.h"
#include "orca_printf.h"

// DEFINITIONS

// TYPEDEF
struct LayerActivationS{
	char  m_activation_type;
};

// FUNCTION PROTOTYPES
extern void LayerActivationS_init(struct LayerActivationS* self);
extern struct LayerActivationS* LayerActivationS_create();
extern void Activation_load_weights(struct LayerActivationS* self);
extern struct DataChunkFlatS* Activation_compute_output1D(struct LayerActivationS* self, struct  DataChunkFlatS* dc);
extern struct DataChunk2DS* Activation_compute_output3D(struct LayerActivationS* self, struct  DataChunk2DS* dc);
extern unsigned int Activation_get_input_rows(struct LayerActivationS* self);
extern unsigned int Activation_get_input_cols(struct LayerActivationS* self);
extern unsigned int Activation_get_output_units(struct LayerActivationS* self);
extern void LayerActivationS_reset(struct LayerActivationS* self);
extern void LayerActivationS_destroy(struct LayerActivationS* self);

#endif
