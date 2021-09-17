//--------------------------------------------------------------
//クラス名：GameManager.h
//概要	  ：ゲームを管理するクラス
//作成日　：2021/04/26
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/04/22 尾崎蒼宙 作成
//			2021/04/30 ChairとPlayerのh追加
//			2021/05/04 現在のターン・どちらの番か・椅子の生成を管理する変数の追加
//			2021/05/09 尾崎蒼宙 TimeCheck関数(一定時間後に次のラウンドへ移行する関数)の追加
//			2021/05/09 野田八雲 得点周りの変数の追加
//			2021/05/16 尾崎蒼宙 HouseCenter.hの追加
//			2021/05/25 尾崎蒼宙 m_switch_level_time(レベル切り替えの時間)の変数追加
//			2021/07/16 尾崎蒼宙 m_teamPoint(1P2Pどちらも)をプレイ中に確認できるようにEditAnyWhereを追加
//								AddScore(プレイヤーが止まっているマスに近い側の点数を加算する)関数を追加
//			2021/08/09 尾崎蒼宙 m_is_event_(イベント発生中かどうか)
//								m_event_cnt_(イベントが発生した回数)
//								m_event_round_(イベントが発生するラウンド数)
//								NextRound関数(次のラウンドに移動させる関数)を追加
//								↑GameManager.cpp内に酷似した処理があった為まとめました
//			2021/08/30 野田八雲  GetPoint関数の戻り値をInsranceに変更
//			2021/09/04 尾崎蒼宙 デバッグ用に+でラウンド数を増やすように
//			2021/09/07 野田八雲 各椅子がとった得点を計算する変数追加（ウィジェット出力用）
//			2021/09/13 野田八雲 各得点版に椅子が何個乗ってるかを格納する処理に変更
//			2021/09/17 野田八雲 09/07、09/13の件についてのコメント記入、09/07から不要になった変数の削除
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Playerchara.h"
#include "HouseCenter.h"
#include "Instance.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

// 2021/05/10 尾崎 コメント化(試作で作ったもの)
/*struct FChair
{
	AChair* chair_obj_;

	//2点間の距離を格納する変数
	float Vectormeter_;
};
*/

UCLASS(BluePrintable)
class CHASE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


//---------------------------------------------------------
// 尾崎 蒼宙
private:

	bool TimeCheck(float _deltatime);

	float time_cnt_;

	void AddScore();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<APlayerchara*> m_players_;		// Player管理用

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<AChair*> m_chairs_;				// Chair管理用(得点計算処理があるので構造体の方が良いかも)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_is_event_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_chair_create_time_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_switch_level_time;			// レベル遷移の時間

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		int m_event_cnt_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		int m_nowroundnum_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		int m_maxroundnum_;					// 椅子を投げる最大の数

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<int> m_event_round_;

	UFUNCTION(BluePrintCallable)
		void NextRound();

//---------------------------------------------------------
//2021/05/06:　野田　変数、関数追加
public:
	//椅子がすべて止まった時の処理
	void StopChair();

	//椅子の距離ソート用
	void ChairSort();

	//得点計算
	void SetPoint();

	//ウィジェット出力1P
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		int GetPoint1P()const { return Instance->m_teamPoint1P; }

	//ウィジェット出力2P
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		int GetPoint2P()const { return Instance->m_teamPoint2P; }

	//チームポイント（1P用）
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int m_teamPoint1P;

	//チームポイント（2P用）]
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int m_teamPoint2P;

private:

	//自分自身の座標
	FVector m_thisLocation;

	//カウント用変数
	bool m_bFunctionCheck;

//-------------------------------------------------------

	// 2021 05/10 尾崎  m_chairs_に変更
	// AChair* m_pAChair[10] = {NULL};

	float m_ChairDistance[10] = {0.f};

	bool m_Check[10] = { false };

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
// 青木追加
	// GameInstance
	UInstance* Instance;

public:
	// Player1のターン数
	UPROPERTY(BlueprintReadOnly)
		int m_Player1Turn;
	// Player2のターン数
	UPROPERTY(BlueprintReadOnly)
		int m_Player2Turn;
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
};