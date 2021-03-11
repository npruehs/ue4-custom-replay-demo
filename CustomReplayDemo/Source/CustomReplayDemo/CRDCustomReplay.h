#pragma once

#include "CoreMinimal.h"

#include "CRDCustomReplayFrame.h"

#include "CRDCustomReplay.generated.h"

USTRUCT()
struct CUSTOMREPLAYDEMO_API FCRDCustomReplay
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TArray<FCRDCustomReplayFrame> Frames;
};
