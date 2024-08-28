#include "SodokuComponent.h"
#include "../UI/BoardUI.h"
#include "../Utls.h"

USodokuComponent::USodokuComponent()
{


}

void USodokuComponent::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<class UBoardUI> W_BoardUI = Utls::LoadBlueprintFromPath<UBoardUI>("'/Game/Widgets/W_BoardUI.W_BoardUI'");
	UI = CreateWidget<UBoardUI>(GetWorld(), W_BoardUI);
	if (!UI) { UE_LOG(LogTemp, Error, TEXT("[USodokuComponent: %s] UI not initilizaed.")); return; }

	UI->AddToViewport();
}
