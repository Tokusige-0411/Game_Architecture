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


///内積を返す
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x * vb.x + va.y * vb.y;
}

///外積を返す
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x * vb.y - vb.x * va.y;
}

///内積演算子
float
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///外積演算子
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


//-------ここから3Dのターン------
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


///内積を返す
float
Dot(const Vector3& va, const Vector3& vb) {
	return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

///外積を返す
Vector3
Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z * vb.y - va.y * vb.z, va.z * vb.x - va.x * vb.z, va.x * vb.y - vb.x * va.y);
}

///内積演算子
float
operator*(const Vector3& va, const Vector3& vb) {
	return Dot(va, vb);
}

///外積演算子
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
	//地面に当たっている
	//平面の交点P=eye+ray*t
	//t=w/u(wは平面からの距離)
	//平面に近づく大きさ
	//w = eye・N, u = -ray・N
	//t=w/uとしたいが、平面にはoffset(d)がある
	//t = (w+d)/u
	//あとはここから交点Pを求める
	//多分tは４万ぐらい
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
	//レイが正規化済みである前提で…
	//
	//視点から球体中心へのベクトル(視線)を作ります
	Vector3 centerVec = this->pos - ray.start;
	//中心から視線への内積をとります＝＞ベクトル長
	auto dot = Dot(centerVec, ray.vector);
	//視線ベクトルとベクトル長をかけて、中心からの垂線下した点を求めます
	//このtmpがR(C・R)となる
	auto V = centerVec - ray.vector * dot;
	if (V.Magnitude() <= this->radius)
	{
		// 表面の交点tを求める
		auto w = sqrt((this->radius * this->radius) - (V.Magnitude() * V.Magnitude()));
		t = dot - w;
		if (t < 0.0f)
		{
			return false;
		}
		// tから交点Pを求める
		auto hitpos = ray.start + (ray.vector * t);
		// 球体の中心から交点Pへの法線ベクトルを求める
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
