#ifndef GL_MATH_CLASS_H
#define GL_MATH_CLASS_H

#include <csignal>
#include <vector>
#include <math.h>

typedef struct vec4_typedef {
	float val[4];

	vec4_typedef(const float x = 1.0f);
	vec4_typedef(const float w, const float x, const float y, const float z);
	vec4_typedef(const struct vec4_typedef& srcVec4);
	vec4_typedef(const struct vec3_typedef& srcVec3, const float z = 1.0f);
}vec4;
typedef struct vec3_typedef {
	float val[3];

	vec3_typedef(const float x = 1.0f);
	vec3_typedef(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
	vec3_typedef(const struct vec3_typedef& srcVec3);
	vec3_typedef(const struct vec4_typedef& srcVec4);
}vec3;

typedef struct mat4_typedef {
	float val[4][4];

	mat4_typedef(const float x = 1.0f);
	mat4_typedef(const struct mat4_typedef& srcMat4);

	mat4_typedef operator *(const mat4_typedef& srcMat4);
	mat4_typedef operator *(const float srcVal1);
	vec4_typedef operator *(vec4_typedef& vec4);
}mat4;
typedef struct mat3_typedef {
	float val[3][3];

	mat3_typedef(const float x = 1.0f);
	mat3_typedef(const struct mat3_typedef& srcMat3);
}mat3;

float lenght(const vec4& srcVec4);
vec4 normalize(const vec4& srcVec4);
float lenght(const vec3& srcVec3);
vec3 normalize(const vec3& srcVec3);

mat4 perspective(const float fov, const float aspect, const float near, const float far);
//mat4 LookAt(vec3& eye, vec3& at, vec3& up);
mat4 transform(const mat4& srcMat4, const vec3& deltaVec3);
mat4 rotate(const mat4 srcMat4, const float angle, const vec3& axis);
#endif