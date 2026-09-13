#include "Core/ALPlayerController.h"
#include "Core/ALCheatManager.h"

AALPlayerController::AALPlayerController()
{
	// Override the default cheat manager class with our custom one
	CheatClass = UALCheatManager::StaticClass();
}
