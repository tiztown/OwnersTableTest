// Fill out your copyright notice in the Description page of Project Settings.


#include "TOTChangeOwnerWidget.h"

#include "TOTOwnerComponent.h"
#include "TOTOwnerInfoRowWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Engine/DataTable.h"


bool UTOTChangeOwnerWidget::Initialize()
{
    const bool InitResult = Super::Initialize();

    if (OwnerInfosDataTable)
    {
        OwnerInfosDataTable->GetAllRows("", AllOwnerInfos);

        CurrentOwnerInfos = AllOwnerInfos;

        UpdateOwnerRows(CurrentOwnerInfos);
    }

    if (ChangeOwnerButton)
    {
        ChangeOwnerButton->OnClicked.AddDynamic(this, & UTOTChangeOwnerWidget::ChangeOwner);
    }

    if (ClearOwnerButton)
    {
        ClearOwnerButton->OnClicked.AddDynamic(this, & UTOTChangeOwnerWidget::ClearOwner);
    }

    if (CancelButton)
    {
        CancelButton->OnClicked.AddDynamic(this, & UTOTChangeOwnerWidget::CloseWidget);
    }

    if (FindByButton)
    {
        FindByButton->OnClicked.AddDynamic(this, &UTOTChangeOwnerWidget::ChangeFindBy);
    }

    if (FindByTextBox)
    {
        FindByTextBox->OnTextChanged.AddDynamic(this, &UTOTChangeOwnerWidget::FindBy);
    }

    return InitResult;
}

void UTOTChangeOwnerWidget::UpdateOwnerRows(TArray<FOwnerInfo*> OwnerInfos)
{
    if (!OwnerInfosVBox) return;

    OwnerInfos.StableSort();

    OwnerInfosVBox->ClearChildren();

    for (auto OwnerInfo : OwnerInfos)
    {
        const auto OwnerInfoRowWidget = CreateWidget<UTOTOwnerInfoRowWidget>(GetWorld(), OwnerInfoRowWidgetClass);

        OwnerInfoRowWidget->SetOwnerInfo(*OwnerInfo);
        OwnerInfoRowWidget->BackgroundImage->SetOpacity(0);
        OwnerInfoRowWidget->OnWidgetClicked.AddDynamic(this, &UTOTChangeOwnerWidget::ItemSelected);

        OwnerInfosVBox->AddChild(OwnerInfoRowWidget);
    }
}

void UTOTChangeOwnerWidget::FindBy(const FText& Text)
{
    if (Text.IsEmptyOrWhitespace())
    {
        UpdateOwnerRows(AllOwnerInfos);
        return;
    }

    TArray<FOwnerInfo*> FoundOwnerInfo{};

    switch (FindByType)
    {
        case EFindByType::ID:
        {
            for (auto OwnerInfo : AllOwnerInfos)
            {
                FString IdText = FString::FromInt(OwnerInfo->Id);
                if (IdText.Contains(Text.ToString()))
                {
                    FoundOwnerInfo.Add(OwnerInfo);
                }
            }
            break;
        }
        case EFindByType::Name:
        {
            for (auto OwnerInfo : AllOwnerInfos)
            {
                FString IdText = OwnerInfo->Name.ToString();
                if (IdText.Contains(Text.ToString()))
                {
                    FoundOwnerInfo.Add(OwnerInfo);
                }
            }

            break;
        }
        case EFindByType::Sex:
        {
            for (auto OwnerInfo : AllOwnerInfos)
            {
                FString IdText = UEnum::GetValueAsString(OwnerInfo->Sex);
                if (IdText.Contains(Text.ToString()))
                {
                    FoundOwnerInfo.Add(OwnerInfo);
                }
            }

            break;
        }
    }

    UpdateOwnerRows(FoundOwnerInfo);
}

void UTOTChangeOwnerWidget::ItemSelected(UUserWidget* SelectedWidget)
{
    if (SelectedWidgetItem)
    {
        SelectedWidgetItem->BackgroundImage->SetOpacity(0);
    }

    if (UTOTOwnerInfoRowWidget* SelWidget = Cast<UTOTOwnerInfoRowWidget>(SelectedWidget))
    {
        SelectedWidgetItem = SelWidget;
        SelectedWidgetItem->BackgroundImage->SetOpacity(100);
        SelectedOwnerInfo = SelectedWidgetItem->GetOwnerInfo();
    }
}

void UTOTChangeOwnerWidget::ChangeFindBy()
{
    switch (FindByType)
    {
        case EFindByType::ID:
        {
            FindByType = EFindByType::Name;
            break;
        }
        case EFindByType::Name:
        {
            FindByType = EFindByType::Sex;
            break;
        }
        case EFindByType::Sex:
        {
            FindByType = EFindByType::ID;
            break;
        }
    }

    FindByTextBlock->SetText(UEnum::GetDisplayValueAsText(FindByType));

    FindBy(FindByTextBox->GetText());
}

void UTOTChangeOwnerWidget::ChangeOwner()
{
    if (!SelectedOwnerInfo.IsEmpty())
    {
        UTOTOwnerComponent* OwnerInfoComp = InteractedActor->FindComponentByClass<UTOTOwnerComponent>();
        if (OwnerInfoComp)
        {
            OwnerInfoComp->ChangeOwnerInfo(SelectedOwnerInfo.Name);
        }

        CloseWidget();
    }
}

void UTOTChangeOwnerWidget::ClearOwner()
{
    UTOTOwnerComponent* OwnerInfoComp = InteractedActor->FindComponentByClass<UTOTOwnerComponent>();
    if (OwnerInfoComp)
    {
        OwnerInfoComp->ClearOwnerInfo();
    }

    CloseWidget();
}

void UTOTChangeOwnerWidget::CloseWidget()
{
    if (GetWorld())
    {
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly());
            PlayerController->bShowMouseCursor = false;
        }
    }

    SetVisibility(ESlateVisibility::Hidden);

    if (SelectedWidgetItem)
        SelectedWidgetItem->BackgroundImage->SetOpacity(0);

    SelectedWidgetItem = nullptr;
    InteractedActor = nullptr;
}
