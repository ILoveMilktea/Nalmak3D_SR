matrix g_cameraMatrix;
matrix g_viewProj;

texture g_mainTex;

sampler mainSampler = sampler_state
{
	texture = g_mainTex;

	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

struct VS_INPUT
{
	float3 position : POSITION;
	float2 uv : TEXCOORD0;

	float4 worldMatrix1 : TEXCOORD1;
	float4 worldMatrix2 : TEXCOORD2;
	float4 worldMatrix3 : TEXCOORD3;
	float4 worldMatrix4 : TEXCOORD4;
	float4 color : TEXCOORD5;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 uv : TEXCOORD0;
	float4 color : TEXCOORD1;
};

struct PS_INPUT
{
	float2 uv : TEXCOORD0;
	float4 color : TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 초기화 필수!
	float4x4 world = { _input.worldMatrix1 , _input.worldMatrix2 , _input.worldMatrix3 , _input.worldMatrix4 };
	/*{ 
		worldMatrix1.x,worldMatrix1.y,worldMatrix1.z,worldMatrix1.w,
		worldMatrix2.x,worldMatrix2.y,worldMatrix2.z,worldMatrix2.w,
		worldMatrix3.x,worldMatrix3.y,worldMatrix3.z,worldMatrix3.w,
		worldMatrix4.x,worldMatrix4.y,worldMatrix4.z,worldMatrix4.w
	};*/
	float4x4 wvp = mul(world, g_viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	o.uv = _input.uv;
	o.color = _input.color;
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = tex2D(mainSampler, _input.uv);
	o.diffuse = diffuse * _input.color;
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		ZEnable = false;
		ZWriteEnable = false;
		//CullMode = CCW;

		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();


	}


	
};
