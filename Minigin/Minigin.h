#pragma once
#include <string>
#include <functional>
inline int g_windowWidth{ 640 };
inline int g_windowHeight{ 480 };
namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		const float m_targetFPS{ 60.f };
		const float m_fixedTimeStep{ 1.f / m_targetFPS };
	};
}