// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TOTOwnerInfoRowWidget.h"
#include "TOTChangeOwnerWidget.generated.h"

class UTextBlock;
class UEditableTextBox;
class UButton;
class UDataTable;
class UVerticalBox;


UENUM()
enum EFindByType
{
    ID,
    Name,
    Sex
};

/**
 * 
 */
UCLASS()
class TESTOWNERSTABLE_API UTOTChangeOwnerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

    void SetInteractedActor(AActor* InActor) { InteractedActor = InActor; }

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* OwnerInfosVBox;

    UPROPERTY(meta = (BindWidget))
    UButton* ClearOwnerButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ChangeOwnerButton;

    UPROPERTY(meta = (BindWidget))
    UButton* CancelButton;

    UPROPERTY(meta = (BindWidget))
    UButton* FindByButton;

    UPROPERTY(meta = (BindWidget))
    UEditableTextBox* FindByTextBox;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* FindByTextBlock;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> OwnerInfoRowWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UDataTable* OwnerInfosDataTable;


    void UpdateOwnerRows(TArray<FOwnerInfo*> OwnerInfos);

    TArray<FOwnerInfo*> AllOwnerInfos;
    TArray<FOwnerInfo*> CurrentOwnerInfos;

    TEnumAsByte<EFindByType> FindByType = EFindByType::ID;

    UFUNCTION()
    void FindBy(const FText& Text);

    bool bShouldFind = false;

    UPROPERTY()
    UTOTOwnerInfoRowWidget* SelectedWidgetItem = nullptr;

    FOwnerInfo SelectedOwnerInfo;

    UPROPERTY()
    AActor* InteractedActor = nullptr;

    UFUNCTION(BlueprintCallable)
    FText GetInteractedActor() const { return (InteractedActor ? FText::FromString(InteractedActor->GetName()) : FText::FromString("None")); }

    UFUNCTION()
    void ItemSelected(UUserWidget* SelectedWidget);

    UFUNCTION()
    void ChangeFindBy();

    UFUNCTION()
    void ChangeOwner();

    UFUNCTION()
    void ClearOwner();

    UFUNCTION()
    void CloseWidget();
};
