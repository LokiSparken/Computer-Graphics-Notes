// Upgrade NOTE: replaced '_Object2World' with 'unity_ObjectToWorld'
// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Unity Shaders Book/Chapter 8/AlphaTest"
{
    Properties
    {
		_Color("Main Tint", Color) = (1,1,1,1)
		_MainTex("Main Tex", 2D) = "white" {}
		_Cutoff("Alpha Cutoff", Range(0, 1)) = 0.5	// 透明度阈值
    }
    SubShader
    {
		Tags 
		{
			"Queue" = "AlphaTest"					// 指定渲染队列
			"IgnoreProjector" = "True"				// 不受 Projector 影响
			"RenderType" = "TransparentCutout"		// 将当前 Shader 分类到使用透明度测试的组 TransparentCutout
		}

		Pass 
		{
			Tags { "LightMode" = "ForwardBase" }

			CGPROGRAM

			#pragma vertex vert
			#pragma fragment frag
			#include "Lighting.cginc"

			// 颜色四通道，纹理，纹理缩放，透明度
			fixed4 _Color;
			sampler2D _MainTex;
			float4 _MainTex_ST;
			fixed _Cutoff;

			struct a2v 
			{
				float4 vertex : POSITION;
				float3 normal : NORMAL;
				float4 texcoord : TEXCOORD0; 
			};

			struct v2f 
			{
				float4 pos : SV_POSITION;
				float3 worldNormal : TEXCOORD0;
				float3 worldPos : TEXCOORD1;
				float2 uv : TEXCOORD2;
			};

			// 求法线/顶点位置的世界空间坐标，纹理坐标做缩放平移后传给片段着色器
			v2f vert(a2v v) 
			{
				v2f o;
				o.pos = UnityObjectToClipPos(v.vertex);

				o.worldNormal = UnityObjectToWorldNormal(v.normal);

				o.worldPos = mul(unity_ObjectToWorld, v.vertex).xyz;

				o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);

				return o;
			}

			
			fixed4 frag(v2f i) : SV_Target
			{
				// 归一化法线和光源（世界空间）
				fixed3 worldNormal = normalize(i.worldNormal);
				fixed3 worldLightDir = normalize(UnityWorldSpaceLightDir(i.worldPos));

				// 纹理采样
				fixed4 texColor = tex2D(_MainTex, i.uv);

				// 透明度测试
				// Alpha test
				clip(texColor.a - _Cutoff);
				// Equal to 
			//  if ((texColor.a - _Cutoff) < 0.0) 
			//	{
			//      discard;	// CG提供的指令，在FragmentShader中表示立即放弃当前处理的片元
			//  }

				fixed3 albedo = texColor.rgb * _Color.rgb;

				fixed3 ambient = UNITY_LIGHTMODEL_AMBIENT.xyz * albedo;

				fixed3 diffuse = _LightColor0.rgb * albedo * max(0, dot(worldNormal, worldLightDir));

				return fixed4(ambient + diffuse, 1.0);
			}
            ENDCG
		}
    }
	Fallback "Transparent/Cutout/VertexLit"
}
