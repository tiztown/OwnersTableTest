// Fill out your copyright notice in the Description page of Project Settings.


#include "TOTOwnerInfoWidgetComponent.h"

#include "Components/BoxComponent.h"
#include "TestOwnersTable/TestOwnersTableCharacter.h"
#include "TestOwnersTable/UI/TOTOwnerInfoWidget.h"


void UTOTOwnerInfoWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    OwningWidget = Cast<UTOTOwnerInfoWidget>(GetUserWidgetObject());

    if (OwningWidget)
    {
        UTOTOwnerComponent* OwnerInfoComponent = GetOwner()->FindComponentByClass<UTOTOwnerComponent>();

        if (OwnerInfoComponent)
        {
            OwningWidget->SetOwnerInfo(OwnerInfoComponent->GetOwnerInfo());

            OwnerInfoComponent->OnOwnerInfoChanged.AddDynamic(this, &UTOTOwnerInfoWidgetComponent::SetWidgetNewOwnerInfo);
        }
    }

    UBoxComponent* BoxCollision = GetOwner()->FindComponentByClass<UBoxComponent>();

    if (BoxCollision)
    {
        BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &UTOTOwnerInfoWidgetComponent::OnBoxOverlapped);
        BoxCollision->OnComponentEndOverlap.AddDynamic(this, &UTOTOwnerInfoWidgetComponent::OnBoxEndOverlap);
    }

    SetVisibility(false);
}

void UTOTOwnerInfoWidgetComponent::SetWidgetNewOwnerInfo(const FOwnerInfo& NewOwnerInfo)
{
    if (OwningWidget)
    {
        OwningWidget->SetOwnerInfo(NewOwnerInfo);
    }
}

void UTOTOwnerInfoWidgetComponent::OnBoxOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (Cast<ATestOwnersTableCharacter>(OtherActor))
    {
        SetVisibility(true);
    }
}

void UTOTOwnerInfoWidgetComponent::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (Cast<ATestOwnersTableCharacter>(OtherActor))
    {
        SetVisibility(false);
    }
}
