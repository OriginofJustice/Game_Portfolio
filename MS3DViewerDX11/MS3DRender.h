#pragma once

#include <fstream>
#include "Util//euMath.h"
#include "RenderType.h"
#include "VertexType.h"
#include "Abstract/ITexture.h"

#include <vector>

#include <d3d11.h>
#include <d3dx11effect.h>

namespace BWSG
{

	typedef float vec3_t[3];	// x,y,z
	struct MS3DHeader
	{
		char			id[10];							// always "MS3D000000"
		unsigned int	version;						// 3
	};

	struct MS3DVertex
	{
		unsigned char	flags;                                      // SELECTED | SELECTED2 | HIDDEN
		float			vertex[3];                                  //
		char			boneId;                                     // -1 = no bone
		unsigned char	referenceCount;
		float			boneIds[3];
		unsigned char	weights[3];
		unsigned int	extra;
		float renderColor[3];
	};

	struct MS3DTriangle
	{
		unsigned short	flags;                                      // SELECTED | SELECTED2 | HIDDEN
		unsigned short	vertexIndices[3];                           //
		float			vertexNormals[3][3];                        //
		float			s[3];                                       //
		float			t[3];                                       //
		unsigned char	smoothingGroup;                             // 1 - 32
		unsigned char	groupIndex;                                 //
	};

	struct MS3DGroup
	{
		unsigned char	flags;                              // SELECTED | HIDDEN
		char            name[32];                           //
		unsigned short	numtriangles;                       //
		unsigned short  *triangleIndices;				// the groups group the triangles
		char            materialIndex;                      // -1 = no material

		// Ãß°¡
		int numVertices;	
		BWSG::euVertexPNTTIW * vertices;
		BWSG::euVertexPNTTIW * OriginalVertices;


		ID3D11Buffer		*		m_pVB;

		MS3DGroup()
			: m_pVB(nullptr)
		{

		}
		~MS3DGroup()
		{
			RELEASECOM( m_pVB );
		}
	};

	struct MS3DMaterial
	{
		char            name[32];                           //
		float           ambient[4];                         //
		float           diffuse[4];                         //
		float           specular[4];                        //
		float           emissive[4];                        //
		float           shininess;                          // 0.0f - 128.0f
		float           transparency;                       // 0.0f - 1.0f
		char            mode;                               // 0, 1, 2 is unused now
		char            texture[128];                       // texture.bmp
		char            alphamap[128];                      // alpha.bmp

		ITexture	*	pTexture;

		MS3DMaterial()
			:pTexture(nullptr)
		{

		}
		~MS3DMaterial()
		{
			SAFE_DELETE( pTexture );
		}
	};

	struct MS3DKeyframeRotation
	{
		float           time;                               // time in seconds
		float           rotation[3];                        // x, y, z angles
	};

	struct MS3DKeyframePosition
	{
		float           time;                               // time in seconds
		float           position[3];                        // local position
	};

	struct MS3DTangent
	{
		float tangentIn[3];
		float tangentOut[3];
	};

	struct MS3DKeyframeJoint
	{
		unsigned char	flags;                              // SELECTED | DIRTY
		char            name[32];                           //
		char            parentName[32];                     //
		float           rot[3];                        // local reference matrix
		float           pos[3];
		unsigned short  numKeyFramesRot;                    //
		unsigned short	numKeyFramesTrans;                  //
		MS3DKeyframeRotation *keyFramesRot;
		MS3DKeyframePosition *keyFramesTrans;
		MS3DTangent	*		keyTangent;
		float			color[3];
		//for render

		float matLocalSkeleton[3][4];
		float matGlobalSkeleton[3][4];

		float matLocal[3][4];
		float matGlobal[3][4];

		int parentIndex;

	};

	//structura de joint si weight
	struct MS3DJointAndWeight {
		BWSB::euIntVector4   jointIndices;
		BWSB::euIntVector4  jointWeights;

	};


	class CMS3DRender
	{
	public:
		CMS3DRender(void);
		~CMS3DRender(void);

		bool CreateShaderFX		( ID3D11Device* pDevice, cchar_t * szFileName , cchar_t * szTechName , cchar_t * szVersion , ShaderMacro * pMacro );
		void InitShader( ID3D11Device* pDevice);
		void LoadMS3D( ID3D11Device* pDevice , ID3D11DeviceContext* pContext, const char * szName );
		void Update();
		void Render( ID3D11DeviceContext* pContext);
		void Destroy();

	private:
		void RebulidVertex(ID3D11Device* pDevice , ID3D11DeviceContext* pContext);
		void SetupJoints();
		void SetupTangents();
		int  FindJointByName(const char * name);

		void RebuildJoints();
		void RebuildJoint(MS3DKeyframeJoint *joint);


	public:public:

		char *	GetFileName()				{return szFileName; }
		float	GetCurrentFrame()			{return timer;}
		int		GetTotalFrame()				{return m_TotalFrames;}
		int		GetTotalVerTexCount()		{return m_NumOfVertices;}
		int		GetTotalGroupsCount()		{return m_NumOfGroups;}
		int		GetTotalTrianglesCount()	{return m_NumOfTriangles;}
		int		GetTotalMaterialCount()		{return m_NumOfMaterials;}
		int		GetTotalJointCount()		{return m_NumOfJoint;}
	protected:
		unsigned int			m_NumOfVertices;
		unsigned int			m_NumOfGroups;
		unsigned int			m_NumOfTriangles;
		unsigned int			m_NumOfMaterials;
		unsigned short			m_NumOfJoint;

		float					m_AnimationFps;
		float					m_CurrentTime;
		int						m_TotalFrames;

		

		char					szFileName[256];

		MS3DVertex			*	m_pMS3DVertices ;
		MS3DTriangle		*	m_pMS3DTriangles ;
		MS3DGroup			*	m_pMS3DGroups;
		MS3DMaterial		*	m_pMS3DMaterials ;
		MS3DKeyframeJoint	*	m_pMS3DJoint ;

		bool playani;
		float timer;

		/////////////////////////////////////////////////////////////////
		ID3DX11Effect	*			m_pEffect;
		ID3DX11EffectTechnique *	m_pTech;

		ID3D11InputLayout	*		m_pInputLayout;




	};
}

