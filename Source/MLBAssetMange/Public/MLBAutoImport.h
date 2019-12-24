// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Factories/FbxImportUI.h"
#include "MLBAutoImport.generated.h"




//只设置部分常用设置选项
USTRUCT(BlueprintType)
struct FMLB_ImportParam
{
	GENERATED_BODY()

public:
	bool bImportMaterials;
	bool bInvertNormalMap;
	bool bImportTextures;
	bool bCombineToSingle;
	bool bAutoGenerateCollision;

	FMLB_ImportParam()
	{
		bImportMaterials = true;
		bInvertNormalMap = true;
		bImportTextures = true;
		bCombineToSingle = true;
		bAutoGenerateCollision = true;
	}


};




/**
 * 
 */
UCLASS()
class MLBASSETMANGE_API UMLBAutoImport : public UObject
{
	GENERATED_BODY()
public:	
	UMLBAutoImport();

public:
	
	void InitS();
	/*
	**********
	类似递归导入
	**********
	*/
	UFUNCTION()
		void ImportStaticMesh_Implement(const FString& Path);
	UFUNCTION()
		void HandleImportComplete();
	UFUNCTION()
		void ContinueImport();
	//

	//读取json文件
	UFUNCTION()
		void ReadUserSetting();


public:

	UPROPERTY()
		TMap<FString, UObject*>AllFiles;

	UPROPERTY()
		TArray<FString>AllFileNames;


	//需要导入的文件的绝对路径
	UPROPERTY()
		FString Absolute_BasePath;

	UPROPERTY()
		FMLB_ImportParam MLB_ImportParam;

protected:
	UPROPERTY()
	class  UFbxFactory* FBXManger;
	

	//相对路径创建文件
	UPROPERTY()
		FString BasePKGPath;

	UPROPERTY(Transient)
		FString BaseGamePKGPath;

	//Param 
	UPROPERTY()
		FString Mess;




	//取消导入
	 bool&& Canceled = false;

	 bool bCanPopFileName;

};
