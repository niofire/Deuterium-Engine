#pragma once
#include <cmath>
#ifdef ANDROID
#define throw 0
#endif
#define PI 3.1415926f
namespace deuterium
{
struct Vec2f
{
	//--------------------------------------------------
	//				Cosntructor / Destructor
	//---------------------------------------------------
	Vec2f(){x= y= 0;};
	Vec2f(float x, float y)	{this->x = x; this->y = y;};
	virtual ~Vec2f() { };

	//--------------------------------------------------
	//				Core function
	//-------------------------------------------------
	inline float*				GetPtr()	{return &x;};


	//---------------------------------------------------
	//				operator overloading
	//---------------------------------------------------
	Vec2f	operator+( Vec2f &_v) const					{ return Vec2f(x + _v.x,y + _v.y);};
	Vec2f	&operator+=(Vec2f &_v)						{ x += _v.x; y += _v.y; return *this;};
	float	operator*( Vec2f &_v) const					{ return x * _v.x+ y* _v.y;};
	Vec2f	operator*(const float _v) const				{ return Vec2f(x * _v, y * _v);};
	Vec2f	&operator*=(const float _v) 				{ x *= _v; y *= _v; return *this;};
	Vec2f	operator-() const							{return Vec2f(-x,-y);};
	Vec2f	operator-(const float _v) const				{return Vec2f(x - _v, y - _v);};
	Vec2f	operator-(const Vec2f _v) const				{return Vec2f(x - _v.x, y - _v.y);};
	Vec2f	&operator-=(const float _v)					{ x-= _v; y -= _v; return *this;};
	Vec2f	operator/(const float _v) const				{return Vec2f(x/_v,y/_v);};
	Vec2f	&operator/=(const float _v)					{ x/=_v;y/=_v; return *this;};	
	float	&operator[](int _i)							{ (_i < 2) ? 0:throw; return (&x)[_i];};
	inline Vec2f &operator=(const Vec2f &_v)			{ x = _v.x;y = _v.y;};
	Vec2f	GetNormalized()								{ return (*this)/sqrtf(((*this)*(*this)));};
	Vec2f	Normalize()									{return (*this)/=sqrtf(((*this)*(*this)));};
	//--------------------------------------------------
	//				static functions
	//-------------------------------------------------

	Vec2f	Zero()										{return Vec2f(0,0);};
	Vec2f	One()										{return	Vec2f(1,1);};
	float		x,y;

};






struct Vec3f
{
	//--------------------------------------------------
	//				Cosntructor / Destructor
	//---------------------------------------------------
	Vec3f(){x = y = z = 0;};
	Vec3f(float x, float y, float z) { this->x = x; this->y = y; this->z = z;};
	Vec3f(Vec2f vec1, float z) {this->x = vec1.x; this->y = vec1.y; this->z = z;};
	Vec3f(float x, Vec2f vec2) {this->x = x; this->y = vec2.x; this->z = vec2.y;};
	~Vec3f() { };

	//--------------------------------------------------
	//				Core function
	//-------------------------------------------------
	inline float*				GetPtr()	{return &x;};


	//---------------------------------------------------
	//				operator overloading
	//---------------------------------------------------
	Vec3f	operator+( Vec3f &_v) const					{ return Vec3f(x + _v.x,y + _v.y, z + _v.z);};
	Vec3f	&operator+=(Vec3f &_v)						{ x += _v.x; y += _v.y; z += _v.z; return *this;};
	float	operator*( Vec3f &_v) const					{ return x * _v.x+ y* _v.y + z * _v.z;};
	Vec3f	operator*(const float _v) const				{ return Vec3f(x * _v, y * _v,z*_v);};
	Vec3f	&operator*=(const float _v) 				{ x *= _v; y *= _v; z *= _v; return *this;};
	Vec3f	operator-() const							{return Vec3f(-x,-y, -z);};
	Vec3f	operator-(const float _v) const				{return Vec3f(x - _v, y - _v, z-_v);};
	Vec3f	operator-(const Vec3f _v) const				{return Vec3f(x - _v.x, y - _v.y, z-_v.z);};
	Vec3f	&operator-=(const float _v)					{ x-= _v; y -= _v; z -= _v; return *this;};
	Vec3f	operator/(const float _v) const				{return Vec3f(x/_v,y/_v, z/_v);};
	Vec3f	&operator/=(const float _v)					{ x/=_v;y/=_v;z/=_v; return *this;};	
	float	&operator[](int _i)							{ (_i < 3) ? 0:throw; return (&x)[_i];};
	inline Vec3f &operator=(const Vec3f &_v)			{ x = _v.x;y = _v.y; z = _v.z; return *this;};
	
	Vec3f	GetNormalized()								{ return (*this)/sqrtf(((*this)*(*this)));};
	void	Normalize()									{ (*this)/=sqrtf(((*this)*(*this)));};
	//--------------------------------------------------
	//				static functions
	//-------------------------------------------------

	Vec3f	Zero()										{return Vec3f(0,0,0);};
	Vec3f	One()										{return	Vec3f(1,1,1);};
	float		x,y,z;

};


struct Vec4f
{
	//--------------------------------------------------
	//				Cosntructor / Destructor
	//---------------------------------------------------
	Vec4f()	{x = 0; y = 0; z = 0; w = 0;};
	Vec4f(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w;};
	Vec4f(Vec4f vec1,Vec4f vec2){this->x = vec1.x;this->y = vec1.y; this->z = vec2.x; this->w = vec2.y;};
	Vec4f(Vec3f vec1, float w) {this->x = vec1.x;this->y = vec1.y; this->z = vec1.z; this->w = w;};
	Vec4f(float x, Vec3f vec1) {this->x = x;this->y = vec1.x; this->z = vec1.y; this->w = z;};
	~Vec4f() { };
	//--------------------------------------------------
	//				Core function
	//-------------------------------------------------
	inline float*				GetPtr()	{return &x;};


	//---------------------------------------------------
	//				operator overloading
	//---------------------------------------------------
	Vec4f	operator+(const Vec4f &_v) const					{ return Vec4f(x + _v.x,y + _v.y, z + _v.z,w + _v.w);};
	Vec4f	&operator+=(Vec4f &_v)						{ x += _v.x; y += _v.y; z += _v.z; w += _v.w; return *this;};
	float	operator*(Vec4f &_v) const					{ return x * _v.x+ y* _v.y + z * _v.z + w* _v.w;};
	Vec4f	operator*(const float _v) const				{ return Vec4f(x * _v, y * _v,z*_v, w*_v);};
	Vec4f	&operator*=(const float _v) 				{ x *= _v; y *= _v; z *= _v; w *= _v;return *this;};
	Vec4f	operator-() const							{return Vec4f(-x,-y, -z,-w);};
	Vec4f	operator-(const float _v) const				{return Vec4f(x - _v, y - _v, z-_v, w - _v);};
	Vec4f	operator-(const Vec4f _v) const				{return Vec4f(x - _v.x, y - _v.y, z-_v.z, w - _v.w);};
	Vec4f	operator-=(const float _v)					{ x-= _v; y -= _v; z -= _v, w -= _v; return *this;};
	Vec4f	operator/(const float _v) const				{return Vec4f(x/_v,y/_v, z/_v, w/_v);};
	Vec4f	operator/=(const float _v)					{ x/=_v;y/=_v;z/=_v;w /= _v; return *this;};
	float	&operator[](int _i)							{ (_i < 4) ? 0:throw; return (&x)[_i];};
	inline Vec4f &operator=(const Vec4f &_v)			{ x = _v.x;y = _v.y;z = _v.z; w = _v.w;return *this;};

	Vec4f	GetNormalized()								{ return (*this)/sqrtf(((*this)*(*this)));};
	Vec4f	Normalize()									{return (*this)/=sqrtf(((*this)*(*this)));};
	//--------------------------------------------------
	//				static functions
	//-------------------------------------------------

	Vec4f	Zero()										{return Vec4f(0,0,0,0);};
	Vec4f	One()										{return	Vec4f(1,1,1,1);};
	float		x,y,z,w;

};


class Mat3x3
{
public:
	Mat3x3();
	Mat3x3(	float m00, float m10, float m20, 
			float m01, float m11, float m21,
			float m02, float m12, float m22);
	Mat3x3(Vec3f col1, Vec3f col2, Vec3f col3);
	//Mat3x3(Mat3x3 i_CopyMath);
	~Mat3x3();
	float*	GetPtr()	{return &_m[0].x;};

	Mat3x3	operator*(Mat3x3 m);
	Mat3x3  &operator*=(Mat3x3 m);
	Vec3f	operator*(const Vec3f _v);
	Vec3f	&operator[](int _i)	{ (_i < 3) ? 0:throw; return (_m[_i]);};
	Mat3x3	&operator=( Mat3x3 _m);
	void	Transpose();
	Mat3x3	GetTranspose();
	void	SetIdentity();
	static Mat3x3 GetIdentity();
	Vec3f _m[3];
};

class Mat4x4
{
public:
	Mat4x4();
	Mat4x4(	float m00, float m10, float m20,float m30, 
			float m01, float m11, float m21,float m31,
			float m02, float m12, float m22,float m32,
			float m03, float m13, float m23,float m33);
	Mat4x4(Vec4f col1, Vec4f col2, Vec4f col3, Vec4f col4);
	Mat4x4(Mat3x3 mat1);
	//Mat4x4(Mat4x4 i_CopyMath);
	~Mat4x4();
	float*	GetPtr()	{return &_m[0].x;};

	Mat4x4	operator*(Mat4x4 m);
	Mat4x4  &operator*=(Mat4x4 m);
	Vec4f	operator*(const Vec4f _v);
	Vec4f	&operator[](int _i)	{ (_i < 4) ? 0:throw; return (_m[_i]);};
	Mat4x4	&operator=( Mat4x4 _m);
	void	Transpose();
	Mat4x4	GetTranspose();
	void	SetIdentity();
	static Mat4x4 GetIdentity();
	Vec4f _m[4];
};


class MathHelper_L
{
public:
	MathHelper_L();
	~MathHelper_L();
	static float	DegToRad(float i_Angle)	{ return (i_Angle/360) * 2 * PI;}
	static float	RadToDef(float i_Angle)	{ return (i_Angle * 360 / (2*PI));}
	static Vec3f	CrossProduct(Vec3f& v1, Vec3f& v2) {return Vec3f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);}
	static void		FastTranslate(Mat4x4& _m, Vec3f _v);

};
}
