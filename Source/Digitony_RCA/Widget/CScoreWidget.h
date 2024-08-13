#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CScoreWidget.generated.h"

class ACMagicCircle;

UCLASS()
class DIGITONY_RCA_API UCScoreWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Score")
    FText GetCodeBlockCountText() const;

    UFUNCTION(BlueprintCallable, Category = "Score")
    void SetMagicCircle(ACMagicCircle* InMagicCircle);

private:
    UPROPERTY()
    ACMagicCircle* MagicCircle;
};
