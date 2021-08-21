#include "activation.h"

//Constructor without allocation
inline void LayerActivationS_init(struct LayerActivationS* self)
{}

//Allocation+ initialization (equillant to new LayerActivationS)
inline struct LayerActivationS* LayerActivationS_create(void)
{
	struct LayerActivationS* result = (struct LayerActivationS*)my_malloc(sizeof(struct LayerActivationS));
	LayerActivationS_init(result);
	return result;
}

//LayerActivationS :: load weight replacment
inline void Activation_load_weights(struct LayerActivationS* self)
{
	self->m_activation_type = activation_activator[activation_counter];
	activation_counter++;
}

inline struct DataChunkFlatS* Activation_compute_output1D(struct LayerActivationS* self, struct  DataChunkFlatS* dc)
{
	int16_t* y = Flat_get_1d_rw(dc);
	if ((self->m_activation_type) == 'r')
	{
		for (unsigned int k = 0; k < dc->m_size; ++k)
		{
			if (*(y + k) < 0)
				y[k] = 0;
			
		}
	}
	struct DataChunkFlatS* out = DataChunkFlatS_create(dc->m_size);
	Flat_set_data1(out, y);
	return out;
}

inline struct DataChunk2DS* Activation_compute_output3D(struct LayerActivationS* self, struct  DataChunk2DS* dc)
{
	int16_t* y = Chunk2D_get_3d1(dc);
	if ((self->m_activation_type) == 'r')
	{
		for (unsigned int i = 0; i < dc->m_dept; ++i)
		{
			for (unsigned int j = 0; j < dc->m_row; ++j)
			{
				for (unsigned int k = 0; k < dc->m_col; ++k)
				{
					if (*(y + i * dc->m_row * dc->m_col + j * dc->m_col + k) < 0)
						*(y + i * dc->m_row * dc->m_col + j * dc->m_col + k) = 0;

				}
			}
		}
	}
		struct DataChunk2DS* out = DataChunk2DS_create();
		Chunk2D_set_data1(out, y, dc->m_dept, dc->m_row, dc->m_col);
		return out;
	
}

inline unsigned int Activation_get_input_rows(struct LayerActivationS* self)
{
	return 0;
} // look for the value in the preceding layer

inline unsigned int Activation_get_input_cols(struct LayerActivationS* self)
{
	return 0;
} // same as for rows

inline unsigned int Activation_get_output_units(struct LayerActivationS* self)
{
	return 0; 
}

//Destructor without deallocation 
inline void LayerActivationS_reset(struct LayerActivationS* self) 
{}

//Deallocator with deallocation (equillant to delete LayerActivationS
inline void LayerActivationS_destroy(struct LayerActivationS* self)
{
	if (self)
	{
		LayerActivationS_reset(self);
		
	}
}
