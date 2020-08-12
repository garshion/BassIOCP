#pragma once

namespace Bass
{
	enum class ETimerType : int
	{
		NONE = 0,
		
		EVERY_SECOND,		// 1�ʸ��� 
		EVERY_MINUTE,		// 1�и���
		EVERY_HOUR,			// 1�ø���

		EACH_SECOND,		// 1�п� 1�� ���� �ʿ�
		EACH_MINUTE,		// 1�ð��� 1�� ���� ��,�ʿ� 
		EACH_HOUR,			// �Ϸ翡 1�� ���� ��,��,�ʿ�
		EACH_DAY,			// �Ѵ޿� 1�� ���� ��,��,��,�ʿ�
		EACH_DAY_OF_WEEK,	// 1���Ͽ� 1�� ���� ����,��,��,�ʿ�

		ONCE,				// ��,��,��,��,��,�ʿ� �� �ѹ�.

		MAX,
	};

	enum class EDayOfWeek : int
	{
		Sunday = 0,			// ��
		Monday,				// ��
		Tuesday,			// ȭ
		Wednesday,			// ��
		Thursday,			// ��
		Friday,				// ��
		Saturday,			// ��
	};
}