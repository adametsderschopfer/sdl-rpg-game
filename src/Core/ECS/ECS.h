#pragma once

#include "iostream"
#include "array"
#include "vector"
#include "memory"
#include "algorithm"
#include "bitset"

class Component;

class Entity;

class EntityManager;

using ComponentId = std::size_t;
using Group = std::size_t;

inline ComponentId getNewComponentTypeId() {
    static ComponentId lastId = 0u;
    return lastId++;
}

template<typename T>
inline ComponentId getComponentTypeId() noexcept {
    static_assert (std::is_base_of<Component, T>::value, "");
    static ComponentId typeID = getNewComponentTypeId();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

using ComponentArray = std::array<Component *, maxComponents>;

class Component {
public:
    Entity *entity{};

    virtual void init() {};

    virtual void update() {};

    virtual void draw() {};
};

class Entity {
public:
    explicit Entity(EntityManager &_entityManager) : m_entityManager(_entityManager) {};

    [[nodiscard]]
    bool isActive() const { return m_active; }

    void destroy() { m_active = false; }

    bool hasGroup(Group _group) {
        return m_groupBitSet[_group];
    }

    void addGroup(Group _group);

    void delGroup(Group _group) {
        m_groupBitSet[_group] = false;
    }

    template<typename T>
    [[nodiscard]] bool hasComponent() const {
        return m_componentBitSet[getComponentTypeId<T>()];
    }

    template<typename T, typename ...TArgs>
    T &addComponent(TArgs &&... mArgs) {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component>uPtr { c };
        m_components.emplace_back(std::move(uPtr));

        m_componentArray[getComponentTypeId<T>()] = c;
        m_componentBitSet[getComponentTypeId<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T>
    T &getComponent() const {
        Component *pComponent(m_componentArray[getComponentTypeId<T>()]);
        return *static_cast<T *>(pComponent);
    }

    void update() {
        for (const auto &c: m_components) c->update();
    };

    void draw() {
        for (const auto &c: m_components) c->draw();
    }

private:
    bool m_active = true;
    std::vector<std::unique_ptr<Component>> m_components;

    EntityManager &m_entityManager;

    ComponentArray m_componentArray{};

    ComponentBitSet m_componentBitSet;
    GroupBitSet m_groupBitSet;
};

class EntityManager {
public:
    void update() {
        for (const auto &e: m_entities) e->update();
    }

    void draw() {
        for (const auto &e: m_entities) e->draw();
    }

    void refresh() {
        for (unsigned int i(0u); i < maxGroups; i++) {
            auto &v(m_groupedEntities[i]);
            v.erase(
                    std::remove_if(
                            std::begin(v),
                            std::end(v),
                            [i](Entity *_entity) {
                                return !_entity->isActive() || !_entity->hasGroup(i);
                            }
                    ),
                    std::end(v)
            );
        }

        m_entities.erase(
                std::remove_if(
                        std::begin(m_entities),
                        std::end(m_entities),
                        [](const std::unique_ptr<Entity> &m_Entity) {
                            return !m_Entity->isActive();
                        }
                ),
                std::end(m_entities)
        );
    }

    void addToGroup(Entity* _entity, Group _group) {
        m_groupedEntities[_group].emplace_back(_entity);
    }

    std::vector<Entity *> &getGroup(Group _group) {
        return m_groupedEntities[_group];
    }

    Entity &addEntity() {
        auto e = new Entity(*this);
        std::unique_ptr<Entity> pE{e};
        m_entities.emplace_back(std::move(pE));
        return *e;
    }

private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    std::array<std::vector<Entity *>, maxGroups> m_groupedEntities;
};


