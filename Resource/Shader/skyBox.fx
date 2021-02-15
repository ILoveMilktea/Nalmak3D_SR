
matrix g_cameraMatrix;
matrix g_world;
matrix g_viewProj;

texture g_skyBox;


samplerCUBE skyBoxSampler = sampler_state
{
	texture = <g_skyBox>;
	magfilter = LINEAR;
	minfilter = LINEAR;
	mipfilter = LINEAR;
	AddressU = Mirror;
	AddressV = Mirror;

};

struct VS_INPUT
{
	float3 position : POSITION;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float3 texCoord : TEXCOORD0;
};

struct PS_INPUT
{
	float3 texCoord : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; 

	float4 camPos = 1;
	camPos.x = g_cameraMatrix._41;
	camPos.y = g_cameraMatrix._42;
	camPos.z = g_cameraMatrix._43;

	matrix wvp = mul(g_cameraMatrix, g_viewProj);
	o.position = mul(float4(_input.position,1), wvp);

	float4 texCoord = mul(float4(_input.position, 1), g_world);
	o.texCoord = normalize(texCoord - camPos).xyz;
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	o.diffuse =texCUBE(skyBoxSampler, _input.texCoord);
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		ZEnable = false;
		ZWriteEnable = false;
		CullMode = NONE;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
