#include "./Collision.h"

#include "./ECS/ColliderComponent.h"

bool Collision::AABB(const SDL_FRect &rectA, const SDL_FRect &rectB) {
    return SDL_HasRectIntersectionFloat(&rectA, &rectB);
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB) {
    if (AABB(colA.getCollider(), colB.getCollider())) {
        return true;
    }

    return false;
}
