#pragma once

#include "Components/SphereComponent.h"
#include "DemoInteractionComponent.generated.h"

UCLASS(config = Game, MinimalAPI, meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class UDemoInteractionComponent : public USphereComponent
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Interaction)
	void PlayerInteract(class ADemoPlayerCharacter* Player);

protected:

	// UActorComponent interface
	virtual void InitializeComponent() override;
};
