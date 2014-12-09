#include <gtest/gtest.h>
#include <World/Terrain/HeightMap.h>
#include <World/Terrain/NormalMap.h>

using namespace t3d::World::Terrain;

class Test_WorldTerrainNormalMap : public ::testing::Test
{
protected:
	void expectVec3fAreEqual(const Vec3f &v1, const Vec3f &v2, const std::string &message="")
	{
		const float error = 0.0001f;
		EXPECT_NEAR(v1.x, v2.x, error) << message;
		EXPECT_NEAR(v1.y, v2.y, error) << message;
		EXPECT_NEAR(v1.z, v1.z, error) << message;
	}
};

TEST_F(Test_WorldTerrainNormalMap, flatTerrain)
{
	const int hmSize = 2;
	HeightMap hm;
	hm.reserve(hmSize);

	for (int y=0; y<hmSize; y++)
	{
		for (int x=0; x<hmSize; x++)
			hm.set(x, y, 0.0f);
	}

	NormalMap nm;
	nm.generate(hm);

	//there should be only two normals (since there are two triangles)
	EXPECT_EQ(nm.size(), 2);

	//both normals should point straight up
	Vec3f n1 = nm.get(0);
	Vec3f n2 = nm.get(1);
	Vec3f up(0.0f, -1.0f, 0.0f);

	expectVec3fAreEqual(n1, up, "The normal is not straight up");
	expectVec3fAreEqual(n2, up, "The normal is not straight up");
}


TEST_F(Test_WorldTerrainNormalMap, slope45Degree)
{
	const int hmSize = 2;
	HeightMap hm;
	hm.reserve(hmSize);

	hm.set(0, 0, 1.0f);
	hm.set(1, 0, 1.0f);
	hm.set(0, 1, 0);
	hm.set(1, 1, 0);

	NormalMap nm;
	nm.generate(hm);

	//only two normals
	EXPECT_EQ(nm.size(), 2);

	//both normals should be pointing at an angle more downish
	Vec3f n1 = nm.get(0);
	Vec3f n2 = nm.get(0);
	Vec3f outDown(0.0f, -.707107f, -.707107);

	expectVec3fAreEqual(n1, outDown);
	expectVec3fAreEqual(n2, outDown);

	{
		Vec3f p1(0, 1, 0);
		Vec3f p2(1, 1, 0);
		Vec3f p3(0, 0, 1);

		Vec3f v1 = p2-p1;
		Vec3f v2 = p3-p1;

		Vec3f asd = glm::normalize(glm::cross(v1, v2));
	}
}
