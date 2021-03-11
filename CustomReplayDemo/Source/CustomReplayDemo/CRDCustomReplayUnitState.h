#pragma once

#include "CoreMinimal.h"

#include "CRDCustomReplayUnitState.generated.h"

USTRUCT()
struct CUSTOMREPLAYDEMO_API FCRDCustomReplayUnitState
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FName Id;

    UPROPERTY()
    float LocationX;

    UPROPERTY()
    float LocationY;

    UPROPERTY()
    float LocationZ;
};
