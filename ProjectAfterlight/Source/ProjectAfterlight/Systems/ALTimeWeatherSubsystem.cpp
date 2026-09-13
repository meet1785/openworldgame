#include "Systems/ALTimeWeatherSubsystem.h"

void UALTimeWeatherSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentTime24h = 8.0f; // Start at 8 AM
	CurrentWeather = EWeatherState::Clear;
}

void UALTimeWeatherSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UALTimeWeatherSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Advance Time
	float TimePassed = (DeltaTime * TimeScaleFactor) / 3600.f; // Convert seconds to hours
	CurrentTime24h += TimePassed;

	if (CurrentTime24h >= 24.0f)
	{
		CurrentTime24h -= 24.0f; // Wrap around to midnight
	}

	UpdateSky();
}

TStatId UALTimeWeatherSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UALTimeWeatherSubsystem, STATGROUP_Tickables);
}

void UALTimeWeatherSubsystem::SetTimeOfDay(float NewTime24h)
{
	CurrentTime24h = FMath::Clamp(NewTime24h, 0.0f, 24.0f);
	UpdateSky();
}

void UALTimeWeatherSubsystem::SetWeatherState(EWeatherState NewState)
{
	CurrentWeather = NewState;
	// Trigger global weather events/Niagara parameter changes here
}

void UALTimeWeatherSubsystem::UpdateSky()
{
	// Locate the ADirectionalLight representing the sun and update its pitch/yaw based on CurrentTime24h
	// Locate ASkyLight to recapture or adjust intensity
}
