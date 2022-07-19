// Fill out your copyright notice in the Description page of Project Settings.


#include "TOTOwnerComponent.h"

#include "Components/WidgetComponent.h"
#include "TestOwnersTable/UI/TOTOwnerInfoWidget.h"

// Sets default values for this component's properties
UTOTOwnerComponent::UTOTOwnerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UDataTable> OwnersInfoDataObject(TEXT("DataTable'/Game/ForTest/Data/DT_Owners.DT_Owners'"));
    if (OwnersInfoDataObject.Succeeded())
    {
        OwnerInfoRow.DataTable = OwnersInfoDataObject.Object;
    }

    bHasOwner = OwnerInfoRow.RowName.ToString() == "None" ? false : true;
}

void UTOTOwnerComponent::ChangeOwnerInfo(const FName DataRowName)
{
    if (!OwnerInfoRow.DataTable) return;

    const FOwnerInfo* NewOwnerInfo = OwnerInfoRow.DataTable->FindRow<FOwnerInfo>(DataRowName, "", true);
    if (!NewOwnerInfo || (OwnerInfo == NewOwnerInfo)) return;

    OwnerInfo = NewOwnerInfo;

    OwnerInfoRow.RowName = DataRowName;

    bHasOwner = true;

    OnOwnerInfoChanged.Broadcast(OwnerInfo);
}

void UTOTOwnerComponent::ClearOwnerInfo()
{
    if (OwnerInfoRow.RowName == "None") return;

    OwnerInfoRow.RowName = "None";
    OwnerInfo.Clear();
    bHasOwner = false;

    OnOwnerInfoChanged.Broadcast(OwnerInfo);
}

// Called when the game starts
void UTOTOwnerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (OwnerInfoRow.DataTable && OwnerInfoRow.RowName != "None")
    {
        const FOwnerInfo* NewOwnerInfo = OwnerInfoRow.DataTable->FindRow<FOwnerInfo>(OwnerInfoRow.RowName, "");
        if (NewOwnerInfo)
        {
            OwnerInfo.Icon = NewOwnerInfo->Icon;

            OwnerInfo.Id = NewOwnerInfo->Id;
            OwnerInfo.Name = NewOwnerInfo->Name;
            OwnerInfo.Sex = NewOwnerInfo->Sex;
        }
    }

    UTOTOwnerInfoWidget* Widget = Cast<UTOTOwnerInfoWidget>(GetOwner()->FindComponentByClass<UWidgetComponent>()->GetWidget());
    if (Widget)
    {
        Widget->SetOwnerInfo(OwnerInfo);
    }
}
