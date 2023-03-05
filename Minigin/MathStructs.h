#pragma once
#define ZeroVector3 Vector3()
#define UnitVector3 Vector3(1.f,1.f,1.f)

#define ZeroVector2 Vector2()
#define UnitVector2 Vector2(1.f,1.f)
struct Vector2
{
	//=== Datamembers ===
	float x = 0.0f;
	float y = 0.0f;

	//=== Constructors ===
	Vector2() = default;
	Vector2(float _x, float _y) :x(_x), y(_y) {};
};
//Vector 3D
struct Vector3
{
	//=== Datamembers ===
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	//=== Constructors ===
	Vector3() {};
	Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {};
	explicit Vector3(const Vector2 v, float _z = 0.f) :x(v.x), y(v.y), z(_z) {};
	//Vector3(const Vector3& other); //Copy Constructor
	//Vector3& operator=(const Vector3& other); //Copy Assignment Operator
};