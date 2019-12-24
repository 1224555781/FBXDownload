// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MLBAssetMangeStyle.h"

class FMLBAssetMangeCommands : public TCommands<FMLBAssetMangeCommands>
{
public:

	FMLBAssetMangeCommands()
		: TCommands<FMLBAssetMangeCommands>(TEXT("MLBAssetMange"), NSLOCTEXT("Contexts", "MLBAssetMange", "MLBAssetMange Plugin"), NAME_None, FMLBAssetMangeStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
