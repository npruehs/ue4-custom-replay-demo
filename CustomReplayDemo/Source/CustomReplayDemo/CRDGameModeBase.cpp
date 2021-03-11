#include "CRDGameModeBase.h"

#include "JsonObjectConverter.h"

#include "CRDCustomReplay.h"
#include "CRDLog.h"

void ACRDGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    // Build custom replay path.
    FString ReplayPath = FPaths::ProjectSavedDir() / TEXT("CustomReplays") / TEXT("CustomReplay.json");

    UE_LOG(LogCRD, Log, TEXT("Opening custom replay file %s ..."), *ReplayPath);

    // Parse JSON.
    FString ReplayJsonString;
    FFileHelper::LoadFileToString(ReplayJsonString, *ReplayPath);

    FCRDCustomReplay Replay;
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
}
