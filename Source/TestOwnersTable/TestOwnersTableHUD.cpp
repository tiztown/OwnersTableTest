// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestOwnersTableHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "CanvasItem.h"
#include "Blueprint/UserWidget.h"
#include "UI/TOTChangeOwnerWidget.h"
#include "UObject/ConstructorHelpers.h"

ATestOwnersTableHUD::ATestOwnersTableHUD()
{
    // Set the crosshair texture
    static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
    CrosshairTex = CrosshairTexObj.Object;
}


void ATestOwnersTableHUD::DrawHUD()
{
    Super::DrawHUD();

    // Draw very simple crosshair

    // find center of the Canvas
    const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

    // offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
    const FVector2D CrosshairDrawPosition((Center.X),
        (Center.Y + 20.0f));

    // draw the crosshair
    FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
    TileItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem(TileItem);
}

void ATestOwnersTableHUD::BeginPlay()
{
    Super::BeginPlay();

    // ForTest

    
    ChangeOwnerWidget = CreateWidget<UTOTChangeOwnerWidget>(GetWorld(), ChangeOwnerWidgetClass);

    if (ChangeOwnerWidget)
    {
        ChangeOwnerWidget->AddToViewport();
        ChangeOwnerWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ATestOwnersTableHUD::ShowWidget(bool Visible, AActor* InteractedActor)
{
    if (!ChangeOwnerWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Widget!"));
        return;
    }

    if (GetWorld())
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeUIOnly());
            PlayerController->bShowMouseCursor = true;
        }
    }

    ChangeOwnerWidget->SetInteractedActor(InteractedActor);
    ChangeOwnerWidget->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
