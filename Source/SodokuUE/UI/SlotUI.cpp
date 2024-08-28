#include "SlotUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USlotUI::SetColor(FLinearColor NewColor)
{
	Button->SetBackgroundColor(NewColor);
}

void USlotUI::SetNumberValue(int Value)
{
	NumberText->SetText(FText::FromString(FString::FromInt(Value)));
}

void USlotUI::NativeConstruct()
{
	Button->OnClicked.AddDynamic(this, &USlotUI::OnButtonClicked);
	//NumberText->SetText(FText::FromString(FString::FromInt(FMath::RandRange(0, 9))));
}

FReply USlotUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

FReply USlotUI::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

void USlotUI::OnButtonClicked()
{
	OnButtonPressed.Execute(Row, Column);
}
