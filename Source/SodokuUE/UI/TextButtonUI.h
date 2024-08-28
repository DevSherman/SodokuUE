#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextButtonUI.generated.h"

UCLASS()
class UTextButtonUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetNumberValue(int Value);
	void SetState(bool Show);
	TDelegate<void(int)> OnButtonPressed;

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* Text;

private:
	UFUNCTION() void OnButtonClicked();

private:
	int NumberValue = -1;
};
