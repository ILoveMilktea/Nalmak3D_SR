#include "H_common.fx"

matrix g_world;

texture g_mainTex;
float4 g_mainTexColor;
float g_strength = 0.5f;
float g_hitTimer = 0.f;
float4 g_hitPosition;
float g_radius = 5.f;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
	float3 view : TEXCOORD1;

};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float3 normal :NORMAL;
	float2 uv : TEXCOORD0; // x,y = uv  z = depth
	float3 view : TEXCOORD1;
	float3 worldPos : TEXCOORD2;
};

struct PS_INPUT
{
	float3 view  :NORMAL;
	float2 uv : TEXCOORD0;
	float3 normal : TEXCOORD1;
	float3 worldPos : TEXCOORD2;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	matrix wvp = mul(g_world, g_cBuffer.viewProj);

	float4 worldPos = mul(float4(_in.pos, 1), g_world);

	o.pos = mul(worldPos, g_cBuffer.viewProj);

	o.view = (worldPos - g_cBuffer.worldCamPos);

	o.normal = GetWorldNormal(_in.normal, g_world);

	o.worldPos = worldPos;

	o.uv = _in.uv * 7;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float3 view = normalize(_in.view);
	float3 normal = normalize(_in.normal);
	float4 diffuse = tex2D(mainSampler, _in.uv);
	o.diffuse = diffuse * g_mainTexColor;




	float alpha = o.diffuse.a;
	alpha = min(pow(1.f - dot(-normal, view),3) * g_strength, alpha);
	o.diffuse.a = alpha;

	float3 worldPos = _in.worldPos;
	
	//o.diffuse = 1 - (length(g_hitPosition.xyz - worldPos) / g_radius);

	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

	/*	ZEnable = true;
		ZWriteEnable = true;
		CullMode = CCW;*/
		ZWriteEnable = true;
		//CullMode = none;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
