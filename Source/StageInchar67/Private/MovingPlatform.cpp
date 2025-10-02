#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	// 초기 충돌 설정 (필수)
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlatformMesh->SetCollisionResponseToAllChannels(ECR_Block);
	PlatformMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	PlatformMesh->SetMobility(EComponentMobility::Movable); // 움직이는 액터이므로 Movable 설정
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// 특수 타이머 설정 (깜빡임, 순간이동)
	if (SpecialIntervalSec > 0.f)
	{
		GetWorldTimerManager().SetTimer(
			SpecialTimerHandle,
			this,
			&AMovingPlatform::OnSpecialTimerEvent,
			SpecialIntervalSec,
			true // 반복 실행
		);
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPaused)
	{
		return;
	}

	const FVector NormalizedMoveDir = MoveDirection.GetSafeNormal();
	const float DistanceTraveled = FVector::Dist(StartLocation, GetActorLocation());

	// 1. 이동 방향 결정
	FVector Direction = bMovingForward ? NormalizedMoveDir : -NormalizedMoveDir;
	FVector DeltaLocation = Direction * FMath::Abs(MoveDirection.Size()) * DeltaTime;

	// 2. 이동 및 범위 체크
	if (DistanceTraveled >= MaxRange)
	{
		// 방향 전환 및 정지 타이머 시작
		bMovingForward = !bMovingForward;
		bPaused = true;
		GetWorldTimerManager().SetTimer(
			PauseTimerHandle,
			this,
			&AMovingPlatform::ResumeMovement,
			PauseDuration,
			false // 일회성 실행
		);
	}
	else
	{
		// 3. 실제 이동
		AddActorWorldOffset(DeltaLocation, true);
	}
}

void AMovingPlatform::ResumeMovement()
{
	bPaused = false;
	// 타이머를 지워서 메모리 누수를 방지
	GetWorldTimerManager().ClearTimer(PauseTimerHandle);
}

void AMovingPlatform::OnSpecialTimerEvent()
{
	// 1. 주기적인 깜빡임 (충돌 토글 포함)
	if (bTimerBlink && PlatformMesh)
	{
		const bool bWasHidden = PlatformMesh->bHiddenInGame;
		const bool bNowHidden = !bWasHidden;

		// 비주얼만 토글 (자식까지 전파)
		PlatformMesh->SetHiddenInGame(bNowHidden, /*bPropagateToChildren=*/true);

		// 가시성에 맞춰 충돌 토글
		PlatformMesh->SetCollisionEnabled(bNowHidden
			? ECollisionEnabled::NoCollision
			: ECollisionEnabled::QueryAndPhysics);
	}

	// 2. 무작위 순간이동
	if (bTimerRandomTeleport && TeleportRadius > 0.f)
	{
		const float Angle = FMath::FRandRange(0.f, 2.f * PI);
		const float Rad = FMath::Sqrt(FMath::FRand()) * TeleportRadius;
		const float RX = FMath::Cos(Angle) * Rad;
		const float RY = FMath::Sin(Angle) * Rad;

		// StartLocation을 중심으로 X/Y만 변경, Z는 현재 높이 유지
		const FVector NewLoc(StartLocation.X + RX, StartLocation.Y + RY, GetActorLocation().Z);
		SetActorLocation(NewLoc);
	}
}