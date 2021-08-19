//--------------------------------------------------------------
//クラス名：Instance.cpp
//概要    :GameInstance（ターンの制御）
//作成日　：2021/08/10
//作成者　：19CU0301 青木拓洋
//更新履歴：2021/08/10 青木拓洋 作成
//--------------------------------------------------------------


#include "Instance.h"
#include "Engine/Engine.h"

UInstance* UInstance::GetInstance()
{
    UInstance* instance = nullptr;

    if (GEngine)
    {
        FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
        instance = Cast<UInstance>(context->OwningGameInstance);
    }

    return instance;
}