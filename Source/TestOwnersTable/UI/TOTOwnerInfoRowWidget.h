// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TOTOwnerComponent.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TOTOwnerInfoRowWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

/**
 * Row Widget with OwnerInfo Struct
 */
UCLASS()
class TESTOWNERSTABLE_API UTOTOwnerInfoRowWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWidgetClickedSignature, UUserWidget*, ClickedWidget);

public:
    virtual bool Initialize() override;
    void SetOwnerInfo(const FOwnerInfo& NewOwnerInfo);

    FOwnerInfo GetOwnerInfo() const { return OwnerInfo; }

    UPROPERTY(meta = (BindWidget))
    UButton* SelectButton;

    UPROPERTY(meta = (BindWidget))
    UImage* BackgroundImage;

    FOnWidgetClickedSignature OnWidgetClicked;


protected:
    FOwnerInfo OwnerInfo;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* IDTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* SexTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* IconImage;
    
    UFUNCTION()
    void OnClicked();
};
