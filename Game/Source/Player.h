#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"

// NEW
#include "Physics.h"

// NEW -> enum class to manage players input keys
enum class InputKeys {

	WASD,
	TFGH,
	IJKL,
	ARROWS

};

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();
	
	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update(float dt);

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

	// NEW -> manage players movement
	void HandleInput(InputKeys keys, b2Vec2& vel, int speed);

private:

	SDL_Texture* texture;
	const char* texturePath;
	PhysBody* pbody;

	// NEW
	int id;
	InputKeys keys;
};

#endif // __PLAYER_H__