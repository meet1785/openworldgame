#include "Systems/ALEnvironmentController.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/PostProcessComponent.h"
#include "Systems/ALTimeWeatherSubsystem.h"
#include "Engine/World.h"

AALEnvironmentController::AALEnvironmentController()
{
	PrimaryActorTick.bCanEverTick = false;

	SunLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLight"));
	RootComponent = SunLight;
	SunLight->bAtmosphereSunLight = true;
	SunLight->bUseTemperature = true;

	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	SkyLight->SetupAttachment(RootComponent);
	SkyLight->bRealTimeCapture = true;

	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcess->SetupAttachment(RootComponent);
}

void AALEnvironmentController::BeginPlay()
{
	Super::BeginPlay();

	// Register with the subsystem
	if (UWorld* World = GetWorld())
	{
		if (UALTimeWeatherSubsystem* WeatherSub = World->GetSubsystem<UALTimeWeatherSubsystem>())
		{
			WeatherSub->RegisterEnvironmentController(this);
		}
	}
}

void AALEnvironmentController::UpdateTimeOfDay(float Time24h)
{
	// Map 0-24 hours to -90 to 270 degrees pitch
	// 6 AM (6.0) = Sunrise (0 pitch)
	// 12 PM (12.0) = Noon (-90 pitch)
	// 6 PM (18.0) = Sunset (180 pitch)

	float TimeOffset = Time24h - 6.0f; // Offset so 0 is sunrise
	float PitchAngle = (TimeOffset / 24.0f) * 360.0f;
	
	FRotator NewSunRotation = FRotator(-PitchAngle, 0.0f, 0.0f);
	SunLight->SetWorldRotation(NewSunRotation);
}
