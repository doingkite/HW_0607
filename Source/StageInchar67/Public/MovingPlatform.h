#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class STAGEINCHAR67_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlatformMesh;

	// === 이동 설정 ===
	UPROPERTY(EditAnywhere, Category = "Platform|Movement")
	FVector MoveDirection = FVector(100.f, 0.f, 0.f); // 초당 이동량 (속도)

	UPROPERTY(EditAnywhere, Category = "Platform|Movement")
	float MaxRange = 500.f; // 시작 지점에서 최대 이동 거리

	FVector StartLocation;
	bool bMovingForward = true; // 이동 방향 (정방향/역방향)

	// === 타이머 기반 정지 ===
	FTimerHandle PauseTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Platform|Pause Timer")
	float PauseDuration = 1.0f; // 정지 시간

	UPROPERTY(EditAnywhere, Category = "Platform|Pause Timer")
	bool bPaused = false;

	// === 특수 타이머 설정 (깜빡임) ===
	FTimerHandle SpecialTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer", meta = (ClampMin = "0.01"))
	float SpecialIntervalSec = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer")
	bool bTimerBlink = false; // 주기적 깜빡임 활성화

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer")
	bool bTimerRandomTeleport = false; // 무작위 순간이동 활성화

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer")
	float TeleportRadius = 500.0f; // 순간이동 반경

	void ResumeMovement();
	void OnSpecialTimerEvent();
};