#include "RotatingPlatform.h"
#include "Components/StaticMeshComponent.h"

ARotatingPlatform::ARotatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	// �ʱ� ����
	PlatformMesh->SetMobility(EComponentMobility::Movable);
}

void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Ÿ�̸� ��� ���� ��ȯ ����
	if (bTimerFlipDirection && FlipIntervalSec > 0.f)
	{
		GetWorldTimerManager().SetTimer(
			FlipTimerHandle,
			this,
			&ARotatingPlatform::OnTimerEvent,
			FlipIntervalSec,
			true // ���� �ݺ�
		);
	}
}

void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �������� ȸ��
	const FRotator RotationDelta(0.f, RotateSpeed * DeltaTime, 0.f); // YAW ������ ȸ��
	AddActorWorldRotation(RotationDelta);
}

void ARotatingPlatform::OnTimerEvent()
{
	// Ÿ�̸� �̺�Ʈ �߻� �� ȸ�� �ӵ��� ��ȣ�� ���� (���� ��ȯ)
	if (bTimerFlipDirection)
	{
		// RotateSpeed *= -1.f; �� RotationSpeed = -RotationSpeed; �� ���� ���
		RotateSpeed *= -1.f;
	}
}