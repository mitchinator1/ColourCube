#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "EntityPosition.h"
#include "EntityColour.h"

namespace Entity
{
	class EntityBase
	{
	protected:
		Position m_Position;
		Colour m_Colour;
		glm::mat4 m_ModelMatrix;

	public:
		EntityBase() noexcept
			: m_Position({ 0.0f, 0.0f, 0.0f })
			, m_Colour({ 0.0f, 0.0f, 0.0f, 0.0f }) {}
		virtual ~EntityBase()			{}

		virtual void HandleEvents()		{}
		virtual void Update()			{}

		virtual Position& GetPosition() { return m_Position; }
		virtual Colour& GetColour()		{ return m_Colour; }
		glm::mat4& GetModelMatrix()		{ return m_ModelMatrix; }
	};
}

#endif