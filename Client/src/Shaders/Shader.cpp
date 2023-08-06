#include "Shader.h"
#include "../Miscellaneous/Log.h"

// Constructor
Shader::Shader(const std::string& shaderID, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	// Create a fresh shader program.
	program = GPU_CreateShaderProgram();

	// Load the shaders and link them.
	vertexShader = GPU_LoadShader(GPU_VERTEX_SHADER, vertexShaderPath.c_str());
	fragmentShader = GPU_LoadShader(GPU_FRAGMENT_SHADER, fragmentShaderPath.c_str());
	link = GPU_LinkShaders(vertexShader, fragmentShader);

	// Error Handling
	if (!vertexShader) Error("Failed to load vertex shader!");
	if (!fragmentShader) Error("Failed to load fragment shader!");
	if (!link) Error("Failed to link vertex and fragment shaders!");

	// Attach shaders to the shader program.
	GPU_AttachShader(program, vertexShader);
	GPU_AttachShader(program, fragmentShader);

	// Link the shader program.
	GPU_LinkShaderProgram(program);

	// Load the shader block.
	block = GPU_LoadShaderBlock(program, "gpu_Vertex", "gpu_TexCoord", NULL, "gpu_ModelViewProjectionMatrix");

	// Add default variables.
	AddVariable("tex0");
	AddVariable("tex1");
	AddVariable("globalTime");
	AddVariable("resolution");
}

// Main Functions
void Shader::SetImage(GPU_Image* _img) {
	img = _img;

	// Set some modes and apply the image to the shader.
	//GPU_SetSnapMode(img, GPU_SNAP_NONE);
	//GPU_SetWrapMode(img, GPU_WRAP_REPEAT, GPU_WRAP_REPEAT);
	GPU_SetShaderImage(img, GetVariableLocation("tex1"), 1);
}
void Shader::AddVariable(std::string variableID) {
	uint32_t location = GPU_GetUniformLocation(program, variableID.c_str());
	variables.push_back(std::make_pair(variableID, location));
}
void Shader::Activate() { GPU_ActivateShaderProgram(program, &block); }

// Utility Functions
uint32_t Shader::GetVariableLocation(std::string variableID) {
	// Brute-force check the variables vector.
	auto it = std::find_if(variables.begin(), variables.end(), 
		[variableID](std::pair<std::string, uint32_t> var) { return var.first == variableID; });
	
	// If we could find it, return the location
	if (it != variables.end())
		return it->second;

	// We could NOT find the variable so return 2^32-1
	return (Uint32)(-1);
}
