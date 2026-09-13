#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ALEnvironmentController.generated.h"

class UDirectionalLightComponent;
class USkyLightComponent;
class UPostProcessComponent;

UCLASS()
class PROJECTAFTERLIGHT_API AALEnvironmentController : public AActor
{
	GENERATED_BODY()
	
public:	
	AALEnvironmentController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Environment")
	UDirectionalLightComponent* SunLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Environment")
	USkyLightComponent* SkyLight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Environment")
	UPostProcessComponent* PostProcess;

public:	
	// Called by the ALTimeWeatherSubsystem to update the sun's position
	UFUNCTION(BlueprintCallable, Category = "Environment")
	void UpdateTimeOfDay(float Time24h);
};
