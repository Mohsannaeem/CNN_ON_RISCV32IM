#include "convolution.h"

int size_row = 0;
int size_col = 0;



//Constructor without allocation
void LayerConv2DS_init(struct LayerConv2DS* self)
{}

//Allocation+ initialization (equillant to new LayerConv2DS)
struct LayerConv2DS* LayerConv2DS_create(void)
{
	struct LayerConv2DS* result = (struct LayerConv2DS*)my_malloc(sizeof(struct LayerConv2DS));

	//LayerConv2DS_init(result);
	return result;
}

//LayerConv2DS :: load weight replacment
void Conv2D_load_weights(struct LayerConv2DS* self)
{
	if (conv_counter == 0)
	{	//printf("Convolution 1 Weight Enter");
		self->m_depth = conv_depth[conv_counter];
		self->m_rows = conv_row[conv_counter];
		self->m_cols = conv_col[conv_counter];
		self->length = conv_length[conv_counter];
		self->m_border_mode = conv_border[conv_counter];
		self->arra = (int16_t*)my_malloc(sizeof(int16_t[32 * 1 * 3 * 3]));
		for (int i = 0; i < self->length; i++)
			for (int j = 0; j < self->m_depth; j++) 
				for (int k = 0; k < self->m_rows; k++) 
					for (int l = 0; l < self->m_cols; l++) 
						*(self->arra + i * self->m_depth * self->m_rows * self->m_cols + j * self->m_rows * self->m_cols + k * self->m_cols + l) = tmp_depths1n[i][j][k][l];

		self->m_bias = conv_bias1n;
		conv_counter++;
	}
	else if (conv_counter == 1)
	{	//printf("Convolution 2 Weight Enter");
		self->length = conv_length[conv_counter];
		self->m_depth = conv_depth[conv_counter];
		self->m_rows = conv_row[conv_counter];
		self->m_cols = conv_col[conv_counter];
		self->m_border_mode = conv_border[conv_counter];
		self->m_bias = conv_bias2n;
		self->arra = (int16_t*)my_malloc(sizeof(int16_t[64 * 32 * 3 * 3]));
		for (int i = 0; i < self->length; i++) 
			for (int j = 0; j < self->m_depth; j++) 
				for (int k = 0; k < self->m_rows; k++) 
					for (int l = 0; l < self->m_cols; l++) 
						*(self->arra + i * self->m_depth * self->m_rows * self->m_cols + j * self->m_rows * self->m_cols + k * self->m_cols + l) = tmp_depths2n[i][j][k][l];
		conv_counter++;
	}
}
int32_t* conv_single_depth_same(
	int16_t* im, int m_row, int m_col,
	int16_t* arr, int d, int e, int row, int col, int m_depth
)
{
	size_t k1_size = row, k2_size = col;

	unsigned int st_x = (k1_size - 1) >> 1;
	unsigned int st_y = (k2_size - 1) >> 1;
	//static int count = 0;
	size_t max_imc = m_row - 1;
	size_t max_imr = m_col - 1;
	int32_t* y = (int32_t*)my_malloc(m_row * m_col* sizeof(int32_t));//cal
	size_row = m_row;
	size_col = m_col;
	for (unsigned int i = 0; i < m_row; ++i)
	{
		for (unsigned int j = 0; j < m_col; ++j)
		{
			int32_t sum = 0, multi;
			for (unsigned int k1 = 0; k1 < row; ++k1)
			{
				for (unsigned int k2 = 0; k2 < col; ++k2)
				{
					if (i - st_x + k1 < 0)
						continue;
					if (i - st_x + k1 > max_imc)
						continue;
					if (j - st_y + k2 < 0)
						continue;
					if (j - st_y + k2 > max_imr)
						continue;
					multi = q_mul32(*(arr + (d * m_depth * row * col) + (e * row * col) + (row * (k1_size - k1 - 1)) + (k2_size - k2 - 1)), (*(im + e * m_row * m_col + (i - st_x + k1) * m_row + (j - st_y + k2))));
					sum = q_add_sat32(sum , multi);
				}
			}
			*(y + i * m_row + j)=0;
			*(y + i * m_row + j) = sum;
		
		}

	}
	return y;
}
struct DataChunk2DS* Conv2D_compute_output(struct LayerConv2DS* self, struct DataChunk2DS* dc)
{
	unsigned int st_x = (self->m_rows - 1) >> 1;
	unsigned int st_y = (self->m_cols - 1) >> 1;
	int32_t* y_ret;
	int16_t* y_temp;
	int16_t* im = Chunk2D_get_3d1(dc);
	size_t size_x = (self->m_border_mode == 'v') ? dc->m_dept - 2 * st_x : dc->m_row;
	size_t size_y = (self->m_border_mode == 'v') ? dc->m_row - 2 * st_y : dc->m_col;
	y_ret = (int32_t*)my_malloc(self->length * size_x * size_y * sizeof(int32_t));//c  most important
	y_temp = (int16_t*)my_malloc(self->length * size_x * size_y * sizeof(int16_t));//c  most important

	for (int ii = 0; ii < self->length * size_x * size_y; ii++)
	{
		*(y_ret + ii) = 0;
	}
	for (unsigned int j = 0; j < self->length; ++j)
	{ 
		for (int m = 0; m < dc->m_dept; ++m)
		{ 
			int32_t* tmp_w = conv_single_depth_same((im), dc->m_row, dc->m_col, self->arra, j, m, self->m_rows, self->m_cols, self->m_depth);
			for (unsigned int x = 0; x < size_row; ++x)
			{
				for (unsigned int y = 0; y < size_col; ++y)
				{
					
					*(y_ret + j * size_x * size_y + x * size_x + y) = q_add_sat32(*(y_ret + j * size_x * size_y + x * size_x + y),*(tmp_w + x * size_col + y));
		//if(j<1)
		//printf("%d  ",*(y_ret + j * size_x * size_y + x * size_x + y) );
				}

			}
		}
		//float result;
		for (unsigned int x = 0; x < size_x; ++x)
		{
			for (unsigned int y = 0; y < size_y; ++y)
			{
				*(y_temp + j * size_x * size_y + x * size_y + y) = convert32to16(*(y_ret + j * size_x * size_y + x * size_y + y));
				*(y_temp + j * size_x * size_y + x * size_y + y) = q_add_sat(*(y_temp + j * size_x * size_y + x * size_y + y), self->m_bias[j]);
				//result = *(y_temp + j * size_x * size_y + x * size_y + y) / (float)(1 << 15);
			}
		}
	}
	struct DataChunk2DS* out = DataChunk2DS_create();
	Chunk2D_set_data1(out, y_temp, self->length, size_x, size_y);
	return out;
}

unsigned int Conv2D_get_input_rows(struct LayerConv2DS* self)		// look for the value in the preceding layer
{ 
	return self->m_rows;				
} 
unsigned int Conv2D_get_input_cols(struct LayerConv2DS* self)		// same as for rows
{
	return self->m_cols;
} 
unsigned int Conv2D_get_output_units(struct LayerConv2DS* self)
{
	return self->length;
}

//Destructor without deallocation 
void LayerConv2DS_reset(struct LayerConv2DS* self)
{}

//Deallocator with deallocation (equillant to delete LayerConv2DS
void LayerConv2DS_destroy(struct LayerConv2DS* self)
{
	if (self)
	{
		LayerConv2DS_reset(self);
	//	free(self);
	}
}
