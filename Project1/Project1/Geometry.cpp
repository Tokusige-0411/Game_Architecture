#include"Geometry.h"
#include<DxLib.h>
#include<cmath>


void
Rect::Draw() {
	DxLib::DrawBox(Left() * 2, Top() * 2, Right() * 2, Bottom() * 2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((Left() + offset.x) * 2, (Top() + offset.y) * 2, (Right() + offset.x) * 2, (Bottom() + offset.y) * 2, 0xffffffff, false);
}

void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

Vector2
Vector2::operator*(float scale) {
	return Vector2(x * scale, y * scale);
}

bool Vector2::operator==(const Vector2& v)
{
	return (x == v.x && y == v.y);
}

bool Vector2::operator!=(const Vector2& v)
{
	return !(x == v.x && y == v.y);
}

Vector2 operator+(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x + vb.x, va.y + vb.y);
}

Vector2 operator-(const Vector2& va, const Vector2 vb) {
	return Vector2(va.x - vb.x, va.y - vb.y);
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}


void
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}


Vector2
Vector2::Normalized() {
	float mag = Magnitude();
	return Vector2(x / mag, y / mag);
}


Vector2 Vector2::Rotate90(void)
{
	return {-y, x};
}


///���ς�Ԃ�
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x * vb.x + va.y * vb.y;
}

///�O�ς�Ԃ�
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x * vb.y - vb.x * va.y;
}

///���ω��Z�q
float
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
float
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


void
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}


//-------��������3D�̃^�[��------
void
Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

Vector3
Vector3::operator*(float scale)const {
	return Vector3(x * scale, y * scale, z * scale);
}

Vector3 Vector3::operator*(Vector3 v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 operator+(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x + vb.x, va.y + vb.y, va.z + vb.z);
}

Vector3 operator-(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x - vb.x, va.y - vb.y, va.z - vb.z);
}

float
Vector3::Magnitude()const {
	return sqrt(x * x + y * y + z * z);
}


void
Vector3::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}


Vector3
Vector3::Normalized() {
	float mag = Magnitude();
	return Vector3(x / mag, y / mag, z / mag);
}


///���ς�Ԃ�
float
Dot(const Vector3& va, const Vector3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

///�O�ς�Ԃ�
Vector3
Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z * vb.y - va.y * vb.z, va.z * vb.x - va.x * vb.z, va.x * vb.y - vb.x * va.y);
}

///���ω��Z�q
float
operator*(const Vector3& va, const Vector3& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
Vector3
operator%(const Vector3& va, const Vector3& vb) {
	return Cross(va, vb);
}


void
Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
void
Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}


bool Plane::ChackHit(const RayLine& ray, float& t, Vector3& normal) const
{
	//�n�ʂɓ������Ă���
	//���ʂ̌�_P=eye+ray*t
	//t=w/u(w�͕��ʂ���̋���)
	//���ʂɋ߂Â��傫��
	//w = eye�EN, u = -ray�EN
	//t=w/u�Ƃ��������A���ʂɂ�offset(d)������
	//t = (w+d)/u
	//���Ƃ͂��������_P�����߂�
	//����t�͂S�����炢
	auto rayD = Dot(ray.vector, this->normal);
	if (rayD < 0.0f)
	{
		auto w = Dot(ray.start, this->normal);
		auto rayVec = ray.vector;
		auto u = Dot(-rayVec, this->normal);
		t = (w + this->offset) / u;
		return true;
	}
	else
	{
		return false;
	}
}

const Material& Plane::GetMaterial(void) const
{
	return material;
}

float Plane::DistanceFromStart(const Position3& pos)
{
	return 0.0f;
}

bool Sphere::ChackHit(const RayLine& ray, float& t, Vector3& normal) const
{
	//���C�����K���ς݂ł���O��Łc
	//
	//���_���狅�̒��S�ւ̃x�N�g��(����)�����܂�
	Vector3 centerVec = this->pos - ray.start;
	//���S���王���ւ̓��ς��Ƃ�܂������x�N�g����
	auto dot = Dot(centerVec, ray.vector);
	//�����x�N�g���ƃx�N�g�����������āA���S����̐����������_�����߂܂�
	//����tmp��R(C�ER)�ƂȂ�
	auto V = centerVec - ray.vector * dot;
	if (V.Magnitude() <= this->radius)
	{
		// �\�ʂ̌�_t�����߂�
		auto w = sqrt((this->radius * this->radius) - (V.Magnitude() * V.Magnitude()));
		t = dot - w;
		if (t < 0.0f)
		{
			return false;
		}
		// t�����_P�����߂�
		auto hitpos = ray.start + (ray.vector * t);
		// ���̂̒��S�����_P�ւ̖@���x�N�g�������߂�
		normal = (hitpos - this->pos).Normalized();
		return true;
	}
	else
	{
		return false;
	}
}

const Material& Sphere::GetMaterial(void) const
{
	return material;
}

float Sphere::DistanceFromStart(const Position3& pos)
{
	return 0.0f;
}
