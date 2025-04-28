// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterOverlay.h"
#include <Blaster/PlayerController/BlasterPlayerController.h>

void UCharacterOverlay::ToggleChatBox()
{
	ABlasterPlayerController* BlasterPlayerController = Cast<ABlasterPlayerController>(GetOwningPlayer());
	if (BlasterPlayerController)
	{
		if (!bChatBoxVisible)
		{
			ChatInputTextBox->OnTextCommitted.AddDynamic(this, &UCharacterOverlay::TextCommitted);
			ChatInputTextBox->SetVisibility(ESlateVisibility::Visible);
			ChatInputTextBox->SetFocus();
			BlasterPlayerController->SetInputMode(FInputModeGameAndUI());
			bChatBoxVisible = true;
		}
		else
		{
			ChatInputTextBox->OnTextCommitted.RemoveDynamic(this, &UCharacterOverlay::TextCommitted);
			
			ChatInputTextBox->SetVisibility(ESlateVisibility::Collapsed);
			BlasterPlayerController->SetInputMode(FInputModeGameOnly());
			//BlasterPlayerController->bShowMouseCursor = false;
			bChatBoxVisible = false;
		}
	}
}
//void UCharacterOverlay::TextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
//{
//	ABlasterPlayerController* BlasterPlayerController = Cast<ABlasterPlayerController>(GetOwningPlayer());
//
//	if (CommitMethod == ETextCommit::OnEnter)
//	{
//		BlasterPlayerController->Server_BroadcastMessage(GetOwningPlayerState(), Text.ToString());
//		ChatInputTextBox->SetVisibility(ESlateVisibility::Collapsed);
//		BlasterPlayerController->SetInputMode(FInputModeGameOnly());
//		bChatBoxVisible = false;
//		ChatInputTextBox->SetText(FText::FromString(""));
//		ChatInputTextBox->OnTextCommitted.RemoveDynamic(this, &UCharacterOverlay::TextCommitted);
//	}
//}

void UCharacterOverlay::TextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter && !Text.IsEmpty())
	{
		if (APlayerController* PC = GetOwningPlayer())
		{
			if (ABlasterPlayerController* BlasterPC = Cast<ABlasterPlayerController>(PC))
			{
				BlasterPC->ServerSendChatMessage(Text.ToString());
			}
		}
		ChatInputTextBox->SetText(FText::GetEmpty());
	}
}