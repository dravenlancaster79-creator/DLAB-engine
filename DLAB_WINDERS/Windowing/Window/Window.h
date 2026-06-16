#pragma once
#include <SDL.h>
#include <DLABUtilities/SDL_Wrappers.h>
#include<string>
namespace DLAB_WINDowing {
	class Window {
	private:
		WindowUPtr m_pWindow;
		SDL_GLContext m_GLContext;
		std::string m_sTitle;
		int m_Width, m_Height, m_Xpos, m_Ypos;
		Uint32 m_WindowFlags;

	private:
		void CreateWindow(Uint32 flags);

	public:
		Window()
			: Window("default_window", 640, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true, NULL)
		{
		}


		Window(const std::string title, int width, int height, int xPos, int yPos, bool v_sync = true,
			Uint32 flags = (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE));
		~Window();


		inline void SetGLContext(SDL_GLContext gl_context) { m_GLContext = gl_context; }
		inline SDL_GLContext& GetGLContext() { return m_GLContext; }
		inline WindowUPtr& GetWindow() { return m_pWindow; }
		inline std::string GetWindowName() const { return m_sTitle; }
		inline const int GetXpos() const { return m_Xpos; }
		inline const int GetXpos(int x_pos) const { return x_pos; }
		inline const int GetYpos() const { return m_Ypos; }
		inline const int GetYpos(int y_pos) const { return y_pos; }

		inline const int GetWidth() const { return m_Width; }
		inline const int GetHeight() const { return m_Height; }


		void SetWindowName(const std::string& name);

	};

}