﻿#pragma once

#include "DemoNodeCondition.h"
#include "DemoNodeConditionGroup.generated.h"


UCLASS(BlueprintType, Abstract)
class DIALOGUEDEMOUNREAL_API UDemoNodeConditionGroup : public UDemoNodeCondition
{
	GENERATED_UCLASS_BODY()

public:

    virtual bool IsValid(FDemoNodeContextCondition& InContext) const override;

public:

    UPROPERTY(VisibleAnywhere, Instanced, Category="Dialogue")
    TArray< class UDemoNodeCondition* > Conditions;
};
