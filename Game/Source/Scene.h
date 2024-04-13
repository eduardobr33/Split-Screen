#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"

// NEW -> enum class with all the display types available in this implementation.
enum class DisplayType
{
	ONE_SCREEN,
	TWO_HORIZONTAL,
	TWO_VERTICAL,
	THREE_LEFT,
	THREE_CENTERED,
	THREE_RIGHT,
	FOUR_SCREENS
};

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// NEW -> function to create the necessary cameras to display the chosen DisplayType.
	void CreateCameras(DisplayType display);

	// NEW -> Set to public to access the players list
public:
	SDL_Texture* img;
	float textPosX, textPosY = 0;
	uint texW, texH;
	uint windowW, windowH;

	// NEW -> list of players initialized with the entity manager.
	List<Player*> players;

};

#endif // __SCENE_H__