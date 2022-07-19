// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestOwnersTableHUD.generated.h"

class UTOTChangeOwnerWidget;
UCLASS()
class ATestOwnersTableHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestOwnersTableHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;


#pragma region ForTest

public:
    void ShowWidget(bool Visible, AActor* InteractedActor);

    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ChangeOwnerWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UTOTChangeOwnerWidget* ChangeOwnerWidget;

#pragma endregion ForTest

};

