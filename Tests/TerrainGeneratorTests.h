#ifndef TERRAINGENERATORTESTS_H
#define TERRAINGENERATORTESTS_H

#include "AutoTest.h"

class TerrainGeneratorTests : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void test1();
	void cleanupTestCase();
};

DECLARE_TEST(TerrainGeneratorTests)
#endif
