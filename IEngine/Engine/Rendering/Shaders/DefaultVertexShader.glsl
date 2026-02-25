#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 position;
uniform vec3 rotation;   // Euler angles in radians (x, y, z)
uniform vec3 scale;

void main()
{
	vec3 pos = aPos;

	// Scale
	pos *= scale;

	// Rotation around X
	float cx = cos(rotation.x);
	float sx = sin(rotation.x);
	pos = vec3(
		pos.x,
		pos.y * cx - pos.z * sx,
		pos.y * sx + pos.z * cx
	);

	// Rotation around Y
	float cy = cos(rotation.y);
	float sy = sin(rotation.y);
	pos = vec3(
		pos.x * cy + pos.z * sy,
		pos.y,
		-pos.x * sy + pos.z * cy
	);

	// Rotation around Z
	float cz = cos(rotation.z);
	float sz = sin(rotation.z);
	pos = vec3(
		pos.x * cz - pos.y * sz,
		pos.x * sz + pos.y * cz,
		pos.z
	);

	// Translation
	pos += position;

	gl_Position = vec4(pos, 1.0);
}