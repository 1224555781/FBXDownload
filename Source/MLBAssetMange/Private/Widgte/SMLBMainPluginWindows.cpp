// Fill out your copyright notice in the Description page of Project Settings.

#include "SMLBMainPluginWindows.h"
#include "SlateOptMacros.h"
#include "SBorder.h"
#include "SBoxPanel.h"
#include "SButton.h"


void SMLBMainPluginWindows::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().VAlign(VAlign_Fill).HAlign(HAlign_Fill).FillHeight(0.7)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		[
			CreateMainViewportSwitchedIndexButton(TEXT("主界面"), 0)
		]
	+ SHorizontalBox::Slot()
		[
			CreateMainViewportSwitchedIndexButton(TEXT("Config Mange"), 1)
		]
	+ SHorizontalBox::Slot()
		[
			CreateMainViewportSwitchedIndexButton(TEXT("Asset List"), 2)
		]
	+ SHorizontalBox::Slot()
		[
			CreateMainViewportSwitchedIndexButton(TEXT("详细信息"), 3)
		]
		]
		//.BorderImage()
		// Populate the widget
	];
	
}


TSharedRef<class SButton> SMLBMainPluginWindows::CreateMainViewportSwitchedIndexButton(const FString& TitleName, int32 Index)
{
	return SNew(SButton).HAlign(HAlign_Center).Text(FText::FromString(TitleName)).OnClicked_Lambda([this, Index]() {
		MainViewportSwitchedIndex = Index;
		return FReply::Handled();
	});
}
