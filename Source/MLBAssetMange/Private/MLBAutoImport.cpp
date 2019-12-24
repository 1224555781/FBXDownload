// Fill out your copyright notice in the Description page of Project Settings.

#include "MLBAutoImport.h"
#include "Factories/FbxFactory.h"

#include "Engine/StaticMesh.h"
#include "Factories/FbxImportUI.h"
#include "Factories/Factory.h"
#include "AssetImportTask.h"
#include "FbxImporter.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "ObjectTools.h"
#include "EditorReimportHandler.h"
#include "BuildPatchServices/Private/Common/StatsCollector.h"
#include "SearchFolder.h"
#include "FileHelper.h"
#include "JsonReader.h"
#include "JsonSerializerMacros.h"

UMLBAutoImport::UMLBAutoImport()
{
	Mess = "Run";
	BaseGamePKGPath = TEXT("/Game/");
	bCanPopFileName = true;
}

void UMLBAutoImport::InitS()
{
	
	
	
	TSharedPtr<SearchFolder>SearchFileManger = MakeShareable(new SearchFolder());
	ReadUserSetting();
	if (Absolute_BasePath != TEXT(""))
	{
		if (SearchFileManger)
		{
			AllFileNames = SearchFileManger->FindFileWithExtension(Absolute_BasePath, EFBXImportType::FBXIT_StaticMesh);
		}
	}



		
		if (AllFileNames.Num()>0)
		{
			UE_LOG(LogTemp, Error, TEXT("Begin Import %s"), *AllFileNames.Last());
			ImportStaticMesh_Implement(AllFileNames.Last());
		}
	}



void UMLBAutoImport::ImportStaticMesh_Implement(const FString& Path)
{

	FBXManger = NewObject<UFbxFactory>(this);
	UAssetImportTask*FBXTask = NewObject<UAssetImportTask>(this);





	//
	FBXManger->AddToRoot();
	if (FBXManger)
	{


		/*
		******************************************
		后续自动导入...
		*******************************************
		*/
		FBXManger->SetDetectImportTypeOnImport(false);
		FBXManger->ImportUI->MeshTypeToImport = FBXIT_StaticMesh;
		FBXManger->ImportUI->OriginalImportType = FBXIT_StaticMesh;
		FBXManger->ImportUI->bAutoComputeLodDistances = true;
		FBXTask->bAutomated = true;
		FBXTask->bSave = true;
		if (!FBXManger->AssetImportTask)
		{
			FBXManger->SetAssetImportTask(FBXTask);
		}




		////设置导入合成Mesh  设置参数
		//FBXManger->ImportUI->StaticMeshImportData->bCombineMeshes = MLB_ImportParam.bCombineToSingle;
		//FBXManger->ImportUI->StaticMeshImportData->ImportUniformScale = 1.f;
		//FBXManger->ImportUI->bImportMaterials = MLB_ImportParam.bImportMaterials;
		//FBXManger->ImportUI->bImportTextures = MLB_ImportParam.bImportTextures;
		//FBXManger->ImportUI->bAutoComputeLodDistances = true;
		//FBXManger->ImportUI->StaticMeshImportData->bAutoGenerateCollision = MLB_ImportParam.bAutoGenerateCollision;

		/*
		**********************************
		获取单例手动设置选项框内容
		**********************************
		*/


		UnFbx::FFbxImporter* FbxImporter = UnFbx::FFbxImporter::GetInstance();





		FbxImporter->ImportOptions->bCanShowDialog = false;
		FbxImporter->ImportOptions->bImportScene = false;
		FbxImporter->ImportOptions->bImportMaterials = false;
		//FbxImporter->ImportOptions->bImportTextures = MLB_ImportParam.bImportTextures;
		//FbxImporter->ImportOptions->bImportLOD = true;
		//FbxImporter->ImportOptions->bUsedAsFullName = false;
		FbxImporter->ImportOptions->bConvertScene = true;
		//FbxImporter->ImportOptions->bForceFrontXAxis = false;
		//FbxImporter->ImportOptions->bConvertSceneUnit = false;
		//FbxImporter->ImportOptions->bRemoveNameSpace = false;
		//FbxImporter->ImportOptions->ImportTranslation = FVector(0, 0, 0);
		//FbxImporter->ImportOptions->ImportRotation = FRotator(0, 0, 0);
		FbxImporter->ImportOptions->ImportUniformScale = 0.001f;
		//FbxImporter->ImportOptions->NormalImportMethod = EFBXNormalImportMethod::FBXNIM_ImportNormals;
		//FbxImporter->ImportOptions->NormalGenerationMethod = EFBXNormalGenerationMethod::Type::MikkTSpace;
		//FbxImporter->ImportOptions->bTransformVertexToAbsolute = false;
		//FbxImporter->ImportOptions->ImportType = EFBXImportType::FBXIT_StaticMesh;
		FbxImporter->ImportOptions->bCombineToSingle = true;
		//FbxImporter->ImportOptions->VertexColorImportOption = EVertexColorImportOption::Type::Ignore;
		////FbxImporter->ImportOptions->VertexOverrideColor = FColor::Blue;
		//FbxImporter->ImportOptions->bGenerateLightmapUVs = true;
		//FbxImporter->ImportOptions->bAutoGenerateCollision = MLB_ImportParam.bAutoGenerateCollision;
		//FbxImporter->ImportOptions->StaticMeshLODGroup = NAME_None;
		//FbxImporter->ImportOptions->bImportStaticMeshLODs = true;
		//FbxImporter->ImportOptions->bAutoComputeLodDistances = true;
		////FbxImporter->ImportOptions->BaseColorName = NAME_None;
		//FbxImporter->ImportOptions->bRemoveDegenerates = true;
		//FbxImporter->ImportOptions->bBuildAdjacencyBuffer = true;
		//FbxImporter->ImportOptions->bBuildReversedIndexBuffer = true;
		//FbxImporter->ImportOptions->bOneConvexHullPerUCX = true;
		//FbxImporter->ImportOptions->MinimumLodNumber = 0;
		//FbxImporter->ImportOptions->LodNumber = 0;
		//FbxImporter->ImportOptions->MaterialSearchLocation = EMaterialSearchLocation::Local;


		UnFbx::ApplyImportUIToImportOptions(FBXManger->ImportUI, *FbxImporter->ImportOptions);
		if (FBXManger)
		{
			//设置导入合成Mesh  设置参数
			FBXManger->ImportUI->StaticMeshImportData->bCombineMeshes = MLB_ImportParam.bCombineToSingle;
			FBXManger->ImportUI->StaticMeshImportData->ImportUniformScale = 1.f;
			FBXManger->ImportUI->bImportMaterials = MLB_ImportParam.bImportMaterials;
			FBXManger->ImportUI->bImportTextures = MLB_ImportParam.bImportTextures;
			FBXManger->ImportUI->bAutoComputeLodDistances = true;
			FBXManger->ImportUI->StaticMeshImportData->bAutoGenerateCollision = MLB_ImportParam.bAutoGenerateCollision;
		}
		if (FBXManger)
		{
			FString Paths = Path;

			//不转换无法作为参数
			FPaths::MakeStandardFilename(Paths);
			//virtual bool FactoryCanImport(const FString& Filename) override;
			if (FBXManger->FactoryCanImport(Paths))
			{
				//FBXManger->GetCurrentFilename() = bNeedImportPath;
				//FString UFactory::CurrentFilename( bNeedImportPath);
				UE_LOG(LogTemp, Error, TEXT("Can Import this file"));
			}

			FString PKGNames = BaseGamePKGPath + BasePKGPath;

			FString Name = FPaths::GetBaseFilename(Paths);



			// 获取不带扩展的名字
			int32 ExtPos = Name.Find(TEXT("/"), ESearchCase::CaseSensitive, ESearchDir::FromEnd);

			if (ExtPos != INDEX_NONE)
			{
				Name.Right(ExtPos);
			}
			PKGNames = PKGNames + "/" + Name;
			UPackage* DirectFloder = FindPackage(nullptr, *PKGNames);

			if (FEditorFileUtils::IsMapPackageAsset(PKGNames))
			{
				//The error message will be log in the import process
				ensure(false);

			}


			if (!DirectFloder && !FPackageName::DoesPackageExist(PKGNames))
			{
				DirectFloder = CreatePackage(nullptr, *PKGNames);
				//保证完全Load
				if (DirectFloder)
				{
					DirectFloder->FullyLoad();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Create DirectFloder Failed"));
				}

			}


			//DirectFloder->AddToRoot();


			//完成导入的代理  回调 开始 下一个导入
			FEditorDelegates::OnAssetPostImport.AddUFunction(this, "HandleImportComplete");

			FBXManger->ImportObject(UStaticMesh::StaticClass(), DirectFloder, *Name, EObjectFlags::RF_Transactional | EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, Path, nullptr, Canceled);


			//CombineMesh 时需要重新导入一次
			FString PkgNames = FPaths::GetBaseFilename(Paths);
			UObject* Pkg = StaticFindObject(UObject::StaticClass(), DirectFloder, *PkgNames);
			if (Pkg)
			{
				FReimportManager::Instance()->Reimport(Pkg, false, true);
			}

		}
	}
}

void UMLBAutoImport::HandleImportComplete()
{

	UE_LOG(LogTemp, Error, TEXT("Import Success %s"),*AllFileNames.Last());
	if (bCanPopFileName&&AllFileNames.Num() > 0)
	{

		
		AllFileNames.Pop();
		
		
		bCanPopFileName = false;
	


		FBXManger->RemoveFromRoot();
		FBXManger = nullptr;


		ContinueImport();
		/*FTimerHandle TimerHandle;
		if (UWorld* World=GetWorld())
		{
			World->GetTimerManager().SetTimer(TimerHandle,this, &UMLBAutoImport::ContinueImport, 1.f, false, 1.f);
		}*/
	}
}

void UMLBAutoImport::ContinueImport()
{

	UE_LOG(LogTemp, Error, TEXT("Begin Import %s"), *AllFileNames.Last());
	if (AllFileNames.Num() > 0)
	{

		ImportStaticMesh_Implement(AllFileNames.Last());
		bCanPopFileName = true;
	}
}

void UMLBAutoImport::ReadUserSetting()
{
	const FString JsonFilePath = FPaths::ProjectDir() + "/Saved/AssetManager/ImportSetting.json";
	FString ContenString;

	if (!FFileHelper::LoadFileToString(ContenString,*JsonFilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Json File Is Not Exit"));
	}

	//开始解析
	TSharedPtr<FJsonObject>UserJsonObject;

	TSharedRef< TJsonReader<> >UserJsonSetting=TJsonReaderFactory<>::Create(ContenString);

	if (!FJsonSerializer::Deserialize(UserJsonSetting, UserJsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Json File Read Failed"));
	}


	MLB_ImportParam.bAutoGenerateCollision = UserJsonObject->GetBoolField("bAutoGenerateCollision");
	MLB_ImportParam.bCombineToSingle= UserJsonObject->GetBoolField("bCombineToSingle");
	MLB_ImportParam.bImportMaterials = UserJsonObject->GetBoolField("bImportMaterials");
	MLB_ImportParam.bImportTextures = UserJsonObject->GetBoolField("bImportTextures");
	BasePKGPath = UserJsonObject->GetStringField("FileSavedFolder");
	Absolute_BasePath = UserJsonObject->GetStringField("FBXSourceFolder");

}
