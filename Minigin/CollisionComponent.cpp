#include "CollisionComponent.h"
#include "SDL.h"
#include "Renderer.h"
dae::CollisionComponent::CollisionComponent()
	:m_OffSetVector{ 0.f,0.f }
{
	auto& currentScene = SceneManager::GetInstance().GetCurrentScene();
	SetScene(&currentScene);
}
void dae::CollisionComponent::Render()
{
	if (m_DebugOn)
	{
		DrawDebug(m_Collision.left, m_Collision.bottom, m_Collision.left + m_Collision.width, m_Collision.bottom + m_Collision.height);
	}
}

void dae::CollisionComponent::Update(float)
{
	if (m_IsMoveable && m_IsEnabled)
	{
		m_Collision.left = GetOwner()->GetLocalPosition().x + m_OffSetVector.x;
		m_Collision.bottom = GetOwner()->GetLocalPosition().y + m_OffSetVector.y;
	}
}

void dae::CollisionComponent::FixedUpdate(float)
{
}

void dae::CollisionComponent::CreateCollision(const Rectf& collision, CollisionType type, bool debug,bool moveable)
{
	m_Collision = collision;
	//m_OriginalCollisionPosition = collision;
	m_DebugOn = debug;
	m_CollisionType = type;
	m_IsMoveable = moveable;
}

void dae::CollisionComponent::CreateCollision(const Rectf& collision, glm::vec2 offSet, CollisionType type, bool debug, bool moveable)
{
	m_Collision = collision;
	m_OffSetVector = offSet;
	m_DebugOn = debug;
	m_CollisionType = type;
	m_IsMoveable = moveable;
}

void dae::CollisionComponent::CreateCollision(float left, float bottom, float width, float height, CollisionType type, bool debug)
{
	m_Collision = Rectf(left, bottom, width, height);
	m_DebugOn = debug;
	m_CollisionType = type;
}

void dae::CollisionComponent::RemoveCollision()
{
	m_Collision = Rectf{};
	m_CollisionType = None;
}

bool dae::CollisionComponent::Collide(Rectf rect2)
{
	if (m_IsEnabled)
	{
		if ((this->m_Collision.left + this->m_Collision.width) < rect2.left || (rect2.left + rect2.width) < this->m_Collision.left)
		{
			return false;
		}

		// If one rectangle is under the other
		if (this->m_Collision.bottom > (rect2.bottom + rect2.height) || rect2.bottom > (this->m_Collision.bottom + this->m_Collision.height))
		{
			return false;
		}
		return true;
	}
	return false;
}
//
//Scene& dae::CollisionComponent::GetScene()
//{
//	return 
//}

void dae::CollisionComponent::DrawDebug(float left, float bottom, float width, float height)
{

	SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), (int)left, (int)bottom, (int)left, (int)height);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), (int)left, (int)height, (int)width, (int)height);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), (int)width, (int)height, (int)width, (int)bottom);
	SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), (int)width, (int)bottom, (int)left, (int)bottom);
}

void dae::CollisionComponent::SetScene(Scene* scene)
{
	m_Scene = scene;
}
