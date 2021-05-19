#include "Math.h"

const Vector2 Vector2::Zero(0.0f, 0.0f);

Vector2 Vector2::Transform(const Vector2 &vec, const Matrix3 &mat, float w)
{
	Vector2 retVal;
	retVal.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + w * mat.mat[2][0];
	retVal.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + w * mat.mat[2][1];
	//ignore w since we aren't returning a new value for it...
	return retVal;
}
