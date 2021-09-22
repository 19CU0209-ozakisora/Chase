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
	LC_1		UMETA(ToolTip = "Game Start"),
	C_1			UMETA(ToolTip = "Game Start"),
	LC_2		UMETA(ToolTip = "Direction Middle"),
	C_2			UMETA(ToolTip = "Direction Middle"),
	LC_3		UMETA(ToolTip = "Direction Side"),
	C_3			UMETA(ToolTip = "Direction Side"),
	LC_4_1		UMETA(ToolTip = "Throw with a force above threshold"),
	LC_4_2		UMETA(ToolTip = "Throw with a force above threshold"),
	LC_4_3		UMETA(ToolTip = "Throw with a force above threshold"),
	C_4			UMETA(ToolTip = "Throw with a force above threshold"),
	LC_5_1		UMETA(ToolTip = "Throw with a force less than the threshold"),
	LC_5_2		UMETA(ToolTip = "Throw with a force less than the threshold"),
	C_5			UMETA(ToolTip = "Throw with a force less than the threshold"),
	LC_6		UMETA(ToolTip = "In house"),
	C_6_1		UMETA(ToolTip = "In house"),
	C_6_2		UMETA(ToolTip = "In house"),
	LC_7		UMETA(ToolTip = "In outzone"),
	C_7_1		UMETA(ToolTip = "In outzone"),
	C_7_2		UMETA(ToolTip = "In outzone"),
	LC_8		UMETA(ToolTip = "Event 1"),
	LC_8_1		UMETA(ToolTip = "Event 1"),
	LC_8_2		UMETA(ToolTip = "Event 1"),
	C_8			UMETA(ToolTip = "Event 1"),
	LC_9		UMETA(ToolTip = "Event 2"),
	C_9			UMETA(ToolTip = "Event 2"),
	LC_10		UMETA(ToolTip = "Before throwing"),
	C_10		UMETA(ToolTip = "Before throwing"),
	LC_11		UMETA(ToolTip = "Before throwing"),
	C_11		UMETA(ToolTip = "Before throwing"),
	LC_12		UMETA(ToolTip = "Throw with a force above threshold"),
	C_12		UMETA(ToolTip = "Throw with a force above threshold"),
	LC_13		UMETA(ToolTip = "Throw with a force less than the threshold"),
	C_13		UMETA(ToolTip = "Throw with a force less than the threshold"),
	LC_14_1		UMETA(ToolTip = "Spin"),
	LC_14_2		UMETA(ToolTip = "Spin"),
	C_14		UMETA(ToolTip = "Spin"),
	C_15_1		UMETA(ToolTip = "In house"),
	LC_15		UMETA(ToolTip = "In house"),
	C_15_2		UMETA(ToolTip = "In house"),
	LC_16_1		UMETA(ToolTip = "In house"),
	LC_16_2		UMETA(ToolTip = "In house"),
	C_16_1 		UMETA(ToolTip = "In house"),
	C_16_2 		UMETA(ToolTip = "In house"),
	LC_17_1		UMETA(ToolTip = "In outzone"),
	LC_17_2		UMETA(ToolTip = "In outzone"),
	C_17_1 		UMETA(ToolTip = "In outzone"),
	C_17_2 		UMETA(ToolTip = "In outzone"),
	LC_18  		UMETA(ToolTip = "Hit"),
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
