#pragma once

// #include <SDL.h>

#include "Component.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    // virtual void Draw(SDL_Renderer* renderer);
    // virtual SetTexture(SDL_Texture* texture);

    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }
protected:
    // SDL_Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
};