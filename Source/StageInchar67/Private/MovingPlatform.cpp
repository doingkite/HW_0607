#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	// �ʱ� �浹 ���� (�ʼ�)
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlatformMesh->SetCollisionResponseToAllChannels(ECR_Block);
	PlatformMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	PlatformMesh->SetMobility(EComponentMobility::Movable); // �����̴� �����̹Ƿ� Movable ����
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// Ư�� Ÿ�̸� ���� (������, �����̵�)
	if (SpecialIntervalSec > 0.f)
	{
		GetWorldTimerManager().SetTimer(
			SpecialTimerHandle,
			this,
			&AMovingPlatform::OnSpecialTimerEvent,
			SpecialIntervalSec,
			true // �ݺ� ����
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

	// 1. �̵� ���� ����
	FVector Direction = bMovingForward ? NormalizedMoveDir : -NormalizedMoveDir;
	FVector DeltaLocation = Direction * FMath::Abs(MoveDirection.Size()) * DeltaTime;

	// 2. �̵� �� ���� üũ
	if (DistanceTraveled >= MaxRange)
	{
		// ���� ��ȯ �� ���� Ÿ�̸� ����
		bMovingForward = !bMovingForward;
		bPaused = true;
		GetWorldTimerManager().SetTimer(
			PauseTimerHandle,
			this,
			&AMovingPlatform::ResumeMovement,
			PauseDuration,
			false // ��ȸ�� ����
		);
	}
	else
	{
		// 3. ���� �̵�
		AddActorWorldOffset(DeltaLocation, true);
	}
}

void AMovingPlatform::ResumeMovement()
{
	bPaused = false;
	// Ÿ�̸Ӹ� ������ �޸� ������ ����
	GetWorldTimerManager().ClearTimer(PauseTimerHandle);
}

void AMovingPlatform::OnSpecialTimerEvent()
{
	// 1. �ֱ����� ������ (�浹 ��� ����)
	if (bTimerBlink && PlatformMesh)
	{
		const bool bWasHidden = PlatformMesh->bHiddenInGame;
		const bool bNowHidden = !bWasHidden;

		// ���־� ��� (�ڽı��� ����)
		PlatformMesh->SetHiddenInGame(bNowHidden, /*bPropagateToChildren=*/true);

		// ���ü��� ���� �浹 ���
		PlatformMesh->SetCollisionEnabled(bNowHidden
			? ECollisionEnabled::NoCollision
			: ECollisionEnabled::QueryAndPhysics);
	}

	// 2. ������ �����̵�
	if (bTimerRandomTeleport && TeleportRadius > 0.f)
	{
		const float Angle = FMath::FRandRange(0.f, 2.f * PI);
		const float Rad = FMath::Sqrt(FMath::FRand()) * TeleportRadius;
		const float RX = FMath::Cos(Angle) * Rad;
		const float RY = FMath::Sin(Angle) * Rad;

		// StartLocation�� �߽����� X/Y�� ����, Z�� ���� ���� ����
		const FVector NewLoc(StartLocation.X + RX, StartLocation.Y + RY, GetActorLocation().Z);
		SetActorLocation(NewLoc);
	}
}