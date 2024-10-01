#include "Audio/AudioManagerSubsystem.h"
#include "Audio/MusicData.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/AudioManagerSubsystemSettings.h"

void UAudioManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UAudioManagerSubsystemSettings* AudioManagerSubsystemSettings = GetMutableDefault<UAudioManagerSubsystemSettings>();

	if (AudioManagerSubsystemSettings)
	{
		Collection.InitializeDependency(AudioManagerSubsystemSettings->AudioManagerSubsystemBlueprintClass);
	}
}

void UAudioManagerSubsystem::PlayMusic(const FString MusicID)
{
	if (CurrentMusicElement.MusicID == MusicID && CurrentMusicElement.MusicAudioComponent && CurrentMusicElement.MusicAudioComponent->IsPlaying())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("%s music is already playing. Call StopCurrentMusic first"), *MusicID));
		UE_LOG(LogTemp, Warning, TEXT("%s music is already playing. Call StopCurrentMusic first"), *MusicID);
		return;
	}
	
	if (!MusicData)
	{
		return;
	}

	const FMusicDataElement* MusicDataElement = MusicData->MusicData.Find(MusicID);

	if (!MusicDataElement || !MusicDataElement->Sound)
	{
		return;
	}
	
	if (!MusicDataElement->AudioComponent)
	{
		InitializeMusicElement(MusicID);
	}

	if (MusicDataElement->AudioComponent)
	{
		StopCurrentMusic();
		
		CurrentMusicElement.MusicID = MusicID;
		CurrentMusicElement.MusicAudioComponent = MusicDataElement->AudioComponent;

		MusicDataElement->AudioComponent->Play(MusicDataElement->MusicDataSettings.StartTime);
	}
}

void UAudioManagerSubsystem::PlayMusicCrossFaded(const FString MusicID, const FCrossFadeSettings CrossFadeSettings)
{
	if (CurrentMusicElement.MusicID == MusicID && CurrentMusicElement.MusicAudioComponent && CurrentMusicElement.MusicAudioComponent->IsPlaying())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("%s music is already playing. Call StopCurrentMusic first"), *MusicID));
		UE_LOG(LogTemp, Warning, TEXT("%s music is already playing. Call StopCurrentMusic first"), *MusicID);
		return;
	}
	
	if (!MusicData)
	{
		return;
	}

	const FMusicDataElement* MusicDataElement = MusicData->MusicData.Find(MusicID);

	if (!MusicDataElement || !MusicDataElement->Sound)
	{
		return;
	}
	
	if (!MusicDataElement->AudioComponent)
	{
		InitializeMusicElement(MusicID);
	}
	
	if (MusicDataElement->AudioComponent)
	{
		// Fade out current music
		FadeOutCurrentMusic(CrossFadeSettings.FadeOutTime, CrossFadeSettings.FadeOutVolume, CrossFadeSettings.FadeOutCurve);

		// Update current music to new music
		CurrentMusicElement.MusicID = MusicID;
		CurrentMusicElement.MusicAudioComponent = MusicDataElement->AudioComponent;
		
		// Fade in selected music
		CurrentMusicElement.MusicAudioComponent->FadeIn(CrossFadeSettings.FadeInTime, CrossFadeSettings.FadeInVolume, MusicDataElement->MusicDataSettings.StartTime, CrossFadeSettings.FadeInCurve);
	}
}

void UAudioManagerSubsystem::StopCurrentMusic(const float Delay)
{
	if (CurrentMusicElement.MusicAudioComponent && CurrentMusicElement.MusicAudioComponent->IsPlaying())
	{
		CurrentMusicElement.MusicAudioComponent->StopDelayed(Delay);
	}
}

void UAudioManagerSubsystem::FadeOutCurrentMusic(const float FadeOutTime, const float FadeOutVolume, const EAudioFaderCurve FadeOutCurve)
{
	if (CurrentMusicElement.MusicAudioComponent && CurrentMusicElement.MusicAudioComponent->IsPlaying())
	{
		CurrentMusicElement.MusicAudioComponent->FadeOut(FadeOutTime, FadeOutVolume, FadeOutCurve);
	}
}

void UAudioManagerSubsystem::InitializeMusicElement(const FString& MusicID) const
{
	if (!MusicData)
	{
		return;
	}

	FMusicDataElement* MusicDataElement = MusicData->MusicData.Find(MusicID);

	if (MusicDataElement && MusicDataElement->Sound && !MusicDataElement->AudioComponent)
	{
		const FMusicDataSettings MusicDataSettings = MusicDataElement->MusicDataSettings;
		
		MusicDataElement->AudioComponent = UGameplayStatics::CreateSound2D(
			this,
			MusicDataElement->Sound,
			MusicDataSettings.VolumeMultiplier,
			MusicDataSettings.PitchMultiplier,
			MusicDataSettings.StartTime,
			MusicDataSettings.ConcurrencySettings,
			MusicDataSettings.bPersistAcrossLevelTransition,
			MusicDataSettings.bAutoDestroy);

		MusicDataElement->AudioComponent->bIsUISound = MusicDataSettings.bIsUISound;
	}
}