#pragma once
namespace Bass
{
	class Vec3
	{
	public:
		Vec3(const Vec3& v);
		Vec3(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0);
		~Vec3();

		void Set(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0);
		void Set(const Vec3& val);

		Vec3& operator += (const Vec3& val);
		Vec3& operator -= (const Vec3& val);
		Vec3& operator *= (const double& val);
		Vec3& operator /= (const double& val);

		Vec3 operator +(const Vec3& val) const;
		Vec3 operator -(const Vec3& val) const;
		Vec3 operator *(const double& val) const;
		Vec3 operator /(const double& val) const;
		Vec3 operator - () const;

		// DotProduct
		double operator* (const Vec3& val) const;

		// CrossProduct
		Vec3 operator^ (const Vec3& val) const;

		bool Normalize();							// 단위벡터화
		double Length();							// 원점으로부터 거리
		double LengthPow();							// 원점으로부터 거리 제곱
		double Length2D();
		double Length2DPow();

		double Distance(const Vec3& vTarget) const;		// 해당 점과의 거리 구하기
		double Distance2D(const Vec3& vTarget) const;
		double GetAngle(const Vec3& vTarget);		// 원점과 자기 자신과 타겟과의 사이각. (this, O, Target)

		// 위경도로 사용
		const double& Longitude();					// 경도
		const double& Latitude();					// 위도
		const double& Altitude();					// 고도
		// end, 위경도로 사용


		// 자세값으로 사용
		double& Pitch();
		double& Roll();
		double& Yaw();
		// end, 자세값으로 사용

	public:
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

	public:
		static Vec3 XAxis;							// X 축
		static Vec3 YAxis;							// Y 축
		static Vec3 ZAxis;							// Z 축
		static Vec3 Origin;							// 원점
	};

}