#include "H_common.fx"
#include "H_light.fx"

matrix g_world;
DirectionalLight g_directionalLight;

texture g_diffuse;
texture g_normal;
texture g_depth;
texture g_cookTorrance;

sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
};

sampler NormalSampler = sampler_state
{
	texture = g_normal;
};

sampler DepthSampler = sampler_state
{
	texture = g_depth;
};

sampler CookTorranceSampler = sampler_state
{
	texture = g_cookTorrance;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float2 uv :TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _in)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.pos = mul(float4(_in.pos, 1), g_world);
	o.pos.w = 1;
	o.uv = _in.uv;


	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _in) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;

	float2 uvRT = _in.uv + float2(perPixelX, perPixelY);

	float4 diffuse = tex2D(DiffuseSampler, uvRT);
	float3 normal = tex2D(NormalSampler, uvRT).xyz;

	float2 depth = tex2D(DepthSampler, uvRT).xy;
	float4 worldPos = GetWorldPosFromDepth(depth, _in.uv);

	float2 cookTorrance = tex2D(CookTorranceSampler, uvRT).xy;
	float f0 = cookTorrance.x;
	float roughness = cookTorrance.y;


	float4 light = CalcLightInternal(g_directionalLight.base, g_cBuffer.worldCamLook, g_directionalLight.direction, worldPos.xyz, normal);


	/*float specular = LightingGGX_Ref(
		normal,
		g_cBuffer.worldCamLook,
		-g_directionalLight.direction,
		cookTorrance.x,
		cookTorrance.y
	);*/
	//////////////////////////
	float specular;;
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
	{
		specular = 0;
	}
	else
	{
		normal = normal * 2 - 1;
		float3 _N = normal;
		float3 _V = normalize(g_cBuffer.worldCamPos - worldPos.xyz);
		float3 _L = -g_directionalLight.direction;
		float3 _F0 = cookTorrance.x;
		float _Roughness = cookTorrance.y;
		float alpha = _Roughness * _Roughness;

		float3 H = normalize(_V + _L);

		float dotNL = saturate(dot(_N, _L));
		float dotNV = saturate(dot(_N, _V));
		float dotNH = saturate(dot(_N, H));
		float dotLH = saturate(dot(_L, H));

		float F; // Fresnel
		float D; // GGX ref
		float V; // smith's schlick

		float alphaSqr = alpha * alpha;
		const float PI = 3.141592f;
		float denom = dotNH * dotNH * (alphaSqr - 1.0) + 1.0f;
		D = alphaSqr / (PI * denom * denom);

		float dotLH5 = pow(1.0f - dotLH, 5);
		F = _F0 + (1.0 - _F0) * dotLH5;


		float k = alpha / 2.0f;
		V = G1V(dotNL, k) * G1V(dotNV, k);

		specular = dotNL * D * F * V;
	}
	

	
	///////////////////////////
	o.color = light + specular;
	return o;
}

// implicit truncation of vector type


technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z °ª¿¡´ëÇÑ È°¿ë

		ZEnable = false;
		AlphaBlendEnable = true;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
