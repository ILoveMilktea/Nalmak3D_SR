struct DirectionalLight
{
	float3 direction;
	float3 color;
	float intensity;
};
static const float zNear = 1;
static const float zFar = 1000;

struct cBuffer
{
	matrix viewProj;
	matrix invView;
	matrix invProj;
	float3 worldCamPos;

	int wincx;
	int wincy;

	int isDirectionalLight;
	DirectionalLight directionalLight;

};

cBuffer g_cBuffer;




// 투영행렬까지 곱한 버텍스좌표를 받아 uv공간으로 이동시켜준다
float2 ComputeScreenPos(float4 _clipPos)
{
	float2 screenPos = _clipPos.xy / _clipPos.w;
	screenPos = 0.5f * screenPos + 0.5f;
	screenPos.y = 1 - screenPos.y;

	return screenPos;
}

float4 GetWorldNormal(float3 _normal, matrix _world)
{
	return  normalize(mul(float4(_normal, 0.f), _world));
}

float4 GetScaleBiasNormal(float3 _normal)
{
	return float4(_normal * 0.5f + 0.5f, 0.f);
}

float4 GetDepth(float2 _projZW)
{
	return float4(_projZW.x / _projZW.y, _projZW.y / zFar, 0.f, 0.f);
}



float4 GetWorldPosFromDepth(float2 _depth, float2 _screenUV)
{
	float linearZ = _depth.y * zFar;

	float4 pos;
	pos.x = (_screenUV.x * 2.f - 1.f) * linearZ;
	pos.y = (_screenUV.y * -2.f + 1.f) * linearZ;
	pos.z = _depth.x * linearZ;
	pos.w = linearZ;

	pos = mul(pos, g_cBuffer.invProj);
	pos = mul(pos, g_cBuffer.invView);

	return pos;
}



