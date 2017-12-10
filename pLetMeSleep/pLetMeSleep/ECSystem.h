#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

//Alias
using ComponentID = std::size_t;

//This function allow to define differents ID for your components
inline ComponentID getComponentTypeID() {

	static ComponentID lastID = 0;
	return lastID++;

}

//Template -> using to tell than a function is generic
//Inline -> Function which is not define in a class
template <typename T> inline ComponentID getComponentTypeID() {

	static ComponentID typeID = getComponentTypeID();
	return typeID;

}

//Constant expression
//size_t : using for defining a size of an array
constexpr std::size_t maxComponents = 32;


//Alias bitset contains true if there is a Component at the specified index
using ComponentBitSet = std::bitset<maxComponents>;
//Alias array<Type T, size_t>
using ComponentArray = std::array<Component*, maxComponents>;

class Component {

public:

	Entity* entity;

	//Virtual because the method contains a body yet.
	virtual void init(){}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}

};

class Entity {

private:

	bool active = true;
	//unique_ptr : smart pointer that owns and manages another object through a pointer and disposes of that object when unique_ptr goes out of scope.
	//Vector of pointers of Component
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:

	void update() {
		
		//Auto : specifier than automatically deduce the type of the variable
		for (auto& c : components) c->update();

	}

	void draw(){
	
		for (auto& c : components) c->draw();
	
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const {

		return componentBitSet[getComponentTypeID<T>];

	}


	template <typename T, typename...TArgs>
	T& addComponent(TArgs&&... mArgs) {

		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;

	}

	template<typename T> T& getComponent() const {

		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);

	}

};

class Manager {

private:

	std::vector<std::unique_ptr<Entity>> entities;

public:

	void update() {

		for (auto& e : entities) e->update();

	}

	void draw() {

		for (auto& e : entities) e->draw();

	}

	void refresh() {

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity) {

			return !mEntity->isActive();

		}),
			std::end(entities));

	}

	Entity& addEntity() {

		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;

	}

};