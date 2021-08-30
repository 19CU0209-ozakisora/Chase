//--------------------------------------------------------------
//クラス名：Chair.cpp
//概要	  ：椅子が止まっていた時にスコアを加算させる用クラス
//作成日　：2021/07/16
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/07/16 尾崎蒼宙 作成
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AddScoreTrigger.generated.h"

UCLASS()
class CHASE_API AAddScoreTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAddScoreTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)			// 追加する得点を設定する変数
		int m_score_;

};
