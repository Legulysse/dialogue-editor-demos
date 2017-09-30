#pragma once

#include "Camera/CameraActor.h"
#include "Dialogue/DemoDialoguePrefab.h"
#include "DemoDialogueCamera.generated.h"


UCLASS(BlueprintType)
class ADemoDialogueCamera : public ACameraActor
{
    GENERATED_UCLASS_BODY()

public:

    UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
    EDemoDialoguePrefabPosition Speaker;

    UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
    EDemoDialoguePrefabPosition Listener;
};
