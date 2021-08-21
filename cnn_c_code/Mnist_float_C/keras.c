#include"variable.h"
#include"classes.h"
#include <stdint.h>
#include <stdio.h>
#include<stddef.h>
#include<math.h>
#include<stdlib.h>
#include"vector.h"
#define CVECTOR_LOGARITHMIC_GROWTH
struct DataChunk2DS {
	float *y_ret_3D;
	int m_dept;
	int m_row;
	int m_col;
};
//Constructor without allocation
void DataChunk2DS_init(struct DataChunk2DS * self) {

}
//Allocation+ initialization (equillant to new DataChunk2DS)
struct DataChunk2DS * DataChunk2DS_create() {
	struct DataChunk2DS* result = (struct DataChunk2DS*)malloc(sizeof(struct DataChunk2DS));
	DataChunk2DS_init(result);
	return result;
}
//Destructor without deallocation 
void DataChunk2DS_reset(struct DataChunk2DS * self) {

}
//Deallocator with deallocation (equillant to delete DataChunk2DS
void DataChunk2DS_destroy(struct DataChunk2DS* self) {
	if (self) {
		DataChunk2DS_reset(self);
		free(self);
	}
}
float* Chunk2D_get_3d1(struct DataChunk2DS *self) { return self->y_ret_3D; };

void Chunk2D_set_data1(struct DataChunk2DS * self, float * y_ret, int depth, int row, int col) {
	self->y_ret_3D = y_ret;
	self->m_dept = depth;
	self->m_row = row;
	self->m_col = col;
}
size_t Chunk2D_get_data_dim(void) { return 3; }

void Chunk2D_show_name()
{
	// std::cout << "DataChunk2D " << data.size() << "x" << data[0].size() << "x" << data[0][0].size() << std::endl;
}

void Chunk2D_show_values()
{
	//std::cout << "DataChunk2D values:" << std::endl;
	/*for (size_t i = 0; i < data.size(); ++i)
	{
		// std::cout << "Kernel " << i << std::endl;
		for (size_t j = 0; j < data[0].size(); ++j)
		{
			for (size_t k = 0; k < data[0][0].size(); ++k)
			{
				std::cout << data[i][j][k] << " ";
			}
			std::cout << std::endl;
		}
	}*/
}
//unsigned int get_count() {
//  return data.size()*data[0].size()*data[0][0].size();
//}


void Chun2D_read_from_file1Dep(struct DataChunk2DS * self) {
	self->y_ret_3D = (float *)malloc(depth * 28 * 28* sizeof(float));//C
	self->m_row = 28;
	self->m_col = 28;
	self->m_dept = 1;
	for (int i = 0; i < self->m_dept; i++) {
		for (int j = 0; j < self->m_row; j++) {
			for (int k = 0; k < self->m_col; k++) {
				*(self->y_ret_3D + i * self->m_row*self->m_col + j * self->m_col + j) = tmp_single_depth11n[j][k];
			}
		}
	}


}
struct DataChunkFlatS {
	int m_size;
	float * f;

};
//Constructor without allocation
void DataChunkFlatS_init(struct DataChunkFlatS * self, int size) {
	self->m_size = size;
	self->f = (float*)malloc(size*sizeof(float));//call
	for(int i=0;i<size;i++){
		*(self->f+i)=0;
}


}
//Allocation+ initialization (equillant to new DataChunkFlatS)
struct DataChunkFlatS * DataChunkFlatS_create(int size) {
	struct DataChunkFlatS* result = (struct DataChunkFlatS*)malloc(sizeof(struct DataChunkFlatS));
	DataChunkFlatS_init(result, size);
	return result;
}
//Destructor without deallocation 
void DataChunkFlatS_reset(struct DataChunkFlatS * self) {

}
//Deallocator with deallocation (equillant to delete DataChunkFlatS
void DataChunkFlatS_destroy(struct DataChunkFlatS* self) {
	if (self) {
		DataChunkFlatS_reset(self);
		free(self);
	}
}
float * Flat_get_1d_rw(struct DataChunkFlatS *self) { return self->f; }
void Flat_set_data1(struct DataChunkFlatS *dc, float *d) { dc->f = d; };
size_t Flat_get_data_dim(void) { return 1; }
void Flat_show_name(struct DataChunkFlatS *self)
{
	//  std::cout << "DataChunkFlat " << f.size() << std::endl;
}
void Flat_show_values(struct DataChunkFlatS *self)
{
	//std::cout << "DataChunkFlat values:" << std::endl;
	//for (size_t i = 0; i < self->m_size; ++i)
	//	std::cout << *(self->f + i) << " ";
	//std::cout << std::endl;
}

struct LayerFlattenS {

};
//Constructor without allocation
void LayerFlattenS_init(struct LayerFlattenS * self) {

}
//Allocation+ initialization (equillant to new LayerFlattenS)
struct LayerFlattenS * LayerFlattenS_create() {
	struct LayerFlattenS* result = (struct LayerFlattenS*)malloc(sizeof(struct LayerFlattenS));
	LayerFlattenS_init(result);
	return result;
}
//LayerFlattenS :: load weight replacment
void Flatten_load_weights(struct LayerFlattenS * self) {

};
struct DataChunkFlatS* Flatten_compute_output(struct LayerFlattenS* self, struct DataChunk2DS *dc) {
	//cout << "OKA1" << endl;

	float* im = Chunk2D_get_3d1(dc);

	size_t csize = dc->m_row;
	size_t rsize = dc->m_col;
	size_t size = dc->m_col * csize * rsize;

	struct DataChunkFlatS *out =DataChunkFlatS_create(size);
	//cout << "OKA2" << endl;
	float *y_ret = Flat_get_1d_rw(out);

	for (size_t i = 0, dst = 0; i < dc->m_dept; ++i)
	{
		for (size_t j = 0; j < csize; ++j)
		{
			float *row = (im+i*dc->m_dept+j);
			for (size_t k = 0; k < rsize; ++k)
			{
				*(y_ret+dst) =*(row+k);
				dst = dst++;
			}
		}
	}

	return out;
}
unsigned int Flatten_get_input_rows(struct LayerFlattenS * self) { return 0; } // look for the value in the preceding layer
unsigned int Flatten_get_input_cols(struct LayerFlattenS * self) { return 0; } // same as for rows
unsigned int Flatten_get_output_units(struct LayerFlattenS * self) { return 0; }
//Destructor without deallocation 
void LayerFlattenS_reset(struct LayerFlattenS * self) {

}
//Deallocator with deallocation (equillant to delete LayerFlattenS
void LayerFlattenS_destroy(struct LayerFlattenS* self) {
	if (self) {
		LayerFlattenS_reset(self);
		free(self);
	}
}
struct LayerMaxPoolingS {
	int m_pool_x;
	int m_pool_y;
};
//Constructor without allocation
void LayerMaxPoolingS_init(struct LayerMaxPoolingS * self, int m_pool_x, int m_pool_y) {
	self->m_pool_x = m_pool_x;
	self->m_pool_y = m_pool_y;

}
//Allocation+ initialization (equillant to new LayerMaxPoolingS)
struct LayerMaxPoolingS * LayerMaxPoolingS_create() {
	struct LayerMaxPoolingS* result = (struct LayerMaxPoolingS*)malloc(sizeof(struct LayerMaxPoolingS));
	// LayerMaxPoolingS_init(result,m_pool_x,m_pool_y);
	return result;
}
//LayerMaxPoolingS :: load weight replacment
void MaxPooling_load_weights(struct LayerMaxPoolingS * self) {
	self->m_pool_x = 2;
	self->m_pool_y = 2;
	//cout << "MaxPooling " << self->m_pool_x << "x" << self->m_pool_y << endl;

};
struct DataChunk2DS* MaxPooling_compute_output(struct LayerMaxPoolingS* self, struct DataChunk2DS *dc) {
	 float * im = Chunk2D_get_3d1(dc);
	float* y_ret;
	y_ret = (float*)malloc(dc->m_dept*dc->m_col*dc->m_row*sizeof(float));//call
	
	for (unsigned int d = 0; d <dc->m_dept; ++d)
	{
		for (unsigned int x = 0; x < dc->m_row; ++x)
		{
			unsigned int start_x = x * self->m_pool_x;
			unsigned int end_x = start_x + self->m_pool_x;
			for (unsigned int y = 0; y < dc->m_col; ++y)
			{
				unsigned int start_y = y * self->m_pool_y;
				unsigned int end_y = start_y + self->m_pool_y;
				//float *value = (float*)malloc(2*2*sizeof(float));

				//vector<float> values;
			float *v = NULL;
						

				for (unsigned int i = start_x; i < end_x; ++i)
				{
					for (unsigned int j = start_y; j < end_y; ++j)
					{
						vector_push_back(v,*(im + d * end_x*end_y + i * end_y + j));
					}
				}

			float max=v[0];	
			if(v) {
			size_t i;
			for(i = 1; i < vector_size(v); ++i) {
				if(v[i]>max)
				max=v[i];
			}
		}		
		*(y_ret + d * dc->m_row*dc->m_col+ x * dc->m_col + y) = max;
		/* well, we don't have destructors, so let's clean things up */
		vector_free(v);
		//		*(y_ret + d * dc->m_row*dc->m_col+ x * dc->m_col + y) = *max_element(values.begin(), values.end());
				
			}
		}
	}
	struct DataChunk2DS *out = DataChunk2DS_create();
	Chunk2D_set_data1(out,y_ret, dc->m_dept, dc->m_row, dc->m_col);
	return out;

}
unsigned int MaxPooling_get_input_rows(struct LayerMaxPoolingS * self) { return 0; } // look for the value in the preceding layer
unsigned int MaxPooling_get_input_cols(struct LayerMaxPoolingS * self) { return 0; } // same as for rows
unsigned int MaxPooling_get_output_units(struct LayerMaxPoolingS * self) { return 0; }
//Destructor without deallocation 
void LayerMaxPoolingS_reset(struct LayerMaxPoolingS * self) {

}
//Deallocator with deallocation (equillant to delete LayerMaxPoolingS
void LayerMaxPoolingS_destroy(struct  LayerMaxPoolingS* self) {
	if (self) {
		LayerMaxPoolingS_reset(self);
		free(self);
	}
}
struct LayerActivationS {
	char * m_activation_type;
};
//Constructor without allocation
void LayerActivationS_init(struct LayerActivationS * self) {

}
//Allocation+ initialization (equillant to new LayerActivationS)
struct LayerActivationS * LayerActivationS_create() {
	struct LayerActivationS* result = (struct LayerActivationS*)malloc(sizeof(struct LayerActivationS));
	LayerActivationS_init(result);
	return result;
}
//LayerActivationS :: load weight replacment
void Activation_load_weights(struct LayerActivationS * self) {
	self->m_activation_type = activation_activator[activation_counter];
	activation_counter++;
	//cout << "Activation type " << self->m_activation_type << endl;


};
struct DataChunkFlatS* Activation_compute_output1D(struct LayerActivationS* self,struct  DataChunkFlatS *dc) {
// flat data, use 1D
		float * y = Flat_get_1d_rw(dc);
		if (*(self->m_activation_type) == 'r')
		{
			for (unsigned int k = 0; k < dc->m_size; ++k)
			{
				if (y[k] < 0)
					y[k] = 0;
			}
		}
		else if (*(self->m_activation_type) == 's')//Softmax
		{
			float sum = 0.0;
			for (unsigned int k = 0; k < dc->m_size; ++k)
			{
				y[k] = exp(y[k]);
				sum += y[k];
			}
			for (unsigned int k = 0; k < dc->m_size; ++k)
			{
				y[k] /= sum;
				printf("V %f ",y[k]);
				printf(" ");
					
			}
		}
		else if (self->m_activation_type == "S")  //sigmoid
		{
			for (unsigned int k = 0; k < dc->m_size; ++k)
			{
				y[k] = 1 / (1 + exp(-y[k]));
			}
		}
		else if (self->m_activation_type == "t")
		{
			for (unsigned int k = 0; k < dc->m_size; ++k)
			{
				y[k] = tanh(y[k]);
			}
		}
		else
		{
			missing_activation_impl(self->m_activation_type);
		}

		struct DataChunkFlatS *out =  DataChunkFlatS_create(0);
		Flat_set_data1(out,y);
		Flat_show_values(out);
		//cout << "OKa from secon" << endl;
		return out;
	
	//cout << "OKa dc" << endl;
	return dc;

}
struct DataChunk2DS* Activation_compute_output3D(struct LayerActivationS* self,struct  DataChunk2DS *dc) {
	float *y = Chunk2D_get_3d1(dc);
	//cout << self->m_activation_type;
	if (*(self->m_activation_type) == 'r')
	{
		for (unsigned int i = 0; i < dc->m_dept; ++i)
		{
			for (unsigned int j = 0; j < dc->m_row; ++j)
			{
				for (unsigned int k = 0; k < dc->m_col; ++k)
				{
					if (*(y + i * dc->m_row*dc->m_col + j * dc->m_col + k) < 0)
						*(y + i * dc->m_row*dc->m_col + j * dc->m_col+ k) = 0;
				}
			}
			}
			struct DataChunk2DS *out = DataChunk2DS_create();
			Chunk2D_set_data1(out,y, dc->m_dept, dc->m_row, dc->m_col);
	//		cout << "OKa from" << endl;
			return out;
		
	}
	else
	{
		missing_activation_impl();
	}

}
unsigned int Activation_get_input_rows(struct LayerActivationS * self) { return 0; } // look for the value in the preceding layer
unsigned int Activation_get_input_cols(struct LayerActivationS * self) { return 0; } // same as for rows
unsigned int Activation_get_output_units(struct LayerActivationS * self) { return 0; }
//Destructor without deallocation 

void LayerActivationS_reset(struct LayerActivationS * self) {

}
//Deallocator with deallocation (equillant to delete LayerActivationS
void LayerActivationS_destroy(struct LayerActivationS* self) {
	if (self) {
		LayerActivationS_reset(self);
		free(self);
	}
}

struct LayerConv2DS {
	
	float *arra ;
	float *m_bias;                                           // kernel
	char * m_border_mode;
	int m_kernels_cnt;
	int length;
	int m_depth;
	int m_rows;
	int m_cols;

};
//Constructor without allocation
void LayerConv2DS_init(struct LayerConv2DS * self) {

}
//Allocation+ initialization (equillant to new LayerConv2DS)
struct LayerConv2DS * LayerConv2DS_create() {
	struct LayerConv2DS* result = (struct LayerConv2DS*)malloc(sizeof(struct LayerConv2DS));
	
	//LayerConv2DS_init(result);
	return result;
}
//LayerConv2DS :: load weight replacment
void Conv2D_load_weights(struct LayerConv2DS * self) {

	//cout << "conv1_weight" << endl;
	if (conv_counter == 0)
	{
		
		self->m_depth = conv_depth[conv_counter];
		self->m_rows = conv_row[conv_counter];
		self->m_cols = conv_col[conv_counter];
		self->length = conv_length[conv_counter];
		self->m_border_mode = conv_border[conv_counter];
		
		//Print4D(self->m_kernels, tmp_depths1);
		//self->m_kernels = tmp_depths1;
		self->arra = (float *)malloc(sizeof(float[4*1*3*3]));
		for (int i = 0; i < self->length; i++) {
			for (int j = 0; j < self->m_depth; j++) {
				for (int k = 0; k < self->m_rows; k++) {
					for (int l = 0; l < self->m_cols; l++) {
						*(self->arra + i * self->m_depth* self->m_rows * self->m_cols+ j * self->m_rows *self->m_cols + k * self->m_cols + l) = tmp_depths1n[i][j][k][l];
					}
				}
			}
		}

		//cout << "First" << endl;
		self->m_bias = conv_bias1n;
		conv_counter++;

	}
	else if (conv_counter == 1)
	{
		self->length = conv_length[conv_counter];
		self->m_depth = conv_depth[conv_counter];
		self->m_rows = conv_row[conv_counter];
		self->m_cols = conv_col[conv_counter];
		self->m_border_mode = conv_border[conv_counter];
		self->m_bias = conv_bias2n;
		//self->m_kernels = tmp_depths2;
		self->arra = (float *)malloc(sizeof(float[4 * 4 * 3 * 3]));
		for (int i = 0; i < self->length; i++) {
			for (int j = 0; j < self->m_depth; j++) {
				for (int k = 0; k < self->m_rows; k++) {
					for (int l = 0; l < self->m_cols; l++) {
						*(self->arra + i * self->m_depth* self->m_rows * self->m_cols + j * self->m_rows *self->m_cols + k * self->m_cols + l) = tmp_depths2n[i][j][k][l];
					}
				}
			}
		}

		//cout << "Second" << endl;
	}
	//cout << "conv1_weight" << endl;

}

struct DataChunk2DS* Conv2D_compute_output(struct LayerConv2DS* self, struct DataChunk2DS *dc) {
	//cout << "CON1" << endl;
	//cout << self->length << self->m_rows << self->m_cols << endl;
	//unsigned int st_x = (self->m_kernels[0][0].size() - 1) >> 1;
	//unsigned int st_y = (self->m_kernels[0][0][0].size() - 1) >> 1;
	unsigned int st_x = (self->m_rows - 1) >> 1;
	unsigned int st_y = (self->m_cols - 1) >> 1;

	float * y_ret;
	float *im = Chunk2D_get_3d1(dc);
	
	size_t size_x = (self->m_border_mode == "valid") ? dc->m_dept - 2 * st_x : dc->m_row;
	size_t size_y = (self->m_border_mode == "valid") ? dc->m_row - 2 * st_y : dc->m_col;
	y_ret = (float * )malloc(self->length*size_x*size_y* sizeof(float));//c  most important
	
	for (unsigned int j = 0; j < self->length; ++j)
	{ // loop over kernels
		for (int m = 0; m < dc->m_dept; ++m)
		{ // loope over image depth

	float* tmp_w = (self->m_border_mode == "valid") ? conv_single_depth_valid(
		((im+m)),dc->m_row,dc->m_col, self->arra,self->m_rows,self->m_cols): conv_single_depth_same(((im + m)), dc->m_row, dc->m_col, self->arra,self->m_rows,self->m_cols);
	for (unsigned int x = 0; x < size_row; ++x)
			{
				for (unsigned int y = 0; y < size_col; ++y)
				{
						*(y_ret+j*size_x*size_y+x*size_y+y)+=*(tmp_w+x*size_col+y);
				}
			}
		}

		for (unsigned int x = 0; x < size_x; ++x)
		{
			for (unsigned int y = 0; y < size_y; ++y)
			{
				*(y_ret + j * size_x*size_y + x * size_y + y) += self->m_bias[j];
			}
		}
	}
	//std::cout << "conv2" << endl;
	struct DataChunk2DS *out = DataChunk2DS_create();
	Chunk2D_set_data1(out,y_ret,self->length,size_x,size_y);
	return out;

}
unsigned int Conv2D_get_input_rows(struct LayerConv2DS * self) { return self->m_rows; } // look for the value in the preceding layer
unsigned int Conv2D_get_input_cols(struct LayerConv2DS * self) { return self->m_cols; } // same as for rows
unsigned int Conv2D_get_output_units(struct LayerConv2DS * self) { return self->m_kernels_cnt; }
//Destructor without deallocation 
void LayerConv2DS_reset(struct LayerConv2DS * self) {


}
//Deallocator with deallocation (equillant to delete LayerConv2DS
void LayerConv2DS_destroy(struct LayerConv2DS* self) {
	if (self) {
		LayerConv2DS_reset(self);
		free(self);
	}
}


struct LayerDenseS {
	float * m_weights; //input, neuron
	float * m_bias;
	int m_row;
	int m_col;
	int m_input_cnt;
	int m_neurons;

};
//Constructor without allocation
void LayerDenseS_init(struct LayerDenseS * self) {

}
//Allocation+ initialization (equillant to new LayerDenseS)
struct LayerDenseS * LayerDenseS_create() {
	struct LayerDenseS* result = (struct LayerDenseS*)malloc(sizeof(struct LayerDenseS));
	//LayerDenseS_init(result);
	return result;
}
//LayerDenseS :: load weight replacment
void Dense_load_weights(struct LayerDenseS * self) {

	if (dense_counter == 0)
	{   
		self->m_weights =(float *)malloc(784*6*sizeof(float));//c
		self->m_row = 784;
		self->m_col = 6;
		for (int i = 0; i < self->m_row; i++) {
			for (int j = 0; j < self->m_col; j++) {
				*(self->m_weights + i * self->m_col + j) = dense_weight1n[i][j];
			}
		}
		self->m_bias = dense_bias1n;
		dense_counter++;
	}
	else if (dense_counter == 1)
	{
		self->m_bias = dense_bias2n;
		self->m_weights = (float*)malloc(6*10*sizeof(float));//c
		self->m_row = 6;
		self->m_col = 10;
		for (int i = 0; i < self->m_row; i++) {
			for (int j = 0; j < self->m_col; j++) {
				*(self->m_weights + i * self->m_col + j) = dense_weight2n[i][j];
			}
		}
	}
	//cout << "weights " << m_weights.size() << endl;

}
struct DataChunkFlatS* Dense_compute_output(struct LayerDenseS* self, struct DataChunkFlatS * dc) {

	//cout << "weights: input size " << m_weights.size() << endl;
	//cout << "weights: neurons size " << m_weights[0].size() << endl;
	//cout << "bias " << m_bias.size() << endl;
	size_t size = self->m_col;
	size_t size8 = size >> 3;
	struct DataChunkFlatS *out =  DataChunkFlatS_create(size);
	float *y_ret = Flat_get_1d_rw(out);

	float *im  = Flat_get_1d_rw(dc);

	for (size_t j = 0; j < self->m_row; ++j)
	{ // iter over input
		const float *w = (self->m_weights+j*self->m_col);
		float p = *(im+j);
		size_t k = 0;
		for (size_t i = 0; i < size8; ++i)
		{                         // iter over neurons
			y_ret[k] += w[k] * p; // vectorize if you can
			y_ret[k + 1] += w[k + 1] * p;
			y_ret[k + 2] += w[k + 2] * p;
			y_ret[k + 3] += w[k + 3] * p;
			y_ret[k + 4] += w[k + 4] * p;
			y_ret[k + 5] += w[k + 5] * p;
			y_ret[k + 6] += w[k + 6] * p;
			y_ret[k + 7] += w[k + 7] * p;
			k += 8;
		}
		while (k < size)
		{
			y_ret[k] += w[k] * p;
			++k;
		}
	}
	for (size_t i = 0; i < size; ++i)
	{ // add biases
		y_ret[i] += self->m_bias[i];
	}

	return out;
}
unsigned int Dense_get_input_rows(struct LayerDenseS * self) { return 0; } // look for the value in the preceding layer
unsigned int Dense_get_input_cols(struct LayerDenseS * self) { return self->m_input_cnt; } // same as for rows
unsigned int Dense_get_output_units(struct LayerDenseS * self) { return self->m_neurons; }
//Destructor without deallocation 
void LayerDenseS_reset(struct LayerDenseS * self) {


}
//Deallocator with deallocation (equillant to delete LayerDenseS
void LayerDenseS_destroy(struct LayerDenseS* self) {
	if (self) {
		LayerDenseS_reset(self);
		free(self);
	}
}

int main(void)
{
	struct DataChunk2DS *sample = DataChunk2DS_create();
	Chun2D_read_from_file1Dep(sample);
	struct DataChunk2DS*inp = sample;
	struct DataChunk2DS *out = 0;
	struct LayerConv2DS *la_conv1 =  LayerConv2DS_create();
	Conv2D_load_weights(la_conv1);
	out = Conv2D_compute_output(la_conv1,inp);

	//out->show_values();
	if (inp != sample)
		//delete inp;
	inp = 0L;
	inp = out;
	struct LayerActivationS *la_activ1 = LayerActivationS_create();
	Activation_load_weights(la_activ1);
	out = Activation_compute_output3D(la_activ1,inp);
	if (inp != sample)
		//delete inp;
	inp = 0L;
	inp = out;
	struct LayerConv2DS *la_conv2 = LayerConv2DS_create();
	Conv2D_load_weights(la_conv2);
	out = Conv2D_compute_output(la_conv2, inp);

	if (inp != sample)
		//delete inp;
	inp = 0L;
	inp = out;
	struct LayerActivationS *la_activ2 = LayerActivationS_create();
	Activation_load_weights(la_activ2);
	out = Activation_compute_output3D(la_activ2,inp);
	if (inp != sample)
		//delete inp;
	inp = 0L;
	inp = out;
	//cout << "Done2" << endl;
	struct LayerMaxPoolingS *la_pool1 = LayerMaxPoolingS_create();
	MaxPooling_load_weights(la_pool1);
	out = MaxPooling_compute_output(la_pool1, inp);
	if (inp != sample)
		//delete inp;
	inp = 0L;
	inp = out;

	struct LayerFlattenS *la_flat1 = LayerFlattenS_create();
	Flatten_load_weights(la_flat1);
	struct DataChunkFlatS *out1 = 0,*inp1=0;
	out1 = Flatten_compute_output(la_flat1, inp);
	//cout << "OKA2" << endl;
	inp1 = 0L;
	inp1 = out1;
	//cout << "done3" << endl;
	struct LayerDenseS *la_dense1 =  LayerDenseS_create();
	Dense_load_weights(la_dense1);
	out1 = Dense_compute_output(la_dense1,inp1);
	inp1 = 0L;
	inp1 = out1;
	struct LayerActivationS *la_activ3 = LayerActivationS_create();
	Activation_load_weights(la_activ3);
	out1 = Activation_compute_output1D(la_activ3,inp1);
	inp1 = 0L;
	inp1 = out1;

	struct LayerDenseS *la_dense2 =  LayerDenseS_create();
	Dense_load_weights(la_dense2);
	out1 = Dense_compute_output(la_dense2,inp1);
	inp1 = 0L;
	inp1 = out1;

	struct LayerActivationS *la_activ4 = LayerActivationS_create();
	Activation_load_weights(la_activ4);
	out1 = Activation_compute_output1D(la_activ4,inp1);
	inp1 = 0L;
	inp1 = out1;
	//float*  flat_out = Flat_get_1d_rw(out1);
	//Flat_show_values(out1);
	//delete out;
	//delete sample;
	//system("pause");
	return 0;
}
