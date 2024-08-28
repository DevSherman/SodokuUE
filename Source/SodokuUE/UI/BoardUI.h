#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BoardUI.generated.h"

UCLASS()
class SODOKUUE_API UBoardUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UGridPanel* Grid;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) class UGridPanel* NumberGridBox;

	UPROPERTY(EditAnywhere) FLinearColor DefaultColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	UPROPERTY(EditAnywhere) FLinearColor SelectedColor = FLinearColor(0.17f, 0.25f, 1.0f, 1.0f);
	UPROPERTY(EditAnywhere) FLinearColor AlingColor = FLinearColor(0.5f, 0.5f, 1.0f, 1.0f);

private:
	UFUNCTION()	void OnButtonPresed(int row, int column);
	UFUNCTION()	void OnNumberButtonPresed(int number);
	void ClearSelection();

private:
	int BoardSize = 9;
	class USlotUI* Slots[9][9];
	USlotUI* CurrentSlotSelected;
	class UTextButton* NumberButtons[9];
};
