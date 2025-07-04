#pragma once
#include "myMath.h"

static const float deltaTime = 1.0f / 60.0f;

// 基本物体情報
struct PhysicalObject {
    Vector3 position;       // ボールの位置
    Vector3 velocity;       // ボールの速度
    Vector3 acceleration;   // ボールの加速度
    float mass;             // ボールの質量
    unsigned int color;     // ボールの色
};

struct Spring {
	Vector3 anchor;
	PhysicalObject end; // バネの片端の物体
	float naturalLength; //自然長
	float  stiffness; //剛性。バネ定数k
	float dampingCoefficient; //減衰係数
};


// ボールの情報
struct Ball:PhysicalObject {
    float radius;           // ボールの半径
};

void springUpdate(Spring* spring);

