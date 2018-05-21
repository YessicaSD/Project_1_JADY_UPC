#include "Application.h"
#include "ModuleEnemies.h"
#include "Enemy_Pinata_Spawner.h"
#include "Enemy_Pinata.h"
#include "ModuleStage05.h"
#include "ModuleCollision.h"


Enemy_Pinata_Spawner::Enemy_Pinata_Spawner(int x, int y, POWERUP_TYPE pu_t) : Enemy(x, y, pu_t)
{
	for (uint i = 0; i < MAX_SPAWNED; ++i) {
		spawned[i] = nullptr;
	}

	fixedPos.x = x - App->stage05->spawnPos.x;
	fixedPos.y = y - App->stage05->spawnPos.y;
	//Animation-------------------------------------------
	openAnim.PushBack({ 156,62,64,19 });
	openAnim.PushBack({ 156,81,64,19 });
	openAnim.PushBack({ 156,100,64,19 });
	openAnim.PushBack({ 156,119,64,19 });
	openAnim.PushBack({ 156,138,64,19 });
	openAnim.PushBack({ 156,138,64,19 });
	openAnim.PushBack({ 156,119,64,19 });
	openAnim.PushBack({ 156,100,64,19 });
	openAnim.PushBack({ 156,81,64,19 });

	openAnim.speed = 0.1f;
	//Add collider----------------------------------------
	collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY_HEAVY, (Module*)App->enemies);

}

void Enemy_Pinata_Spawner::Move()
{
	uint i;
	//Update position-------------------------------------------
	position = App->stage05->spawnPos + fixedPos;
	collider->SetPos(position.x, position.y);


	//Enemies Spawning------------------------------------------
	currentEnemies = 0;

	for (i = 0; i < MAX_SPAWNED; ++i) {

		if (spawned[i] != nullptr && spawned[i]->isDead == true) {
			spawned[i] = nullptr;
		}
		if (spawned[i] != nullptr && spawned[i]->isDead == false) {
			currentEnemies += 1;

		}
	}

	LOG("currentEnemies : %d", currentEnemies);

	if (currentEnemies != 3) {
		spawnFrames += 1;
	}
	
	if (currentEnemies < 3 && spawnFrames > SPAWN_FRAMES - 60) {
		currentState = OPEN;
	}

	if (currentEnemies < 3  && spawnFrames > SPAWN_FRAMES) {

		for (i = 0; i < MAX_SPAWNED; ++i) {
			if (spawned[i] == nullptr) {
				spawned[i] = App->enemies->InstaSpawn(PINATA, position.x, position.y);
				break;
			}
		}

		spawnFrames = 0;
	}


}

void Enemy_Pinata_Spawner::Draw(SDL_Texture* sprites) {

	SDL_Rect currentAnim;

	switch (currentState)
	{
	case Enemy_Pinata_Spawner::IDLE:

		currentAnim = openAnim.frames[0];
		break;

	case Enemy_Pinata_Spawner::OPEN:

		if (openAnim.finished == true) {
			openAnim.Reset();
			currentState = IDLE;
			break;
		}
		currentAnim = openAnim.GetFrameEx();
		break;
	}

	App->render->Blit(sprites, position.x, position.y, &currentAnim);

}