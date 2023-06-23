#include"Object3d.hlsli"
struct Material {
	float32_t4 color;//元の色
	int32_t enableLighting;//ライトのフラグ
};
struct DirectionalLight {
	float32_t4 color;//ライトの色
	float32_t3 direction;//ライトの向き
	float intensity;//ライトの輝度
};
ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);
struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};
 
PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
	float32_t4 textureColor = gTexture.Sample(gSampler,input.texcoord);
	if (gMaterial.enableLighting ==true) {//Lightingする場合
		float cos = saturate(dot(normalize(input.normal),-gDirectionalLight.direction));
		output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;
	}
	else {//Lightingしない場合
		output.color = gMaterial.color * textureColor;
	}
	
	return output;
}