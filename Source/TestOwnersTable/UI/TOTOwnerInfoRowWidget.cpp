// Fill out your copyright notice in the Description page of Project Settings.


#include "TOTOwnerInfoRowWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

bool UTOTOwnerInfoRowWidget::Initialize()
{
    const auto InitResult = Super::Initialize();

    SelectButton->OnClicked.AddDynamic(this, &UTOTOwnerInfoRowWidget::OnClicked);

    return InitResult;
}

void UTOTOwnerInfoRowWidget::SetOwnerInfo(const FOwnerInfo& NewOwnerInfo)
{
    if (OwnerInfo == &NewOwnerInfo) return;

    OwnerInfo = NewOwnerInfo;

    IDTextBlock->SetText(FText::AsNumber(OwnerInfo.Id));
    NameTextBlock->SetText(FText::FromName(OwnerInfo.Name));
    SexTextBlock->SetText(UEnum::GetDisplayValueAsText(OwnerInfo.Sex));
    IconImage->SetBrushFromMaterial(OwnerInfo.Icon);
}

void UTOTOwnerInfoRowWidget::OnClicked()
{
    OnWidgetClicked.Broadcast(this);
}
