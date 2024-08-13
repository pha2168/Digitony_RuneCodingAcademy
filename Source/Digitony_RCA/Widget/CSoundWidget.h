#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSoundWidget.generated.h"

class UCheckBox;
class USlider;
class USoundClass;
class UAudioComponent;
class USoundCue;

UCLASS()
class DIGITONY_RCA_API UCSoundWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UCheckBox* SoundToggleCheckBox;

    UPROPERTY(meta = (BindWidget))
    USlider* VolumeSlider;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundClass* SoundClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundCue* SoundCue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float InitialVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    bool bIsSoundEnabled = true;

private:
    UPROPERTY()
    UAudioComponent* AudioComponent;

    UFUNCTION()
    void OnSoundToggleChanged(bool bIsChecked);

    UFUNCTION()
    void OnVolumeSliderChanged(float Value);
};
