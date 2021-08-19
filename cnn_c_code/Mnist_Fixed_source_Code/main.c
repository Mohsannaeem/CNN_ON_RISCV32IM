#include "convolution.h"
#include "conv.h"
#include "dense.h"
#include "activation.h"
#include "flatten.h"
#include "pooling.h"
#include "datachunk.h"
#include "newvariable.h"

int main(void)
{
	struct DataChunk2DS* sample = DataChunk2DS_create();
	Chun2D_read_from_file1Dep(sample);
	struct DataChunk2DS* inp = sample;
	struct DataChunk2DS* out = 0;
	struct LayerConv2DS* la_conv1 = LayerConv2DS_create();
	Conv2D_load_weights(la_conv1);
	out = Conv2D_compute_output(la_conv1, inp);
	inp = 0L;
	inp = out;
	struct LayerActivationS* la_activ1 = LayerActivationS_create();
	Activation_load_weights(la_activ1);
	out = Activation_compute_output3D(la_activ1, inp);
	inp = 0L;
	inp = out;
	printf("Activation 1 Done \n ");
	//chunk_showvalues(inp);
	struct LayerConv2DS* la_conv2 = LayerConv2DS_create();
	Conv2D_load_weights(la_conv2);
	out = Conv2D_compute_output(la_conv2, inp);

	inp = 0L;
	inp = out;
	struct LayerActivationS* la_activ2 = LayerActivationS_create();
	Activation_load_weights(la_activ2);
	out = Activation_compute_output3D(la_activ2, inp);
	inp = 0L;
	inp = out;
	struct LayerMaxPoolingS* la_pool1 = LayerMaxPoolingS_create();
	MaxPooling_load_weights(la_pool1);
	out = MaxPooling_compute_output(la_pool1, inp);
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
	struct LayerActivationS* la_activ3 = LayerActivationS_create();
	Activation_load_weights(la_activ3);
	out1 = Activation_compute_output1D(la_activ3, inp1);
	inp1 = 0L;
	inp1 = out1;

	struct LayerDenseS* la_dense2 = LayerDenseS_create();
	Dense_load_weights(la_dense2);
	out1 = Dense_compute_output(la_dense2, inp1);
	inp1 = 0L;
	inp1 = out1;

	struct LayerActivationS* la_activ4 = LayerActivationS_create();
	Activation_load_weights(la_activ4);
	out1 = Activation_compute_output1D(la_activ4, inp1);
	inp1 = 0L;
	inp1 = out1;
	int16_t y;
	for (size_t i = 0; i < out1->m_size; ++i)
	{
		y = *(out1->f + i);
		printf("%d \n", y);
	}
	//Flat_show_values(out1);

	//system("pause");
	return 0;
}
