// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MLBAssetMange.h"
#include "MLBAssetMangeStyle.h"
#include "MLBAssetMangeCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "MLBAssetTypes.h"
#include "LevelEditor.h"
#include "SDockTab.h"
#include "DeclarativeSyntaxSupport.h"
#include "Widgte/SMLBMainPluginWindows.h"
#include "Widgets/SWidget.h"
#include "MLBAutoImport.h"

static const FName MLBAssetMangeTabName("MLBAssetMange");

#define LOCTEXT_NAMESPACE "FMLBAssetMangeModule"

void FMLBAssetMangeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMLBAssetMangeStyle::Initialize();
	FMLBAssetMangeStyle::ReloadTextures();

	FMLBAssetMangeCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	//绑定点击事件  稍后会在添加UI时进一步绑定
	PluginCommands->MapAction(
		FMLBAssetMangeCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMLBAssetMangeModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	/*
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMLBAssetMangeModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}*/
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMLBAssetMangeModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	//InitialMLBAssetMangeUI();


}

void FMLBAssetMangeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMLBAssetMangeStyle::Shutdown();

	FMLBAssetMangeCommands::Unregister();
}

void FMLBAssetMangeModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	//FText DialogText = FText::Format(
		//LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
		//FText::FromString(TEXT("FMLBAssetMangeModule::PluginButtonClicked()")),
		//FText::FromString(TEXT("MLBAssetMange.cpp"))
		// );
	
	//FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Clicked this plugins"));
	FGlobalTabmanager::Get()->InvokeTab(MLBAssetMangeTabName);
	UMLBAutoImport* Imports_MLB = NewObject<UMLBAutoImport>(GetTransientPackage());

	Imports_MLB->InitS();


}

void FMLBAssetMangeModule::InitialMLBAssetMangeUI()
{
	const TSharedRef<FGlobalTabmanager> TabManger=FGlobalTabmanager::Get();

	TabManger->RegisterNomadTabSpawner(MLBAssetMangeTabName, FOnSpawnTab::CreateRaw(this, &FMLBAssetMangeModule::CreateTabUI));

}

TSharedRef<SDockTab> FMLBAssetMangeModule::CreateTabUI(const FSpawnTabArgs& TabUI)
{
	return  SNew(SDockTab).TabRole(ETabRole::NomadTab)
		[
			SAssignNew(MLBMainWindow, SMLBMainPluginWindows)
		];
}

void FMLBAssetMangeModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMLBAssetMangeCommands::Get().PluginAction);
}

void FMLBAssetMangeModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMLBAssetMangeCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMLBAssetMangeModule, MLBAssetMange)