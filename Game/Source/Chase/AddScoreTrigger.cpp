//--------------------------------------------------------------
//クラス名：Chair.cpp
//概要	  ：椅子が止まっていた時にスコアを加算させる用クラス
//作成日　：2021/07/16
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/07/16 尾崎蒼宙 作成
//--------------------------------------------------------------


#include "AddScoreTrigger.h"

// Sets default values
AAddScoreTrigger::AAddScoreTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// falseに変更
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAddScoreTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAddScoreTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

