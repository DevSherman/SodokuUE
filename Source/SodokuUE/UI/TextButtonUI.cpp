#include "TextButtonUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTextButtonUI::SetNumberValue(int Value)
{
	NumberValue = Value;
	Text->SetText(FText::FromString(FString::FromInt(Value)));
}

void UTextButtonUI::SetState(bool bShow)
{
	Button->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UTextButtonUI::NativeConstruct()
{
	Button->OnClicked.AddDynamic(this, &UTextButtonUI::OnButtonClicked);
}

void UTextButtonUI::OnButtonClicked()
{
	//UE_LOG(LogTemp, Warning, TEXT("%i"), NumberValue);
	OnButtonPressed.Execute(NumberValue);
}
