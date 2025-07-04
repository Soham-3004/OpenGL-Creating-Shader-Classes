#ifndef SHADER_H
#define SHADER_H
#include<glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>

class Shader {
public:
	unsigned int ID;	//program ID
	Shader(const char* vertexPath, const char* fragmentPath);	// constructor reads and builds the shader
	void use();	// use/activate the shader
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif // !SHADER_H

