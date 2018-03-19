#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "pathfinder.h"
#include "PathfinderLib.generated.h"
DECLARE_LOG_CATEGORY_EXTERN(PathfinderLog, Log, All);
USTRUCT(BlueprintType)
struct FTrajectoryStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector2D> BotTrajectory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector2D> LeftTrajectory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector2D> RightTrajectory;
};

UCLASS()
class VICTORYPLANNERUE_API UPathfinderLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


		UFUNCTION(BlueprintCallable, Category = "Pathfinder")
		static FTrajectoryStruct GetPoints(TArray<FTransform> input);


};
