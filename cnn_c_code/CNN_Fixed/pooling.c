#include "pooling.h"

//Constructor without allocation
void LayerMaxPoolingS_init(struct LayerMaxPoolingS* self, int m_pool_x, int m_pool_y)
{
	self->m_pool_x = m_pool_x;
	self->m_pool_y = m_pool_y;
}

//Allocation+ initialization (equillant to new LayerMaxPoolingS)
struct LayerMaxPoolingS* LayerMaxPoolingS_create(void)
{
	struct LayerMaxPoolingS* result = (struct LayerMaxPoolingS*)my_malloc(sizeof(struct LayerMaxPoolingS));
	// LayerMaxPoolingS_init(result,m_pool_x,m_pool_y);
	return result;
}

//LayerMaxPoolingS :: load weight replacment
void MaxPooling_load_weights(struct LayerMaxPoolingS* self)
{
	self->m_pool_x = 2;
	self->m_pool_y = 2;
}

struct DataChunk2DS* MaxPooling_compute_output(struct LayerMaxPoolingS* self, struct DataChunk2DS* dc)
{
	int16_t* im = Chunk2D_get_3d1(dc);
	int16_t* y_ret;
	int m_col = dc->m_col / self->m_pool_y;
	int m_row = dc->m_row / self->m_pool_x;
	y_ret = (int16_t*)my_malloc(dc->m_dept * m_col * m_row * sizeof(int16_t));
	for (unsigned int d = 0; d < dc->m_dept; ++d)
	{
		for (unsigned int x = 0; x < m_row; ++x)
		{
			unsigned int start_x = x * self->m_pool_x;
			unsigned int end_x = start_x + self->m_pool_x;
			for (unsigned int y = 0; y < m_col; ++y)
			{
				unsigned int start_y = y * self->m_pool_y;
				unsigned int end_y = start_y + self->m_pool_y;
				int16_t max =0;
				for (unsigned int i = start_x; i < end_x; ++i)
				{
					for (unsigned int j = start_y; j < end_y; ++j)
					{
						
						int16_t x= *(im + d * dc->m_row * dc->m_col + i * dc->m_col + j); 
						if(x>max)
							max=x;

					}
				}

				*(y_ret + d * m_row * m_col + x * m_col + y) = max;
				//float max_res = *(y_ret + d * m_row*m_col + x * m_col + y) / (float)(1 << 15);
			}
		}

	}
	struct DataChunk2DS* out = DataChunk2DS_create();
	Chunk2D_set_data1(out, y_ret, dc->m_dept, m_row, m_col);
	return out;
}

unsigned int MaxPooling_get_input_rows(struct LayerMaxPoolingS* self) 
{
	return 0;
} // look for the value in the preceding layer

unsigned int MaxPooling_get_input_cols(struct LayerMaxPoolingS* self) 
{
	return 0;
} // same as for rows

unsigned int MaxPooling_get_output_units(struct LayerMaxPoolingS* self)
{
	return 0; 
}

//Destructor without deallocation 
void LayerMaxPoolingS_reset(struct LayerMaxPoolingS* self)
{}

//Deallocator with deallocation (equillant to delete LayerMaxPoolingS
void LayerMaxPoolingS_destroy(struct  LayerMaxPoolingS* self)
{
	if (self)
	{
		LayerMaxPoolingS_reset(self);
//		free(self);
	}
}
