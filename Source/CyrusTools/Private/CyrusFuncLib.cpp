// Fill out your copyright notice in the Description page of Project Settings.


#include "CyrusFuncLib.h"

//#include "DesktopPlatformModule.h"
#include "Blueprint/UserWidget.h"
#include "Misc/Paths.h"
#include "Windows/WindowsPlatformProcess.h"
#include "Widgets/SWindow.h"
#include "Framework/Application/SlateApplication.h"

//FString UCyrusFuncLib::SelectFileOnDisk()
//{
//    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
//    if (DesktopPlatform)
//    {
//        TArray<FString> OpenFilenames;
//        DesktopPlatform->OpenFileDialog(
//            nullptr,
//            TEXT("OpenFile"),
//            FString(TEXT("")),
//            TEXT(""),
//            TEXT("All Files (*.*)"),
//            EFileDialogFlags::None,
//            OpenFilenames
//        );
//
//        if (OpenFilenames.Num() > 0)
//        {
//            return FPaths::ConvertRelativePathToFull(OpenFilenames[0]);
//        }
//    }
//    return TEXT("");
//}

void UCyrusFuncLib::CreateWindow(FText inWindowTitle, UUserWidget* inWidget, FVector2D inSize)
{
	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(inWindowTitle)
		.SizingRule(ESizingRule::UserSized)
		.ClientSize(inSize)
		.AutoCenter(EAutoCenter::PreferredWorkArea)
		.ScreenPosition(FVector2D(0, 0))
		.IsEnabled(true)
		.SupportsMinimize(true)
		.SupportsMaximize(true);

	Window->SetContent
	(
		inWidget->TakeWidget()
	);

	TSharedPtr<SWindow> TopWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
	if (TopWindow.IsValid())
	{
		//Add as Native
		FSlateApplication::Get().AddWindowAsNativeChild(Window, TopWindow.ToSharedRef(), true);
	}
	else
	{

		//Default in case no top window
		FSlateApplication::Get().AddWindow(Window);
	}
	CreationWindow = Window;

}

TSharedPtr<SWindow> UCyrusFuncLib::CreationWindow = nullptr;
void UCyrusFuncLib::DestroyWindow()
{
	if (CreationWindow)
		CreationWindow->RequestDestroyWindow();
}

void UCyrusFuncLib::CreateProcess(FString fileName)
{
	if (!FPaths::FileExists(fileName))
	{
		UE_LOG(LogTemp, Error, TEXT("%s is not exist!"), *fileName);
		return;
	}
	FPlatformProcess::LaunchFileInDefaultExternalApplication(*fileName);
}
