#ifndef INPUT_BASE_H
#define INPUT_BASE_H
#include <memory>
#include <unordered_map>

namespace Entity { class EntityBase; }
struct Display;

namespace Input
{
	class InputBase
	{
	protected:
		std::unordered_map<std::string, std::string> m_KeyCodes;
		std::shared_ptr<Display> m_Display;

	public:
		InputBase(std::shared_ptr<Display>& display);
		virtual ~InputBase();

		virtual void HandleEvents(Entity::EntityBase& entity) {}
		virtual void Update(Entity::EntityBase& entity) {}

	protected:
		bool IsPressed(int id);
		void LoadKeyCodes(const std::string& filename);
		int GetKeyCode(const std::string& name);
		const char* GetKeyName(const unsigned int code);

	};
}

#endif