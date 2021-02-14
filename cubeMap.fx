
matrix g_world;
matrix g_viewProj;

texture g_cubeTex;
float4 g_mainTexColor;

sampler skyBoxSampler = sampler_state
{
	texture = g_cubeTex;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float3 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float3 position : POSITION;
	float3 uv : TEXCOORD0;
};

struct PS_INPUT
{
	float3 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float3 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 초기???�수!

	
	float4x4 wvp = mul(g_world, g_viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	o.uv = _input.uv;
	//o.normal = float3(0, 0, 1);
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = tex2D(mainSampler, _input.uv);
	o.diffuse = diffuse * g_mainTexColor;
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();
	}


		

	
}
