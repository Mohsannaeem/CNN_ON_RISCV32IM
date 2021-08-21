#include "convolution.h"
#include "conv.h"
#include "dense.h"
#include "activation.h"
#include "flatten.h"
#include "pooling.h"
#include "datachunk.h"
#include "newvariable.h"

#include "orca_malloc.h"
#include "orca_printf.h"
#define HEAP_ADDRESS 0x001000000
#define HEAP_SIZE    0x00A00000
#define CACHE_SIZE      32

int main(void)
{
	//Intialize Heap here 
	//printf("Program Started\r\n");	
	//printf("Program Started\r\n");	
	//printf("Program Started\r\n");	
		
	init_malloc((void*)HEAP_ADDRESS,HEAP_SIZE,CACHE_SIZE);//intialize heap of 20MB and aligned 4 byte 	
	//printf("Program reached DataChunk_create\r\n");
	struct DataChunk2DS* self = DataChunk2DS_create();
	//printf("Program reached Chun2D_read_from_file1Dep\r\n");	
	self->y_ret_3D =(int16_t*)my_malloc( 28 * 28);//C	
	self->m_row = 28;
	self->m_col = 28;
	self->m_dept = 1;
	for (int i = 0; i < self->m_dept; i++) {
		for (int j = 0; j < self->m_row; j++) {
			for (int k = 0; k < self->m_col; k++) {
				//printf("DDR%d \r ",*(self->y_ret_3D + i * self->m_row * self->m_col + j * self->m_col + k) );
				*(self->y_ret_3D + i * self->m_row * self->m_col + j * self->m_col + k) = tmp_single_depth11n[j][k];
				//printf("Malloc %d \r ",*(self->y_ret_3D + i * self->m_row * self->m_col + j * self->m_col + k) );
			}
		}
	}
	//printf("Program Cleared \r\n");	
	struct DataChunk2DS* inp = self;
	struct DataChunk2DS* out = 0;
	struct LayerConv2DS* la_conv1 = LayerConv2DS_create();
	//printf("Program Reached After Compute convolution1 \r\n");	
	Conv2D_load_weights(la_conv1);
	//printf("Program Reached After Compute convolution2 \r\n");
	out = Conv2D_compute_output(la_conv1, inp);
	//printf("Program Reached After Compute convolution 3\r\n");
		
	inp = 0L;
	inp = out;
	printf("Convolution 1 Done\r\n");		
	struct LayerActivationS* la_activ1 = LayerActivationS_create();
	Activation_load_weights(la_activ1);
	out = Activation_compute_output3D(la_activ1, inp);
	inp = 0L;
	inp = out;
	//printf("Activation 1 Done\r\n");		
	//chunk_showvalues(inp);
	struct LayerConv2DS* la_conv2 = LayerConv2DS_create();
	Conv2D_load_weights(la_conv2);
	out = Conv2D_compute_output(la_conv2, inp);

	inp = 0L;
	inp = out;
	//printf("Convolution 2 Done\r\n");			
	struct LayerActivationS* la_activ2 = LayerActivationS_create();
	Activation_load_weights(la_activ2);
	out = Activation_compute_output3D(la_activ2, inp);
	inp = 0L;
	inp = out;
	//printf("Activation 2 Done\r\n");
	struct LayerMaxPoolingS* la_pool1 = LayerMaxPoolingS_create();
	//printf("Max Pooling  Done1\r\n");
	MaxPooling_load_weights(la_pool1);
	//printf("Max Pooling  Done2\r\n");
	out = MaxPooling_compute_output(la_pool1, inp);
	//printf("Max Pooling  Done3\r\n");
	inp = 0L;
	inp = out;
	
	struct LayerFlattenS* la_flat1 = LayerFlattenS_create();
	Flatten_load_weights(la_flat1);
	struct DataChunkFlatS* out1 = 0, *inp1 = 0;
	out1 = Flatten_compute_output(la_flat1, inp);
	inp1 = 0L;
	inp1 = out1;

	struct LayerDenseS* la_dense1 = LayerDenseS_create();
	Dense_load_weights(la_dense1);
	out1 = Dense_compute_output(la_dense1, inp1);
	inp1 = 0L;
	inp1 = out1;
	//printf("Dense Layer 1 Done\r\n");
	struct LayerActivationS* la_activ3 = LayerActivationS_create();
	Activation_load_weights(la_activ3);
	out1 = Activation_compute_output1D(la_activ3, inp1);
	inp1 = 0L;
	inp1 = out1;
	//printf("Activation 3 Layer 1 Done\r\n");
	struct LayerDenseS* la_dense2 = LayerDenseS_create();
	Dense_load_weights(la_dense2);
	out1 = Dense_compute_output(la_dense2, inp1);
	inp1 = 0L;
	inp1 = out1;
	//printf("Dense Layer 2 Done\r\n");	
	struct LayerActivationS* la_activ4 = LayerActivationS_create();
	Activation_load_weights(la_activ4);
	out1 = Activation_compute_output1D(la_activ4, inp1);
	inp1 = 0L;
	inp1 = out1;
	//printf("Activation 3 Layer 1 Done\r\n");
	
	int16_t y;
	for (size_t i = 0; i < out1->m_size; ++i)
	{
		y = *(out1->f + i);
		printf("%d \n", y);
	}
	//Flat_show_values(out1);

	return 0;
}
