#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CRDGameModeBase.generated.h"

UCLASS()
class CUSTOMREPLAYDEMO_API ACRDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};
