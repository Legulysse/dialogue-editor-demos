#include "Assets/DemoDialogue.h"
#include "Assets/DemoDialogueNode.h"


UDemoDialogue::UDemoDialogue(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, RootNodeID(-1)
, RootNode(nullptr)
{
}

UDemoDialogueNode* UDemoDialogue::GetNodeByID(int32 ID) const
{
    for (UDemoDialogueNode* Node : ListNodes)
    {
        if (Node->ID == ID)
            return Node;
    }
    return nullptr;
}
