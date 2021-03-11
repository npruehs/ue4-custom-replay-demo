#include "CRDGameModeBase.h"

#include "JsonObjectConverter.h"

#include "CRDLog.h"

ACRDGameModeBase::ACRDGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ACRDGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    // Build custom replay path.
    FString ReplayPath = FPaths::ProjectSavedDir() / TEXT("CustomReplays") / TEXT("CustomReplay.json");

    UE_LOG(LogCRD, Log, TEXT("Opening custom replay file %s ..."), *ReplayPath);

    // Parse JSON.
    FString ReplayJsonString;
    FFileHelper::LoadFileToString(ReplayJsonString, *ReplayPath);
    FJsonObjectConverter::JsonObjectStringToUStruct<FCRDCustomReplay>(ReplayJsonString, &Replay, 0, 0);

    UE_LOG(LogCRD, Log, TEXT("Successfully parsed custom replay file %s"), *ReplayPath);

    // Log replay contents.
    for (int32 FrameIndex = 0; FrameIndex < Replay.Frames.Num(); ++FrameIndex)
    {
        const FCRDCustomReplayFrame& Frame = Replay.Frames[FrameIndex];

        for (const FCRDCustomReplayUnitState& Unit : Frame.Units)
        {
            UE_LOG(LogCRD, Log, TEXT("Frame %i - Unit %s - Location: %f, %f, %f"),
                FrameIndex, *Unit.Id.ToString(), Unit.LocationX, Unit.LocationY, Unit.LocationZ);
        }
    }

    // Start playing.
    ReplayFrame = -1;
}

void ACRDGameModeBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Calculate new replay frame index.
    int32 NewReplayFrame = FMath::FloorToInt(GetWorld()->GetTimeSeconds() / SecondsPerReplayFrame);

    // Check if we need to update the game world.
    if (NewReplayFrame > ReplayFrame && Replay.Frames.IsValidIndex(NewReplayFrame))
    {
        ApplyReplayFrame(NewReplayFrame);
    }
}

void ACRDGameModeBase::ApplyReplayFrame(int32 NewReplayFrame)
{
    ReplayFrame = NewReplayFrame;

    UE_LOG(LogCRD, Log, TEXT("Replay frame %i started!"), ReplayFrame);

    const FCRDCustomReplayFrame& Frame = Replay.Frames[ReplayFrame];

    // Update all units.
    for (const FCRDCustomReplayUnitState& ReplayUnit : Frame.Units)
    {
        // Get Unreal actor representing the replay unit.
        AActor* Unit = Units.FindRef(ReplayUnit.Id);

        if (!IsValid(Unit))
        {
            // We've never seen that unit before.
            // Pragmatic approach: Just lazily spawn new actor for the unit.
            Unit = GetWorld()->SpawnActor(UnitActorClass);
            Units.Add(ReplayUnit.Id, Unit);

            UE_LOG(LogCRD, Log, TEXT("Spawned new actor %s for unit %s."), *Unit->GetName(), *ReplayUnit.Id.ToString());
        }

        // Update actor location.
        FVector NewLocation = FVector(ReplayUnit.LocationX, ReplayUnit.LocationY, ReplayUnit.LocationZ);
        Unit->SetActorLocation(NewLocation);

        UE_LOG(LogCRD, Log, TEXT("Unit %s moved to location %f, %f, %f"),
            *ReplayUnit.Id.ToString(), ReplayUnit.LocationX, ReplayUnit.LocationY, ReplayUnit.LocationZ);
    }
}
