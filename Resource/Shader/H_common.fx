
static const float zNear = 1;
static const float zFar = 1000;
static const int WINCX = 1920;
static const int WINCY = 1080;
static const float perPixelX = 0.5f / WINCX;
static const float perPixelY = 0.5f / WINCY;


struct cBuffer
{
	matrix viewProj;
	matrix invView;
	matrix invProj;
	float3 worldCamPos;
	float3 worldCamLook;

};

cBuffer g_cBuffer;





float2 ComputeScreenUV(float4 _clipPos)
{
	float2 screenUV = _clipPos.xy / _clipPos.w;
	screenUV = 0.5f * screenUV + 0.5f;
	screenUV.y = 1 - screenUV.y;

	return screenUV;
}

float4 GetWorldNormal(float3 _normal, matrix _world)
{
	return  normalize(mul(float4(_normal, 0.f), _world));
}

float4 GetScaleBiasNormal(float3 _normal)
{
	return float4(_normal * 0.5f + 0.5f, 1.f);
}
// ( zx , zy , 0~far, z)     ->       z ( near ~ far)
float4 GetDepth(float2 _projZW)
{
	//              0 ~ far / near ~ far,   near ~ far / far    
	return float4(_projZW.x / _projZW.y,     _projZW.y / zFar,      0.f, 0.f);
}



float4 GetWorldPosFromDepth(float2 _depth, float2 _screenUV)
{
	float linearZ = _depth.y * zFar; // near ~ far

	float4 pos;
	pos.x = (_screenUV.x * 2.f - 1.f) * linearZ;
	pos.y = (_screenUV.y * -2.f + 1.f) * linearZ;
	pos.z = _depth.x * linearZ;
	pos.w = linearZ;

	pos = mul(pos, g_cBuffer.invProj);
	pos = mul(pos, g_cBuffer.invView);

	return pos;
}

float4 GetWorldPosFromDepth2(float _depth, float2 _screenUV)
{

}


