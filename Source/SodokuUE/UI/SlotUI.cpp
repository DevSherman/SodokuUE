#include "SlotUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USlotUI::SetColor(FLinearColor NewColor)
{
	Button->SetBackgroundColor(NewColor);
}

void USlotUI::SetNumberValue(int Value)
{
	Number = Value;
	NumberText->SetText(FText::FromString(FString::FromInt(Number)));


	switch (Value)
	{
		case 1: Button->SetBackgroundColor(FLinearColor(0.5f,0.5f,0.5f)); break;	
		case 2: Button->SetBackgroundColor(FLinearColor(1.0f, 0.5f, 0.5f)); break;
		case 3: Button->SetBackgroundColor(FLinearColor(0.5f, 1.0f, 0.5f)); break;
		case 4: Button->SetBackgroundColor(FLinearColor(0.5f, 0.5f, 1.0f)); break;
		case 5: Button->SetBackgroundColor(FLinearColor(0.2f, 0.5f, 0.5f)); break;
		case 6: Button->SetBackgroundColor(FLinearColor(0.5f, 0.2f, 0.5f)); break;
		case 7: Button->SetBackgroundColor(FLinearColor(0.5f, 0.5f, 0.2f)); break;
		case 8: Button->SetBackgroundColor(FLinearColor(0.7f, 0.5f, 0.5f)); break;
		case 9: Button->SetBackgroundColor(FLinearColor(0.5f, 0.7f, 1.0f)); break;
		default: break;
	}

}

void USlotUI::NativeConstruct()
{
	Button->OnClicked.AddDynamic(this, &USlotUI::OnButtonClicked);
	//NumberText->SetText(FText::FromString(FString::FromInt(FMath::RandRange(0, 9))));
}

/*FReply USlotUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

FReply USlotUI::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}*/

void USlotUI::OnButtonClicked()
{
	OnButtonPressed.Execute(Row, Column);
}
