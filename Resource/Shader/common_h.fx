struct DirectionalLight
{
	float3 direction;
	float3 color;
	float intensity;
};

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

///////////////////////////////////////////////////////////////////////////////////////////////

// 투영행렬까지 곱한 버텍스좌표를 받아 uv공간으로 이동시켜준다
float2 ComputeScreenPos(float4 _clipPos)
{
	float2 screenPos = _clipPos.xy / _clipPos.w;
	screenPos = 0.5f * screenPos + 0.5f;
	screenPos.y = 1 - screenPos.y;

	return screenPos;
}

float CalcLinearZ(float _depth)
{
	const float zFar = 1000.0;
	const float zNear = 1.0;

	float linearZ = zNear / (zFar - _depth * (zFar - zNear)) * zFar;

	return (linearZ * 2.0) - 1.0;
}

float3 GetWorldPosFromDepth(float _depth, float2 _screenUV)
{
	float viewZ = CalcLinearZ(_depth);

	float4 clipSpacePos = float4(_screenUV * 2.0 - 1.0, viewZ, 1);

	float4 viewSpacePos = mul(g_cBuffer.invProj,clipSpacePos);

	viewSpacePos /= viewSpacePos.w;

	float4 worldSpacePos = mul(g_cBuffer.invView, viewSpacePos);

	return worldSpacePos.xyz;
}