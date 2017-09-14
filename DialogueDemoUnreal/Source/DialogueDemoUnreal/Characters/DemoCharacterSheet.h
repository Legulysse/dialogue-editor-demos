#pragma once

#include "DemoCharacterSheet.generated.h"


UCLASS(BlueprintType, Blueprintable)
class UDemoCharacterSheet : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Demo)
	FString ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Demo)
	FString DisplayName;
};
