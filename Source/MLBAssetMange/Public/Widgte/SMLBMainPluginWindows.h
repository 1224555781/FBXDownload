// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MLBASSETMANGE_API SMLBMainPluginWindows : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMLBMainPluginWindows)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TSharedRef<class SButton> CreateMainViewportSwitchedIndexButton(const FString& TitleName,int32 Index);


public:

	int32 MainViewportSwitchedIndex;
};
