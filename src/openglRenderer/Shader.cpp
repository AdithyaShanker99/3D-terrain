#include "Shader.h"
#include <fstream>
#include <sstream>
#include "error.h"

std::string load_shader_from_file(const char* path)
{
	std::ifstream input;

	input.open(path);

	if (input.fail())
	{
		std::cerr << " error  shader not open \n " + std::string(path) << std::endl;
	}

	std::string result;
	std::string line;

	while (getline(input, line))
	{
		result += line; 	result += "\n";
	}

	return result;
}


	shaderCompilation::shaderCompilation(const char* vertex_filepath, const char* fragment_filepath, const char* name)
	{
		auto vertex = load_shader_from_file(vertex_filepath);	auto fragment = load_shader_from_file(fragment_filepath);

		unsigned int program = glCreateProgram();

		Error_check(unsigned shader_obj = glCreateShader(GL_VERTEX_SHADER));
		const char* src = vertex.c_str();
		Error_check(glShaderSource(shader_obj, 1, &src, nullptr));
		Error_check(glCompileShader(shader_obj));
		
		int status = 0;
		Error_check(glad_glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &status));

		if (status == GL_FALSE)
		{
			int length;
			Error_check(glad_glGetShaderiv(shader_obj, GL_INFO_LOG_LENGTH, &length));

			char* message = (char*)alloca(sizeof(char) * length);
			Error_check(glad_glGetShaderInfoLog(shader_obj, length, &length, message));

			std::cout << m_name + " error -> " << "[vertex shader error: ]"  << message << std::endl;
		}

		unsigned int m_vs = shader_obj;

		shader_obj = 0;
		src = nullptr;
		Error_check(shader_obj = glCreateShader(GL_FRAGMENT_SHADER));
		src = fragment.c_str();
		Error_check(glShaderSource(shader_obj, 1, &src, nullptr));
		Error_check(glCompileShader(shader_obj));

		status = 0;
		Error_check(glad_glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &status));

		if (status == GL_FALSE)
		{
			int length;
			Error_check(glad_glGetShaderiv(shader_obj, GL_INFO_LOG_LENGTH, &length));

			char* message = (char*)alloca(sizeof(char) * length);
			Error_check(glad_glGetShaderInfoLog(shader_obj, length, &length, message));

			std::cout << m_name + " error -> " << "[Fragment shader error: ]"  << message << std::endl;
		}

		unsigned int m_fs = shader_obj;

		Error_check(glAttachShader(program, m_vs));
		Error_check(glAttachShader(program, m_fs));

		Error_check(glLinkProgram(program));

		
		Error_check(glValidateProgram(program));

		object_ID_ = program;
	}


	shaderCompilation::~shaderCompilation()
	{

	}

	void shaderCompilation::Bind()const 
	{
		Error_check(glUseProgram(object_ID_));
	}

	void shaderCompilation::Unbind()const
	{
		Error_check(glUseProgram(0));
	}

	void shaderCompilation::setUniformMat4(const char* name, const glm::mat4 data, unsigned int count)
	{
		Error_check(glUniformMatrix4fv(getUniformLocation(name), (int)count, GL_FALSE, &( data[0][0]) ));
	}

	void shaderCompilation::setUniformFloat3(const char* name, const glm::vec3& data, unsigned int count)
	{
		Bind();
		Error_check(glUniform3fv(getUniformLocation(name), (int)count, &data[0]));
	}



	void shaderCompilation::setUniformInt(const char* name, int r_data, unsigned int count)
	{
		Bind();
		Error_check(glUniform1iv(getUniformLocation(name), (int)count, &r_data));
	}


	void shaderCompilation::setUniformFloat(const char* name, float data)
	{
		Error_check(glUniform1f(getUniformLocation(name), data));
	}




	int shaderCompilation::getUniformLocation(const char* name)
	{
		if (uniform_Locations_cache.find(name) != uniform_Locations_cache.end())
		{
			return  uniform_Locations_cache[name];
		}

		Error_check(int location = glGetUniformLocation(object_ID_, name));
		std::cout << (location < 0 || location == -1? name : "") << (location < 0 ? " is not a valid uniform" : "") << std::endl;
		uniform_Locations_cache[name] = location;
		return location;
	}

