#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PController.generated.h"

UCLASS()
class SODOKUUE_API APController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
