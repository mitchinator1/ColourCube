#ifndef INPUT_BASE_H
#define INPUT_BASE_H
#include <memory>
#include <unordered_map>
#include <string>

namespace Entity { class EntityBase; }
struct Display;

namespace Input
{
	class InputBase
	{
	protected:
		std::shared_ptr<Display> m_Display;

	public:
		InputBase(std::shared_ptr<Display>& display);
		virtual ~InputBase();

		virtual void HandleEvents(Entity::EntityBase& entity) {}
		virtual void Update(Entity::EntityBase& entity) {}

	};
}

#endif