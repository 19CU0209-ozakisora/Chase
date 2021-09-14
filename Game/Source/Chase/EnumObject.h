//--------------------------------------------------------------
//クラス名：EnumObject
//概要	  ：Enum管理用
//作成日　：2021/09/14
//作成者　：19CU0238 渡邊龍音
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumObject.generated.h"

// CommentTable(DataTable型)のRow Name取得用
UENUM(BlueprintType)
enum class ECommentID : uint8
{
	NL			UMETA(DisplayName = "NL"),
	LC_1		UMETA(DisplayName = "1_LC"),
	C_1			UMETA(DisplayName = "1_C"),
	LC_2		UMETA(DisplayName = "2_LC"),
	C_2			UMETA(DisplayName = "2_C"),
	LC_3		UMETA(DisplayName = "3_LC"),
	C_3			UMETA(DisplayName = "3_C"),
	LC_4_1		UMETA(DisplayName = "4_1_LC"),
	LC_4_2		UMETA(DisplayName = "4_2_LC"),
	LC_4_3		UMETA(DisplayName = "4_3_LC"),
	C_4			UMETA(DisplayName = "4_C"),
	LC_5_1		UMETA(DisplayName = "5_1_LC"),
	LC_5_2		UMETA(DisplayName = "5_2_LC"),
	C_5			UMETA(DisplayName = "5_C"),
	LC_6		UMETA(DisplayName = "6_LC"),
	C_6_1		UMETA(DisplayName = "6_1_C"),
	C_6_2		UMETA(DisplayName = "6_2_C"),
	LC_7		UMETA(DisplayName = "7_LC"),
	C_7_1		UMETA(DisplayName = "7_1_C"),
	C_7_2		UMETA(DisplayName = "7_2_C"),
	LC_8		UMETA(DisplayName = "8_LC"),
	C_8			UMETA(DisplayName = "8_C"),
	LC_9		UMETA(DisplayName = "9_LC"),
	C_9			UMETA(DisplayName = "9_C"),
};

UCLASS()
class CHASE_API UEnumObject : public UObject
{
	GENERATED_BODY()

	
};
