#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SodokuComponent.generated.h"

struct SCoord
{
	int Row;
	int Column;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SODOKUUE_API USodokuComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	USodokuComponent();
	UFUNCTION() void Generate();
	UFUNCTION() void ShowQuadrant(int row, int column);

protected:
	virtual void BeginPlay() override;

private:
	int GenerateRandomNumber();
	TArray<int> GenerateSuffleNumberList();
	int GenerateValidValue(int row, int column);
	bool IsValidNumberGrid(int number, int row, int column) const;
	int GetQuadrant(int row, int column);

	void GenerateValues(int fromRow, int toRow, int fromColumn, int toColumn);

private:
	class UBoardUI* UI;
	TArray<TArray<SCoord>> Quadrants;
	int iterationCount = 0;
};
