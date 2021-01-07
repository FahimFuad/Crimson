#pragma once

struct GLFWwindow;

namespace Crimson {
	class Window {
	private:
		GLFWwindow* m_window;

		int m_width, m_height;
	public:
		Window(const char* title, int w, int h);
		virtual ~Window();

		void Update();
		void Clear();
		
		bool ShouldClose();
	};
}