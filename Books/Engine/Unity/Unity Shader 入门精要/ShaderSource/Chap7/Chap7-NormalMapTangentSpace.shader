// 在切线空间中做计算：顶点着色器内把光照和视角转到TBN
Shader "Unity Shaders Book/Chapter 7/NormalMapInTangentSpace"
{
    Properties 
    {
        _Color ("Color Tint", Color) = (1,1,1,1)
        _MainTex ("Main Tex", 2D) = "white" {}

        // 法线纹理_BumpMap默认值"bump"：Unity内置法线纹理，_BumpScale控制凹凸程度，=0时对光照无影响
        _BumpMap ("Normal Map", 2D) = "bump" {}
        _BumpScale ("Bump Scale", Float) = 1.0

        _Specular ("Specular", Color) = (1, 1, 1, 1)
        _Gloss ("Gloss", Range(8.0, 256)) = 20
    }

    SubShader 
    {
        Pass 
        { 
            Tags { "LightMode"="ForwardBase" }

            CGPROGRAM

            #pragma vertex vert
            #pragma fragment frag
            #include "Lighting.cginc"

            // 与Properties语义块中的属性建立联系
            fixed4 _Color;
            sampler2D _MainTex;
            float4 _MainTex_ST;
            sampler2D _BumpMap;
            float4 _BumpMap_ST;
            float _BumpScale;
            fixed4 _Specular;
            float _Gloss;

            struct a2v 
            {
                float4 vertex : POSITION;

                /* 通过顶点法线、切线构建TBN。
                 * 切线tangent为float4，比N多一维，通过tangent.w决定副切线B的方向性。
                 */
                float3 normal : NORMAL;
                float4 tangent : TANGENT;
                
                float4 texcoord : TEXCOORD0;
            };

            struct v2f 
            {
                float4 pos : SV_POSITION;

                // uv.xy存_MainTex，uv.zw存_BumpMap。
                // 共存，减少插值寄存器使用数
                float4 uv : TEXCOORD0;

                // 变换到切线空间下的光照和视角，传给fragment shader
                float3 lightDir: TEXCOORD1;
                float3 viewDir : TEXCOORD2;
            };

            v2f vert(a2v v) 
            {
                v2f o;
                o.pos = mul(UNITY_MATRIX_MVP, v.vertex);

                o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
                o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;

                // 求模型空间到TBN的变换矩阵
                // Compute the binormal
            //  float3 binormal = cross( normalize(v.normal), normalize(v.tangent.xyz) ) * v.tangent.w;
            //  // Construct a matrix which transform vectors from object space to tangent space
            //  float3x3 rotation = float3x3(v.tangent.xyz, binormal, v.normal);
                // Or just use the built-in macro
                TANGENT_SPACE_ROTATION;

                // Transform the light direction from object space to tangent space
                o.lightDir = mul(rotation, ObjSpaceLightDir(v.vertex)).xyz;
                // Transform the view direction from object space to tangent space
                o.viewDir = mul(rotation, ObjSpaceViewDir(v.vertex)).xyz;

                return o;
            }

            fixed4 frag(v2f i) : SV_Target
            {
                fixed3 tangentLightDir = normalize(i.lightDir);
                fixed3 tangentViewDir = normalize(i.viewDir);

                // 采样法线纹理
                fixed4 packedNormal = tex2D(_BumpMap, i.uv.zw);
                fixed3 tangentNormal;
                // 纹理类型未设为 Normal map 时
                // 1. 手动把 [0, 1] 范围的采样结果反映射到 [-1, 1] 的法线范围
                // 2. * _BumpScale 控制凹凸程度
                // 3. 通过单位向量的模为1的性质求z，由于是TBN下的法线所以z分量开根取正值
                //  tangentNormal.xy = (packedNormal.xy * 2 - 1) * _BumpScale;
                //  tangentNormal.z = sqrt(1.0 - saturate(dot(tangentNormal.xy, tangentNormal.xy)));

                // 纹理类型设为 Normal map 后，必须用内置函数，因为 Unity 会根据平台选择不同压缩方法
                // Or mark the texture as "Normal map", and use the built-in funciton
                tangentNormal = UnpackNormal(packedNormal);
                tangentNormal.xy *= _BumpScale;
                tangentNormal.z = sqrt(1.0 - saturate(dot(tangentNormal.xy, tangentNormal.xy)));

                // 采样普通纹理获取漫反射系数
                fixed3 albedo = tex2D(_MainTex, i.uv).rgb * _Color.rgb;

                fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

                // 虽然变换了空间，但法线和光照还是处于同一坐标空间下，点积值仍然正确
                fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(tangentNormal, tangentLightDir));

                // 应用TBN下的法线、光照、视角，达到了通过采样法线纹理影响光照的目的
                fixed3 halfDir = normalize(tangentLightDir + tangentViewDir);
                fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(tangentNormal, halfDir)), _Gloss);

                return fixed4(ambient + diffuse + specular, 1.0);
            }

            ENDCG
        }
    }
    Fallback "Specular"
}