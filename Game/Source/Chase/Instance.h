//--------------------------------------------------------------
//クラス名：Instance.h
//概要    :GameInstance（ターンの制御）
//作成日　：2021/08/10
//作成者　：19CU0301 青木拓洋
//更新履歴：2021/08/10 青木拓洋 作成
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Instance.generated.h"

UCLASS()
class CHASE_API UInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// GameInstanceの実態を検索している関数
	static UInstance* GetInstance();

	// ターン数
	UPROPERTY(BlueprintReadWrite)
		int m_Turn = 6;
};
