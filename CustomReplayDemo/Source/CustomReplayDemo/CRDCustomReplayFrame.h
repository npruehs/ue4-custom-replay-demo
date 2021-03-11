#pragma once

#include "CoreMinimal.h"

#include "CRDCustomReplayUnitState.h"

#include "CRDCustomReplayFrame.generated.h"

USTRUCT()
struct CUSTOMREPLAYDEMO_API FCRDCustomReplayFrame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TArray<FCRDCustomReplayUnitState> Units;    
};
