#include "dense.h"

//Constructor without allocation
void LayerDenseS_init(struct LayerDenseS* self)
{}

//Allocation+ initialization (equillant to new LayerDenseS)
struct LayerDenseS* LayerDenseS_create()
{
	struct LayerDenseS* result = (struct LayerDenseS*)my_malloc(sizeof(struct LayerDenseS));
	//LayerDenseS_init(result);
	return result;
}

//LayerDenseS :: load weight replacment
void Dense_load_weights(struct LayerDenseS* self)
{
	if (dense_counter == 0)
	{	///printf("Dense 1 Weight Enter");
		
		self->m_weights = (int16_t*)my_malloc(12544 * 128 * sizeof(int16_t));//c
		self->m_row = 12544;
		self->m_col = 128;
		for (int i = 0; i < self->m_row; i++) {
			for (int j = 0; j < self->m_col; j++) {
				*(self->m_weights + i * self->m_col + j) = dense_weight1n[i][j];
			}
		}
		self->m_bias = dense_bias1n;
		dense_counter++;
	}
	else if (dense_counter == 1)
	{	//printf("Dense 2 Weight Enter");
		self->m_bias = dense_bias2n;
		self->m_weights = (int16_t*)my_malloc(128 * 10 * sizeof(int16_t));//c
		self->m_row = 128;
		self->m_col = 10;
		for (int i = 0; i < self->m_row; i++) {
			for (int j = 0; j < self->m_col; j++) {
				*(self->m_weights + i * self->m_col + j) = dense_weight2n[i][j];
			}
		}
	}
}

struct DataChunkFlatS* Dense_compute_output(struct LayerDenseS* self, struct DataChunkFlatS * dc)
{

	size_t size = self->m_col;
	size_t size8 = size >> 3;
	struct DataChunkFlatS *out = DataChunkFlatS_create(size);
	int16_t *y_ret = Flat_get_1d_rw(out);
	int32_t* acc_res = (int32_t*)(my_malloc(size8 * 8*sizeof(int32_t)));
	int32_t mul_result;
	int16_t *im = Flat_get_1d_rw(dc);
	for(int m=0;m<size8 * 8;m++){
	*(acc_res+m)=0;
	}
	for (size_t j = 0; j < self->m_row; ++j)
	{ 
		int16_t p = *(im + j);
		size_t k = 0;
		for (size_t i = 0; i < size8; ++i)
		{    
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k) , p);
			*(acc_res + k) = q_add_sat32(*(acc_res + k) , mul_result);
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k+1), p);
			*(acc_res + k+1) = q_add_sat32(*(acc_res + k+1), mul_result);
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k+2), p);
			*(acc_res + k+2) = q_add_sat32(*(acc_res + k+2), mul_result);
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k+3), p);
			*(acc_res + k+3) = q_add_sat32(*(acc_res + k+3), mul_result);
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k+4), p);
			*(acc_res + k+4) = q_add_sat32(*(acc_res + k+4), mul_result);
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k+5), p);
			*(acc_res + k+5) = q_add_sat32(*(acc_res + k+5), mul_result);
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k+6), p);
			*(acc_res + k+6) = q_add_sat32(*(acc_res + k+6), mul_result);
			mul_result = q_mul32(*(self->m_weights + j * self->m_col + k+7), p);
			*(acc_res + k+7) = q_add_sat32(*(acc_res + k+7), mul_result);
			k = k + 8;
		}
		while (k < size)
		{
			*(acc_res + k) += q_mul32(*(self->m_weights + j * self->m_col + k), p);
			++k;
		}
	}
	for (size_t i = 0; i < size; ++i)
	{
		//int32_t c = *(acc_res + i);
		*(y_ret + i) = convert32to16(*(acc_res + i)); //Q1.15 from Q2.30
		*(y_ret + i) = q_add_sat(*(y_ret + i) , self->m_bias[i]);//Q1.15=Q1.15+Q1.15

		
	}

	Flat_set_data1(out, y_ret);
	return out;
}

unsigned int Dense_get_input_rows(struct LayerDenseS* self)
{
	return 0;
} // look for the value in the preceding layer

unsigned int Dense_get_input_cols(struct LayerDenseS* self)
{
	return self->m_input_cnt;
} // same as for rows

unsigned int Dense_get_output_units(struct LayerDenseS* self)
{
	return self->m_neurons;
}
//Destructor without deallocation 
void LayerDenseS_reset(struct LayerDenseS* self)
{}

//Deallocator with deallocation (equillant to delete LayerDenseS
void LayerDenseS_destroy(struct LayerDenseS* self)
{
	if (self)
	{
		LayerDenseS_reset(self);
//		free(self);
	}
}
