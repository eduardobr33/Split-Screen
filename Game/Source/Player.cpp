#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
}

Player::~Player() {

}

bool Player::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	// NEW -> initialize players identification from XML
	id = parameters.attribute("id").as_int();

	// NEW -> initialize players input keys from XML
	if (SString(parameters.attribute("keys").as_string()) == SString("wasd")) keys = InputKeys::WASD;
	if (SString(parameters.attribute("keys").as_string()) == SString("tfgh")) keys = InputKeys::TFGH;
	if (SString(parameters.attribute("keys").as_string()) == SString("ijkl")) keys = InputKeys::IJKL;
	if (SString(parameters.attribute("keys").as_string()) == SString("arrows")) keys = InputKeys::ARROWS;

	return true;
}

bool Player::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	pbody = app->physics->CreateCircle(position.x + 16, position.y + 16, 16, bodyType::DYNAMIC);
	pbody->listener = this;
	pbody->ctype = ColliderType::PLAYER;

	return true;
}

// NEW -> Updated the Update function
bool Player::Update(float dt)
{
	// Add physics to the player and update player position using physics.

	int speed = 5;
	b2Vec2 vel = b2Vec2(0, 0);

	// Manage players movement according to active cameras, input keys and speed used.
	HandleInput(keys, vel, speed);

	// Set the velocity of the pbody of the player.
	pbody->body->SetLinearVelocity(vel);

	// Update player position in pixels.
	position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 16;
	position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 16;

	// Draw player texture.
	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

bool Player::CleanUp()
{

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}

// NEW -> manage players movement according to input keys and speed used.
void Player::HandleInput(InputKeys keys, b2Vec2& vel, int speed) {

	if (id <= app->render->cameras.Count()) { // For N cameras available, allows movement to N players.

		if (keys == InputKeys::WASD) {

			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) vel = b2Vec2(0, -speed);
			if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) vel = b2Vec2(0, speed);
			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) vel = b2Vec2(-speed, 0);
			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) vel = b2Vec2(speed, 0);

		}

		if (keys == InputKeys::TFGH) {

			if (app->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT) vel = b2Vec2(0, -speed);
			if (app->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT) vel = b2Vec2(0, speed);
			if (app->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) vel = b2Vec2(-speed, 0);
			if (app->input->GetKey(SDL_SCANCODE_H) == KEY_REPEAT) vel = b2Vec2(speed, 0);

		}

		if (keys == InputKeys::IJKL) {

			if (app->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT) vel = b2Vec2(0, -speed);
			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT) vel = b2Vec2(0, speed);
			if (app->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) vel = b2Vec2(-speed, 0);
			if (app->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) vel = b2Vec2(speed, 0);

		}

		if (keys == InputKeys::ARROWS) {

			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) vel = b2Vec2(0, -speed);
			if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) vel = b2Vec2(0, speed);
			if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) vel = b2Vec2(-speed, 0);
			if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) vel = b2Vec2(speed, 0);

		}

	}

}