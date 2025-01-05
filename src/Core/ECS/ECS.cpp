#include "ECS.h"

void Entity::addGroup(Group _group) {
    m_groupBitSet[_group] = true;
    m_entityManager.addToGroup(this, _group);
}