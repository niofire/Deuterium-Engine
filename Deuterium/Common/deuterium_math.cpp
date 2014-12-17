#include "deuterium_math.h"

//-----------------------------------------------------------------------------------
//								Mat3x3
//-----------------------------------------------------------------------------------
namespace deuterium
{
Mat3x3::Mat3x3()
{
	for(int i = 0; i < 3; ++i)
		_m[i] = Vec3f(0,0,0);
}

Mat3x3::Mat3x3(float m00, float m10, float m20, 
			float m01, float m11, float m21,
			float m02, float m12, float m22)
{
	_m[0][0] = m00;	_m[0][1] = m10; _m[0][2] = m20;
	_m[1][0] = m01;	_m[1][1] = m11; _m[1][2] = m21;
	_m[2][0] = m02;	_m[2][1] = m12; _m[2][2] = m22;
}

Mat3x3::Mat3x3(Vec3f col1, Vec3f col2, Vec3f col3)
{
	_m[0] = col1;
	_m[1] = col2;
	_m[2] = col3;
}

Mat3x3::~Mat3x3()
{

}

Mat3x3	Mat3x3::operator*(Mat3x3 m)
{
	Mat3x3 temp;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			temp[i][j] = m[i][0] * _m[0][j] + m[i][1] * _m[1][j] + m[i][2] * _m[2][j];
		}
	}
	return temp;
}

Mat3x3&	Mat3x3::operator*=(Mat3x3 m)
{
	Mat3x3 temp(*this);
	
	return *this = temp*m;

}

Vec3f Mat3x3::operator*(Vec3f  _v)
{
	Vec3f temp;
	for(int i = 0; i < 3; ++i)
	{
			temp[i] =   _v[0] * _m[0][i] + _v[1] * _m[1][i] +  _v[2]  *_m[2][i];
		
	}
	return temp;
}
	
Mat3x3& Mat3x3::operator=( Mat3x3 _m)
{
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			this->_m[i][j] = _m[i][j];
	return *this;
}

Mat3x3 Mat3x3::GetIdentity()
{
	return Mat3x3(Vec3f(1,0,0),Vec3f(0,1,0),Vec3f(0,0,1));
}

void Mat3x3::SetIdentity()
{
	*this = Mat3x3(Vec3f(1,0,0),Vec3f(0,1,0),Vec3f(0,0,1));
}

Mat3x3 Mat3x3::GetTranspose()
{
	Mat3x3 temp;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3 ; ++j)
		{
			temp[i][j] = _m[j][i];
		}
	}
	return temp;
}

void Mat3x3::Transpose()
{
	*this = this->GetTranspose();
}



//----------------------------------------------------------------
//					Mat4x4
//----------------------------------------------------------------

Mat4x4::Mat4x4()
{
	this->SetIdentity();

}

Mat4x4::Mat4x4(	float m00, float m10, float m20,float m30, 
				float m01, float m11, float m21,float m31,
				float m02, float m12, float m22,float m32,
				float m03, float m13, float m23,float m33)
{

	_m[0][0] = m00;	_m[0][1] = m10; _m[0][2] = m20; _m[0][3] = m30;
	_m[1][0] = m01;	_m[1][1] = m11; _m[1][2] = m21; _m[1][3] = m31;
	_m[2][0] = m02;	_m[2][1] = m12; _m[2][2] = m22; _m[2][3] = m32;
	_m[3][0] = m03;	_m[3][1] = m13; _m[3][2] = m23; _m[3][3] = m33;
}

Mat4x4::Mat4x4(Vec4f col1, Vec4f col2, Vec4f col3, Vec4f col4)
{
	_m[0] = col1;
	_m[1] = col2;
	_m[2] = col3;
	_m[3] = col4;
}
Mat4x4::Mat4x4(Mat3x3 m1)
{
	for(int i =0; i < 3; ++i)
	{
		_m[i] = Vec4f(m1[i],0);
	}
	_m[3] = Vec4f(0,0,0,0);
}

Mat4x4::~Mat4x4()
{
	//do nothing
}

Mat4x4 Mat4x4::operator*(Mat4x4 m)
{
	Mat4x4 temp;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			temp[i][j] = m[i][0] * _m[0][j] + m[i][1] * _m[1][j] + m[i][2] * _m[2][j] + m[i][3] * _m[3][j] ;
		}
	}
	return temp;
}

Mat4x4& Mat4x4::operator*=(Mat4x4 m)
{
	*this = *this * m;
	return *this;
}

Vec4f Mat4x4::operator*(Vec4f _v)
{
	Vec4f temp;
	for(int i = 0; i < 4; ++i)
	{

			temp[i] =   _v[0] * _m[0][i] + _v[1] * _m[1][i] +  _v[2]  *_m[2][i] + _v[3] *_m[3][i];
		
	}
	return temp;
}

Mat4x4 Mat4x4::GetIdentity()
{
	return Mat4x4(
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1);

}

void Mat4x4::SetIdentity()
{
	_m[0] = Vec4f(1,0,0,0);
	_m[1] = Vec4f(0,1,0,0);
	_m[2] = Vec4f(0,0,1,0);
	_m[3] = Vec4f(0,0,0,1);
}

void Mat4x4::Transpose()
{
	*this = GetTranspose();
}

Mat4x4 Mat4x4::GetTranspose()
{
	Mat4x4 temp;
	for(int i = 0; i < 4; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			temp[i][j] = _m[j][i];
		}
	}
	return temp;
}

Mat4x4& Mat4x4::operator=(Mat4x4 m)
{
	for(int i = 0; i < 4; ++i)
	{
		_m[i] = m[i];
	}
	return *this;
}


void	MathHelper_L::fast_translate(Mat4x4& _m, Vec3f _v)
{
	_m[3] =  _m[0] * _v[0] + _m[1] * _v[1] + _m[2] * _v[2] + _m[3];
}

}
