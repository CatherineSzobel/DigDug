#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}



Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));

}

void dae::Scene::AddUI(std::shared_ptr<GameObject> object)
{
	m_UIobjects.emplace_back(object);
}

std::vector < std::shared_ptr<GameObject>> dae::Scene::MoveOverUI(Scene& level)
{

	std::vector < std::shared_ptr<GameObject>> temp;
	for (auto& object : m_UIobjects)
	{
		temp.emplace_back(object);
		level.AddUI(object);
	}
	m_UIobjects.clear();
	return temp;
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), object);
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), *it));
}

void Scene::RemoveAll()
{
	m_objects.clear();
	/*for (const auto& object : m_objects)
	{
		object->MarkForDeletion(false);
	}*/
}

void Scene::Update(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
	for (auto& object : m_UIobjects)
	{
		object->Update(deltaTime);
	}
}
void dae::Scene::FixedUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(deltaTime);
	}
	for (auto& object : m_UIobjects)
	{
		object->FixedUpdate(deltaTime);
	}
}
void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
	for (const auto& object : m_UIobjects)
	{
		object->Render();
	}
}

