#include "Matrix.h"
#include <math.h>


Bass::Matrix::Matrix()
{
	Identify();
}

Bass::Matrix::Matrix(const Matrix & mat)
{
	_CopyData(mat);
}

Bass::Matrix::~Matrix()
{
}

void Bass::Matrix::Identify()
{
	memset(v, 0x00, sizeof(double) * 16);
	for (int i = 0; i < 4; ++i)
		v[i][i] = 1.0;
}

bool Bass::Matrix::IsIdentify() const
{
	if (v[0][0] != 1.0
		|| v[0][1] != 0.0
		|| v[0][2] != 0.0
		|| v[0][3] != 0.0
		|| v[1][0] != 0.0
		|| v[1][1] != 1.0
		|| v[1][2] != 0.0
		|| v[1][3] != 0.0
		|| v[2][0] != 0.0
		|| v[2][1] != 0.0
		|| v[2][2] != 1.0
		|| v[2][3] != 0.0
		|| v[3][0] != 0.0
		|| v[3][1] != 0.0
		|| v[3][2] != 0.0
		|| v[3][3] != 1.0)
		return false;
	return true;
}

double Bass::Matrix::Determinant()
{
	return 	v[0][0] * v[1][1] * v[2][2] * v[3][3] +
		v[0][0] * v[1][2] * v[2][3] * v[3][1] +
		v[0][0] * v[1][3] * v[2][1] * v[3][2] +
		v[0][1] * v[1][0] * v[2][3] * v[3][2] +
		v[0][1] * v[1][2] * v[2][0] * v[3][3] +
		v[0][1] * v[1][3] * v[2][2] * v[3][0] +
		v[0][2] * v[1][0] * v[2][1] * v[3][3] +
		v[0][2] * v[1][1] * v[2][3] * v[3][0] +
		v[0][2] * v[1][3] * v[2][0] * v[3][1] +
		v[0][3] * v[1][0] * v[2][2] * v[3][1] +
		v[0][3] * v[1][1] * v[2][0] * v[3][2] +
		v[0][3] * v[1][2] * v[2][1] * v[3][0] -
		v[0][0] * v[1][1] * v[2][3] * v[3][2] -
		v[0][0] * v[1][2] * v[2][1] * v[3][3] -
		v[0][0] * v[1][3] * v[2][2] * v[3][1] -
		v[0][1] * v[1][0] * v[2][2] * v[3][3] -
		v[0][1] * v[1][2] * v[2][3] * v[3][0] -
		v[0][1] * v[1][3] * v[2][0] * v[3][2] -
		v[0][2] * v[1][0] * v[2][3] * v[3][1] -
		v[0][2] * v[1][1] * v[2][0] * v[3][3] -
		v[0][2] * v[1][3] * v[2][1] * v[3][0] -
		v[0][3] * v[1][0] * v[2][1] * v[3][2] -
		v[0][3] * v[1][1] * v[2][2] * v[3][0] -
		v[0][3] * v[1][2] * v[2][0] * v[3][1];
}

bool Bass::Matrix::IsDeterminantZero()
{
	return Determinant() == 0 ? true : false;
}

bool Bass::Matrix::Invert()
{
	if(true == IsDeterminantZero())
		return false;

	double dDet = 1.0 / Determinant();

	Matrix mat;

	mat.v[0][0] = dDet * (M11()*M22()*M33() + M12()*M23()*M31() + M13()*M21()*M32() - M11()*M23()*M32() - M12()*M21()*M33() - M13()*M22()*M31());
	mat.v[0][1] = dDet * (M01()*M23()*M32() + M02()*M21()*M33() + M03()*M22()*M31() - M01()*M22()*M33() - M02()*M23()*M31() - M03()*M21()*M32());
	mat.v[0][2] = dDet * (M01()*M12()*M33() + M02()*M13()*M31() + M03()*M11()*M32() - M01()*M13()*M32() - M02()*M11()*M33() - M03()*M12()*M31());
	mat.v[0][3] = dDet * (M01()*M13()*M22() + M02()*M11()*M23() + M03()*M12()*M21() - M01()*M12()*M23() - M02()*M13()*M21() - M03()*M11()*M22());

	mat.v[1][0] = dDet * (M10()*M23()*M32() + M12()*M20()*M33() + M13()*M22()*M30() - M10()*M22()*M33() - M12()*M23()*M30() - M13()*M20()*M32());
	mat.v[1][1] = dDet * (M00()*M22()*M33() + M02()*M23()*M30() + M03()*M20()*M32() - M00()*M23()*M32() - M02()*M20()*M33() - M03()*M22()*M30());
	mat.v[1][2] = dDet * (M00()*M13()*M32() + M02()*M10()*M33() + M03()*M12()*M30() - M00()*M12()*M33() - M02()*M13()*M30() - M03()*M10()*M32());
	mat.v[1][3] = dDet * (M00()*M12()*M23() + M02()*M13()*M20() + M03()*M10()*M22() - M00()*M13()*M22() - M02()*M10()*M23() - M03()*M12()*M20());

	mat.v[2][0] = dDet * (M10()*M21()*M33() + M11()*M23()*M30() + M13()*M20()*M31() - M10()*M23()*M31() - M11()*M20()*M33() - M13()*M21()*M30());
	mat.v[2][1] = dDet * (M00()*M23()*M31() + M01()*M20()*M33() + M03()*M21()*M30() - M00()*M21()*M33() - M01()*M23()*M30() - M03()*M20()*M31());
	mat.v[2][2] = dDet * (M00()*M11()*M33() + M01()*M13()*M30() + M03()*M10()*M31() - M00()*M13()*M31() - M01()*M10()*M33() - M03()*M11()*M30());
	mat.v[2][3] = dDet * (M00()*M13()*M21() + M01()*M10()*M23() + M03()*M11()*M20() - M00()*M11()*M23() - M01()*M13()*M20() - M03()*M10()*M21());

	mat.v[3][0] = dDet * (M10()*M22()*M31() + M11()*M20()*M32() + M12()*M21()*M30() - M10()*M21()*M32() - M11()*M22()*M30() - M12()*M20()*M31());
	mat.v[3][1] = dDet * (M00()*M21()*M32() + M01()*M22()*M30() + M02()*M20()*M31() - M00()*M22()*M31() - M01()*M20()*M32() - M02()*M21()*M30());
	mat.v[3][2] = dDet * (M00()*M12()*M31() + M01()*M10()*M32() + M02()*M11()*M30() - M00()*M11()*M32() - M01()*M12()*M30() - M02()*M10()*M31());
	mat.v[3][3] = dDet * (M00()*M11()*M22() + M01()*M12()*M20() + M02()*M10()*M21() - M00()*M12()*M21() - M01()*M10()*M22() - M02()*M11()*M20());

	_CopyData(mat);
	return true;
}

void Bass::Matrix::Scale(const double & dX, const double & dY, const double & dZ)
{
	Identify();
	v[0][0] = dX;
	v[1][1] = dY;
	v[2][2] = dZ;
}

void Bass::Matrix::Scale(const Vec3 & vVec)
{
	Scale(vVec.x, vVec.y, vVec.z);
}

void Bass::Matrix::Translate(const double & dX, const double & dY, const double & dZ)
{
	Identify();
	v[0][3] = dX;
	v[1][3] = dY;
	v[2][3] = dZ;
}

void Bass::Matrix::Translate(const Vec3 & vVec)
{
	Translate(vVec.x, vVec.y, vVec.z);
}

void Bass::Matrix::RotateX(const double & dRadian)
{
	Identify();
	v[1][1] = cos(dRadian);
	v[1][2] = -sin(dRadian);
	v[2][1] = sin(dRadian);
	v[2][2] = cos(dRadian);
}

void Bass::Matrix::RotateY(const double & dRadian)
{
	Identify();
	v[0][0] = cos(dRadian);
	v[0][2] = sin(dRadian);
	v[2][0] = -sin(dRadian);
	v[2][2] = cos(dRadian);
}

void Bass::Matrix::RotateZ(const double & dRadian)
{
	Identify();
	v[0][0] = cos(dRadian);
	v[0][1] = -sin(dRadian);
	v[1][0] = sin(dRadian);
	v[1][1] = cos(dRadian);
}

void Bass::Matrix::Rotate(const Vec3 & vAxis, const double & dRadian)
{
	Identify();
	double dCos = cos(dRadian);
	double dSin = sin(dRadian);
	double d1_Cos = 1.0 - dCos;

	Vec3 vA = vAxis;
	vA.Normalize();

	M00() = vA.x * vA.x * d1_Cos + dCos;
	M01() = vA.x * vA.y * d1_Cos - vA.z * dSin;
	M02() = vA.x * vA.z * d1_Cos + vA.y * dSin;

	M10() = vA.y * vA.x * d1_Cos + vA.z * dSin;
	M11() = vA.y * vA.y * d1_Cos + dCos;
	M12() = vA.y * vA.z * d1_Cos - vA.x * dSin;

	M20() = vA.z * vA.x * d1_Cos - vA.y * dSin;
	M21() = vA.z * vA.y * d1_Cos + vA.x * dSin;
	M22() = vA.z * vA.z * d1_Cos + dCos;
}

double Bass::Matrix::Get(int nRow, int nCol)
{
	if (nRow < 0
		|| nCol < 0
		|| nRow >= 4
		|| nCol >= 4)
		return NAN;
	return v[nRow][nCol];
}

Bass::Matrix & Bass::Matrix::operator=(const Matrix & mat)
{
	_CopyData(mat);
	return *this;
}

Bass::Matrix & Bass::Matrix::operator*=(const Matrix & mat)
{
	*this = mat * (*this);
	return *this;
}

Bass::Matrix Bass::Matrix::operator+(const Matrix & mat) const
{
	Matrix matRet = *this;
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			matRet.v[row][col] += mat.v[row][col];
	return matRet;
}

Bass::Matrix Bass::Matrix::operator-(const Matrix & mat) const
{
	Matrix matRet = *this;
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			matRet.v[row][col] -= mat.v[row][col];
	return matRet;
}

Bass::Matrix Bass::Matrix::operator*(const Matrix & mat) const
{
	Matrix matRet = *this;
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			matRet.v[row][col] = v[row][0] * mat.v[0][col] + v[row][1] * mat.v[1][col] + v[row][2] * mat.v[2][col] + v[row][3] * mat.v[3][col];
	return matRet;
}

Bass::Matrix Bass::Matrix::operator*(const double & scalar) const
{
	Matrix matRet = *this;
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			matRet.v[row][col] *= scalar;
	return matRet;
}

Bass::Vec3 Bass::Matrix::operator*(const Vec3 & vTarget) const
{
	Vec3 vRet;
	vRet.x = vTarget.x * v[0][0] + vTarget.y * v[0][1] + vTarget.z * v[0][2] + v[0][3];
	vRet.y = vTarget.x * v[1][0] + vTarget.y * v[1][1] + vTarget.z * v[1][2] + v[1][3];
	vRet.z = vTarget.x * v[2][0] + vTarget.y * v[2][1] + vTarget.z * v[2][2] + v[2][3];
	return vRet;
}

Bass::Matrix Bass::Matrix::operator/(const double & scalar) const
{
	if (0.0 == scalar)
		return *this;

	Matrix matRet = *this;
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			matRet.v[row][col] /= scalar;
	return matRet;
}

bool Bass::Matrix::GetEularAngle(double & o_dYaw, double & o_dPitch, double & o_dRoll)
{
	o_dYaw = atan2(v[1][0], v[0][0]);
	o_dPitch = atan2(v[2][1], v[2][2]);
	o_dRoll = atan2(v[2][0], sqrt(v[2][1] * v[2][1] + v[2][2] * v[2][2]));

	if (true == isnan(o_dYaw)
		|| true == isnan(o_dRoll)
		|| true == isnan(o_dPitch)
		|| true == isinf(o_dYaw)
		|| true == isinf(o_dRoll)
		|| true == isinf(o_dPitch))
		return false;
	return true;
}

void Bass::Matrix::_CopyData(const Matrix & mat)
{
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			v[r][c] = mat.v[r][c];
}
