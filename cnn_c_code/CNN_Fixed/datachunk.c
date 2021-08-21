#include "datachunk.h"

//Constructor without allocation
void DataChunk2DS_init(struct DataChunk2DS* self)
{}

//Allocation+ initialization (equillant to new DataChunk2DS)
struct DataChunk2DS* DataChunk2DS_create()
{
	struct DataChunk2DS* result = (struct DataChunk2DS*)my_malloc(sizeof(struct DataChunk2DS));
	DataChunk2DS_init(result);
	return result;
}

//Destructor without deallocation 
void DataChunk2DS_reset(struct DataChunk2DS* self)
{}

//Deallocator with deallocation (equillant to delete DataChunk2DS
void DataChunk2DS_destroy(struct DataChunk2DS* self)
{
	if (self)
	{
		DataChunk2DS_reset(self);
		///free(self);
	}
}

int16_t* Chunk2D_get_3d1(struct DataChunk2DS* self)
{
	return self->y_ret_3D; 
}

void Chunk2D_set_data1(struct DataChunk2DS* self, int16_t* y_ret, int depth, int row, int col)
{
	self->y_ret_3D = y_ret;
	self->m_dept = depth;
	self->m_row = row;
	self->m_col = col;
}

size_t Chunk2D_get_data_dim(void) 
{
	return 3;
}

int Chun2D_read_from_file1Dep(struct DataChunk2DS* self) 
{
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
return 0;
}

void chunk_showvalues(struct DataChunk2DS* self){
	for (int i = 0; i < self->m_dept; i++) {
		for (int j = 0; j < self->m_row; j++) {
			for (int k = 0; k < self->m_col; k++) {
			printf("%d   ",*(self->y_ret_3D + i * self->m_row * self->m_col + j * self->m_col + k)); 			
			}
	printf("\n j=%d\n",j);
		}
	printf("Depth\n");
	}
	
}
//Constructor without allocation
void DataChunkFlatS_init(struct DataChunkFlatS* self, int size) 
{
	self->m_size = size;
	self->f = (int16_t*)my_malloc(size * sizeof(int16_t));//call
	for (int i = 0; i < size; i++) {
		*(self->f + i) = 0;
	}
}

//Allocation+ initialization (equillant to new DataChunkFlatS)
struct DataChunkFlatS* DataChunkFlatS_create(int size) 
{
	struct DataChunkFlatS* result = (struct DataChunkFlatS*)my_malloc(sizeof(struct DataChunkFlatS));
	DataChunkFlatS_init(result, size);
	return result;
}

//Destructor without deallocation 
void DataChunkFlatS_reset(struct DataChunkFlatS* self) 
{}

//Deallocator with deallocation (equillant to delete DataChunkFlatS
void DataChunkFlatS_destroy(struct DataChunkFlatS* self) 
{
	if (self) 
	{
		DataChunkFlatS_reset(self);
//		free(self);
	}
}

int16_t* Flat_get_1d_rw(struct DataChunkFlatS* self)
{
	return self->f;
}

void Flat_set_data1(struct DataChunkFlatS* dc, int16_t* d)
{ 
	dc->f = d;
}

size_t Flat_get_data_dim(void)
{
	return 1;
}

void Flat_show_values(struct DataChunkFlatS* self)
{
	int16_t y;
	for (size_t i = 0; i < self->m_size; ++i)
	{
		y = *(self->f + i);
		printf("%d  \n", y );
	}
}
