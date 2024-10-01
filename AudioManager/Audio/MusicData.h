#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MusicData.generated.h"

/**
 * @struct FMusicDataSettings
 * @brief Struct that contains the creation settings of a music element.
 */
USTRUCT(BlueprintType)
struct FMusicDataSettings
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	float VolumeMultiplier = 1.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	float PitchMultiplier = 1.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	float StartTime = 0.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	USoundConcurrency* ConcurrencySettings = nullptr;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	bool bPersistAcrossLevelTransition = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	bool bAutoDestroy = true;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	bool bIsUISound = false;
};

/**
 * @struct FMusicDataElement
 * @brief Struct that contains the sound data for a music element.
 */
USTRUCT(BlueprintType)
struct FMusicDataElement
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	USoundBase* Sound;

	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data Info")
	FMusicDataSettings MusicDataSettings;
};

/**
 * @class UMusicData
 * @brief Data asset that contains a list of music sounds identified by string.
 */
UCLASS(BlueprintType)
class AUDIOMANAGER_API UMusicData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music Data")
	TMap<FString, FMusicDataElement> MusicData;
};