#include"Object3d.hlsli"
struct Material
{
    float32_t4 color; //元の色
    int32_t enableLighting; //ライトのフラグ
    float32_t4x4 uvTransform; //uvのSRT
};
struct DirectionalLight
{
    float32_t4 color; //ライトの色
    float32_t3 direction; //ライトの向き
    float intensity; //ライトの輝度
};
ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<DirectionalLight> gDirectionalLight : register(b1);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);
struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    float cos;

	//ライティング
    if (gMaterial.enableLighting != 0)
    { //Lightingする場合
        if (gMaterial.enableLighting == harfLambert)
        {
            float NdotL = dot(normalize(input.normal), -gDirectionalLight.direction);
            cos = pow(NdotL * 0.5f + 0.5f, 2.0f);
            output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;
            if (cos > 0.9f)
            {
                output.color.x += 0.4f;
                output.color.z -= 0.4f;
            }
            else if (cos > 0.8f)
            {
                output.color.x += 0.3f;
                output.color.z -= 0.3f;
            }
            else if (cos > 0.6f)
            {
                output.color.x += 0.3f;
                //output.color.y -= 0.2f;
                output.color.z -= 0.2f;
            }
            else if (cos > 0.3f)
            {
                output.color.x += 0.2f;
                output.color.z -= 0.2f;
            }
            else if (cos > 0.0f)
            {
                output.color.y -= 0.2f;
                output.color.z += 0.4f;
            }
        }
        else if (gMaterial.enableLighting == Lambert)
        {
            cos = saturate(dot(normalize(input.normal), -gDirectionalLight.direction));
            output.color = gMaterial.color * textureColor * gDirectionalLight.color * cos * gDirectionalLight.intensity;
            if (cos > 0.9f)
            {
                output.color.x += 0.4f;
                output.color.y -= 0.4f;
                output.color.z -= 0.4f;
            }
            else if (cos > 0.8f)
            {
                output.color.x += 0.3f;
                output.color.y -= 0.3f;
                output.color.z -= 0.3f;
            }
            else if (cos > 0.6f)
            {
                output.color.x += 0.2f;
                output.color.y -= 0.2f;
                output.color.z -= 0.2f;
            }
            else if (cos > 0.4f)
            {
                output.color.x += 0.1f;
                output.color.y -= 0.1f;
                output.color.z -= 0.1f;
            }
            else if (cos > 0.0f)
            {
                output.color.x -= 0.1f;
                output.color.y -= 0.1f;
                output.color.z += 0.1f;
            }
            else if (cos > -0.5f)
            {
                output.color.x -= 0.2f;
                output.color.y -= 0.2f;
                output.color.z += 0.2f;
            }
            else if (cos > -1.0f)
            {
            output.color.x -= 0.4f;
            output.color.y -= 0.4f;
            output.color.z += 0.4f;
            }
        }
    }
    else
    { //Lightingしない場合
        output.color = gMaterial.color * textureColor;
    }
    
    return output;
}