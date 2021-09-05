//--------------------------------------------------------------
//�N���X���FDoor.h
//�T�v	  �F�����̔��𐧌䂷��N���X
//�쐬���@�F2021/09/04
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/0
//--------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"		// ���̑�p(2021/04/13 Player�̑���Ɏg�p)
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
		USceneComponent* m_proot_;			 			// root�p

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* m_pdoor_mesh_right_;		// �����̃h�A�̃��b�V��(�E)

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, category = "Mesh")
		UStaticMeshComponent* m_pdoor_mesh_left_;		// �����̃h�A�̃��b�V��(��)

};
