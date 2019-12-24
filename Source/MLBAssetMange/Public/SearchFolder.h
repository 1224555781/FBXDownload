// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/FbxImportUI.h"

/**
 * Ѱ����Ҫ������ļ�
 */
class MLBASSETMANGE_API SearchFolder
{
public:
	SearchFolder();
	~SearchFolder()=default;

	class IFileManager* FileManager = nullptr;

public:
	TArray<FString> FindFileWithExtension(FString FolderPath, EFBXImportType ImportType,FString Extension=TEXT("fbx"));

	FString FindSingleFile(FString BasePath,FString Name);

	

};
