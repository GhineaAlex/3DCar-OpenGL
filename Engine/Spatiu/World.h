#ifndef WORLD_H_
#define WORLD_H_

#include "../Texture/Plane.h"
#include "../Texture/BmpToTexture.h"
#include "../Mate/Vector3D.h"
#include "../Mate/Vector4D.h"
#include "../Texture/Map.h"

class World {

private:
	Plane * ground;
	GLuint skybox[5]; // Skybox textures
	GLuint skyboxList;
	Vector3D *skyboxPosition;
	Map *map;

	Vector4D diffuse;
	Vector4D ambient;
	Vector4D specular;

	void initSkyboxList();

public:
	World();
	virtual ~World();
	void draw();
	void setSkyboxPosition(Vector3D *position);
	
	void renderLight();
};

#endif /* WORLD_H_ */
