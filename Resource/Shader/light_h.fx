struct BaseLight
{
	float3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct PointLight
{
	BaseLight base;

	float3 position;
	float radius;
};

//struct DirectionalLight
//{
//	BaseLight base;
//	vec3 Direction;
//};

float4 CalcLightInternal(BaseLight _light, float3 _camPos, float3 _direction, float3 _worldPos, float3 _normal)
{
	//float4 ambientColor = float4(_light.color * _light.ambientIntensity, 1.0);
	float diffuseFactor = dot(_normal, -_direction);

	float4 diffuseColor = 0;
	//float4 specularColor = 0;
	if (diffuseFactor > 0.0)
	{
		diffuseColor = float4(_light.color * _light.diffuseIntensity * diffuseFactor, 1.0);

		//float3 vertexToEye = normalize(_camPos - _worldPos);
	}

	//return ambientColor + diffuseColor;
	return diffuseColor;
}

float4 CalcPointLight(PointLight _pointLight, float3 _lightPos, float3 _camPos, float3 _worldPos, float3 _normal)
{
	//_lightPos = 0;
	float3 lightDirection = _worldPos - _camPos;
	float distance = length(lightDirection);
	lightDirection = normalize(lightDirection);

	float4 color = CalcLightInternal(_pointLight.base, _camPos, lightDirection, _worldPos, _normal);

	//float attenuation = (_pointLight.constant) + (_pointLight.linearRatio * distance) + (_pointLight.exp * distance * distance);
	float attenuation = pow(saturate(1.f - distance / _pointLight.radius), 1);

	/*if (distance > _pointLight.radius)
		color = 0;*/
	/*if (distance < _pointLight.radius)
		color = 1;
	else
		color = 0;*/
	//attenuation = max(1.0, attenuation);

	return  attenuation;
}

//float4 CalcLightInternal(baseLightInfo _light, float3 _lightDir, float3 _normal)
//{
//	float4 ambientColor = float4(_light.color, 1.0) * _light.ambientIntensity;
//	float diffuseFactor = dot(_normal, -lightDir);
//
//	float4 diffuseColor = 0;
//	float4 specular
//}