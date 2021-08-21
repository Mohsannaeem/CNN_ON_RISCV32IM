
\



#include<stddef.h>
#include<stdlib.h>
void missing_activation_impl()
{
	//cout << "Activation " << act << " not defined!" << endl;
	//cout << "Please add its implementation before use." << endl;
	exit(1);
}
// with border mode = valid
static int size_row = 0;
static int size_col = 0;
float* conv_single_depth_valid(
	float *im, int m_row, int m_col,
	float *arr,int row,int col)
{
	int k1_size = row, k2_size =col;
	unsigned int st_x = (k1_size - 1) >> 1;
	unsigned int st_y = (k2_size - 1) >> 1;
	size_row = m_row - 2 * st_x;
	size_col = m_col - 2 * st_y;
	float * y = (float*)malloc(size_row*size_col*sizeof(float));//ca
	for(int m=0;m<size_row;m++){
for(int l=0;l<size_col;l++){
 
*(y+m*size_col+l)=0;
}
}
	for (unsigned int i = st_x; i < m_row - st_x; ++i)
	{
		for (unsigned int j = st_y; j < m_col - st_y; ++j)
		{

			float sum = 0;
			for (unsigned int k1 = 0; k1 < row; ++k1)
			{
				//const float * k_data = k[k1_size-k1-1].data();
				//const float * im_data = im[i-st_x+k1].data();
				for (unsigned int k2 = 0; k2 < col; ++k2)
				{
					sum += *(arr + (k1_size - k1 - 1)*row + k2_size - k2 - 1)* (*(im + (i - st_x + k1)*m_row + j - st_y + k2));

			}
			}
			*(y+(i - st_x)*size_col+(j - st_y)) = sum;
		}
	}
	return y;
}

// with border mode = same
float* conv_single_depth_same(
	float *im,int m_row,int m_col,
	float *arr,int row,int col
	)
{
	size_t k1_size = row, k2_size = col;

	unsigned int st_x = (k1_size - 1) >> 1;
	unsigned int st_y = (k2_size - 1) >> 1;

	size_t max_imc = m_row- 1;
	size_t max_imr = m_col - 1;
	//std::vector<std::vector<float>> y(m_row, vector<float>(m_col, 0));
	float * y = (float*)malloc(m_row*m_col* sizeof(float));//cal
	size_row = m_row;
	size_col = m_col;
	for (unsigned int i = 0; i < m_row; ++i)
	{
		for (unsigned int j = 0; j < m_col; ++j)
		{
			float sum = 0;
			for (unsigned int k1 = 0; k1 <row; ++k1)
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

					sum += * (arr + (k1_size - k1 - 1)*row + k2_size - k2 - 1) *  (*(im + (i - st_x + k1)*m_row + j - st_y + k2));
						
				}
			}
		*(y+i*m_col+j)= sum;
		}
	}
	return y;
}
