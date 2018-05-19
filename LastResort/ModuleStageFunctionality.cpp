#include "Application.h"
#include "ModuleStageFunctionality.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "Player1.h"
#include "Player2.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePowerups.h"
#include "ModuleUnit.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStage01.h"
#include "ModuleStage02.h"
#include "ModuleStage05.h"
#include "ModuleStageClear.h"
#include "ModuleGameOver.h"
#include "ModuleNeoGeo.h"
#include "ModuleGameTitle.h"
#include "ModuleReady.h"
#include "ModuleContinue.h"
#include "ModuleUI.h"

ModuleStageFunctionality::ModuleStageFunctionality()
{

}

ModuleStageFunctionality::~ModuleStageFunctionality()
{

}

bool ModuleStageFunctionality::Start()
{

	if (App->player1->isActived == true) {
		App->player1->Enable();
	}

	if (App->player2->isActived == true) {
		App->player2->Enable();
	}
	
	//textures-----------------------------------------------------------------------
	PlayerTexture = App->textures->Load("Assets/SpaceShip_player1.png"); // arcade version		
	SpeedAnimationTex = App->textures->Load("Assets/Powerups/speed.png");
	App->ui->ShowUi();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	return true;
}

bool ModuleStageFunctionality::CleanUp()
{
	App->ui->HideUi();
	App->player1->Disable();
	App->player2->Disable();
	App->unit1->Disable();
	App->unit2->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->enemies->Disable();
	App->powerups->Disable();
	return true;
}

update_status ModuleStageFunctionality::PreUpdate()
{
	Debugging();
	return UPDATE_CONTINUE;
}

void ModuleStageFunctionality::Debugging()
{
	//SCENES-------------------------------------------------------------------------------------------------------------------------------------
	//- Select scene
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_REPEAT)
	{
		if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) { ChooseDebugElem(0, pressedNumScene, selectedScene, 1, 11); }//11 = there are currently 11 scenes in the game (although lvl 3 and lvl 4 are not implemented)
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN) { ChooseDebugElem(1, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN) { ChooseDebugElem(2, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN) { ChooseDebugElem(3, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN) { ChooseDebugElem(4, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_5] == KEY_DOWN) { ChooseDebugElem(5, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN) { ChooseDebugElem(6, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN) { ChooseDebugElem(7, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN) { ChooseDebugElem(8, pressedNumScene, selectedScene, 1, 11); }
		if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN) { ChooseDebugElem(9, pressedNumScene, selectedScene, 1, 11); }
	}
	//- Go to scene
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_UP)
	{
		GoToScene();
		pressedNumScene = false;
	}

	//CHECKPOINTS--------------------------------------------------------------------------------------------------------------------------------
	if(currentStage == App->stage05)
	{
		//- Select checkpoint
		if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_REPEAT)
		{
			if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) { ChooseDebugElem(0, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }//The number of checkpoints in level 5
			if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN) { ChooseDebugElem(1, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN) { ChooseDebugElem(2, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN) { ChooseDebugElem(3, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN) { ChooseDebugElem(4, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_5] == KEY_DOWN) { ChooseDebugElem(5, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN) { ChooseDebugElem(6, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN) { ChooseDebugElem(7, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN) { ChooseDebugElem(8, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
			if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN) { ChooseDebugElem(9, pressedNumCheckpoint, selectedCheckpoint, 0, 24); }
		}
		//- Go to checkpoint
		if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_UP)
		{
			App->stage05->cameraMovement.SetMovement(selectedCheckpoint);
			pressedNumCheckpoint = false;
		}
	}
	
	//ENEMIES------------------------------------------------------------------------------------------------------------------------------------
	//- Select enemy
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_REPEAT)
	{
		if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) { ChooseDebugElem(0, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN) { ChooseDebugElem(1, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN) { ChooseDebugElem(2, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN) { ChooseDebugElem(3, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN) { ChooseDebugElem(4, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_5] == KEY_DOWN) { ChooseDebugElem(5, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN) { ChooseDebugElem(6, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN) { ChooseDebugElem(7, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN) { ChooseDebugElem(8, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
		if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN) { ChooseDebugElem(9, pressedNumEnemy, selectedEnemy, 0, ENEMY_TYPES::MAX_ENEMY - 1); }
	}
	//- Spawn enemy
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_UP)
	{
		//if (App->player1.isDead == false)
		//{
			App->enemies->AddEnemy((ENEMY_TYPES)selectedEnemy, App->player1->position.x - App->stage05->spawnPos.x + 100, App->player1->position.y - App->stage05->spawnPos.y);//We need to substract this position because in module enemies we add it to check if it's in position
		//}
		//else
		//{
		//	App->enemies->AddEnemy((ENEMY_TYPES)selectedEnemy, App->player2->position.x + 100, App->player2->position.y);
		//}
		
		pressedNumEnemy = false;
	}

	//POWERUPS-----------------------------------------------------------------------------------------------------------------------------------
	//- Select powerup
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_REPEAT)
	{
		if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) { ChooseDebugElem(0, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_1] == KEY_DOWN) { ChooseDebugElem(1, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_2] == KEY_DOWN) { ChooseDebugElem(2, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN) { ChooseDebugElem(3, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_4] == KEY_DOWN) { ChooseDebugElem(4, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_5] == KEY_DOWN) { ChooseDebugElem(5, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN) { ChooseDebugElem(6, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN) { ChooseDebugElem(7, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN) { ChooseDebugElem(8, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
		if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN) { ChooseDebugElem(9, pressedNumPowerup, selectedPowerup, 0, POWERUP_TYPE::MAX_POWERUP - 1); }
	}
	//- Spawn powerup
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_UP)
	{
		//if(App->player1->IsEnabled())
		//{
			App->powerups->AddPowerup(App->player1->position.x + 100, App->player1->position.y, (POWERUP_TYPE)selectedPowerup);
		//}
		//else
		//{
		//	App->powerups->AddPowerup(App->player2->position.x + 100, App->player2->position.y, (POWERUP_TYPE)selectedPowerup);
		//}
		
		pressedNumPowerup = false;
	}
}

void ModuleStageFunctionality::ChooseDebugElem(int numPressed, bool &pressedNumBefore, int &selectedElem, int minimumElement, int maximumElem)
{
	//Update the selected element
	if (pressedNumBefore == false)
	{
		selectedElem = numPressed;
		pressedNumBefore = true;
	}
	else
	{
		selectedElem = selectedElem * 10 + numPressed;
	}

	//Check it isn't an element that doesn't exist
	if(selectedElem < minimumElement)
	{
		selectedElem = minimumElement;
	}

	if (selectedElem > maximumElem)
	{
		selectedElem = maximumElem;
	}
}

void ModuleStageFunctionality::GoToScene()
{
	switch (selectedScene)
	{
	case 1:
		//STAGE 1
		App->fade->FadeToBlack(currentStage, App->stage01, 0.5f);
		break;
	case 2:
		//STAGE 2
		App->fade->FadeToBlack(currentStage, App->stage02, 0.5f);
		break;
		//case 3:
		//	//STAGE 3
		//	break;
		//case 4:
		//	//STAGE 4
		//	break;
	case 5:
		//STAGE 5
		App->fade->FadeToBlack(currentStage, App->stage05, 0.5f);
		break;
	case 6:
		//WIN SCREEN
		if (App->player1->winlvl == false && App->player2->winlvl == false)
		{
			App->player1->winlvl = App->player2->winlvl = true;
			App->player1->numLvlwin = App->player2->numLvlwin = 1;
		}
		App->fade->FadeToBlack(currentStage, App->stageclearScene, 3.5f);
		App->unit1->Disable();
		App->unit2->Disable();
		currentStage = nullptr;
		break;
	case 7:
		//LOSE SCREEN
		App->fade->FadeToBlack(currentStage, App->gameoverScene, 3.5f);
		App->unit1->Disable();
		App->unit2->Disable();
		currentStage = nullptr;
		break;
	case 8:
		//NEO GEO SCREEEN
		App->fade->FadeToBlack(currentStage, App->neogeoScene, 3.5f);
		break;
	case 9:
		//LAST RESORT SCREEN
		App->fade->FadeToBlack(currentStage, App->titleScene, 3.5f);
		break;
	case 10:
		//READY SCREEN
		App->fade->FadeToBlack(currentStage, App->readyScene, 3.5f);
		break;
	case 11:
		//CONTINUE SCREEN
		App->fade->FadeToBlack(currentStage, App->continueScene, 3.5f);
		break;
	}
}