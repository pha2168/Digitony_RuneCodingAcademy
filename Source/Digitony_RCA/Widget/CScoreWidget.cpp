#include "CScoreWidget.h"
#include "MagicClicle/CMagicCircle.h"
#include "Components/TextBlock.h"

FText UCScoreWidget::GetCodeBlockCountText() const
{
    if (MagicCircle)
    {
        int32 CodeBlockCount = MagicCircle->CodeBlocks.Num();
        return FText::AsNumber(CodeBlockCount);
    }
    return FText::FromString(TEXT("0"));
}

void UCScoreWidget::SetMagicCircle(ACMagicCircle* InMagicCircle)
{
    MagicCircle = InMagicCircle;
}
