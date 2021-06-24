#pragma once

//�T�C�Y��\���\����
struct Size {
	float w;//��
	float h;//����
};

//2D���W�E�x�N�g����\���\����
struct Vector2 {
	Vector2() :x(0), y(0) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {}
	float x, y;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector2 Normalized();

	Vector2 Rotate90(void);

	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(float scale);
	Vector2 operator*(float scale);
	Vector2 operator-() {
		return Vector2(-x, -y);
	}
	static const Vector2 Zero(){
		return { 0.0f, 0.0f };
	}

	bool operator==(const Vector2& v);
	bool operator!=(const Vector2& v);
};

Vector2 operator+(const Vector2& va, const Vector2 vb);
Vector2 operator-(const Vector2& va, const Vector2 vb);

///���ς�Ԃ�
float Dot(const Vector2& va, const Vector2& vb);

///�O�ς�Ԃ�
float Cross(const Vector2& va, const Vector2& vb);

///���ω��Z�q
float operator*(const Vector2& va, const Vector2& vb);

///�O�ω��Z�q
float operator%(const Vector2& va, const Vector2& vb);

//�Ƃ肠�����u���W�v���ĈӖ����ƃx�N�^���
//Position�̂ق����悭�ˁH���ė��R�ł��̖��O
typedef Vector2 Position2;


//3D���W�E�x�N�g����\���\����
struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float inx, float iny, float inz) :x(inx), y(iny), z(inz) {}
	float x, y, z;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector3 Normalized();

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	Vector3 operator*(Vector3 v)const;
	Vector3 operator-() {
		return Vector3(-x, -y, -z);
	}
};
Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

///���ς�Ԃ�
float Dot(const Vector3& va, const Vector3& vb);

///�O�ς�Ԃ�
Vector3 Cross(const Vector3& va, const Vector3& vb);

///���ω��Z�q
float operator*(const Vector3& va, const Vector3& vb);

///�O�ω��Z�q
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

using Color = Vector3;


// ����(����)��\���\����
struct RayLine
{
	Position3 start;
	Vector3 vector;

	// �R���X�g���N�^
	RayLine(const Position3& s, const Vector3& v) : start(s), vector(v) {};

	// �n�_�ƏI�_���王�����쐬
	void InitFromStartEnd(const Position3& s, const Vector3& e) {
		start = s;
		vector = (e - s).Normalized();
	}
};

// �\�ʖ͗l��`
enum class Pattern
{
	none,			// �͗l�Ȃ�
	hstripe,		// �Ȗ͗l(��)
	vstripe,		// �Ȗ͗l(�c)
	chackered,		// �s���͗l
	textured,		// �e�N�X�`��
};

//Vector3 White = Vector3(1.0, 1.0, 1.0);
//Vector3 Black = Vector3(1.0, 1.0, 1.0);

// �\�ʂ̍ގ���\���\����
struct Material
{
	Color diffuse;			// �g�U���ː���
	Color specular;			// ���ʔ��ː���
	Color ambient;			// ����(�Q�^)
	float specularity;		// �X�y�L�����̋���
	float reflectance;		// ���˗�
	Pattern pattern;		//�͗l���
	Material() : diffuse(1, 1, 1), specular(0, 0, 0), ambient(0, 0, 0), specularity(0), reflectance(0), pattern(Pattern::none) {}
	Material(const Color& diff, const Color& spec, const Color& amb, float inSpecularity, float inReflectance, Pattern p = Pattern::none) :
		diffuse(diff), specular(spec), ambient(amb), specularity(inSpecularity), reflectance(inReflectance), pattern(p) {}
};

// ���̂̐e�ɂȂ�z
struct Primitive
{
public:
	Material material;
	Primitive(const Material& m) : material(m) {}

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="ray"></��������n�܂钼��>
	/// <param name="hitPos"></�Փ˓_>
	/// <param name="normal"></�Փ˓_����̖@���x�N�g��>
	/// <returns></returns>
	virtual bool ChackHit(const RayLine& ray, float& t, Vector3& normal)const = 0;
	/// <summary>
	/// �}�e���A����Ԃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns></�}�e���A��>
	virtual const Material& GetMaterial(void) const = 0;
	/// <summary>
	/// �w����W����̍ŒZ����
	/// </summary>
	/// <param name="pos"></�����𑪂肽���_(���W)>
	/// <returns></returns>
	virtual float DistanceFromStart(const Position3& pos) = 0;
};

///�~��\���\����
struct Circle {
	float radius;//���a
	Position2 pos; //���S���W
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};

///����\���\����
struct Sphere : public Primitive {
public:
	float radius;//���a
	Position3 pos; //���S���W
	Sphere() : radius(0), pos(0, 0, 0), Primitive(Material()) {}
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="r"></���a>
	/// <param name="p"></���S���W>
	/// <param name="m"></�}�e���A��>
	Sphere(float r, Position3& p, Material& m) : radius(r), pos(p), Primitive(m) {}

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="ray"></��������n�܂钼��>
	/// <param name="hitPos"></�Փ˓_>
	/// <param name="normal"></�Փ˓_����̖@���x�N�g��>
	/// <returns></returns>
	bool ChackHit(const RayLine& ray, float& t, Vector3& normal)const override;
	/// <summary>
	/// �}�e���A����Ԃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Material& GetMaterial(void)const override;
	/// <summary>
	/// �w����W����̍ŒZ����
	/// </summary>
	/// <param name="pos"></�����𑪂肽���_(���W)>
	/// <returns></returns>
	float DistanceFromStart(const Position3& pos)override;
};

// ����
struct Plane : public Primitive
{
public:
	Vector3 normal;		// �@���x�N�g��
	float offset;		// ���_����̃I�t�Z�b�g(������-����)
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="n"></�@���x�N�g��>
	/// <param name="o"></���_����̃I�t�Z�b�g>
	/// <param name="m"></�}�e���A��>
	Plane(Vector3& n, float o, const Material& m) : normal(n), offset(o), Primitive(m) {};

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="ray"></��������n�܂钼��>
	/// <param name="hitPos"></�Փ˓_>
	/// <param name="normal"></�Փ˓_����̖@���x�N�g��>
	/// <returns></returns>
	bool ChackHit(const RayLine& ray, float& t, Vector3& normal)const override;
	/// <summary>
	/// �}�e���A����Ԃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Material& GetMaterial(void)const override;
	/// <summary>
	/// �w����W����̍ŒZ����
	/// </summary>
	/// <param name="pos"></�����𑪂肽���_(���W)>
	/// <returns></returns>
	float DistanceFromStart(const Position3& pos)override;
};

///��`��\���\����
struct Rect {
	Position2 pos; //���S���W
	int w, h;//��,����
	Rect() : pos(0, 0), w(0), h(0) {}
	Rect(float x, float y, int inw, int inh) :
		pos(x, y), w(inw), h(inh) {}
	Rect(Position2& inpos, int inw, int inh) :
		pos(inpos), w(inw), h(inh)
	{}
	void SetCenter(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void SetCenter(const Position2& inpos) {
		pos.x = inpos.x;
		pos.y = inpos.y;
	}
	Vector2 Center() {
		return pos;
	}
	float Left() { return pos.x - w / 2; }
	float Top() { return pos.y - h / 2; }
	float Right() { return pos.x + w / 2; }
	float Bottom() { return pos.y + h / 2; }
	void Draw();//�����̋�`��`�悷��
	void Draw(Vector2& offset);//�����̋�`��`�悷��(�I�t�Z�b�g�t��)
};