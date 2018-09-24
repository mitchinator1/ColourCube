#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "EntityPosition.h"
#include "EntityColour.h"

namespace Entity
{
	class EntityBase
	{
	public:
		Position position;
		Colour colour;

	protected:
		glm::mat4 m_ModelMatrix;

	public:
		EntityBase() noexcept
			: position({ 0.0f, 0.0f, 0.0f })
			, colour({ 0.0f, 0.0f, 0.0f, 0.0f }) {}
		virtual ~EntityBase()			{}

		virtual void HandleEvents()		{}
		virtual void Update()			{}

		virtual Colour& GetColour()		{ return colour; }
		glm::mat4& GetModelMatrix()		{ return m_ModelMatrix; }
	};
}

#endif