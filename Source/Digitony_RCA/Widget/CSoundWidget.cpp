#include "Widget/CSoundWidget.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UCSoundWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (SoundToggleCheckBox)
    {
        SoundToggleCheckBox->SetIsChecked(bIsSoundEnabled);
        SoundToggleCheckBox->OnCheckStateChanged.AddDynamic(this, &UCSoundWidget::OnSoundToggleChanged);
    }

    if (VolumeSlider)
    {
        VolumeSlider->SetValue(InitialVolume);
        VolumeSlider->OnValueChanged.AddDynamic(this, &UCSoundWidget::OnVolumeSliderChanged);
    }

    if (SoundCue) // Removed SoundClass check; SoundCue suffices for sound playback
    {
        AudioComponent = UGameplayStatics::SpawnSound2D(this, SoundCue);
        if (AudioComponent)
        {
            // Set initial volume based on sound toggle state
            AudioComponent->SetVolumeMultiplier(bIsSoundEnabled ? InitialVolume : 0.0f);
        }
    }
}

void UCSoundWidget::OnSoundToggleChanged(bool bIsChecked)
{
    if (AudioComponent)
    {
        if (bIsChecked)
        {
            // Ensure audio component is playing if sound is enabled
            if (!AudioComponent->IsPlaying())
            {
                AudioComponent->Play();
            }
            AudioComponent->SetVolumeMultiplier(VolumeSlider->GetValue());
        }
        else
        {
            AudioComponent->SetVolumeMultiplier(0.0f);
        }
    }
}

void UCSoundWidget::OnVolumeSliderChanged(float Value)
{
    if (AudioComponent && SoundToggleCheckBox->IsChecked())
    {
        if (!AudioComponent->IsPlaying())
        {
            AudioComponent->Play(); // Resume playback if not already playing
        }
        AudioComponent->SetVolumeMultiplier(Value);
    }
}

void UCSoundWidget::StopSound()
{
    if (AudioComponent && AudioComponent->IsPlaying())
    {
        AudioComponent->Stop();
    }
}

