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
	LC_1		UMETA(DisplayName = "LC_1"	, ToolTip = "Game Start"),
	C_1			UMETA(DisplayName = "C_1", ToolTip = "Game Start"),
	LC_2		UMETA(DisplayName = "LC_2", ToolTip = "Direction Middle"),
	C_2			UMETA(DisplayName = "C_2", ToolTip = "Direction Middle"),
	LC_3		UMETA(DisplayName = "LC_3", ToolTip = "Direction Side"),
	C_3			UMETA(DisplayName = "C_3", ToolTip = "Direction Side"),
	LC_4_1		UMETA(DisplayName = "LC_4_1", ToolTip = "Throw with a force above threshold"),
	LC_4_2		UMETA(DisplayName = "LC_4_2", ToolTip = "Throw with a force above threshold"),
	LC_4_3		UMETA(DisplayName = "LC_4_3", ToolTip = "Throw with a force above threshold"),
	C_4			UMETA(DisplayName = "C_4", ToolTip = "Throw with a force above threshold"),
	LC_5_1		UMETA(DisplayName = "LC_5_1", ToolTip = "Throw with a force less than the threshold"),
	LC_5_2		UMETA(DisplayName = "LC_5_2", ToolTip = "Throw with a force less than the threshold"),
	C_5			UMETA(DisplayName = "C_5", ToolTip = "Throw with a force less than the threshold"),
	LC_6		UMETA(DisplayName = "LC_6", ToolTip = "In house"),
	C_6_1		UMETA(DisplayName = "C_6_1", ToolTip = "In house"),
	C_6_2		UMETA(DisplayName = "C_6_2", ToolTip = "In house"),
	LC_7		UMETA(DisplayName = "LC_7", ToolTip = "In outzone"),
	C_7_1		UMETA(DisplayName = "C_7_1", ToolTip = "In outzone"),
	C_7_2		UMETA(DisplayName = "C_7_2", ToolTip = "In outzone"),
	LC_8		UMETA(DisplayName = "LC_8", ToolTip = "Event 1"),
	LC_8_1		UMETA(DisplayName = "LC_8_1", ToolTip = "Event 1"),
	LC_8_2		UMETA(DisplayName = "LC_8_2", ToolTip = "Event 1"),
	C_8			UMETA(DisplayName = "C_8", ToolTip = "Event 1"),
	LC_9		UMETA(DisplayName = "LC_9", ToolTip = "Event 2"),
	C_9			UMETA(DisplayName = "C_9"	, ToolTip = "Event 2")	,
};

// LiveCommentaryWidget用の列挙型
UENUM(BlueprintType)
enum class ECommentaryTextBox : uint8
{
	LineTextBox = 0		UMETA(ToolTip = "LineTextBox"),
	NameTextBox			UMETA(ToolTip = "NameTextBox"),
	ColonTextBox		UMETA(ToolTip = "ColonTextBox"),
	CommentTextBox		UMETA(ToolTip = "CommentTextBox"),
};

UCLASS()
class CHASE_API UEnumObject : public UObject
{
	GENERATED_BODY()

	
};
