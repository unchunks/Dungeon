#pragma once

#include <vector>

#include "SpriteComponent.h"
#include "Math.h"

class BGSpriteComponent : public SpriteComponent
{
public:
    BGSpriteComponent(class Actor* owner, int drawOrder = 10);
    void Update() override;// float deltaTime
    // void Draw(SDL_Renderer* renderer) override;
    void SetScreenSize(const Vector2& size) { mScreenSize = size; }
private:
    // struct BGTexture
    // {
        // SDL_Texture* mTexture;
        // Vector2 mOffset;
    // };
    // std::vector<BGTexture> mBGTextures;
    Vector2 mScreenSize;
}