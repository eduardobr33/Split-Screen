#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"
#include "Point.h"

// NEW -> Added includes
#include "List.h"
#include "Camera.h"

#include "SDL/include/SDL.h"

class Render : public Module
{
public:

	Render();

	// Destructor
	virtual ~Render();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();

	// Drawing
	bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	// NEW -> function to create a camera according to a viewport.
	void AddCamera(SDL_Rect viewport);

	// NEW -> function to empty the cameras list.
	void ClearCameras();

	// NEW -> function to center an active camera to a player.
	void CenterCamera(ListItem<Camera*>* item, int player);

public:

	SDL_Renderer* renderer;
	SDL_Rect viewport;
	SDL_Color background;

	// NEW
	List<Camera*> cameras;
};

#endif // __RENDER_H__