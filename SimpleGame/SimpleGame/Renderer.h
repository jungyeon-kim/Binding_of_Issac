#pragma once

#include "Dependencies\glm/glm.hpp"
#include "Dependencies\glm/gtc/matrix_transform.hpp"
#include "Dependencies\glm/gtx/euler_angles.hpp"
#include "LoadPng.h"

#define MAX_TEXTURES 1000
#define MAX_PARTICLES 1000

typedef struct S_PARTICLE{
	GLuint VBO;
	GLuint VertexCount;
} S_PARTICLE;

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();

	void DrawSolidRect(Vector pos, float size, Color col, bool bShadow = false);
	void DrawSolidRect(Vector pos, Vector vol, Color col, bool bShadow = false, float depth = 0.0f);
	void DrawSolidRectBorder(Vector pos, Vector vol, Color col);
	void DrawSolidRectGauge(Vector pos, Vector rpos, Vector vol, Color col, 
		float percent, bool bShadow = false, float depth = 0.0f);
	void DrawTextureRect(Vector pos, Vector vol, Color col, 
		int textureID, bool bShadow = false, float depth = 0.0f);
	void DrawTextureRectAnim(Vector pos, Vector vol, Color col,
		int textureID, int totalX, int totalY, int currX, int currY, bool bShadow = false, float depth = 0.0f);

	void DrawGround(Vector pos, Vector vol, Color col, int textureID, float depth = 1.0f); 
	void Renderer::DrawParticle(int particleObjectID, Vector pos, float size, Color col,
		float gDirX, float gDirY, GLuint texID, float ratio, float timeInSeconds);
	void Renderer::DrawParticle(int particleObjectID, Vector pos, float size, Color col,
		float gDirX, float gDirY, GLuint texID, float ratio, float timeInSeconds, float depth);

	void SetCameraPos(float x, float y);

	int CreateParticleObject(
		int particleCount,
		float minX, float minY,
		float maxX, float maxY,
		float minSizeX, float minSizeY,
		float maxSizeX, float maxSizeY,
		float minVelX, float minVelY,
		float maxVelX, float maxVelY);

	int GenPngTexture(char* filePath, GLuint sampling = GL_NEAREST);
	int GenBmpTexture(char* filePath, GLuint sampling = GL_NEAREST);
	bool DeleteTexture(int idx, bool printLog = false);
	bool DeleteParticle(int idx, bool printLog = false);

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();

	void DrawShadow(Vector pos, Vector vol, Color col, int textureID);

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	//camera position
	glm::vec3 m_v3Camera_Position;
	//camera lookat position
	glm::vec3 m_v3Camera_Lookat;
	//camera up vector
	glm::vec3 m_v3Camera_Up;

	glm::mat4 m_m4OrthoProj;
	glm::mat4 m_m4PersProj;
	glm::mat4 m_m4Model;
	glm::mat4 m_m4View;
	glm::mat4 m_m4ProjView;

	//GL resources :: must destory before exit
	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;
	GLuint m_SOlidRectGaugeShader = 0;
	GLuint m_TextureRectShader = 0;
	GLuint m_TextureRectAnimShader = 0;
	GLuint m_ParticleShader = 0;
	int m_Textures[MAX_TEXTURES];
	S_PARTICLE m_Particles[MAX_TEXTURES];
	GLuint m_ShadowTexture = 0;
	GLuint m_VBORectBorder = 0;
};

