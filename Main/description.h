#pragma once
#include "../AntiDebug/CallStack-Spoofer.h"
#include "../Includes/includes.hpp"



Vector3 GetBone(uintptr_t mesh, int bone_id)
{
	SPOOF_FUNC;
	int is_cached = driver.read<int>(mesh + BONE_ARRAY_CACHE);
	uintptr_t bone_array = driver.read<uintptr_t>(mesh + BONE_ARRAY + (is_cached * 0x10));
	FTransform bone = driver.read<FTransform>(bone_array + (bone_id * 0x60));
	FTransform component_to_world = driver.read<FTransform>(mesh + COMPONENT_TO_WORLD);
	D3DMATRIX matrix = matrix_multiplication(bone.to_matrix_with_scale(), component_to_world.to_matrix_with_scale());
	return Vector3(matrix._41, matrix._42, matrix._43);
}




struct CamewaDescwipsion
{

	Vector3 location;
	Vector3 rotation;
	float FieldOfView;
};

CamewaDescwipsion GetViewPoint()
{
	SPOOF_FUNC;
	CamewaDescwipsion ViewPoint;
	__int64 result; // rax
	__int64 v7; // rcx

	result = driver.read<__int64>(rootAddress + 0xE2CED18);
	v7 = rootAddress + 0xE2CECD8;
	if (result)
		v7 = result;

	__int64 EncryptedData[7];
	for (int i = 0; i < 7; i++)
		EncryptedData[i] = driver.read<__int64>(v7 + (i * 8));
	EncryptedData[0] ^= 0x4CF1F15DFE2D977Fi64;
	EncryptedData[1] ^= 0x4CF1F15DFE2D977Fi64;
	EncryptedData[2] ^= 0x4EF1F15DFE2D977Fi64;
	EncryptedData[3] ^= 0xAF29A7F813EFC5Ci64;
	EncryptedData[4] ^= 0xAF29A7F813EFC5Ci64;
	EncryptedData[5] ^= 0x4EF29A7E813EFC5Di64;
	EncryptedData[6] ^= 0x4E1772384C14291Fi64;

	ViewPoint.location = { *(double*)(&EncryptedData[1]),*(double*)(&EncryptedData[0]), *(double*)(&EncryptedData[2]) };
	ViewPoint.rotation = { *(double*)(&EncryptedData[4]),*(double*)(&EncryptedData[3]), *(double*)(&EncryptedData[5]) };
	ViewPoint.FieldOfView = *(float*)(&EncryptedData[6]);

	return ViewPoint;
}

//// (rootAddress + VIEW_POINT);

Vector3 Localcam;


 namespace cache
 {
	  uintptr_t uworld;
	  uintptr_t game_instance;
	  uintptr_t local_players;
	  uintptr_t player_controller;
	  uintptr_t local_pawn;
	  uintptr_t currentVehicle;
	  uintptr_t root_component;
	  Vector3 relative_location;
	  uintptr_t player_state;
	  int my_team_id;
	  uintptr_t game_state;
	  uintptr_t player_array;
	  int player_count;

	  CamewaDescwipsion local_camera;
 }


 Vector3 w2s(Vector3 WorldLocation)
 {
	 CamewaDescwipsion ViewPoint = GetViewPoint();
	 D3DMATRIX tempMatrix = to_matrix(ViewPoint.rotation);
	 Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	 Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	 Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	 Vector3 vDelta = WorldLocation - ViewPoint.location;
	 Vector3 vTransformed = Vector3(vDelta.dot(vAxisY), vDelta.dot(vAxisZ), vDelta.dot(vAxisX));
	 if (vTransformed.z < 1.f)
		 vTransformed.z = 1.f;
	 return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(ViewPoint.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
 }
