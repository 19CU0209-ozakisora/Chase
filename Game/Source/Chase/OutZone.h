//--------------------------------------------------------------
//�N���X���FOutZone
//�T�v	  �F�֎q���~�܂������ɍ폜�����]�[��
//�쐬���@�F2021/08/05
//�쐬�ҁ@�F�n粗���
//�X�V�����F2021/08/10 �n粗��� BP����ڍs
//		�@�F2021/08/18 �n粗��� UI�̕\��
//		�@�F2021/09/10 �n粗��� Chair�^�ɃL���X�g��Chair��m_Phase�𒲂ׂ�悤��
//							�@  �����蔻��ł͂Ȃ�TargetPoint�Ŕ͈͂��w�肷��悤��
//			2021/09/16 �n粗��� �p�b�P�[�W���ŃG���[���N���邽��TargetPoint����SceneComponent��
//			2021/09/27 �n粗��� BeginPlay�Ńv���C���[���擾�ł��Ȃ��Ȃ��Ă��܂����̂ŏC��
//--------------------------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Chair.h"
#include "Blueprint/UserWidget.h"
#include "Engine/TargetPoint.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "OutZone.generated.h"

UCLASS()
class CHASE_API AOutZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool isSetActor;
	TArray<AChair*> deleteChair;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintCallable)
		void DeleteActor(AChair* _chair);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent* TargetStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent* TargetEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> outWidget;
};