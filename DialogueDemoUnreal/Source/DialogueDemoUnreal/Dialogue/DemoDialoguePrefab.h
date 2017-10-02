#pragma once

#include "DemoDialoguePrefab.generated.h"


UENUM(BlueprintType)
enum class EDemoDialoguePrefabPosition : uint8
{
    Character_01,
    Character_02,
    Character_03,
    Character_04,
    Character_05,
    Character_06,
};

UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class UDemoDialoguePrefabRolePosition : public USceneComponent
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	EDemoDialoguePrefabPosition Position;
};

UCLASS(BlueprintType)
class ADemoDialoguePrefab : public AActor
{
	GENERATED_UCLASS_BODY()
};
