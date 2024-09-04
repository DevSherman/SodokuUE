#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "SlotUI.generated.h"

UCLASS()
class SODOKUUE_API USlotUI : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetCoord(int row, int column) { Row = row; Column = column; }
	void SetColor(FLinearColor NewColor);
	void SetNumberValue(int Value);
	FORCEINLINE int GetValue() const { return Number; }

	TDelegate<void(int, int)> OnButtonPressed;

protected:
	virtual void NativeConstruct() override;

protected:
	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UButton* Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UTextBlock* NumberText;

private:
	UFUNCTION() void OnButtonClicked();

private:
	int Row = -1;
	int Column = -1;
	int Number = -1;
};
