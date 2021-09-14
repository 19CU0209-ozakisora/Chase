//--------------------------------------------------------------
//クラス名：Instance.h
//概要    :GameInstance（ターンの制御）
//作成日　：2021/08/10
//作成者　：19CU0301 青木拓洋
//更新履歴：2021/08/10 青木拓洋 作成
//			2021/08/31 野田八雲 チームごとの合計得点を格納する変数追加（ウィジェット出力用）
//			2021/09/07 野田八雲 各椅子がとった得点を計算する変数追加（ウィジェット出力用）
//			2021/09/09 渡邊龍音 実況のウィジェットを作成し、保持する
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
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

	//各チームの得点を格納（1P）
	UPROPERTY(BlueprintReadWrite)
		int m_teamPoint1P = 0;

	//各チームの得点を格納（2P）
	UPROPERTY(BlueprintReadWrite)
		int m_teamPoint2P = 0;

	// 実況ウィジェット
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* commentWidget;

	//各得点格納用
	//ウィジェットが不可変配列非対応、TArray型だと取得した得点の型が合わないため、
	//無理やりではあるがそれぞれの得点配列を追加。直せれば直す。
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
