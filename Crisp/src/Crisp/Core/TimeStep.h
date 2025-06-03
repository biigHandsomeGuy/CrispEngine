#pragma once


namespace Crisp
{
	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
			:m_Time(time)
		{

		}

		operator float() { return m_Time; }

		float GetSceonds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		// millisecond
		float m_Time;
	};


}