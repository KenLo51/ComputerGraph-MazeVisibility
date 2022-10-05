#include "glMath.h"
# define M_PI           3.14159265358979323846
// vec3 functions
vec3_typedef::vec3_typedef(const float x) {
	vec3_typedef::val[0] = x;
	vec3_typedef::val[1] = x;
	vec3_typedef::val[2] = x;
}
vec3_typedef::vec3_typedef(const float x, const float y, const float z) {
	vec3_typedef::val[0] = x;
	vec3_typedef::val[1] = y;
	vec3_typedef::val[2] = z;
}
vec3_typedef::vec3_typedef(const struct vec3_typedef& srcVec3) {
	vec3_typedef::val[0] = srcVec3.val[0];
	vec3_typedef::val[1] = srcVec3.val[1];
	vec3_typedef::val[2] = srcVec3.val[2];
}
vec3_typedef::vec3_typedef(const struct vec4_typedef& srcVec4) {
	vec3_typedef::val[0] = srcVec4.val[0];
	vec3_typedef::val[1] = srcVec4.val[1];
	vec3_typedef::val[2] = srcVec4.val[2];
}

float lenght(const vec3& srcVec3) {
	float len = srcVec3.val[0] * srcVec3.val[0] +
		srcVec3.val[1] * srcVec3.val[1] +
		srcVec3.val[2] * srcVec3.val[2];
	len = sqrtf(len);
	return len;
}
vec3 normalize(const vec3& srcVec3) {
	vec3 newVec3(srcVec3);
	float len = lenght(srcVec3);
	newVec3.val[0] /= len;
	newVec3.val[1] /= len;
	newVec3.val[2] /= len;
	return newVec3;
}

// vec4 functions
vec4_typedef::vec4_typedef(const float x) {
	vec4_typedef::val[0] = x;
	vec4_typedef::val[1] = x;
	vec4_typedef::val[2] = x;
	vec4_typedef::val[3] = x;
}
vec4_typedef::vec4_typedef(const float w, const float x, const float y, const float z) {
	vec4_typedef::val[0] = w;
	vec4_typedef::val[1] = x;
	vec4_typedef::val[2] = y;
	vec4_typedef::val[3] = z;
}
vec4_typedef::vec4_typedef(const struct vec4_typedef& srcVec4) {
	vec4_typedef::val[0] = srcVec4.val[0];
	vec4_typedef::val[1] = srcVec4.val[1];
	vec4_typedef::val[2] = srcVec4.val[2];
	vec4_typedef::val[3] = srcVec4.val[3];
}
vec4_typedef::vec4_typedef(const struct vec3_typedef& srcVec3, const float z) {
	vec4_typedef::val[0] = srcVec3.val[0];
	vec4_typedef::val[1] = srcVec3.val[1];
	vec4_typedef::val[2] = srcVec3.val[2];
	vec4_typedef::val[3] = z;
}

float lenght(const vec4& srcVec4) {
	float len = srcVec4.val[0] * srcVec4.val[0] +
		srcVec4.val[1] * srcVec4.val[1] +
		srcVec4.val[2] * srcVec4.val[2] +
		srcVec4.val[3] * srcVec4.val[3];
	len = sqrtf(len);
	return len;
}
vec4 normalize(vec4& srcVec4) {
	vec4 newVec4(srcVec4);
	float len = lenght(srcVec4);
	newVec4.val[0] /= len;
	newVec4.val[1] /= len;
	newVec4.val[2] /= len;
	newVec4.val[3] /= len;
	return newVec4;
}



// mat4 functions
// 0(0, 0)   1(1, 0)  2(2, 0)  3(3, 0)
// 4(0, 1)   5(1, 1)  6(2, 1)  7(3, 1)
// 8(0, 2)   9(1, 2) 10(2, 2) 11(3, 2)
// 12(0, 3) 13(1, 3) 14(2, 3) 15(3, 3)
mat4_typedef::mat4_typedef(const float x) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat4_typedef::val[i][j] = (i == j) ? x : 0.0f;
}
mat4_typedef::mat4_typedef(const mat4_typedef& srcMat) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat4_typedef::val[i][j] = srcMat.val[i][j];
}

mat4& ones() {
	mat4 newMat4;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			newMat4.val[i][j] = 1.0f;
	return newMat4;
}


mat4 mat4_typedef::operator *(const mat4_typedef& srcMat4) {
	mat4 newMat4(0.0f);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float newVal = 0.0f;
			for (int k = 0; k < 4; k++) {
				newVal += mat4::val[i][k] * srcMat4.val[k][j];
			}
			newMat4.val[i][j] = newVal;
		}
	}
	return newMat4;
}
mat4_typedef mat4_typedef::operator *(const float srcVal1) {
	struct mat4_typedef newMat4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			newMat4.val[i][j] = mat4_typedef::val[i][j] * srcVal1;
		}
	}
	return newMat4;
}
vec4_typedef mat4_typedef::operator *(vec4_typedef& vec4) {
	struct vec4_typedef newVec4;
	for (int i = 0; i < 4; i++) {
		float newVal = 0.0f;
		for (int j = 0; j < 4; j++) {
			newVal += mat4_typedef::val[i][j] * vec4.val[j];
		}
		newVec4.val[i] = newVal;
	}
	return newVec4;
}

mat4 perspective(const float fov, const float aspect, const float near, const float far) {
	mat4 newMat4(0.0f);

	float D2R = M_PI / 180.0;
	float yScale = 1.0 / tan(D2R * fov / 2);
	float xScale = yScale / aspect;
	float nearmfar = near - far;

	newMat4.val[0][0] = xScale;
	newMat4.val[1][1] = yScale;
	newMat4.val[2][2] = (far + near) / nearmfar;
	newMat4.val[2][3] = -1.0f;
	newMat4.val[3][2] = -(2.0f * far * near) / nearmfar;

	return newMat4;
}

//mat4 LookAt(vec3& eye, vec3& at, vec3& up)
//{
//	vec3 zaxis = normalize(at - eye);
//	vec3 xaxis = normalize(cross(zaxis, up));
//	vec3 yaxis = cross(xaxis, zaxis);
//
//	negate(zaxis);
//
//	mat4 viewMatrix = {
//	  vec4(xaxis.x, xaxis.y, xaxis.z, -dot(xaxis, eye)),
//	  vec4(yaxis.x, yaxis.y, yaxis.z, -dot(yaxis, eye)),
//	  vec4(zaxis.x, zaxis.y, zaxis.z, -dot(zaxis, eye)),
//	  vec4(0, 0, 0, 1)
//	};
//
//	return viewMatrix;
//}

mat4 transform(const mat4& srcMat4, const vec3& deltaVec3) {
	mat4 newMat4(1.0f);

	newMat4.val[0][3] += deltaVec3.val[0];
	newMat4.val[1][3] += deltaVec3.val[1];
	newMat4.val[2][3] += deltaVec3.val[2];

	newMat4 = newMat4 * srcMat4;

	return newMat4;
}

mat4 rotate(const mat4 srcMat4, const float angle, const vec3& axis) {
	mat4 rotateMat4(1.0f);
	rotateMat4.val[0][0] = cosf(angle) + powf(axis.val[0], 2) * (1 - cos(angle));
	rotateMat4.val[0][1] = axis.val[0] * axis.val[1] * (1 - cos(angle)) - axis.val[2] * sin(angle);
	rotateMat4.val[0][2] = axis.val[0] * axis.val[2] * (1 - cos(angle)) + axis.val[1] * sin(angle);

	rotateMat4.val[1][0] = axis.val[1] * axis.val[0] * (1 - cos(angle)) + axis.val[2] * sin(angle);
	rotateMat4.val[1][1] = cosf(angle) + powf(axis.val[1], 2) * (1 - cos(angle));
	rotateMat4.val[1][2] = axis.val[1] * axis.val[2] * (1 - cos(angle)) - axis.val[0] * sin(angle);

	rotateMat4.val[2][0] = axis.val[2] * axis.val[0] * (1 - cos(angle)) - axis.val[1] * sin(angle);
	rotateMat4.val[2][1] = axis.val[2] * axis.val[1] * (1 - cos(angle)) + axis.val[0] * sin(angle);
	rotateMat4.val[2][2] = cosf(angle) + powf(axis.val[2], 2) * (1 - cos(angle));

	rotateMat4 = rotateMat4 * srcMat4;

	return rotateMat4;
}