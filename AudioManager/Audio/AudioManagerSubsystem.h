#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioManagerSubsystem.generated.h"

class UMusicData;

/**
 * @struct FMusicElement
 * @brief Struct that contains a music ID and it's AudioComponent reference
 */
USTRUCT(BlueprintType)
struct FMusicElement
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Music Element")
	FString MusicID;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Music Element")
	UAudioComponent* MusicAudioComponent;
};

/**
 * @struct FCrossFadeSettings
 * @brief Struct that contains fade-in and fade-out settings.
 */
USTRUCT(BlueprintType)
struct FCrossFadeSettings
{
	GENERATED_BODY()

	// Fade In
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrossFade Settings")
	float FadeInTime = 4.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrossFade Settings")
	float FadeInVolume = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrossFade Settings")
	EAudioFaderCurve FadeInCurve = EAudioFaderCurve::Linear;

	// Fade Out
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrossFade Settings")
	float FadeOutTime = 4.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrossFade Settings")
	float FadeOutVolume = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CrossFade Settings")
	EAudioFaderCurve FadeOutCurve = EAudioFaderCurve::Linear;
};

/**
 * @class UAudioManagerSubsystem
 * @brief Audio subsystem that handles music playing.
 */
UCLASS(Blueprintable, Abstract)
class AUDIOMANAGER_API UAudioManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
public:

	UFUNCTION(BlueprintCallable, Category = "Audio Manager")
	FORCEINLINE FMusicElement GetCurrentMusic() const { return CurrentMusicElement; }

	UFUNCTION(BlueprintCallable, Category = "Audio Manager")
	void PlayMusic(const FString MusicID);

	UFUNCTION(BlueprintCallable, Category = "Audio Manager")
	void PlayMusicCrossFaded(const FString MusicID, const FCrossFadeSettings CrossFadeSettings);

	UFUNCTION(BlueprintCallable, Category = "Audio Manager")
	void StopCurrentMusic(const float Delay = 0.f);

	UFUNCTION(BlueprintCallable, Category = "Audio Manager")
	void FadeOutCurrentMusic(const float FadeOutTime = 2.f, const float FadeOutVolume = 0.f, const EAudioFaderCurve FadeOutCurve = EAudioFaderCurve::Linear);

private:

	void InitializeMusicElement(const FString& MusicID) const;

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Music")
	UMusicData* MusicData;

private:

	FMusicElement CurrentMusicElement;
};