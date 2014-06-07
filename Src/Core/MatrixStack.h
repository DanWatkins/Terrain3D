//=======================================================================================================================|
// Created 2014.04.27 by Daniel L. Watkins
//
// Copyright (C) 2014 Daniel L. Watkins
// This file is licensed under the MIT License.
//=======================================================================================================================|

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
		void rotate(const Vec3f &axis, Float angleDeg) { mCurrentMatrix = glm::rotate(mCurrentMatrix, angleDeg, axis); }
		void rotateX(Float angleDeg) { rotate(Vec3f(1.0f, 0.0f, 0.0f), angleDeg); }
		void rotateY(Float angleDeg) { rotate(Vec3f(0.0f, 1.0f, 0.0f), angleDeg); }
		void rotateZ(Float angleDeg) { rotate(Vec3f(0.0f, 0.0f, 1.0f), angleDeg); }

		void scale(const Vec3f &scaleVec) { mCurrentMatrix = glm::scale(scaleVec); }
		void scale(Float scaleX, Float scaleY, Float scaleZ) { scale(Vec3f(scaleX, scaleY, scaleZ)); }
		void scale(Float uniformScale) { scale(Vec3f(uniformScale)); }

		void translate(const Vec3f &deltaVec) { mCurrentMatrix = glm::translate(deltaVec); }
		void translate(Float dx, Float dy, Float dz) { translate(Vec3f(dx, dy, dz)); }

		//helpers
		void lookAt(const Vec3f &cameraPos, const Vec3f &lookatPos, const Vec3f &upDir) { mCurrentMatrix *= glm::lookAt(cameraPos, lookatPos, upDir); }
		void perspective(Float fovDeg, Float aspectRatio, Float zNear, Float zFar);
		void orthographic(Float left, Float right, Float bottom, Float top, Float zNear=1.0f, Float zFar=1.0f);
		void pixelPerfectOrtho(const glm::ivec2 &size, const Vec2f &depthRange, Bool isTopLeft = true);
		
		void applyMatrix(const Mat4 &matrix) { mCurrentMatrix *= matrix; }
		void setMatrix(const Mat4 &matrix) { mCurrentMatrix = matrix; }
		void setIdentity() { mCurrentMatrix = glm::mat4(1.0f); }
	};
};


#endif

