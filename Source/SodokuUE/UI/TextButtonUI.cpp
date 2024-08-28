#include "TextButtonUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTextButtonUI::SetNumberValue(int Value)
{
	NumberValue = Value;
	Text->SetText(FText::FromString(FString::FromInt(Value)));
}

void UTextButtonUI::SetState(bool Show)
{
	Button->SetIsEnabled(Show);
}

void UTextButtonUI::NativeConstruct()
{
	Button->OnClicked.AddDynamic(this, &UTextButtonUI::OnButtonClicked);
}

void UTextButtonUI::OnButtonClicked()
{
	OnButtonPressed.Execute(NumberValue);
}
