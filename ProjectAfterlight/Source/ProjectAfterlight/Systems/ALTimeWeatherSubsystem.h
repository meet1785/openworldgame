#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ALTimeWeatherSubsystem.generated.h"

UENUM(BlueprintType)
enum class EWeatherState : uint8
{
	Clear,
	Cloudy,
	Rain,
	HeavyRain,
	Storm
};

UCLASS()
class PROJECTAFTERLIGHT_API UALTimeWeatherSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void SetTimeOfDay(float NewTime24h);

	UFUNCTION(BlueprintPure, Category = "Environment")
	float GetTimeOfDay() const { return CurrentTime24h; }

	UFUNCTION(BlueprintCallable, Category = "Environment")
	void SetWeatherState(EWeatherState NewState);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time")
	float CurrentTime24h;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float TimeScaleFactor = 24.0f; // 1 real second = 24 game seconds

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weather")
	EWeatherState CurrentWeather;

	// Internal logic to update Directional Light and SkyAtmosphere
	void UpdateSky();
};
