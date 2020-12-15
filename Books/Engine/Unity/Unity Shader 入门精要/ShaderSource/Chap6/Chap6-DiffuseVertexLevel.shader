Shader "Unity Shaders Book/Chapter 6/DiffuseVertexLevel"
{
    properties
    {
        _Diffuse ("Diffuse", Color) = (1, 1, 1, 1)
    }
    SubShader
    {
        Pass
        {
            Tags { "LightMode" = "ForwardBase"}
            
            CGPROGRAM
            
            #pragma vertex vert
            #pragma fragment frag

            #include "Lighting.cginc"
            fixed4 _Diffuse;

            struct a2v
            {
                float4 vertex : POSITION;
                float3 normal : NORMAL;
            };

            struct v2f
            {
                float4 pos : SV_POSITION;
                fixed3 color : COLOR;
            };

            v2f vert(a2v v)
            {
                v2f output;
                // 1. 将顶点坐标做MVP变换，从模型空间变换到裁剪空间
                output.pos = mul(UNITY_MATRIX_MVP, v.vertex);
                // 2. 获取环境光
                fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz;
                /*
                 * 3. 法线和光源的点积：注意变换到同一坐标空间，此处把顶点法线转换到世界空间。
                 * 逆转置：_World2Object 为顶点 MVP 矩阵的逆矩阵，mul换位相当于乘转置。
                 * 光源：_WorldSpaceLightPos0，仅当场景中只有单个平行光时适用。
                 * saturate：截取到[0, 1]
                 */
                fixed3 worldNormal = normalize(mul(v.normal, (float3x3)_World2Object));
                fixed3 worldLight = normalize(_WorldSpaceLightPos0.xyz);
                fixed3 diffuse = _LightColor0.rgb * _Diffuse.rgb * saturate(dot(worldNormal, worldLight));

                output.color = ambient + diffuse;
                return output;
            }

            fixed4 frag(v2f input) : SV_Target
            {
                return fixed4(input.color, 1.0);
            }

            ENDCG
        }
    }
    Fallback "Diffuse"
}