#pragma once

#include "DemoDialogue.generated.h"


UCLASS(BlueprintType)
class DIALOGUEDEMOUNREAL_API UDemoDialogue : public UObject
{
	GENERATED_UCLASS_BODY()

public:
		
#if WITH_EDITORONLY_DATA

    UPROPERTY(VisibleAnywhere, Instanced)
	class UAssetImportData* AssetImportData;

#endif // WITH_EDITORONLY_DATA
};
