#pragma once
#ifndef CONVOLUTION_H_
#define CONVOLUTION_H_


// INCLUDES
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "conv.h"
#include "newvariable.h"
#include "datachunk.h"
// DEFINITIONS

// TYPEDEF
struct LayerConv2DS {
	int16_t* arra;
	int16_t* m_bias;                                           // kernel
	char m_border_mode;
	int length;
	int m_depth;
	int m_rows;
	int m_cols;
};

//GLOBAL VARIABLES
extern int size_row;
extern int size_col;

// FUNCTION PROTOTYPES
int32_t* conv_single_depth_same( int16_t* im, int m_row, int m_col, int16_t* arr, int d, int e, int row, int col, int m_depth);
void LayerConv2DS_init(struct LayerConv2DS* self);
struct LayerConv2DS* LayerConv2DS_create(void);
void Conv2D_load_weights(struct LayerConv2DS* self);
struct DataChunk2DS* Conv2D_compute_output(struct LayerConv2DS* self, struct DataChunk2DS* dc);
unsigned int Conv2D_get_input_rows(struct LayerConv2DS* self);
unsigned int Conv2D_get_input_cols(struct LayerConv2DS* self);
unsigned int Conv2D_get_output_units(struct LayerConv2DS* self);
void LayerConv2DS_reset(struct LayerConv2DS* self);
void LayerConv2DS_destroy(struct LayerConv2DS* self);

#endif