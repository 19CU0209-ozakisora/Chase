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

	//各チームの得点を格納
	UPROPERTY(BlueprintReadWrite)
		int m_teamPoint1P = 0;

	UPROPERTY(BlueprintReadWrite)
		int m_teamPoint2P = 0;

	//各得点格納用
	//ウィジェットが不可変配列非対応、TArray型だと型が合わないため、無理やりではあるが
	//それぞれの得点配列を追加。直せれば直す。
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_1 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_2 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_3 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_4 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint1P_5 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_1 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_2 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_3 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_4 = 0;
	UPROPERTY(BlueprintReadWrite)
		int m_chairEachPoint2P_5 = 0;

};
