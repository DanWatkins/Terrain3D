//==================================================================================================================|
// Created 2014.04.27 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//==================================================================================================================|

#ifndef _GL_MATRIX_STACK_H
#define _GL_MATRIX_STACK_H

#include <stack>
#include <vector>
#include "../Main.h"

namespace t3d
{
	class MatrixStack
	{
	private:
		std::stack<Mat4, std::vector<Mat4>> mStack;
		Mat4 mCurrentMatrix;

	public:
		MatrixStack();
		explicit MatrixStack(const Mat4 &initialMatrix);

		//stack operations
		void push() { mStack.push(mCurrentMatrix); }
		void pop() { mCurrentMatrix = mStack.top(); mStack.pop(); }
		void reset() { mCurrentMatrix = mStack.top(); }
		const Mat4 &top() const { return mCurrentMatrix; }

		//general transformations
		void rotate(const Vec3f &axis, float angleDeg) { mCurrentMatrix = glm::rotate(mCurrentMatrix, angleDeg, axis); }
		void rotateX(float angleDeg) { rotate(Vec3f(1.0f, 0.0f, 0.0f), angleDeg); }
		void rotateY(float angleDeg) { rotate(Vec3f(0.0f, 1.0f, 0.0f), angleDeg); }
		void rotateZ(float angleDeg) { rotate(Vec3f(0.0f, 0.0f, 1.0f), angleDeg); }

		void scale(const Vec3f &scaleVec) { mCurrentMatrix = glm::scale(scaleVec); }
		void scale(float scaleX, float scaleY, float scaleZ) { scale(Vec3f(scaleX, scaleY, scaleZ)); }
		void scale(float uniformScale) { scale(Vec3f(uniformScale)); }

		void translate(const Vec3f &deltaVec) { mCurrentMatrix = glm::translate(deltaVec); }
		void translate(float dx, float dy, float dz) { translate(Vec3f(dx, dy, dz)); }

		//helpers
		void lookAt(const Vec3f &cameraPos, const Vec3f &lookatPos, const Vec3f &upDir)
		{
			mCurrentMatrix *= glm::lookAt(cameraPos, lookatPos, upDir);
		}
		void perspective(float fovDeg, float aspectRatio, float zNear, float zFar);
		void orthographic(float left, float right, float bottom, float top, float zNear=1.0f, float zFar=1.0f);
		void pixelPerfectOrtho(const glm::ivec2 &size, const Vec2f &depthRange, bool isTopLeft = true);
		
		void applyMatrix(const Mat4 &matrix) { mCurrentMatrix *= matrix; }
		void setMatrix(const Mat4 &matrix) { mCurrentMatrix = matrix; }
		void setIdentity() { mCurrentMatrix = glm::mat4(1.0f); }
	};
};


#endif

