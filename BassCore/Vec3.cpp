#include "Vec3.h"
#include <cmath>
#include "BassCommon.h"
#include "MathCommon.h"

Bass::Vec3 Bass::Vec3::XAxis(1.0, 0.0, 0.0);
Bass::Vec3 Bass::Vec3::YAxis(0.0, 1.0, 0.0);
Bass::Vec3 Bass::Vec3::ZAxis(0.0, 0.0, 1.0);
Bass::Vec3 Bass::Vec3::Origin(0.0, 0.0, 0.0);

Bass::Vec3::Vec3(const Vec3& v)
{
	Set(v);
}

Bass::Vec3::Vec3(const double& xx, const double& yy, const double& zz)
{
	Set(xx, yy, zz);
}

Bass::Vec3::~Vec3()
{
}

void Bass::Vec3::Set(const double& xx, const double& yy, const double& zz)
{
	x = xx;
	y = yy;
	z = zz;
}

void Bass::Vec3::Set(const Vec3& val)
{
	x = val.x;
	y = val.y;
	z = val.z;
}

Bass::Vec3& Bass::Vec3::operator+=(const Vec3& val)
{
	x += val.x;
	y += val.y;
	z += val.z;
	return *this;
}

Bass::Vec3& Bass::Vec3::operator-=(const Vec3& val)
{
	x -= val.x;
	y -= val.y;
	z -= val.z;
	return *this;
}

Bass::Vec3& Bass::Vec3::operator*=(const double& val)
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}

Bass::Vec3& Bass::Vec3::operator/=(const double& val)
{
	x /= val;
	y /= val;
	z /= val;
	return *this;
}

Bass::Vec3 Bass::Vec3::operator+(const Vec3& val) const
{
	Vec3 vRet(x + val.x, y + val.y, z + val.z);
	return vRet;
}

Bass::Vec3 Bass::Vec3::operator-(const Vec3& val) const
{
	Vec3 vRet(x - val.x, y - val.y, z - val.z);
	return vRet;
}

Bass::Vec3 Bass::Vec3::operator*(const double& val) const
{
	Vec3 vRet(x * val, y * val, z * val);
	return vRet;
}

Bass::Vec3 Bass::Vec3::operator/(const double& val) const
{
	Vec3 vRet(x / val, y / val, z / val);
	return vRet;
}

Bass::Vec3 Bass::Vec3::operator-() const
{
	Vec3 vRet(-x, -y, -z);
	return vRet;
}

double Bass::Vec3::operator*(const Vec3& val) const
{
	double dDot = x * val.x + y * val.y + z * val.z;
	return dDot;
}

Bass::Vec3 Bass::Vec3::operator^(const Vec3& val) const
{
	Vec3 vCross(y * val.z - z * val.y, z * val.x - x * val.z, x * val.y - y * val.x);
	return vCross;
}

bool Bass::Vec3::Normalize()
{
	double dLength = Length();

	if (0.0 >= dLength)
		return false;

	*this /= dLength;
	return true;
}

double Bass::Vec3::Length()
{
	return sqrt(fabs(LengthPow()));
}

double Bass::Vec3::LengthPow()
{
	double dLengthPow = x * x + y * y + z * z;
	return dLengthPow;
}

double Bass::Vec3::Length2D()
{
	return sqrt(fabs(Length2DPow()));
}

double Bass::Vec3::Length2DPow()
{
	double dLengthPow = x * x + y * y;
	return dLengthPow;
}

double Bass::Vec3::Distance(const Vec3& vTarget) const
{
	Vec3 vGap(vTarget.x - x, vTarget.y - y, vTarget.z - z);
	return vGap.Length();
}

double Bass::Vec3::Distance2D(const Vec3& vTarget) const
{
	Vec3 vGap = vTarget - *this;
	return vGap.Length2D();
}

double Bass::Vec3::GetAngle(const Vec3& vTarget)
{
	Vec3 vCheck(vTarget);
	if (Length() <= 0.0
		|| vCheck.Length() <= 0.0)
		return 0.0;

	double dVal = ((*this) * vTarget) / Length() * vCheck.Length();

	dVal = dVal > 1 ? 1 : dVal;
	dVal = dVal < -1 ? -1 : dVal;

	double dAngle = Bass::RadianNormalize(acos(dVal));
	return ((*this) ^ vCheck).z < 0 ? RadianNormalize(-dAngle) : dAngle;
}

const double& Bass::Vec3::Longitude()
{
	return x;
}

const double& Bass::Vec3::Latitude()
{
	return y;
}

const double& Bass::Vec3::Altitude()
{
	return z;
}

double& Bass::Vec3::Pitch()
{
	return x;
}

double& Bass::Vec3::Roll()
{
	return y;
}

double& Bass::Vec3::Yaw()
{
	return z;
}
