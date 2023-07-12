#include "Player.h"
#include "AnimSpriteComponent.h"
#include "Dungeon.h"

Player::Player(Dungeon* dungeon)
:Actor(dungeon)
{
    AnimSpriteComponent* asc = new AnimSpriteComponent(this);
    // std:vector<SDL_Texture*> anims = {
    //     game->GetTexture("Assets/Ship01.png"),
	// 	game->GetTexture("Assets/Ship02.png"),
	// 	game->GetTexture("Assets/Ship03.png"),
	// 	game->GetTexture("Assets/Ship04.png"),
    // }
    // asc->SetAnimTextures(anims);
}

void Player::UpdateActor()//float deltaTime
{
    Actor::UpdateActor();//deltaTime
    Vector2 pos = GetPosition();
	SetPosition(pos);
}

void Ship::ProcessKeyboard(const char state)//uint8_t*
{
    switch(state)
    {
        case 'w': y--;
        case 'a': x--;
        case 's': y++;
        case 'd': x++;
    }
	// if (state[SDL_SCANCODE_D])
	// {
	// 	mRightSpeed += 250.0f;
	// }
	// if (state[SDL_SCANCODE_A])
	// {
	// 	mRightSpeed -= 250.0f;
	// }
	// // up/down
	// if (state[SDL_SCANCODE_S])
	// {
	// 	mDownSpeed += 300.0f;
	// }
	// if (state[SDL_SCANCODE_W])
	// {
	// 	mDownSpeed -= 300.0f;
	// }
}