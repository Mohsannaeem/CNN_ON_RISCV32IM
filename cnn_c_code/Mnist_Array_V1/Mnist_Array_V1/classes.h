#define _CRT_SECURE_NO_WARNINGS
#include<stddef.h>
#include<stdint.h>
#include<stdlib.h>
#include <stdio.h>
#define _CRT_SECURE_NO_DEPRECATE
#define CVECTOR_LOGARITHMIC_GROWTH


#define Q 15
#define K   (1 << (Q - 1))
#define K1   (1 << (31 - 1))


// saturate to range of int16_t
int16_t sat16(int32_t x)
{
	if (x > 0x7FFF)
		return 0x7FFF;
	else if (x < -0x8000)
		return -0x8000;
	else
		return (int16_t)x;
}


int16_t q_mul(int16_t a, int16_t b)
{
	int16_t result;
	int32_t temp;

	temp = (int32_t)a * (int32_t)b; // result type is operand's type
	return (temp >> Q);
}
int32_t q_mul1(int16_t a, int16_t b)
{
	//int16_t result;
	int32_t temp;

	temp = (int32_t)a * (int32_t)b; //0000 0000 0000 0010 1010 0010 0000
									//0000 0000 0000 0010 1010 0010 0000
									
	return temp;
}
int16_t convert32to16(int32_t temp) {
	return sat16(temp >> Q);
}
///////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////32_bit////////////////////////
//typedef int32_t fixed_point_t;
//#define FIXED_POINT_FRACTIONAL_BITS 31
inline float fixed_to_float32(int32_t input)
{
	return ((double)input / (double)(1 << 30));
}
inline int32_t float_to_fixed32(double input)
{
	return (int32_t)((input * (1 << 31)));
}

///////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////16_bit////////////////////////
typedef int16_t fixed_point_t;
//#define FIXED_POINT_FRACTIONAL_BITS 15
inline double fixed_to_float(int16_t input)
{
	return ((double)input / (double)(1 << 15));
}
inline int16_t float_to_fixed(double input)
{
	return (int16_t)((input * (1 << 15)));
}
///////////////////////////////////////////////
//////////////////////////////////////////////
/////////////////////////////////////////////



void missing_activation_impl()
{
	//cout << "Activation " << act << " not defined!" << endl;
	//cout << "Please add its implementation before use." << endl;
	exit(1);
}
// with border mode = valid
static int size_row = 0;
static int size_col = 0;
int16_t* conv_single_depth_valid(
	int16_t* im, int m_row, int m_col,
	int16_t* arr, int row, int col)
{
	int k1_size = row, k2_size = col;
	unsigned int st_x = (k1_size - 1) >> 1;
	unsigned int st_y = (k2_size - 1) >> 1;
	size_row = m_row - 2 * st_x;
	size_col = m_col - 2 * st_y;
	int16_t* y = (int16_t*)malloc(size_row * size_col * sizeof(int16_t));//ca
	for (int m = 0; m < size_row; m++) {
		for (int l = 0; l < size_col; l++) {

			*(y + m * size_col + l) = 0;
		}
	}
	for (unsigned int i = st_x; i < m_row - st_x; ++i)
	{
		for (unsigned int j = st_y; j < m_col - st_y; ++j)
		{

			int16_t sum = 0;
			for (unsigned int k1 = 0; k1 < row; ++k1)
			{
				//const int16_t * k_data = k[k1_size-k1-1].data();
				//const int16_t * im_data = im[i-st_x+k1].data();
				for (unsigned int k2 = 0; k2 < col; ++k2)
				{
					sum += *(arr + (k1_size - k1 - 1) * row + k2_size - k2 - 1) * (*(im + (i - st_x + k1) * m_row + j - st_y + k2));

				}
			}
			*(y + (i - st_x) * size_col + (j - st_y)) = sum;
		}
	}
	return y;
}

// with border mode = same
int16_t* conv_single_depth_same(
	int16_t* im, int m_row, int m_col,
	int16_t* arr, int d, int e, int row, int col, int m_depth
)
{
	size_t k1_size = row, k2_size = col;

	unsigned int st_x = (k1_size - 1) >> 1;
	unsigned int st_y = (k2_size - 1) >> 1;
	static int count = 0;
	size_t max_imc = m_row - 1;
	size_t max_imr = m_col - 1;
	int16_t* y = (int16_t*)calloc(m_row * m_col, sizeof(int16_t));//cal
	size_row = m_row;
	size_col = m_col;
	for (unsigned int i = 0; i < m_row; ++i)
	{
		for (unsigned int j = 0; j < m_col; ++j)
		{
			int32_t sum = 0;
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
					int16_t x = *(arr + (d * m_depth * row * col) + (e * row * col) + (row * (k1_size - k1 - 1)) + (k2_size - k2 - 1));//Convolution input 1x28x28
					//fprintf(fptr, "%f\n", fixed_to_float(x));
					int16_t y = (*(im + e * m_row * m_col + (i - st_x + k1) * m_row + (j - st_y + k2))); //Convolution Filter or kernal 3x3
					sum += q_mul1(*(arr + (d * m_depth * row * col) + (e * row * col) + (row * (k1_size - k1 - 1)) + (k2_size - k2 - 1)), (*(im + e * m_row * m_col + (i - st_x + k1) * m_row + (j - st_y + k2))));
					//printf("S%f\n", fixed_to_float32(sum));
				}
			}
			*(y + i * m_row + j) = convert32to16(sum); ///Convert Q2.31 to Q 1.15 (>>  To convert 15 bit to Right) 
			//printf("Y%f \n",fixed_to_float(*(y + i * m_row + j)));
		}

	}
	return y;

}
int32_t* conv_single_depth_same1(
	int16_t* im, int m_row, int m_col,
	int16_t* arr, int d, int e, int row, int col, int m_depth
)
{
	size_t k1_size = row, k2_size = col;

	unsigned int st_x = (k1_size - 1) >> 1;
	unsigned int st_y = (k2_size - 1) >> 1;
	static int count = 0;
	size_t max_imc = m_row - 1;
	size_t max_imr = m_col - 1;
	int32_t* y = (int32_t*)calloc(m_row * m_col, sizeof(int32_t));//cal
	size_row = m_row;
	size_col = m_col;
	for (unsigned int i = 0; i < m_row; ++i)
	{
		for (unsigned int j = 0; j < m_col; ++j)
		{
			int32_t sum = 0;
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
					int16_t x = *(arr + (d * m_depth * row * col) + (e * row * col) + (row * (k1_size - k1 - 1)) + (k2_size - k2 - 1));//Convolution input 1x28x28
					int16_t yy = (*(im + e * m_row * m_col + (i - st_x + k1) * m_row + (j - st_y + k2))); //Convolution Filter or kernal 3x3
					sum += q_mul1(*(arr + (d * m_depth * row * col) + (e * row * col) + (row * (k1_size - k1 - 1)) + (k2_size - k2 - 1)), (*(im + e * m_row * m_col + (i - st_x + k1) * m_row + (j - st_y + k2))));
					//printf("S %f %f %f \n", fixed_to_float32(sum),fixed_to_float(x),fixed_to_float(yy));
				}
			}
			*(y + i * m_row + j) = sum;  
			//printf("Y%f \n",fixed_to_float32(*(y + i * m_row + j)));
		}

	}
	return y;

}
