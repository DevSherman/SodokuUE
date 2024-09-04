#include "SodokuComponent.h"
#include "../UI/BoardUI.h"
#include "../Utls.h"

USodokuComponent::USodokuComponent()
{
	/////////////////////////////////
	Quadrants.Add(TArray<SCoord>(
	{
		{ 0, 0 }, { 0, 1 }, { 0, 2 },
		{ 1, 0 }, { 1, 1 }, { 1, 2 },
		{ 2, 0 }, { 2, 1 }, { 2, 2 },
	}));
	Quadrants.Add(TArray<SCoord>(
	{
		{ 3, 0 }, { 3, 1 }, { 3, 2 },
		{ 4, 0 }, { 4, 1 }, { 4, 2 },
		{ 5, 0 }, { 5, 1 }, { 5, 2 },
	}));
	Quadrants.Add(TArray<SCoord>(
	{
		{ 6, 0 }, { 6, 1 }, { 6, 2 },
		{ 7, 0 }, { 7, 1 }, { 7, 2 },
		{ 8, 0 }, { 8, 1 }, { 8, 2 },
	}));
	/////////////////////////////////
	Quadrants.Add(TArray<SCoord>(
	{
		{ 0, 3 }, { 0, 4 }, { 0, 5 },
		{ 1, 3 }, { 1, 4 }, { 1, 5 },
		{ 2, 3 }, { 2, 4 }, { 2, 5 },
	}));
	Quadrants.Add(TArray<SCoord>(
	{
		{ 3, 3 }, { 3, 4 }, { 3, 5 },
		{ 4, 3 }, { 4, 4 }, { 4, 5 },
		{ 5, 3 }, { 5, 4 }, { 5, 5 },
	}));
	Quadrants.Add(TArray<SCoord>(
	{
		{ 6, 3 }, { 6, 4 }, { 6, 5 },
		{ 7, 3 }, { 7, 4 }, { 7, 5 },
		{ 8, 3 }, { 8, 4 }, { 8, 5 },
	}));
	/////////////////////////////////
	Quadrants.Add(TArray<SCoord>(
	{
		{ 0, 6 }, { 0, 7 }, { 0, 8 },
		{ 1, 6 }, { 1, 7 }, { 1, 8 },
		{ 2, 6 }, { 2, 7 }, { 2, 8 },
	}));
	Quadrants.Add(TArray<SCoord>(
	{
		{ 3, 6 }, { 3, 7 }, { 3, 8 },
		{ 4, 6 }, { 4, 7 }, { 4, 8 },
		{ 5, 6 }, { 5, 7 }, { 5, 8 },
	}));
	Quadrants.Add(TArray<SCoord>(
	{
		{ 6, 6 }, { 6, 7 }, { 6, 8 },
		{ 7, 6 }, { 7, 7 }, { 7, 8 },
		{ 8, 6 }, { 8, 7 }, { 8, 8 },
	}));
}

void USodokuComponent::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<class UBoardUI> W_BoardUI = Utls::LoadBlueprintFromPath<UBoardUI>("'/Game/Widgets/W_BoardUI.W_BoardUI'");
	UI = CreateWidget<UBoardUI>(GetWorld(), W_BoardUI);
	if (!UI) { UE_LOG(LogTemp, Error, TEXT("[USodokuComponent: %s] UI not initilizaed.")); return; }

	UI->AddToViewport();

	UI->OnGeneratePressed.BindUFunction(this, "Generate");
	UI->OnSlotPressed.BindUFunction(this, "ShowQuadrant");
	Generate();

	/*for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			UI->SetNumberToSlot(-1, Quadrants[i][j].Row, Quadrants[i][j].Column);*/
}

void USodokuComponent::Generate()
{
	UE_LOG(LogTemp, Warning, TEXT("[USodokuComponent] Generating new board."));

	//generate first quadrant
	TArray<int> suffleList = GenerateSuffleNumberList();
	for (size_t i = 0; i < 9; i++)
		UI->SetNumberToSlot(suffleList[i], Quadrants[0][i].Row, Quadrants[0][i].Column);
	
	//backtracking
	//first row
	GenerateValues(0, 3, 3, 9);
	UE_LOG(LogTemp, Warning, TEXT("First row iteration count: %i times."), iterationCount); iterationCount = 0;
	//second row
	GenerateValues(3, 6, 0, 9);
	UE_LOG(LogTemp, Warning, TEXT("Second row iteration count: %i times."), iterationCount); iterationCount = 0;
	//third row
	GenerateValues(6, 9, 0, 9);
	UE_LOG(LogTemp, Warning, TEXT("Second row iteration count: %i times."), iterationCount); iterationCount = 0;
}

void USodokuComponent::GenerateValues(int fromRow, int toRow, int fromColumn, int toColumn)
{
	bool valid = true;
	//reset
	for (size_t c = fromColumn; c < toColumn; c++)
		for (size_t r = fromRow; r < toRow; r++)
			UI->SetNumberToSlot(-1, r, c);

	for (size_t c = fromColumn; c < toColumn; c++)
	{
		for (size_t r = fromRow; r < toRow; r++)
		{
			int value = GenerateValidValue(r, c);
			UI->SetNumberToSlot(value, r, c);
			if (value != -1) UI->SetNumberToSlot(value, r, c);
			else
			{
				valid = false;
				break;
			}
		}
	}
	iterationCount++;
	if (iterationCount > 100)
	{
		//UE_DEBUG_BREAK();
		Generate();
	}

	if (!valid) GenerateValues(fromRow, toRow, fromColumn, toColumn);
}

int USodokuComponent::GenerateRandomNumber()
{
	return (int) FMath::RandRange(1, 9);
}

TArray<int> USodokuComponent::GenerateSuffleNumberList()
{
	TArray<int> NumberArray = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Utls::ShuffleArray(NumberArray);
	return NumberArray;
}

int USodokuComponent::GenerateValidValue(int row, int column)
{
	TArray<int> NumberArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	for (size_t r = 0; r < 9; r++)
	{
		int value = UI->GetSlotValue(r, column);
		if (value != -1) NumberArray.Remove(value);
	}
	for (size_t c = 0; c < 9; c++)
	{
		int value = UI->GetSlotValue(row, c);
		if (value != -1) NumberArray.Remove(value);
	}

	int q = GetQuadrant(row, column);
	if (q < 0) return - 1;

	for (size_t i = 0; i < 9; i++)
	{
		int value = UI->GetSlotValue(Quadrants[q][i].Row, Quadrants[q][i].Column);
		if (value != -1) NumberArray.Remove(value);
	}

	if (NumberArray.Num() <= 0) return -1;

	return NumberArray[FMath::RandRange(0, NumberArray.Num() - 1)];
}

bool USodokuComponent::IsValidNumberGrid(int number, int row, int column) const
{
	for (size_t r = 0; r < 9; r++)
		if (r != row && UI->GetSlotValue(r, column) == number) return false;
	for (size_t c = 0; c < 9; c++)
		if (c != column && UI->GetSlotValue(row, c) == number) return false;



	return true;			
}

int USodokuComponent::GetQuadrant(int row, int column)
{
	if (row < 3 && column < 3) return 0;
	if (row >= 3 && row < 6 && column < 3) return 1;
	if (row >= 6 && column < 3) return 2;

	if (row < 3 && column && column < 6) return 3;
	if (row >= 3 && row < 6 && column >= 3 && column < 6) return 4;
	if (row >= 6 && column >= 3 && column < 6) return 5;

	if (row < 3 && column >= 6) return 6;
	if (row >= 3 && row < 6 && column >= 6) return 7;
	if (row >= 6 && column >= 6) return 8;

	return -1;
}


void USodokuComponent::ShowQuadrant(int row, int column)
{
	int q = GetQuadrant(row, column);
	if (q < 0) return;

	for (size_t i = 0; i < 9; i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%i"), UI->GetSlotValue(Quadrants[q][i].Row, Quadrants[q][i].Column));
		UI->SelectSlot(Quadrants[q][i].Row, Quadrants[q][i].Column);
	}

}

