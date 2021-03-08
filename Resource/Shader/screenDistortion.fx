#include "H_common.fx"

matrix g_world;

texture g_mainTex;
float2 g_distortionCenter;
float g_distortionPower;
float g_distortionSize;
float g_distortionThickness;
sampler mainSampler = sampler_state
{
	texture = g_mainTex;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
	
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 clipPos : TEXCOORD0;
	float2 uv : TEXCOORD1;
};

struct PS_INPUT
{
	float4 clipPos : TEXCOORD0;
	float2 uv :TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR;

};



VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	o.pos = float4(_in.pos, 1);

	o.uv = _in.uv;
	
	o.clipPos = o.pos;
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float2 screenUV = ComputeScreenUV(_in.clipPos);

	float ratio =  (float)WINCX / WINCY;
	float2 scaledUV = (screenUV - float2(0.5f, 0.f)) / float2(ratio, 1.0f) + float2(0.5f , 0.0f);

	float mask = (1.0f - smoothstep(g_distortionSize - 0.1f, g_distortionSize, length(scaledUV - g_distortionCenter)))
		* smoothstep(g_distortionSize - 0.1f - g_distortionThickness, g_distortionSize - g_distortionThickness, length(scaledUV - g_distortionCenter));

	float2 distortionUV = normalize(scaledUV - g_distortionCenter) * g_distortionPower * mask;
	float4 diffuse = tex2D(mainSampler, screenUV - distortionUV + float2(perPixelX, perPixelY));


	o.diffuse = diffuse;

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
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
