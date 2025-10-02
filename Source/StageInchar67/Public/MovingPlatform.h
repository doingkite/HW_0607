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

	// === �̵� ���� ===
	UPROPERTY(EditAnywhere, Category = "Platform|Movement")
	FVector MoveDirection = FVector(100.f, 0.f, 0.f); // �ʴ� �̵��� (�ӵ�)

	UPROPERTY(EditAnywhere, Category = "Platform|Movement")
	float MaxRange = 500.f; // ���� �������� �ִ� �̵� �Ÿ�

	FVector StartLocation;
	bool bMovingForward = true; // �̵� ���� (������/������)

	// === Ÿ�̸� ��� ���� ===
	FTimerHandle PauseTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Platform|Pause Timer")
	float PauseDuration = 1.0f; // ���� �ð�

	UPROPERTY(EditAnywhere, Category = "Platform|Pause Timer")
	bool bPaused = false;

	// === Ư�� Ÿ�̸� ���� (������) ===
	FTimerHandle SpecialTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer", meta = (ClampMin = "0.01"))
	float SpecialIntervalSec = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer")
	bool bTimerBlink = false; // �ֱ��� ������ Ȱ��ȭ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer")
	bool bTimerRandomTeleport = false; // ������ �����̵� Ȱ��ȭ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Special Timer")
	float TeleportRadius = 500.0f; // �����̵� �ݰ�

	void ResumeMovement();
	void OnSpecialTimerEvent();
};