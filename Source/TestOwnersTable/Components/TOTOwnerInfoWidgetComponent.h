// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TOTOwnerComponent.h"
#include "Components/WidgetComponent.h"
#include "TOTOwnerInfoWidgetComponent.generated.h"


class UTOTOwnerInfoWidget;
/**
 * Component Owner should have BoxCollisionComponent To Show widget.
 *
 * This is most simple way to show widget. Also we can calculate distance to player and show widget at "success" distance.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class TESTOWNERSTABLE_API UTOTOwnerInfoWidgetComponent : public UWidgetComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    // Called when TOTOwnerComponent Changes his OwnerInfo. Copies new owner info to widget. 
    UFUNCTION()
    void SetWidgetNewOwnerInfo(const FOwnerInfo& NewOwnerInfo);

protected:
    UFUNCTION()
    void OnBoxOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UPROPERTY()
    UTOTOwnerInfoWidget* OwningWidget;
};
