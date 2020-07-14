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

		bool Normalize();							// ��������ȭ
		double Length();							// �������κ��� �Ÿ�
		double LengthPow();							// �������κ��� �Ÿ� ����
		double Length2D();
		double Length2DPow();

		double Distance(const Vec3& vTarget) const;		// �ش� ������ �Ÿ� ���ϱ�
		double Distance2D(const Vec3& vTarget) const;
		double GetAngle(const Vec3& vTarget);		// ������ �ڱ� �ڽŰ� Ÿ�ٰ��� ���̰�. (this, O, Target)

		// ���浵�� ���
		const double& Longitude();					// �浵
		const double& Latitude();					// ����
		const double& Altitude();					// ��
		// end, ���浵�� ���


		// �ڼ������� ���
		double& Pitch();
		double& Roll();
		double& Yaw();
		// end, �ڼ������� ���

	public:
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

	public:
		static Vec3 XAxis;							// X ��
		static Vec3 YAxis;							// Y ��
		static Vec3 ZAxis;							// Z ��
		static Vec3 Origin;							// ����
	};

}