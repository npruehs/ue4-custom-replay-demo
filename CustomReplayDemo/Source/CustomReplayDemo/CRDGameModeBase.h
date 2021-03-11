#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"

#include "CRDCustomReplay.h"

#include "CRDGameModeBase.generated.h"

UCLASS()
class CUSTOMREPLAYDEMO_API ACRDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    ACRDGameModeBase();

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    /** Current replay we're playing. */
    UPROPERTY()
    FCRDCustomReplay Replay;
    
    /** Current frame of the replay we're playing. */
    int32 ReplayFrame;

    /** Unreal actors we've spawned for units of the replay. */
    UPROPERTY()
    TMap<FName, AActor*> Units;

    /** Duration of a replay frame, in seconds. */
    UPROPERTY(EditDefaultsOnly)
    float SecondsPerReplayFrame;

    /** Class of actors to spawn for replay units. */
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AActor> UnitActorClass;

    void ApplyReplayFrame(int32 NewReplayFrame);
};
