#include "Main.h"

#include <Core/FPSCounter.h>

using namespace t3d;
#define CLASS Test_CoreFPSCounter

TEST_CLASS
{
protected:
	class MockTimer : public Timer
	{
	public:
		qint64 elapsed() override
		{
			return mTime;
		}


		void start() override
		{
			mTime = 0;
		}

		void addTime(qint64 amount) { mTime += amount; }

	private:
		qint64 mTime = 0;
	};
};


TEST_CASE(fps40_supR1000_subR500)
{
	const int superSampleRate = 1000;
	const int subSampleRate = 500;

	strong<MockTimer> timer(new MockTimer);
	FPSCounter counter(superSampleRate, subSampleRate, timer);

	FOR_TIMES(sub, 2)
	{
		FOR_TIMES(i, 20)
		{
			if (i == 19)
				timer->addTime(subSampleRate);

			counter.update();
		}
	}

	ASSERT_EQ(40, counter.fps());
}


TEST_CASE(fps60_supR1000_subR250)
{
	const int superSampleRate = 1000;
	const int subSampleRate = 250;

	strong<MockTimer> timer(new MockTimer);
	FPSCounter counter(superSampleRate, subSampleRate, timer);

	FOR_TIMES(sub, 4)
	{
		FOR_TIMES(i, 15)
		{
			if (i == 14)
				timer->addTime(subSampleRate);

			counter.update();
		}
	}

	ASSERT_EQ(60, counter.fps());
}


TEST_CASE(fps60_subIs30t30t30_supR1000_subR_500)
{
	const int superSampleRate = 1000;
	const int subSampleRate = 500;

	strong<MockTimer> timer(new MockTimer);
	FPSCounter counter(superSampleRate, subSampleRate, timer);

	FOR_TIMES(i, 3)
	{
		FOR_TIMES(i, 30)
		{
			if (i == 29)
				timer->addTime(subSampleRate);

			counter.update();
		}
	}

	ASSERT_EQ(60, counter.fps());
}
