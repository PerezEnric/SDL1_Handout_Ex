#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({7, 14, 60, 90});
	idle.PushBack({95, 15, 60, 89});
	idle.PushBack({184, 14, 60, 90});
	idle.PushBack({276, 11, 60, 93});
	idle.PushBack({366, 12, 60, 92});
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88});
	forward.PushBack({162, 128, 64, 92});
	forward.PushBack({259, 128, 63, 90});
	forward.PushBack({352, 128, 54, 91});
	forward.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 544,131,60,88 });
	backward.PushBack({ 628,124,64,92 });
	backward.PushBack({ 710,124,63,90 });
	backward.PushBack({ 795,124,64,91 });
	backward.PushBack({ 874,124,64,91 });
	backward.speed = 0.1f;

	//punch
	punch.PushBack({ 10,262,80,100 });
	punch.PushBack({ 100,262,110,100 });
	punch.PushBack({ 10,262,80,100 });
	punch.speed = 0.1f;

	//kick

	kick.PushBack({ 600,262,80,100 });
	kick.PushBack({ 690,262,80,100 });
	kick.PushBack({ 778,262,115,100 });
	kick.PushBack({ 690,262,80,100 });
	kick.speed = 0.1f;

	//jump

	jump.PushBack({ 10,832,80,100 });
	jump.PushBack({ 90,822,80,113});
	jump.PushBack({ 170,800,70,135 });
	jump.PushBack({ 250,790,70,145 });
	jump.PushBack({ 310,800,70,135 });
	jump.PushBack({ 390,800,70,135 });
	jump.PushBack({ 90,822,80,113 });
	jump.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_J] == 1)
		current_animation = &punch;

	if (App->input->keyboard[SDL_SCANCODE_K] == 1)
		current_animation = &kick;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		current_animation = &jump;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}