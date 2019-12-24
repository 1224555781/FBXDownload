// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Factories/FbxImportUI.h"
#include "MLBAutoImport.generated.h"




//ֻ���ò��ֳ�������ѡ��
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
	���Ƶݹ鵼��
	**********
	*/
	UFUNCTION()
		void ImportStaticMesh_Implement(const FString& Path);
	UFUNCTION()
		void HandleImportComplete();
	UFUNCTION()
		void ContinueImport();
	//

	//��ȡjson�ļ�
	UFUNCTION()
		void ReadUserSetting();


public:

	UPROPERTY()
		TMap<FString, UObject*>AllFiles;

	UPROPERTY()
		TArray<FString>AllFileNames;


	//��Ҫ������ļ��ľ���·��
	UPROPERTY()
		FString Absolute_BasePath;

	UPROPERTY()
		FMLB_ImportParam MLB_ImportParam;

protected:
	UPROPERTY()
	class  UFbxFactory* FBXManger;
	

	//���·�������ļ�
	UPROPERTY()
		FString BasePKGPath;

	UPROPERTY(Transient)
		FString BaseGamePKGPath;

	//Param 
	UPROPERTY()
		FString Mess;




	//ȡ������
	 bool&& Canceled = false;

	 bool bCanPopFileName;

};
