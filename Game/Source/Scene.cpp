#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	// NEW -> instantiate the players using the entity manager and add them to the players list.
	for (pugi::xml_node playerNode = config.child("player"); playerNode; playerNode = playerNode.next_sibling("player"))
	{
		Player* player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
		player->parameters = playerNode;

		players.Add(player);

	}

	if (config.child("map")) {
		//Get the map name from the config file and assigns the value in the module
		app->map->name = config.child("map").attribute("name").as_string();
		app->map->path = config.child("map").attribute("path").as_string();
	}

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// NOTE: We have to avoid the use of paths in the code, we will move it later to a config file
	//img = app->tex->Load("Assets/Textures/test.png");
	
	//Music is commented so that you can add your own music
	//app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

	//Get the size of the window
	app->win->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	app->tex->GetSize(img, texW, texH);

	textPosX = (float)windowW / 2 - (float)texW / 2;
	textPosY = (float)windowH / 2 - (float)texH / 2;

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width,
		app->map->mapData.height,
		app->map->mapData.tileWidth,
		app->map->mapData.tileHeight,
		app->map->mapData.tilesets.Count());

	// NEW -> create the necessary cameras to show the chosen DisplayType.
	// Change the DisplayType to control how many screens will be loaded.
	CreateCameras(DisplayType::FOUR_SCREENS);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// NEW -> Update the map
	app->map->Update(dt);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

// NEW -> function to create the necessary cameras to display the chosen DisplayType (Hardcoded).
void Scene::CreateCameras(DisplayType display)
{
	switch (display)
	{
	case DisplayType::ONE_SCREEN:

		app->render->AddCamera({ 0, 0, 1280, 720 });

		break;

	case DisplayType::TWO_HORIZONTAL:

		app->render->AddCamera({ 2, 2, 1276, 357 });
		app->render->AddCamera({ 2, 361, 1276, 357 });

		break;

	case DisplayType::TWO_VERTICAL:

		app->render->AddCamera({ 2, 2, 637, 716 });
		app->render->AddCamera({ 641, 2, 637, 716 });

		break;

	case DisplayType::THREE_LEFT:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 2, 361, 637, 357 });

		break;

	case DisplayType::THREE_CENTERED:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 321, 361, 637, 357 });

		break;

	case DisplayType::THREE_RIGHT:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 641, 361, 637, 357 });

		break;

	case DisplayType::FOUR_SCREENS:

		app->render->AddCamera({ 2, 2, 637, 357 });
		app->render->AddCamera({ 641, 2, 637, 357 });
		app->render->AddCamera({ 2, 361, 637, 357 });
		app->render->AddCamera({ 641, 361, 637, 357 });

		break;

	}
}