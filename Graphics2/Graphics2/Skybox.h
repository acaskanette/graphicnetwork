#pragma once
#include "RenderObject.h"
#include <vector>
#include <string>

using namespace std;

class CubemapTexture
{
public:

	CubemapTexture(const string& Directory,
		const string& PosXFilename,
		const string& NegXFilename,
		const string& PosYFilename,
		const string& NegYFilename,
		const string& PosZFilename,
		const string& NegZFilename);

	~CubemapTexture();

	bool Load();

	void Bind(GLenum TextureUnit);

private:

	string m_fileNames[6];
	GLuint m_textureObj;
};

class Skybox :
	public RenderObject
{
public:
	Skybox();
	~Skybox();
	
	glm::vec3 lightPosition;

	GLuint skyboxVAO, skyboxVBO, skyboxProgram;

	virtual void Render(Camera* camera);
	virtual void Update();
	void LoadCubeMap(std::vector<const GLchar*> faces);

	float timeElapsed;

};

