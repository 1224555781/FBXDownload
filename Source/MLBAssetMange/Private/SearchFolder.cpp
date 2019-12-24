// Fill out your copyright notice in the Description page of Project Settings.

#include "SearchFolder.h"
#include "FileManager.h"

SearchFolder::SearchFolder()
{
}



TArray<FString> SearchFolder::FindFileWithExtension(FString FolderPath, EFBXImportType ImportType, FString Extension/*=TEXT("fbx")*/)
{
	TArray<FString>Temp;
	TArray<FString>ReturnResult;
	FileManager = &IFileManager::Get();



	if (FileManager)
	{
		if (FileManager->DirectoryExists(*FolderPath))
		{
			FileManager->FindFiles(Temp, *FolderPath, *Extension);
		}
	}
	FString SingleFullPath = TEXT("");

	for (int32 i=0;i<Temp.Num();i++)
	{
		SingleFullPath = FolderPath + "/" + Temp[i];
		ReturnResult.Add(SingleFullPath);
	}


	return ReturnResult;
}

FString SearchFolder::FindSingleFile(FString BasePath, FString Name)
{

	if (IFileManager::Get().DirectoryExists(*(BasePath + Name)))
	{
		return BasePath + Name;

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The Folder has not this file"));
		ensure(false);
	}

	return BasePath + Name;
}
