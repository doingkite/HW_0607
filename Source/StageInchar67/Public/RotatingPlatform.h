#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class STAGEINCHAR67_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()

public:
	ARotatingPlatform();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	class UStaticMeshComponent* PlatformMesh;
	
	// === 회전 설정 ===
	UPROPERTY(EditAnywhere, Category = "Platform|Rotation")
	float RotateSpeed = 90.f; // 초당 회전 각도 (도)

	// === 타이머 설정 (방향 전환) ===
	FTimerHandle FlipTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Timer Flip", meta = (ClampMin = "0.01"))
	float FlipIntervalSec = 3.f; // 방향 전환 간격

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Timer Flip")
	bool bTimerFlipDirection = false; // 주기적 방향 전환 활성화

	UFUNCTION()
	void OnTimerEvent();
};