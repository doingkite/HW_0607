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
	
	// === ȸ�� ���� ===
	UPROPERTY(EditAnywhere, Category = "Platform|Rotation")
	float RotateSpeed = 90.f; // �ʴ� ȸ�� ���� (��)

	// === Ÿ�̸� ���� (���� ��ȯ) ===
	FTimerHandle FlipTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Timer Flip", meta = (ClampMin = "0.01"))
	float FlipIntervalSec = 3.f; // ���� ��ȯ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Timer Flip")
	bool bTimerFlipDirection = false; // �ֱ��� ���� ��ȯ Ȱ��ȭ

	UFUNCTION()
	void OnTimerEvent();
};