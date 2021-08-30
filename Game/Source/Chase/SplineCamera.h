//--------------------------------------------------------------
//�N���X���FSplineCamera.h
//�T�v	  �F�v���C���[�̎��͂����J�����𐧌䂷��N���X
//�쐬���@�F2021/07/12
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/07/19 ���葓�� GameManager.h���C���N���[�h
//								FChangeDirection�\����(�ǂ�phase���ɂǂ̌����ɃJ�������ړ������邩)�̒ǉ�
//								m_change_direction_�̒ǉ�
//			2021/08/20 ���葓�� GameFramework/SpringArmComponent.h�̒ǉ�
//								m_pspring_arm_(�X�v�����O�A�[���i�[�p)��ǉ�
// 			2021/08/21 ���葓�� m_out_range_(�����͈�)�̒ǉ�
//								���X�v�����O�A�[���R���|�[�l���g�����悤���Ă�����CPP�ŕǂ̊O�܂ňړ������Ă���̂Ŕ͈͂�ݒ肷��K�v����
//			2021/08/25 ���葓�� Kismet/KismetSystemLibrary.h(�f�o�b�O�p�̃��C)�̃C���N���[�h
//								m_offset_player_height_(Player�̒��S�_�ƃJ�����̍����𓯎��ɏグ��)�̒ǉ�
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameManager.h"
#include "Engine/Engine.h"			// �X�N���[�����O�o�͗p
#include "Kismet/KismetMathLibrary.h"
#include "GameManager.h"
#include "GameFramework/SpringArmComponent.h"	// �X�v�����O�A�[��
#include "Kismet/KismetSystemLibrary.h"	// ���C
#include "Chair.h"
#include "SplineCamera.generated.h"

// �֎q�̃t�F�[�Y�̗񋓌^
UENUM(BlueprintType)
enum class EDirection : uint8
{
	kfront UMETA(DisplayName = "Front"),					// ����(X+, 0, 0)
	kfrontright UMETA(DisplayName = "FrontRight"),			// �E�O(X+, Y+, 0)
	kright UMETA(DisplayName = "Right"),					// �E(0, Y+, 0)
	kbackright UMETA(DisplayName = "BackRight"),			// �E���(X- Y+, 0)
	kback UMETA(DisplayName = "Back"),						// �w��(X-, 0, 0)
	kbackleft UMETA(DisplayName = "BackLeft"),				// �����(X-, Y-, 0)
	kleft UMETA(DisplayName = "Left"),						// ��(0, Y-, 0)
	kfrontleft UMETA(DisplayName = "FrontLeft"),			// ���O(X+, Y-, 0)
	ktop UMETA(DisplayName = "Top"),						// ��(0, 0, Z+)
	kunder UMETA(DisplayName = "Under"),					// ��(0, 0, Z-)
};

USTRUCT(BlueprintType)
struct FChangeDirection
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
		EPhase phase_;
	UPROPERTY(EditAnywhere)
		EDirection change_direction_;
};

UCLASS()
class CHASE_API ASplineCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	EDirection m_preb_edirection_;
	// EPhase m_prebphase_;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "camera")
		EPhase m_prebphase_;
	UPROPERTY(EditAnywhere, Category = "camera")
		UCameraComponent* m_pcamera_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
		EDirection m_edirection_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		AGameManager* m_pgamemanager_;

	UPROPERTY(EditAnywhere, Category = "rad")
		float radius_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Enum")
		FVector m_before_change_camera_location_;

	UPROPERTY(EditAnywhere, Category = "Enum")
		FVector m_goal_location_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
		float m_leap_alpha_;

	UPROPERTY(EditAnywhere, Category = "Enum")
		FVector m_now_location_;

	UPROPERTY(EditAnywhere, Category = "Enum")
		float m_end_move_time_;

	UPROPERTY(EditAnywhere, Category = "camera")
		float m_offset_location_z;

	UPROPERTY(EditAnywhere, Category = "camera")
		float m_offset_player_height_;

	FVector SetGoalLocation();
	float SetLeapAlpha(float _deltatime);
	FVector SetCameraLocaiton();
	FRotator SetCameraRotator();
	void ResetLeap();

	UPROPERTY(EditAnywhere, Category = "camera")
		TArray<FChangeDirection> m_change_direction_;

	UPROPERTY(EditAnywhere, Category = "camera")
		USpringArmComponent* m_pspring_arm_;

	UPROPERTY(EditAnywhere, Category = "camera")
		float outrenze;

	UFUNCTION(BlueprintCallable, Category = "MyF")
		void Teleportation();
};
