#include "GameWindow.h"

GameWindow::GameWindow(void)
{
}

GameWindow* GameWindow::getInstance()
{
	if (gameWindow == 0)
    {
        gameWindow = new GameWindow();
    }

    return gameWindow;
}

/* Null, because instance will be initialized on demand. */
GameWindow* GameWindow::gameWindow = 0;