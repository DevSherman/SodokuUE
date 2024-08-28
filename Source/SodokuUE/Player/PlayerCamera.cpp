#include "PlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "../Components/SodokuComponent.h"
#include <Kismet/GameplayStatics.h>

APlayerCamera::APlayerCamera()
{
	RootComponent = Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SodokuComponent = CreateDefaultSubobject<USodokuComponent>(TEXT("SodokuComponent"));
}

void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

