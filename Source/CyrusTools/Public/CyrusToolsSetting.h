#pragma once
#include "CyrusToolsSetting.generated.h"

UCLASS(config = Game, defaultconfig)
class CYRUSTOOLS_API UCyrusToolsSetting : public UObject
{
	GENERATED_BODY()
public:

	/** Photo */
	UPROPERTY(config, EditAnywhere, Category = PhotoSubSystemSetting)
		FString LocalCachePath;
};
