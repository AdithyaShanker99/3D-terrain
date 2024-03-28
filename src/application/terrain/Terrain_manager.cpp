#include "Terrain_manager.h"



void HeightMap::Render(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, glm::vec3 viewer, glm::vec3 Light_position)
{
	BindVao();
	Index_data->Bind();

	shader->Bind();

	shader->Bind();

	shader->setUniformFloat("intensity", 1.0f);
	
	shader->setUniformFloat("Height", height_scale);
	
	shader->setUniformFloat3("Eye", viewer);
	
	shader->setUniformFloat3("position", Light_position);

	shader->setUniformMat4("model", model);

	shader->setUniformMat4("view", view);

	shader->setUniformMat4("projection", projection);

	for (unsigned S = 0; S < num_of_strips; S++)
	{
		Error_check(glDrawElements(GL_TRIANGLE_STRIP, Triangles_per_strip + 2,  GL_UNSIGNED_INT,  (void*)(sizeof(unsigned) * (Triangles_per_strip + 2) * S))); 
	}
}

int HeightMap::Size_of_elements(int width, int height) {
	 strip_res = 1;
	 num_of_strips = (height - 1) / strip_res;

	 Triangles_per_strip = (width / strip_res) * 2 - 2;

	return num_of_strips;
}



void HeightMap::BindVao()
{
	Error_check(glBindVertexArray(VAO));
}

