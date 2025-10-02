#include "RotatingPlatform.h"
#include "Components/StaticMeshComponent.h"

ARotatingPlatform::ARotatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	// 초기 설정
	PlatformMesh->SetMobility(EComponentMobility::Movable);
}

void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// 타이머 기반 방향 전환 설정
	if (bTimerFlipDirection && FlipIntervalSec > 0.f)
	{
		GetWorldTimerManager().SetTimer(
			FlipTimerHandle,
			this,
			&ARotatingPlatform::OnTimerEvent,
			FlipIntervalSec,
			true // 루프 반복
		);
	}
}

void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 지속적인 회전
	const FRotator RotationDelta(0.f, RotateSpeed * DeltaTime, 0.f); // YAW 축으로 회전
	AddActorWorldRotation(RotationDelta);
}

void ARotatingPlatform::OnTimerEvent()
{
	// 타이머 이벤트 발생 시 회전 속도의 부호를 반전 (방향 전환)
	if (bTimerFlipDirection)
	{
		// RotateSpeed *= -1.f; 와 RotationSpeed = -RotationSpeed; 는 같은 기능
		RotateSpeed *= -1.f;
	}
}