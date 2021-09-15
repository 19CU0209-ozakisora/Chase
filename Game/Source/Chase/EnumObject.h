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
	NL			UMETA(Hidden),
	LC_1		UMETA(DisplayName = "1_LC"	, ToolTip = "Game Start"),
	C_1			UMETA(DisplayName = "1_C"	, ToolTip = "Game Start"),
	LC_2		UMETA(DisplayName = "2_LC"	, ToolTip = "Direction Middle"),
	C_2			UMETA(DisplayName = "2_C"	, ToolTip = "Direction Middle"),
	LC_3		UMETA(DisplayName = "3_LC"	, ToolTip = "Direction Side"),
	C_3			UMETA(DisplayName = "3_C"	, ToolTip = "Direction Side"),
	LC_4_1		UMETA(DisplayName = "4_1_LC", ToolTip = "Throw with a force above threshold"),
	LC_4_2		UMETA(DisplayName = "4_2_LC", ToolTip = "Throw with a force above threshold"),
	LC_4_3		UMETA(DisplayName = "4_3_LC", ToolTip = "Throw with a force above threshold"),
	C_4			UMETA(DisplayName = "4_C"	, ToolTip = "Throw with a force above threshold"),
	LC_5_1		UMETA(DisplayName = "5_1_LC", ToolTip = "Throw with a force less than the threshold"),
	LC_5_2		UMETA(DisplayName = "5_2_LC", ToolTip = "Throw with a force less than the threshold"),
	C_5			UMETA(DisplayName = "5_C"	, ToolTip = "Throw with a force less than the threshold"),
	LC_6		UMETA(DisplayName = "6_LC"	, ToolTip = "In house"),
	C_6_1		UMETA(DisplayName = "6_1_C"	, ToolTip = "In house"),
	C_6_2		UMETA(DisplayName = "6_2_C"	, ToolTip = "In house"),
	LC_7		UMETA(DisplayName = "7_LC"	, ToolTip = "In outzone"),
	C_7_1		UMETA(DisplayName = "7_1_C"	, ToolTip = "In outzone"),
	C_7_2		UMETA(DisplayName = "7_2_C"	, ToolTip = "In outzone"),
	LC_8		UMETA(DisplayName = "8_LC"	, ToolTip = "Event 1")	,
	C_8			UMETA(DisplayName = "8_C"	, ToolTip = "Event 1")	,
	LC_9		UMETA(DisplayName = "9_LC"	, ToolTip = "Event 2")	,
	C_9			UMETA(DisplayName = "9_C"	, ToolTip = "Event 2")	,
};

UCLASS()
class CHASE_API UEnumObject : public UObject
{
	GENERATED_BODY()

	
};
