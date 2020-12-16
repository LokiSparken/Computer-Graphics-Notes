// 在切线空间中做计算：顶点着色器内把光照和视角转到TBN
Shader "Unity Shaders Book/Chapter 7/NormalMapInWorldSpace"
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

                // 3x3存TBN到世界空间的变换矩阵，w分量存世界空间顶点位置，充分利用插值寄存器
                float4 TtoW0 : TEXCOORD1;  
                float4 TtoW1 : TEXCOORD2;  
                float4 TtoW2 : TEXCOORD3; 
            };

            v2f vert(a2v v) 
            {
                v2f o;
                o.pos = mul(UNITY_MATRIX_MVP, v.vertex);

                o.uv.xy = v.texcoord.xy * _MainTex_ST.xy + _MainTex_ST.zw;
                o.uv.zw = v.texcoord.xy * _BumpMap_ST.xy + _BumpMap_ST.zw;

                // 各量转到世界空间
                float3 worldPos = mul(_Object2World, v.vertex).xyz;  
                fixed3 worldNormal = UnityObjectToWorldNormal(v.normal);  
                fixed3 worldTangent = UnityObjectToWorldDir(v.tangent.xyz);  
                fixed3 worldBinormal = cross(worldNormal, worldTangent) * v.tangent.w; 

                // TBN=>World Space：TBN按列，.w存顶点世界坐标
                // Compute the matrix that transform directions from tangent space to world space
                // Put the world position in w component for optimization
                o.TtoW0 = float4(worldTangent.x, worldBinormal.x, worldNormal.x, worldPos.x);
                o.TtoW1 = float4(worldTangent.y, worldBinormal.y, worldNormal.y, worldPos.y);
                o.TtoW2 = float4(worldTangent.z, worldBinormal.z, worldNormal.z, worldPos.z);

                return o;
            }

            fixed4 frag(v2f i) : SV_Target
            {
                // Get the position in world space      
                float3 worldPos = float3(i.TtoW0.w, i.TtoW1.w, i.TtoW2.w);
                // Compute the light and view dir in world space
                fixed3 lightDir = normalize(UnityWorldSpaceLightDir(worldPos));
                fixed3 viewDir = normalize(UnityWorldSpaceViewDir(worldPos));

                // Get the normal in tangent space
                fixed3 bump = UnpackNormal(tex2D(_BumpMap, i.uv.zw)); // 采样、解码（type = Normal map）
                bump.xy *= _BumpScale;
                bump.z = sqrt(1.0 - saturate(dot(bump.xy, bump.xy)));
                // Transform the normal from tangent space to world space
                bump = normalize(half3(dot(i.TtoW0.xyz, bump), dot(i.TtoW1.xyz, bump), dot(i.TtoW2.xyz, bump)));

                fixed3 albedo = tex2D(_MainTex, i.uv).rgb * _Color.rgb;

                fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

                fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(Normal, LightDir));

                fixed3 halfDir = normalize(LightDir + ViewDir);
                fixed3 specular = _LightColor0.rgb * _Specular.rgb * pow(max(0, dot(Normal, halfDir)), _Gloss);

                return fixed4(ambient + diffuse + specular, 1.0);
            }

            ENDCG
        }
    }
    Fallback "Specular"
}