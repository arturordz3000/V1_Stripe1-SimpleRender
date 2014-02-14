#include "../Game.h"

void CStateMainGame::OnLoad()
{
	this->InitializeResources();

	CActorTexturedCube *cCube = new CActorTexturedCube();
	ActorMgr->LoadActor(cCube);
}

CStateMainGame::CStateMainGame() : CState()
{
	this->OnLoad();
}

CStateMainGame::~CStateMainGame()
{

}

void CStateMainGame::DoFrame()
{	
	ActorMgr->UpdateActors();
	ActorMgr->DrawActors();	
	Input->ResetKeyboard();
}

void CStateMainGame::InitializeResources()
{
	CResources *pTexturedCubeResources = new CResources();
	CResourcesBuilder<TexturedVertex, WORD, MatrixBuffer> *pTexturedCubeResourcesBuilder = new CResourcesBuilder<TexturedVertex, WORD, MatrixBuffer>();

	// Define cómo entrarán
	// los datos al shader
	D3D11_INPUT_ELEMENT_DESC a_d3dLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		//El 12 de aquí indica el número de bytes que hay entre
		//el comienzo del buffer y los datos a los que se hace
		//la referencia. Por ejemplo, hay un Vector de 3 elementos
		//de tipo flotante. Los float son de 4 bytes, entonces 4x3=12
		//y es por eso que se pone aquí un 12, que es donde comienza
		//el vector de color.
		{ "TEXTCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// Create vertex buffer
	TexturedVertex a_sVertices[] =
	{
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f )},
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
			
		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f )},
	};

	// Creamos buffer de indices usando el mismo
	//descriptor
	WORD a_wIndices[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	pTexturedCubeResourcesBuilder->AddVertexShaderResource(L"TextureShader.fx", "VS", "vs_4_0", a_d3dLayout, ARRAYSIZE(a_d3dLayout));
	pTexturedCubeResourcesBuilder->AddPixelShaderResource(L"TextureShader.fx", "PS", "ps_4_0");
	pTexturedCubeResourcesBuilder->AddVertexBuffer(a_sVertices, sizeof(TexturedVertex) * ARRAYSIZE(a_sVertices));
	pTexturedCubeResourcesBuilder->AddIndexBuffer(a_wIndices, sizeof(WORD) * ARRAYSIZE(a_wIndices));
	pTexturedCubeResourcesBuilder->AddConstantBuffer(sizeof(MatrixBuffer));
	pTexturedCubeResourcesBuilder->AddTexture(L"Textures\\p.gif");
	pTexturedCubeResourcesBuilder->AddSampler(D3D11_FILTER_MIN_MAG_MIP_LINEAR, 
		D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, 0, D3D11_FLOAT32_MAX);
	pTexturedCubeResourcesBuilder->Build(pTexturedCubeResources);

	ResourceMgr->AddResources(pTexturedCubeResources, this->uiTexturedCubeResourcesId);
}