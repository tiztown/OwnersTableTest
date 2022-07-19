// Fill out your copyright notice in the Description page of Project Settings.


#include "TOTOwnerInfoWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"


void UTOTOwnerInfoWidget::SetOwnerInfo(const FOwnerInfo& NewOwnerInfo)
{
    if (OwnerInfo == &NewOwnerInfo) return;

    if (NewOwnerInfo.IsEmpty())
    {
        OwnerInfo.Clear();
        ShowNoOwner(true);
    }
    else
        ShowNoOwner(false);

    OwnerInfo = NewOwnerInfo;

    IDTextBlock->SetText(FText::AsNumber(NewOwnerInfo.Id));
    NameTextBlock->SetText(FText::FromName(NewOwnerInfo.Name));
    SexTextBlock->SetText(UEnum::GetDisplayValueAsText<EOwnerSex>(NewOwnerInfo.Sex.GetValue()));
    OwnerIconImage->SetBrushFromMaterial(NewOwnerInfo.Icon);
}

void UTOTOwnerInfoWidget::ShowNoOwner(const bool bShow) const
{
    if (!NoOwnerImage || !NoOwnerTextBlock)
    {
        UE_LOG(LogTemp, Error, TEXT("Not every NO OWNER objects exists in OwnerInfoWidget!"));
    }

    const ESlateVisibility NoOwnerVisibility = bShow ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

    NoOwnerTextBlock->SetVisibility(NoOwnerVisibility);
    NoOwnerImage->SetVisibility(NoOwnerVisibility);
}
