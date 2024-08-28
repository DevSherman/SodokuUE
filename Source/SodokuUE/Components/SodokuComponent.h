#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SodokuComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SODOKUUE_API USodokuComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	USodokuComponent();

protected:
	virtual void BeginPlay() override;

private:
	class UBoardUI* UI;
};
