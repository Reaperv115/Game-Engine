#include "trpch.h"
#include "Camera.h"

Camera::Camera()
{
	this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

void Camera::SetProjectionValues(float fovdegs, float aspectrat, float nearz, float farz)
{
	float fovRads = (fovdegs / 360.0f) * XM_2PI;
	this->projectionMat = XMMatrixPerspectiveFovLH(fovRads, aspectrat, nearz, farz);
}

const DirectX::XMMATRIX& Camera::GetViewMat() const
{
	return this->viewMat;
}

const DirectX::XMMATRIX& Camera::GetProjectionMat() const
{
	return this->projectionMat;
}

const DirectX::XMVECTOR& Camera::GetPosVector() const
{
	return this->posVector;
}

const DirectX::XMFLOAT3& Camera::GetPosFloat3() const
{
	return this->pos;
}

const DirectX::XMVECTOR& Camera::GetRotationVector() const
{
	return this->rotVector;
}

const DirectX::XMFLOAT3& Camera::GetRotationFloat3() const
{
	return this->rot;
}

// setting position
void Camera::SetPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateViewMat();
}

void Camera::SetPosition(const XMFLOAT3& pos)
{
	this->pos = pos;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMat();
}

void Camera::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMat();
}

// adjusting position
void Camera::AdjustPosition(const XMVECTOR& pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateViewMat();
}

void Camera::AdjustPosition(const XMFLOAT3& pos)
{
	this->pos.x += pos.x;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMat();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMat();
}

// setting rotation
void Camera::SetRotation(const XMVECTOR& rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateViewMat();
}

void Camera::SetRotation(const XMFLOAT3& rot)
{
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

void Camera::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

//adjusting rotation
void Camera::AdjustRotation(const XMVECTOR& rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateViewMat();
}

void Camera::AdjustRotation(const XMFLOAT3& rot)
{
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

void Camera::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMat();
}

void Camera::SetookatPos(XMFLOAT3 lookatPos)
{
	if (lookatPos.x == this->pos.x && lookatPos.y == this->pos.y && lookatPos.z == this->pos.z)
		return;

	lookatPos.x = this->pos.x - lookatPos.x;
	lookatPos.y = this->pos.y - lookatPos.y;
	lookatPos.z = this->pos.z - lookatPos.z;

	float pitch = 0;
	if (lookatPos.y != 0.0f)
	{
		const float distance = sqrt(lookatPos.x * lookatPos.x + lookatPos.z * lookatPos.z);
		pitch = atan(lookatPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookatPos.x != 0.0f)
	{
		yaw = atan(lookatPos.x / lookatPos.z);
	}
	if (lookatPos.z > 0)
		yaw += XM_PI;

	this->SetRotation(pitch, yaw, 0.0f);
}

const DirectX::XMVECTOR& Camera::GetForwardVector()
{
	return this->vecForward;
}

const DirectX::XMVECTOR& Camera::GetRightVector()
{
	return this->vecRight;
}

const DirectX::XMVECTOR& Camera::GetBackwardVector()
{
	return this->vecBackward;
}

const DirectX::XMVECTOR& Camera::GetLeftVector()
{
	return this->vecLeft;
}

const DirectX::XMVECTOR& Camera::GetUpVector()
{
	return this->vecUpward;
}

const DirectX::XMVECTOR& Camera::GetDownVector()
{
	return this->vecDownward;
}

void Camera::UpdateViewMat()
{
	XMMATRIX camrotationMat = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	XMVECTOR camTarg = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camrotationMat);
	camTarg += this->posVector;
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camrotationMat);
	this->viewMat = XMMatrixLookAtLH(this->posVector, camTarg, upDir);

	XMMATRIX vecrotationMat = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vecForward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecrotationMat);
	this->vecBackward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecrotationMat);
	this->vecLeft = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecrotationMat);
	this->vecRight = XMVector3Transform(this->DEFAULT_RIGHT_VECTOR, vecrotationMat);
}
