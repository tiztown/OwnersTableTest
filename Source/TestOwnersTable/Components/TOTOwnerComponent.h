// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "TOTOwnerComponent.generated.h"

UENUM()
enum EOwnerSex
{
    None,
    Male,
    Female,
    AttackHelicopter
};

USTRUCT(BlueprintType)
struct FOwnerInfo : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Id = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name = "Name_None";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<EOwnerSex> Sex = EOwnerSex::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = ( ToolTip = "Select from MI_Icon_(1-8)"))
    UMaterialInstance* Icon = nullptr;

    bool operator==(const FOwnerInfo* Other) const
    {
        return (this->Id == Other->Id && this->Name == Other->Name && this->Sex == Other->Sex && this->Icon == Other->Icon);
    }

    void operator=(const FOwnerInfo* Other)
    {
        this->Id = Other->Id;
        this->Name = Other->Name;
        this->Sex = Other->Sex;
        this->Icon = Other->Icon;
    }

    bool operator<(const FOwnerInfo& Other) const
    {
        return this->Sex < Other.Sex;
    }

    bool IsEmpty() const
    {
        return (Id == -1 || Name == "Name_None" || Sex == EOwnerSex::None || !Icon);
    }

    void Clear()
    {
        Id = -1;
        Name = "Name_None";
        Sex = EOwnerSex::None;
        Icon = nullptr;
    }
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOwnerInfoChangedSignature, const FOwnerInfo&, NewOwnerInfo);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),
    HideCategories = ("Variable", "Transform", "Sockets", "Shape", "Navigation", "ComponentTick", "Physics", "Tags", "Cooking", "HLOD",
        "Mobile", "Activation", "Component Replication", "Events", "Asset User Data", "Collision", "Rendering", "Input", "Actor", "LOD"))
class TESTOWNERSTABLE_API UTOTOwnerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTOTOwnerComponent();

    UFUNCTION(BlueprintCallable, Category = "UI")
    FOwnerInfo GetOwnerInfo() const { return OwnerInfo; }

    void ChangeOwnerInfo(const FName DataRowName);

    void ClearOwnerInfo();

    bool HasOwner() const { return bHasOwner && !OwnerInfoRow.IsNull() && OwnerInfoRow.RowName != "None"; }
    
    FOnOwnerInfoChangedSignature OnOwnerInfoChanged;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditInstanceOnly, Category = "OwnerInfo", meta = (DisplayName = "CurrentOwner", ToolTip = "Select owner from Data Table"))
    FDataTableRowHandle OwnerInfoRow;

private:
    bool bHasOwner = false;

    FOwnerInfo OwnerInfo;
};
