#pragma once
#include <cstdint>

namespace Bass
{
	class StopWatchImpl;

	/// <summary>
	/// �� ������ �ð��� ������ �� �ִ� Ŭ����
	/// </summary>
	class StopWatch
	{
	public:
		StopWatch();
		~StopWatch();

		bool Start();	// ���� ����
		bool Stop();	// ���� ����
		void Reset();	// �ʱ�ȭ

		double GetSeconds() const;			// �� ������ ���� (��)
		int64_t GetMilliseconds() const;	// �� ������ ���� (�и���)
		int64_t GetNanoseconds() const;		// �� ������ ���� (������)

	private:
		StopWatchImpl* m_pImpl = nullptr;

	};

}