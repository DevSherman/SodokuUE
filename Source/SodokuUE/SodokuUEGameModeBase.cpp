#include "SodokuUEGameModeBase.h"
#include "Player/PlayerCamera.h"
#include "Player/PController.h"

ASodokuUEGameModeBase::ASodokuUEGameModeBase()
{
	DefaultPawnClass = APlayerCamera::StaticClass();
	PlayerControllerClass = APController::StaticClass();
}