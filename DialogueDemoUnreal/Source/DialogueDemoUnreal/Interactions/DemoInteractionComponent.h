#pragma once

#include "Components/SphereComponent.h"
#include "DemoInteractionComponent.generated.h"

UCLASS(config = Game, MinimalAPI, meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class UDemoInteractionComponent : public USphereComponent
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintPure, Category = Interaction)
	bool CanPlayerInteract(class ADemoPlayerCharacter* Player) const;

	UFUNCTION(BlueprintCallable, Category = Interaction)
	void PlayerInteract(class ADemoPlayerCharacter* Player);

protected:

	// UActorComponent interface
	virtual void InitializeComponent() override;
};
