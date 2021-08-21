#include "flatten.h"

//Constructor without allocation
void LayerFlattenS_init(struct LayerFlattenS* self)
{}

//Allocation+ initialization (equillant to new LayerFlattenS)
struct LayerFlattenS* LayerFlattenS_create()
{
	struct LayerFlattenS* result = (struct LayerFlattenS*)my_malloc(sizeof(struct LayerFlattenS));
	LayerFlattenS_init(result);
	return result;
}

//LayerFlattenS :: load weight replacment
void Flatten_load_weights(struct LayerFlattenS* self)
{}

struct DataChunkFlatS* Flatten_compute_output(struct LayerFlattenS* self, struct DataChunk2DS* dc)
{
	int16_t* im = Chunk2D_get_3d1(dc);

	size_t csize = dc->m_col;
	size_t rsize = dc->m_row;
	size_t size = dc->m_dept * csize * rsize;

	struct DataChunkFlatS* out = DataChunkFlatS_create(size);
	int16_t* y_ret = Flat_get_1d_rw(out);
	for (size_t i = 0, dst = 0; i < dc->m_dept; ++i)
	{
		for (size_t j = 0; j < csize; ++j)
		{
			for (size_t k = 0; k < rsize; ++k)
			{
				
				*(y_ret + dst) = *(im + i * dc->m_row * dc->m_col + j * dc->m_row + k);
				dst = dst + 1;
			}
		}
	}
	Flat_set_data1(out, y_ret);
	return out;
}

unsigned int Flatten_get_input_rows(struct LayerFlattenS* self)
{
	return 0;
} // look for the value in the preceding layer

unsigned int Flatten_get_input_cols(struct LayerFlattenS* self)
{
	return 0;
} // same as for rows

unsigned int Flatten_get_output_units(struct LayerFlattenS* self)
{
	return 0;
}

//Destructor without deallocation 
void LayerFlattenS_reset(struct LayerFlattenS* self) 
{}

//Deallocator with deallocation (equillant to delete LayerFlattenS
void LayerFlattenS_destroy(struct LayerFlattenS* self)
{
	if (self)
	{
		LayerFlattenS_reset(self);
//		free(self);
	}
}
