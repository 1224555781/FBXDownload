// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MLBAssetMangeCommands.h"

#define LOCTEXT_NAMESPACE "FMLBAssetMangeModule"

void FMLBAssetMangeCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MLBAssetMange", "Execute MLBAssetMange action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
