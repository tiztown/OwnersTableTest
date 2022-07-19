// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TOTOwnerComponent.h"
#include "Blueprint/UserWidget.h"
#include "TOTOwnerInfoWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TESTOWNERSTABLE_API UTOTOwnerInfoWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetOwnerInfo(const FOwnerInfo& NewOwnerInfo);

    UFUNCTION(BlueprintCallable, Category = "UI")
    FOwnerInfo GetOwnerInfo() const { return OwnerInfo; }


protected:
    void ShowNoOwner(bool bShow) const;

    FOwnerInfo OwnerInfo{};

    UPROPERTY(Transient, meta = (BindWidget))
    UTextBlock* IDTextBlock;

    UPROPERTY(Transient, meta = (BindWidget))
    UTextBlock* NameTextBlock;

    UPROPERTY(Transient, meta = (BindWidget))
    UTextBlock* SexTextBlock;

    UPROPERTY(Transient, meta = (BindWidget))
    UImage* OwnerIconImage;

    UPROPERTY(Transient, meta = (BindWidget))
    UImage* NoOwnerImage;

    UPROPERTY(Transient, meta = (BindWidget))
    UTextBlock* NoOwnerTextBlock;
};
