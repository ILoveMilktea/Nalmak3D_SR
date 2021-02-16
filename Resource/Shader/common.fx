struct DirectionalLight
{
	float3 direction;
	float3 color;
	float intensity;
};

struct cBuffer
{
	matrix viewProj;
	float3 worldCamPos;

	int isDirectionalLight;
	DirectionalLight directionalLight;

};

cBuffer g_cBuffer;