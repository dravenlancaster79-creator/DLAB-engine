#include "Window.h"
#include <iostream>
#include <DLABUtilities/SDL_Wrappers.h>
namespace DLAB_WINDowing {

		
	void Window::CreateWindow(Uint32 flags)
	{
		m_pWindow = WindowUPtr(SDL_CreateWindow(m_sTitle.c_str(), m_Xpos, m_Ypos, m_Width, m_Height, flags));

		//checking if the window was created successfully
		if (!m_pWindow)
		{
			std::string error = SDL_GetError();
			std::cout << "ERROR failed to create window: " + error  << "\n";
		}
	}

	Window::Window(const std::string title, int width, int height, int xPos, int yPos, bool v_sync, Uint32 flags)

		: m_pWindow{ nullptr }, m_GLContext{}, m_sTitle{ title },
		m_Width{ width }, m_Height{ height }, m_Xpos{ xPos }, m_Ypos{ yPos }, m_WindowFlags{ flags }
	{
		CreateWindow(flags);

		//Enables V-Sync if requested
		if (v_sync)
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
				std::cout << "Warning: Unable to set V-Sync hint. V-Sync may not be enabled.\n";
		}
		std::cout << "WINDOW CREATED\n";
	}



	Window::~Window()
	{

	}
	void Window::SetWindowName(const std::string& name)
	{
		m_sTitle = name ;
		SDL_SetWindowTitle(m_pWindow.get(), name.c_str());
	}

}