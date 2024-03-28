#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "buffers.h"
#include <iostream>

#include "stb_image/stb_image.h"
#include "Shader.h"

#include <array>

class HeightMap
{
public:
	HeightMap(const char* FilePath, float HeightScale = 0.5f)
	{
		if (HeightScale == 0.0f)
		{
			HeightScale = 12.8f; // use 10 % height instead of creating a flat plane 
		}

		height_scale = (HeightScale / 128.0f);
		int width, height;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(FilePath, &width, &height, &NR, 0);

		unsigned bytePerPixel = NR;

		auto normals = std::vector<float>(vertices.size());

		std::array<glm::vec3, 4> normal_sett;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				unsigned char* offset = data + (j + width * i) * bytePerPixel;
				
				unsigned char y = offset[0];

				vertices.push_back((-height / 2.0f + i) / (float)height);   

				vertices.push_back(((float)(int)y * height_scale / 256.0f) );

				vertices.push_back((-width / 2.0f + j) / (float)width); 

				unsigned char* doffset = data + ( j + width * i) * bytePerPixel;
				unsigned char U = doffset[0];

				normal_sett[0] = glm::vec3((-height / 2.0f + i) / (float)height, ((float)(int)U * height_scale / 256.0f), (-width / 2.0f + j) / (float)width);

				doffset = data + (j + 1 + width * i) * bytePerPixel;
				U = doffset[0];
				normal_sett[1] = glm::vec3((-height / 2.0f + i) / (float)height, ((float)(int)U * height_scale / 256.0f), (-width / 2.0f + (j + 1)) / (float)width);
				
				doffset = data + (j + width * i + 1) * bytePerPixel;
				U = doffset[0];
				normal_sett[2] = glm::vec3((-height / 2.0f + (i + 1)) / (float)height, ((float)(int)U * height_scale / 256.0f), (-width / 2.0f + j) / (float)width);
				
				doffset = data + (j + 1 + width * (i + 1)) * bytePerPixel;
				U = doffset[0];
				normal_sett[3] = glm::vec3((-height / 2.0f + (i + 1)) / (float)height, ((float)(int)U * height_scale / 256.0f), (-width / 2.0f + (j + 1) ) / (float)width);

				glm::vec3 normal1; 
				glm::vec3 st_edge = normal_sett[2] - normal_sett[1];
				glm::vec3 st_edge2 = normal_sett[2] - normal_sett[0]; 

				normal1 = glm::normalize(glm::cross(st_edge, st_edge2));

				glm::vec3 normal2;
				glm::vec3 nd_edge = normal_sett[3] - normal_sett[2];
				glm::vec3 nd_edge2 = normal_sett[3] - normal_sett[1];

				normal2 = glm::normalize(glm::cross(nd_edge, nd_edge2));

				glm::vec3 final_normal = (normal1 + normal2) / 2.0f;

				normals.push_back(final_normal.x);
				normals.push_back(final_normal.y);
				normals.push_back(final_normal.z);
			}
		}

		strip_res = 1;
		for (unsigned i = 0; i < height - 1; i += strip_res)
		{
			for (unsigned j = 0; j < width; j += strip_res)
			{
				for (unsigned k = 0; k < 2; k++)
				{
					indices.push_back(j + width * (i + k * strip_res));
				}
			}
		}



		shader = new shaderCompilation("shaders/heightmap_vertex_shader.glsl", 
			"shaders/heightmap_fragment_shader.glsl",
			"Main_shader");

		stbi_image_free(data);

		int numElements = Size_of_elements(width, height);

		Error_check(glGenVertexArrays(1, &VAO));
		Error_check(glBindVertexArray(VAO));


		Vertex_data = new Buffer(&(vertices[0]), vertices.size() * sizeof(float));

		Index_data = new Element_buffer(&(indices[0]), indices.size() * sizeof(unsigned));

		Error_check(glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0));
		Error_check(glEnableVertexAttribArray(0));

		// Update vertex buffer with new normals
		Normal_data = new Buffer(&(normals[0]), normals.size() * sizeof(float));
		Normal_data->Bind();

		// Enable normal attribute
		Error_check(glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0));
		Error_check(glEnableVertexAttribArray(1));

		Vertex_data->Bind();

		Index_data->Bind();

	}
	~HeightMap()
	{
		delete Vertex_data;
		delete Index_data;
		delete shader;
	}


	void Render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, glm::vec3 viewer, glm::vec3 Light_position = glm::vec3(0.0f, 10.0f, 0.0f));

	void BindVao();

private:
	int NR;

	int Triangles_per_strip;

	int strip_res;

	int num_of_strips;

	float height_scale;

	unsigned int VAO;
	Buffer* Vertex_data;
	Buffer* Normal_data;

	Element_buffer* Index_data;

	shaderCompilation* shader;

	int Size_of_elements(int width, int height);

	std::vector<float> vertices;

	std::vector<unsigned> indices;

};

