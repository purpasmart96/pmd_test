
#ifndef _VEC_H
#define _VEC_H

#include "util.h"

typedef union
{
    u8 v[4];

    struct
    {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };

} clov4;

typedef union
{
    u8 v[3];

    struct
    {
        u8 r;
        u8 g;
        u8 b;
    };

} clov3;

typedef union
{
    float v[4];
    struct
    {
        float x;
        float y;
        float z;
        float w;
    };

    struct
    {
        float r;
        float g;
        float b;
        float a;
    };

} vec4;

typedef union
{
    int v[4];
    struct
    {
        int x;
        int y;
        int z;
        int w;
    };

    struct
    {
        int r;
        int g;
        int b;
        int a;
    };

} ivec4;

typedef union vec3
{
    float v[3];
    struct
    {
        float x;
        float y;
        float z;
    };

    struct
    {
        float r;
        float g;
        float b;
    };

} vec3;

typedef union ivec3
{
    int v[3];
    struct
    {
        int x;
        int y;
        int z;
    };

    struct
    {
        int r;
        int g;
        int b;
    };

} ivec3;

typedef union vec2
{
    float v[2];

    struct
    {
        float x;
        float y;
    };

    struct
    {
        float r;
        float g;
    };

} vec2;

typedef union ivec2
{
    int v[2];

    struct
    {
        int x;
        int y;
    };

    struct
    {
        int r;
        int g;
    };

} ivec2;

typedef union mat4
{
    float m[16];
    struct
    {
        vec4 a;
        vec4 b;
        vec4 c;
        vec4 d;
    };

} mat4;

typedef union imat4
{
    int m[16];
    struct
    {
        ivec4 a;
        ivec4 b;
        ivec4 c;
        ivec4 d;
    };

} imat4;

typedef union
{
    float m[9];
    struct
    {
        vec3 a;
        vec3 b;
        vec3 c;
    };

} mat3;

typedef union
{
    ivec3 m[3];
    struct
    {
        ivec3 a;
        ivec3 b;
        ivec3 c;
    };

} imat3;


typedef union
{
    vec2 m[2];
    struct
    {
        vec2 a;
        vec2 b;
    };

} mat2;

typedef union
{
    ivec2 m[2];
    struct
    {
        ivec2 a;
        ivec2 b;
    };

} imat2;

vec4  vec4_zero();
vec4  vec4_add(vec4, vec4);
vec4  vec4_sub(vec4, vec4);
vec4  vec4_mul(vec4, vec4);
float vec4_dot(vec4 v, vec4 u);
vec4  vec4_cross(vec4 v, vec4 u);
vec4  vec4_abs(vec4 v);
vec4  vec4_scale(vec4 a, float lambda);
vec4  vec4_scale_xyz(vec4 a, float x, float y, float z);
vec4  vec4_scale_xyzw(vec4 a, float x, float y, float z, float w);
vec4  vec4_normalize(vec4 a);
float vec4_length(vec4 a);
vec4  vec4_mad(vec4 a, vec4 b, vec4 c);
vec4  make_vec4(float x, float y, float z, float w);

ivec4 ivec4_add(ivec4 a, ivec4 b);
ivec4 ivec4_sub(ivec4 v, ivec4 u);
ivec4 ivec4_mul(ivec4 v, ivec4 u);
int   ivec4_dot(ivec4 a, ivec4 b);
ivec4 ivec4_cross(ivec4 v, ivec4 u);
ivec4 ivec4_abs(ivec4 v);
ivec4 ivec4_scale(ivec4 a, int lambda);
ivec4 ivec4_scale_xyz(ivec4 a, int x, int y, int z);
ivec4 ivec4_scale_xyzw(ivec4 a, int x, int y, int z, int w);
ivec4 ivec4_normalize(ivec4 a);
int   ivec4_length(ivec4 a);
ivec4 ivec4_mad(ivec4 a, ivec4 b, ivec4 c);
ivec4 make_ivec4(int x, int y, int z, int w);

vec3  vec3_add(vec3 a, vec3 b);
vec3  vec3_sub(vec3 a, vec3 b);
vec3  vec3_mul(vec3 v, vec3 u);
float vec3_dot(vec3 a, vec3 b);
vec3  vec3_abs(vec3 v);
float vec3_length(vec3 a);
vec3  vec3_scale(vec3 a, float lambda);
vec3  vec3_scale_xyz(vec3 a, float x, float y, float z);
vec3  vec3_normalize(vec3 a);
vec3  vec3_cross(vec3 a, vec3 b);
vec3  vec3_lerp(vec3 a, vec3 b, float t);
vec3  make_vec3(float x, float y, float z);

ivec3 ivec3_add(ivec3 a, ivec3 b);
ivec3 ivec3_mul(ivec3 v, ivec3 u);
int   ivec3_dot(ivec3 a, ivec3 b);
ivec3 ivec3_abs(ivec3 v);
ivec3 ivec3_scale(ivec3 a, int lambda);
ivec3 ivec3_scale_xyz(ivec3 a, int x, int y, int z);
ivec3 ivec3_normalize(ivec3 a);
ivec3 ivec3_cross(ivec3 a, ivec3 b);
int   ivec3_length(ivec3 a);
ivec3 ivec3_lerp(ivec3 a, ivec3 b, int t);
ivec3 make_ivec3(int x, int y, int z);

vec2  vec2_add(vec2 a, vec2 b);
vec2  vec2_sub(vec2 a, vec2 b);
vec2  vec2_mul(vec2 v, vec2 u);
float vec2_dot(vec2 a, vec2 b);
vec2  vec2_abs(vec2 v);
float vec2_length(vec2 a);
vec2  vec2_scale(vec2 a, float lambda);
vec2  vec2_normalize(vec2 a);
vec2  vec2_lerp(vec2 a, vec2 b, float t);
vec2  make_vec2(float x, float y);

ivec2 ivec2_add(ivec2 a, ivec2 b);
ivec2 ivec2_sub(ivec2 a, ivec2 b);
ivec2 ivec2_mul(ivec2 v, ivec2 u);
int   ivec2_dot(ivec2 a, ivec2 b);
ivec2 ivec2_abs(ivec2 v);
ivec2 ivec2_scale(ivec2 a, int lambda);
ivec2 ivec2_normalize(ivec2 a);
int   ivec2_length(ivec2 a);
ivec2 ivec2_lerp(ivec2 a, ivec2 b, int t);
ivec2 make_ivec2(int x, int y);

mat4 mat4_make(vec4 a, vec4 b, vec4 c, vec4 d);
mat4 mat4_identity();
mat4 mat4_init();
mat4 mat4_add(mat4 a, mat4 b);
mat4 mat4_scale(mat4 m, float lamba);
mat4 mat4_scale_xyz(mat4 m, float x, float y, float z);
mat4 mat4_scale_xyzw(mat4 m, float x, float y, float z, float w);
mat4 mat4_mul(mat4 a, mat4 b);
mat4 mat4_translate(mat4 m, float x, float y, float z);
//mat4 mat4_translate3(mat4 m, float x, float y, float z);
//mat4 mat4_translate2(mat4 m, vec3 v);
mat4 mat4_rotate(mat4 m, float angle, float x, float y, float z);
mat4 mat4_tranpose(mat4 a);
mat4 mat4_tranpose2(mat4 m);
mat4 mat4_ortho(mat4 mtx, float left, float right, float bottom, float top, float znear, float zfar);
mat4 mat4_ortho2(mat4 mtx, float left, float right, float bottom, float top, float znear, float zfar);
mat4 mat4_ortho3(mat4 mtx, float left, float right, float bottom, float top, float znear, float zfar);
mat4 mat4_perspective(float angle, float ratio, float znear, float zfar);
mat4 mat4_lookAt(vec3 eye, vec3 center, vec3 up);
mat4 mat4_lookAt2(mat4 mtx, vec3 eye, vec3 center, vec3 up);

imat4 imat4_make(ivec4 a, ivec4 b, ivec4 c, ivec4 d);
imat4 imat4_translate(imat4 m, int x, int y, int z);


#endif
