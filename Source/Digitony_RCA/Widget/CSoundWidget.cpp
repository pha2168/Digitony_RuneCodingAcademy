#include "Widget/CSoundWidget.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"

void UCSoundWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 체크박스와 슬라이더의 초기 상태 설정 및 이벤트 바인딩
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

    // 초기 상태에 따른 사운드 클래스의 볼륨 설정
    if (SoundClass)
    {
        SoundClass->Properties.Volume = bIsSoundEnabled ? InitialVolume : 0.0f;
    }
}

void UCSoundWidget::OnSoundToggleChanged(bool bIsChecked)
{
    // 체크박스 상태에 따라 사운드 클래스의 볼륨을 조절
    if (SoundClass)
    {
        SoundClass->Properties.Volume = bIsChecked ? VolumeSlider->GetValue() : 0.0f;
    }
}

void UCSoundWidget::OnVolumeSliderChanged(float Value)
{
    // 슬라이더 값에 따라 사운드 클래스의 볼륨을 조절
    if (SoundClass && SoundToggleCheckBox->IsChecked())
    {
        SoundClass->Properties.Volume = Value;
    }
}