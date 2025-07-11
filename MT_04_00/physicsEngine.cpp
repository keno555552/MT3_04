#include "physicsEngine.h"

void springUpdate(Spring* spring) {
	Vector3 diff = spring->end.position - spring->anchor;
	float length = Length(diff);
	if (length != 0.0f) {
		Vector3 direction = Normalize(diff);
		Vector3 restPosition = spring->anchor + direction * spring->naturalLength;
		Vector3 displacement = length * (spring->end.position - restPosition);
		Vector3 restoringForce = -spring->stiffness * displacement;
		Vector3 dampingForce = -spring->dampingCoefficient * spring->end.velocity;
		Vector3 force = restoringForce + dampingForce;
		spring->end.acceleration = force / spring->end.mass;
	}
	// 加速度や速度のどちらも秒を基準として計算する
	// それが、1/60秒間(deltaTime)適用されたと考える
	/// ここ変わる
	spring->end.velocity = spring->end.velocity + spring->end.acceleration * deltaTime;
	spring->end.position = spring->end.position + spring->end.velocity * deltaTime;

}

Vector3 PendulumUpdate(Pendulum* pendulum) {
	pendulum->angularAcceleration =
		-(9.8f / pendulum->length) * std::sin(pendulum->angle);
	pendulum->angularVelocity += pendulum->angularAcceleration * deltaTime;
	pendulum->angle += pendulum->angularVelocity * deltaTime;

	// pは振り子の先端の位置。取り付けたいものを取り付ければ良い
	Vector3 result = {};
	result.x = pendulum->anchor.x + std::sin(pendulum->angle) * pendulum->length;
	result.y = pendulum->anchor.y - std::cos(pendulum->angle) * pendulum->length;
	result.z = pendulum->anchor.z;

	return result;
}

void conicalPendulumUpdate(ConicalPendulum* pendulum) {
	pendulum->angularVelocity = std::sqrt(9.8f / (pendulum->length * std::cos(pendulum->halfApexAngle)));
	pendulum->angle += pendulum->angularVelocity * deltaTime;

	float radius = std::sin(pendulum->halfApexAngle) * pendulum->length;
	float height = std::cos(pendulum->halfApexAngle) * pendulum->length;
	pendulum->end.position.x = pendulum->anchor.x + std::cos(pendulum->angle) * radius;
	pendulum->end.position.y = pendulum->anchor.y - height;
	pendulum->end.position.z = pendulum->anchor.z - std::sin(pendulum->angle) * radius;
}

Vector3 Reflect(Ball* ball, Plane* plane) {
	Vector3 reflected = ReflectVector3(ball->velocity, plane->normal);
	Vector3 projectToNormal = Project(reflected, plane->normal);
	Vector3 movingDirection = reflected - projectToNormal;
	ball->velocity = projectToNormal * 0.95f/*反発係数*/ + movingDirection;
	return ball->velocity;
}
