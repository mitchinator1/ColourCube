#ifndef UI_MASTER_H
#define UI_MASTER_H
#include "UIBackground.h"
#include "../Mesh/Mesh.h"

#include <vector>

namespace UI
{
	class UIMaster
	{
	private:
		std::vector<UIBackground> m_Backgrounds;
		Mesh* m_Mesh;

	public:
		UIMaster();
		~UIMaster();

		void AddBackground(UIBackground& background);
		void CalculateMesh();

		void Bind();
		void Unbind();

		inline unsigned int GetCount() { return m_Mesh->GetCount(); }
	};
}

#endif