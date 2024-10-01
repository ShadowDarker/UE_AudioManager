#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AudioManagerSubsystemSettings.generated.h"

class UAudioManagerSubsystem;

/**
 * @class UAudioManagerSubsystemSettings
 * @brief Class that stores AudioManager settings.
 */
UCLASS(config = Game, DefaultConfig, meta = (DisplayName = "AudioManager"))
class AUDIOMANAGER_API UAudioManagerSubsystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, Meta = (BlueprintBaseOnly))
	TSubclassOf<UAudioManagerSubsystem> AudioManagerSubsystemBlueprintClass;
};