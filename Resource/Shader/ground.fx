#include "H_common.fx"
#include "H_light.fx"

matrix g_world;
texture g_mainTex;
float4 g_fadeColor;
float g_moveSpeed;
sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;


};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	matrix matWorld = 0;
	matWorld._11 = 1;
	matWorld._22 = 1;
	matWorld._33 = 1;
	matWorld._44 = 1;

	matWorld._41 = g_cBuffer.worldCamPos.x;
	matWorld._42 = g_cBuffer.worldCamPos.y - 0.1f;
	matWorld._43 = g_cBuffer.worldCamPos.z;


	float4x4 wvp = mul(matWorld, g_cBuffer.viewProj);
	float4 pos = mul(float4(_input.position, 1), wvp).xyww;
	pos.z *= 0.95f;
	o.position = pos;
	o.uv = _input.uv;
	//o.normal = float3(0, 0, 1);


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input)
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 moveUV = _input.uv + float2(g_cBuffer.worldCamPos.x, -g_cBuffer.worldCamPos.z) * g_moveSpeed;
	float4 diffuse = tex2D(mainSampler, moveUV * 5);


	float2 uv = _input.uv - float2(0.5f, 0.5f);
	float distance = sqrt(pow(uv.x, 2) + pow(uv.y, 2));
	float ratio = max(min(distance * 2.f,1),0.1f);

	o.diffuse = diffuse * (1-ratio) + g_fadeColor * ratio;
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		//ZEnable = true;
		//ZWriteEnable = true;
		//CullMode = NONE;
		AlphaBlendEnable = true;

		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}





};
