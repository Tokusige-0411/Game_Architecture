#pragma once

//サイズを表す構造体
struct Size {
	float w;//幅
	float h;//高さ
};

//2D座標・ベクトルを表す構造体
struct Vector2 {
	Vector2() :x(0), y(0) {}
	Vector2(float inx, float iny) :x(inx), y(iny) {}
	float x, y;
	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
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

///内積を返す
float Dot(const Vector2& va, const Vector2& vb);

///外積を返す
float Cross(const Vector2& va, const Vector2& vb);

///内積演算子
float operator*(const Vector2& va, const Vector2& vb);

///外積演算子
float operator%(const Vector2& va, const Vector2& vb);

//とりあえず「座標」って意味だとベクタより
//Positionのほうがよくね？って理由でこの名前
typedef Vector2 Position2;


//3D座標・ベクトルを表す構造体
struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float inx, float iny, float inz) :x(inx), y(iny), z(inz) {}
	float x, y, z;
	///ベクトルの大きさを返します
	float Magnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
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

///内積を返す
float Dot(const Vector3& va, const Vector3& vb);

///外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb);

///内積演算子
float operator*(const Vector3& va, const Vector3& vb);

///外積演算子
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

using Color = Vector3;


// 直線(光線)を表す構造体
struct RayLine
{
	Position3 start;
	Vector3 vector;

	// コンストラクタ
	RayLine(const Position3& s, const Vector3& v) : start(s), vector(v) {};

	// 始点と終点から視線を作成
	void InitFromStartEnd(const Position3& s, const Vector3& e) {
		start = s;
		vector = (e - s).Normalized();
	}
};

// 表面模様定義
enum class Pattern
{
	none,			// 模様なし
	hstripe,		// 縞模様(横)
	vstripe,		// 縞模様(縦)
	chackered,		// 市松模様
	textured,		// テクスチャ
};

//Vector3 White = Vector3(1.0, 1.0, 1.0);
//Vector3 Black = Vector3(1.0, 1.0, 1.0);

// 表面の材質を表す構造体
struct Material
{
	Color diffuse;			// 拡散反射成分
	Color specular;			// 鏡面反射成分
	Color ambient;			// 環境光(ゲタ)
	float specularity;		// スペキュラの強さ
	float reflectance;		// 反射率
	Pattern pattern;		//模様種別
	Material() : diffuse(1, 1, 1), specular(0, 0, 0), ambient(0, 0, 0), specularity(0), reflectance(0), pattern(Pattern::none) {}
	Material(const Color& diff, const Color& spec, const Color& amb, float inSpecularity, float inReflectance, Pattern p = Pattern::none) :
		diffuse(diff), specular(spec), ambient(amb), specularity(inSpecularity), reflectance(inReflectance), pattern(p) {}
};

// 物体の親になる奴
struct Primitive
{
public:
	Material material;
	Primitive(const Material& m) : material(m) {}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="ray"></視線から始まる直線>
	/// <param name="hitPos"></衝突点>
	/// <param name="normal"></衝突点からの法線ベクトル>
	/// <returns></returns>
	virtual bool ChackHit(const RayLine& ray, float& t, Vector3& normal)const = 0;
	/// <summary>
	/// マテリアルを返す
	/// </summary>
	/// <param name=""></param>
	/// <returns></マテリアル>
	virtual const Material& GetMaterial(void) const = 0;
	/// <summary>
	/// 指定座標からの最短距離
	/// </summary>
	/// <param name="pos"></距離を測りたい点(座標)>
	/// <returns></returns>
	virtual float DistanceFromStart(const Position3& pos) = 0;
};

///円を表す構造体
struct Circle {
	float radius;//半径
	Position2 pos; //中心座標
	Circle() :radius(0), pos(0, 0) {}
	Circle(float r, Position2& p) :radius(r), pos(p) {}
};

///球を表す構造体
struct Sphere : public Primitive {
public:
	float radius;//半径
	Position3 pos; //中心座標
	Sphere() : radius(0), pos(0, 0, 0), Primitive(Material()) {}
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="r"></半径>
	/// <param name="p"></中心座標>
	/// <param name="m"></マテリアル>
	Sphere(float r, Position3& p, Material& m) : radius(r), pos(p), Primitive(m) {}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="ray"></視線から始まる直線>
	/// <param name="hitPos"></衝突点>
	/// <param name="normal"></衝突点からの法線ベクトル>
	/// <returns></returns>
	bool ChackHit(const RayLine& ray, float& t, Vector3& normal)const override;
	/// <summary>
	/// マテリアルを返す
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Material& GetMaterial(void)const override;
	/// <summary>
	/// 指定座標からの最短距離
	/// </summary>
	/// <param name="pos"></距離を測りたい点(座標)>
	/// <returns></returns>
	float DistanceFromStart(const Position3& pos)override;
};

// 平面
struct Plane : public Primitive
{
public:
	Vector3 normal;		// 法線ベクトル
	float offset;		// 原点からのオフセット(ただし-方向)
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="n"></法線ベクトル>
	/// <param name="o"></原点からのオフセット>
	/// <param name="m"></マテリアル>
	Plane(Vector3& n, float o, const Material& m) : normal(n), offset(o), Primitive(m) {};

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="ray"></視線から始まる直線>
	/// <param name="hitPos"></衝突点>
	/// <param name="normal"></衝突点からの法線ベクトル>
	/// <returns></returns>
	bool ChackHit(const RayLine& ray, float& t, Vector3& normal)const override;
	/// <summary>
	/// マテリアルを返す
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Material& GetMaterial(void)const override;
	/// <summary>
	/// 指定座標からの最短距離
	/// </summary>
	/// <param name="pos"></距離を測りたい点(座標)>
	/// <returns></returns>
	float DistanceFromStart(const Position3& pos)override;
};

///矩形を表す構造体
struct Rect {
	Position2 pos; //中心座標
	int w, h;//幅,高さ
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
	void Draw();//自分の矩形を描画する
	void Draw(Vector2& offset);//自分の矩形を描画する(オフセット付き)
};