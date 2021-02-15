matrix g_cameraMatrix;
matrix g_world;
matrix g_viewProj;

texture g_mainTex;
float4 g_mainTexColor;

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
	float3 normal :NORMAL;
	float3 uvAndDepth : COLOR; // x,y = uv  z = depth
	
};

struct PS_INPUT
{
	float3 normal :NORMAL;
	float3 uvAndDepth : COLOR;
};

struct PS_OUTPUT
{
	float4 diffuse : COLOR0;
	float4 depth : COLOR1;
	float4 normal : COLOR2;

};

VS_OUTPUT VS_Main_Default(VS_INPUT _input)
{
	VS_OUTPUT o = (VS_OUTPUT)0; // 

	float4x4 wvp = mul(g_world, g_viewProj);
	o.position = mul(float4(_input.position,1), wvp);
	o.normal = _input.normal;
	o.uvAndDepth.xy = _input.uv;
	o.uvAndDepth.z = 1 - (o.position.z / o.position.w);
	//o.normal = float3(0, 0, 1);
	
	
	return o;
}


PS_OUTPUT PS_Main_Default(PS_INPUT  _input) 
{
	PS_OUTPUT o = (PS_OUTPUT)0;
	float4 diffuse = tex2D(mainSampler, _input.uvAndDepth.xy);
	float4 final = diffuse * g_mainTexColor;
	o.diffuse = final;
	o.depth = _input.uvAndDepth.z;
	o.normal.xyz = ((_input.normal + 1) * 0.5f);
	o.normal.w = 1;
	return o;
}



technique DefaultTechnique
{
	Pass DefaultPass
	{
		//https://blueswamp.tistory.com/entry/D3DRSZENABLE-D3DRSZWRITEENABLE Z 값에대한 활용

		//ZEnable = true;
		//ZWriteEnable = true;
		CullMode = CCW;
		VertexShader = compile vs_3_0 VS_Main_Default();
		PixelShader = compile ps_3_0 PS_Main_Default();

	}


		

	
};
