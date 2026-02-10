#include <iostream>
struct VertexData
{
	float pos[3];
	float color[3];
	float texCord[2];
};

class VertexDataArray
{
	VertexData *vertices;
	int size = 0;

public:
	VertexDataArray(int size = 0)
	{
		this->size = size;
		vertices = new VertexData[size];
	}

	VertexData &operator[](int i)
	{
		return vertices[i];
	}

	float *getArray() const
	{
		float *arr = new float[8 * size];
		for (int i = 0; i < size; i++)
		{
			int ind = i * 8;
			arr[ind + 0] = vertices[i].pos[0];
			arr[ind + 1] = vertices[i].pos[1];
			arr[ind + 2] = vertices[i].pos[2];
			arr[ind + 3] = vertices[i].color[0];
			arr[ind + 4] = vertices[i].color[1];
			arr[ind + 5] = vertices[i].color[2];
			arr[ind + 6] = vertices[i].texCord[0];
			arr[ind + 7] = vertices[i].texCord[1];
		}

		return arr;
	}

	int get_size()
	{
		return size;
	}

	~VertexDataArray()
	{
		delete[] vertices;
	}
};