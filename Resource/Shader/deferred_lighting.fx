
matrix g_world;
matrix g_viewProj;

texture g_diffuse;
texture g_depth;
texture g_normal;

float3 g_lightDirection = (0, -0.6f, 0.3f);
sampler DiffuseSampler = sampler_state
{
	texture = g_diffuse;
};
sampler DepthSampler = sampler_state
{
	texture = g_depth;
};
sampler NormalSampler = sampler_state
{
	texture = g_normal;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
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

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	float4x4 wvp = mul(g_world, g_viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	o.uv = _input.uv;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = tex2D(DiffuseSampler, _input.uv);
	float3 normal = tex2D(NormalSampler, _input.uv).xyz;

	float light = max(dot(normal, g_lightDirection),0.0);

	o.color = light;
	o.color.w = 1;
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		//ZEnable = true;
		//ZWriteEnable = true;
		//CullMode = CCW;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
