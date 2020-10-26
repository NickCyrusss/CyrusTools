// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CyrusTools.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "CyrusToolsSetting.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FCyrusToolsModule"

void FCyrusToolsModule::StartupModule()
{
	RegisterSettings();
}

void FCyrusToolsModule::ShutdownModule()
{
    if (UObjectInitialized())
    {
        UnRegisterSettings();
    }
}

void FCyrusToolsModule::RegisterSettings()
{
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "CyrusTools",
                                                                               LOCTEXT("RuntimeSettingsName",
                                                                                   "CyrusTools"),
                                                                               LOCTEXT("RuntimeSettingsDescription",
                                                                                   "Tool setting"),
                                                                               GetMutableDefault<UCyrusToolsSetting>());

        if (SettingsSection.IsValid())
        {
            SettingsSection->OnModified().BindRaw(this, &FCyrusToolsModule::HandleSettingSaved);
        }
    }
}

void FCyrusToolsModule::UnRegisterSettings()
{
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "CyrusTools");
    }
}

bool FCyrusToolsModule::HandleSettingSaved()
{
    UCyrusToolsSetting* Settings = GetMutableDefault<UCyrusToolsSetting>();
    Settings->SaveConfig();
    return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCyrusToolsModule, CyrusTools)
