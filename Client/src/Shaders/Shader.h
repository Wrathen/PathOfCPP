#pragma once
#include <string>
#include <vector>
#include <SDL_gpu.h>

class Shader {
public:
	// Constructor & DTor 
	Shader(const std::string& shaderID = "DefaultShader", 
		   const std::string& vertexShaderPath = "src/Shaders/DefaultVertexShader.vert", 
		   const std::string& fragmentShaderPath = "src/Shaders/DefaultFragmentShader.frag");
	~Shader() {}

	// Main Functions
	void AddVariable(std::string variableID);
	void SetImage(GPU_Image* _img);
	void Activate();
	
	// Utility Functions
	uint32_t GetVariableLocation(std::string variableID); 
	std::string GetID() { return ID; }
	
private:
	// Shader attributes and uniform locations
	GPU_ShaderBlock block;
	GPU_Image* img = nullptr;

	std::string ID;
	uint32_t vertexShader, fragmentShader, link, program;
	
	 // Array of pair (VariableID, VariableLocation)
	std::vector<std::pair<std::string, uint32_t>> variables;
};