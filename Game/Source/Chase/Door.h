//--------------------------------------------------------------
//クラス名：Door.h
//概要	  ：教室の扉を制御するクラス
//作成日　：2021/09/04
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/0
//--------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"		// 矢印の代用(2021/04/13 Playerの代わりに使用)
#include "Door.generated.h"

UCLASS()
class CHASE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

public:

	UPROPERTY(EditAnyWhere, Category = "Infomation")
		USceneComponent* m_proot_;			 			// root用

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* m_pdoor_mesh_right_;		// 教室のドアのメッシュ(右)

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, category = "Mesh")
		UStaticMeshComponent* m_pdoor_mesh_left_;		// 教室のドアのメッシュ(左)

};
