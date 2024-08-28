#include "PController.h"

void APController::BeginPlay()
{
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	CurrentMouseCursor = EMouseCursor::Default;
}

