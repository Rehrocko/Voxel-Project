#pragma once
#include "../Common.h"

namespace GL {
	void		Init(int width, int height);
	void		ProcessInput();
	void		SwapBuffersPollEvents();
	void		Terminate();
	bool		WindowIsOpen();
	int			GetWindowWidth();
	int			GetWindowHeight();
	int			GetCursorX();
	int			GetCursorY();
	void		DisableCursor();
	void		HideCursor();
	void		ShowCursor();
	void		ToggleCursor();
	bool		CursorIsVisible();
	void		EnableVSync();
	void		DisableVSync();
	void		ToggleVSync();
	bool		VSyncIsEnabled();
	GLFWwindow* GetWindowPtr();
	int			GetCursorScreenX();
	int			GetCursorScreenY();
	int			GetScrollOffset();
	void		SetScrollOffset(int off);
	bool		WindowHasFocus();
	bool		WindowHasNotBeenForceClosed();
	void		ForceCloseWindow();
	void		ClearScreen(glm::vec4 colorRGBA, GLbitfield mask);

	enum WindowMode { WINDOWED, FULLSCREEN };
	void CreateWindow(WindowMode windowMode);
	void SetWindowMode(WindowMode windowMode);
	void ToggleFullscreen();
}