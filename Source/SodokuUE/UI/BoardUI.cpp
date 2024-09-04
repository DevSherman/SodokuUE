#include "BoardUI.h"
#include "SlotUI.h"
#include "Components/GridPanel.h"
#include "TextButtonUI.h"
#include "../Utls.h"

void UBoardUI::SetNumberToSlot(int number, int row, int column)
{
	Slots[row][column]->SetNumberValue(number);
}

int UBoardUI::GetSlotValue(int row, int column)
{
	return Slots[row][column]->GetValue();
}

void UBoardUI::SelectSlot(int row, int column)
{
	Slots[row][column]->SetColor(AlingColor);
}

void UBoardUI::NativePreConstruct()
{
	float fillAmount = 1.0f / BoardSize;
	Grid->ColumnFill.Empty();
	Grid->RowFill.Empty();

	for (size_t i = 0; i < BoardSize; i++)
	{
		Grid->ColumnFill.Add(fillAmount);
		Grid->RowFill.Add(fillAmount);
	}
	TSubclassOf<USlotUI> W_SlotUI = Utls::LoadBlueprintFromPath<UBoardUI>("'/Game/Widgets/W_SlotUI.W_SlotUI'");
	if (!W_SlotUI)
	{
		UE_LOG(LogTemp, Error, TEXT("[UBoardUI] W_SlotUI not found in -/Game/Widgets/- directory"));
		return;
	}
	for (size_t row = 0; row < BoardSize; row++)
	{
		for (size_t column = 0; column < BoardSize; column++)
		{
			USlotUI* SlotUI = CreateWidget<USlotUI>(GetWorld(), W_SlotUI);
			SlotUI->OnButtonPressed.BindUFunction(this, "OnButtonPresed");
			SlotUI->SetCoord(row, column);
			Grid->AddChildToGrid(SlotUI, row, column);

			Slots[row][column] = SlotUI;
		}
	}
	TSubclassOf<UTextButtonUI> W_TextButtonUI = Utls::LoadBlueprintFromPath<UTextButtonUI>("'/Game/Widgets/W_TextButtonUI.W_TextButtonUI'");
	
	NumberGridBox->RowFill.Empty();
	NumberGridBox->ColumnFill.Empty();
	
	NumberGridBox->ColumnFill.Add(1);
	for (size_t i = 0; i < BoardSize; i++)
	{
		UTextButtonUI* TextButtonUI = CreateWidget<UTextButtonUI>(GetWorld(), W_TextButtonUI);
		TextButtonUI->OnButtonPressed.BindUFunction(this, "OnNumberButtonPresed");
		TextButtonUI->SetNumberValue(i + 1);

		NumberGridBox->RowFill.Add(1);
		NumberGridBox->AddChildToGrid(TextButtonUI, i, 0);
	}
}

//button events
void UBoardUI::Generate() const { OnGeneratePressed.Execute(); }

void UBoardUI::OnButtonPresed(int row, int column)
{
	ClearSelection();
	for (size_t i = 0; i < 9; i++)
	{
		Slots[row][i]->SetColor(AlingColor);
		Slots[i][column]->SetColor(AlingColor);
	}
	CurrentSlotSelected = Slots[row][column];
	CurrentSlotSelected->SetColor(SelectedColor);

	OnSlotPressed.Execute(row, column);
	//UE_LOG(LogTemp, Warning, TEXT("[UBoardUI] Button (Column:%i,Row:%i) pressed."), row, column);
}

void UBoardUI::OnNumberButtonPresed(int number)
{
	if (CurrentSlotSelected)
	{
		CurrentSlotSelected->SetNumberValue(number);
	}
	//UE_LOG(LogTemp, Warning, TEXT("[UBoardUI] NumberButton %i pressed."), number);
}

void UBoardUI::ClearSelection()
{
	for (size_t row = 0; row < BoardSize; row++)
		for (size_t column = 0; column < BoardSize; column++)
			Slots[row][column]->SetColor(DefaultColor);
}
