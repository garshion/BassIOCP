#pragma once
#include "Vec3.h"
#include <string.h>

namespace Bass
{
	class Matrix
	{
	public:
		Matrix();
		Matrix(const Matrix& mat);
		virtual ~Matrix();

		void Identify();					// 단위행렬로 만들기
		bool IsIdentify() const;			// 단위행렬 여부

		double Determinant();				// 행렬식 값 얻기
		bool IsDeterminantZero();			// 행렬식 값이 0인지

		bool Invert();						// 역행렬 만들기

		void Scale(const double& dX, const double& dY, const double& dZ);
		void Scale(const Vec3& vVec);
		void Translate(const double& dX, const double& dY, const double& dZ);
		void Translate(const Vec3& vVec);
		void RotateX(const double& dRadian);
		void RotateY(const double& dRadian);
		void RotateZ(const double& dRadian);
		void Rotate(const Vec3& vAxis, const double& dRadian);

		double Get(int nRow, int nCol);

		Matrix& operator=(const Matrix& mat);
		Matrix& operator*=(const Matrix& mat);

		Matrix operator+(const Matrix& mat) const;
		Matrix operator-(const Matrix& mat) const;
		Matrix operator*(const Matrix& mat) const;
		Matrix operator*(const double& scalar) const;
		Vec3 operator*(const Vec3& vTarget) const;
		Matrix operator/(const double& scalar) const;

		bool GetEularAngle(double& o_dYaw, double& o_dPitch, double& o_dRoll);

		double& M00() { return v[0][0]; }
		double& M01() { return v[0][1]; }
		double& M02() { return v[0][2]; }
		double& M03() { return v[0][3]; }
		double& M10() { return v[1][0]; }
		double& M11() { return v[1][1]; }
		double& M12() { return v[1][2]; }
		double& M13() { return v[1][3]; }
		double& M20() { return v[2][0]; }
		double& M21() { return v[2][1]; }
		double& M22() { return v[2][2]; }
		double& M23() { return v[2][3]; }
		double& M30() { return v[3][0]; }
		double& M31() { return v[3][1]; }
		double& M32() { return v[3][2]; }
		double& M33() { return v[3][3]; }

	public:
		double v[4][4];
	private:
		void _CopyData(const Matrix& mat);
	};

}