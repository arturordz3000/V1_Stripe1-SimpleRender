#include "../Game.h"

void InitializeTexturedCubeResources(unsigned int &uiOutputId);
void InitializeBumpedCubeResources(unsigned int &uiOutputId);
void InitializeTerrainResources(unsigned int &uiOutputId);

int indexCount = 0;
TerrainVertex *terrainVertices;
int deltaX, deltaY, verticesQty;

void CStateMainGame::OnLoad()
{
	this->InitializeResources();

	/*CActorTexturedCube *cCube = new CActorTexturedCube();
	cCube->SetResourcesId(this->uiTexturedCubeResourcesId);
	ActorMgr->LoadActor(cCube);*/

	CActorTerrain *cTerrain = new CActorTerrain();
	cTerrain->iIndexCount = indexCount;
	cTerrain->SetResourcesId(this->uiTerrainResourcesId);
	ActorMgr->LoadActor(cTerrain);

	/*CActorBumpedCube *cCube = new CActorBumpedCube();
	cCube->SetResourcesId(this->uiBumpedCubeResourcesId);
	ActorMgr->LoadActor(cCube);*/
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
	Camera->Update();

	XMVECTOR cameraPosition = Camera->GetPosition();
	int vx = (int) ((cameraPosition.x + 256) / deltaX);
	int vy = (int) ((cameraPosition.z + 256) / deltaY) * ((512));
	int vertexIndex = (int)( vx + vy );
		
	if(vx > 0 && vx <= 512)
	{
		if(vertexIndex < verticesQty && vertexIndex >= 0)
		{
			float height = terrainVertices[vertexIndex].pos.y;
			Camera->SetPositionY(height + 3);
		}
	}

	ActorMgr->UpdateActors();
	ActorMgr->DrawActors();	
	Input->ResetKeyboard();
}

void CStateMainGame::InitializeResources()
{
	//InitializeTexturedCubeResources(this->uiTexturedCubeResourcesId);
	InitializeTerrainResources(this->uiTerrainResourcesId);
	//InitializeBumpedCubeResources(this->uiBumpedCubeResourcesId);
}

void InitializeTexturedCubeResources(unsigned int &uiOutputId)
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

	ResourceMgr->AddResources(pTexturedCubeResources, uiOutputId);
}

void InitializeTerrainResources(unsigned int &uiOutputId)
{
	CResources *pTerrainResources = new CResources();
	CResourcesBuilder<TerrainVertex, UINT, TerrainConstantBuffer> *pTexturedCubeResourcesBuilder = new CResourcesBuilder<TerrainVertex, UINT, TerrainConstantBuffer>();

	D3D11_INPUT_ELEMENT_DESC terrainLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	int ancho = 512, alto = 512;
	int anchoTexTerr = 0, altoTexTerr = 0;
	float anchof = 0, altof = 0;
	//float deltax = 0, deltay = 0;
	float tile = 10;
	UINT* indices = NULL;
	TerrainVertex* vertices = NULL;
	BYTE** alturaData = NULL;
	ID3D11Resource* heightMap = NULL;

	HRESULT resultado;
	D3DX11_IMAGE_INFO texInfo;
	resultado = D3DX11GetImageInfoFromFile(L"Textures\\GrandCanyon.png", NULL, &texInfo, NULL);

	D3DX11_IMAGE_LOAD_INFO texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.CpuAccessFlags = D3D11_CPU_ACCESS_READ;
	texDesc.Usage = D3D11_USAGE_STAGING;
	texDesc.pSrcInfo = &texInfo;
	texDesc.Height = texInfo.Height;
	texDesc.Width = texInfo.Width;
	texDesc.Depth = texInfo.Depth;
	texDesc.Format = texInfo.Format;
	texDesc.Filter = D3DX11_FILTER_LINEAR;
	texDesc.MipLevels = texInfo.MipLevels;

	anchoTexTerr = (int)texInfo.Width;
	altoTexTerr = (int)texInfo.Height;
	alturaData = new BYTE*[altoTexTerr];
	for( int i = 0 ; i < anchoTexTerr ; i++ )
		alturaData[i] = new BYTE[anchoTexTerr];

	resultado = D3DX11CreateTextureFromFile(Graphics->GetDevice(), L"Textures\\GrandCanyon.png", &texDesc, NULL, &heightMap, NULL);

	D3D11_MAPPED_SUBRESOURCE subResrc;
	resultado = Graphics->GetDeviceContext()->Map(heightMap, 0, D3D11_MAP_READ, NULL, &subResrc);
	BYTE *pixel = reinterpret_cast<BYTE*>(subResrc.pData);

	for(UINT x = 0; x < altoTexTerr; x++)
	{
		for(UINT y=0; y<anchoTexTerr; y++)
		{
			BYTE pPixel = pixel[(x * anchoTexTerr + y)*4];
			alturaData[x][y] = pPixel/5;
		}
	}
		
	Graphics->GetDeviceContext()->Unmap(heightMap, 0);

	anchof = (float)(ancho / 2.0f);
	altof = (float)(alto / 2.0f);
	float du = tile / (float)(anchoTexTerr);
	float dv = tile / (float)(altoTexTerr);
	float blend_du = 1 / (float)(anchoTexTerr);
	float blend_dv = 1 / (float)(altoTexTerr);
	int cuentaVertex = anchoTexTerr * altoTexTerr;
	vertices = new TerrainVertex[cuentaVertex];

	// Se obtiene el espaciado entre cada vertice
	float deltaAlto = alto / altoTexTerr;
	float deltaAncho = ancho / anchoTexTerr;

	deltaX = deltaAlto;
	deltaY = deltaAncho;
	verticesQty = cuentaVertex;

	for(int x = 0; x < altoTexTerr; x++)
	{
		for (int y = 0; y < anchoTexTerr; y++)
		{
			int indiceArreglo = x * anchoTexTerr + y;

			// Se calculan los vertices 'x' y 'z'. 'Y' se saca del mapa de normales
			vertices[indiceArreglo].pos.x = deltaAncho * y - anchof;
			vertices[indiceArreglo].pos.y = alturaData[x][y];
			vertices[indiceArreglo].pos.z = deltaAlto * x - altof;
			vertices[indiceArreglo].uv.x = y * du;
			vertices[indiceArreglo].uv.y = x * dv;
			vertices[indiceArreglo].blendUV.x = y * blend_du;
			vertices[indiceArreglo].blendUV.y = x * blend_dv;
			vertices[indiceArreglo].normal = XMFLOAT3(0.0f , 0.0f , 0.0f);
		}
	}

	terrainVertices = vertices;

	for(int i=0; i<altoTexTerr-1;i++)
		{
			for(int j=0;j<anchoTexTerr-1;j++)
			{
				int bottomleft = i * anchoTexTerr + j;
				int topright = (i + 1) * anchoTexTerr + (j + 1);
				int topleft = (i + 1) * anchoTexTerr + j;
				int bottomright = i * anchoTexTerr + (j + 1);

				// Se obtiene la normal del primer triangulo
				XMVECTOR v1 = XMLoadFloat3(&vertices[topleft].pos) - XMLoadFloat3(&vertices[bottomleft].pos);
				XMVECTOR v2 = XMLoadFloat3(&vertices[bottomright].pos) - XMLoadFloat3(&vertices[bottomleft].pos);
				XMVECTOR T1 = XMVector3Cross(v1, v2);
				XMFLOAT3 sumNor;
				XMStoreFloat3(&sumNor, T1);
				vertices[bottomleft].normal = XMFLOAT3(vertices[bottomleft].normal.x + sumNor.x,
													   vertices[bottomleft].normal.y + sumNor.y,
													   vertices[bottomleft].normal.z + sumNor.z);
				vertices[topleft].normal = XMFLOAT3(vertices[topleft].normal.x + sumNor.x,
													vertices[topleft].normal.y + sumNor.y,
													vertices[topleft].normal.z + sumNor.z);
				vertices[bottomright].normal = XMFLOAT3(vertices[bottomright].normal.x + sumNor.x,
													    vertices[bottomright].normal.y + sumNor.y,
													    vertices[bottomright].normal.z + sumNor.z);

				v1 = XMLoadFloat3(&vertices[topleft].pos) - XMLoadFloat3(&vertices[bottomright].pos);
				v2 = XMLoadFloat3(&vertices[topright].pos) - XMLoadFloat3(&vertices[bottomright].pos);
				T1 = XMVector3Cross(v1, v2);
				XMStoreFloat3(&sumNor, T1);

				vertices[topright].normal = XMFLOAT3(vertices[topright].normal.x + sumNor.x,
													 vertices[topright].normal.y + sumNor.y,
													 vertices[topright].normal.z + sumNor.z);
				vertices[topleft].normal = XMFLOAT3(vertices[topleft].normal.x + sumNor.x,
													vertices[topleft].normal.y + sumNor.y,
													vertices[topleft].normal.z + sumNor.z);
				vertices[bottomright].normal = XMFLOAT3(vertices[bottomright].normal.x + sumNor.x,
													    vertices[bottomright].normal.y + sumNor.y,
													    vertices[bottomright].normal.z + sumNor.z);
			}
		}
		for(int i=0; i < anchoTexTerr * altoTexTerr; i++)
		{
			XMVECTOR normal = XMLoadFloat3(&vertices[i].normal);
			normal = XMVector3Normalize(normal);
			XMStoreFloat3(&vertices[i].normal, normal);
		}

	int cuentaIndex = (anchoTexTerr - 1) * (altoTexTerr - 1) * 6;
	indexCount = cuentaIndex;
	indices = new UINT[cuentaIndex];

	int counter = 0;
	for(int y = 0; y < altoTexTerr-1; y++)
	{
		for(int x=0; x < anchoTexTerr-1; x++)
		{
			int lowerLeft = y * anchoTexTerr + x;
			int lowerRight = y * anchoTexTerr + (x + 1);
			int topLeft = (y + 1) * anchoTexTerr + x;
			int topRight = (y + 1) * anchoTexTerr + (x + 1);

			indices[counter++] = lowerLeft;
			indices[counter++] = topLeft;
			indices[counter++] = lowerRight;

			indices[counter++] = lowerRight; 
			indices[counter++] = topLeft;
			indices[counter++] = topRight;
		}
	}

	pTexturedCubeResourcesBuilder->AddVertexShaderResource(L"TerrainShader.fx", "VS", "vs_4_0", terrainLayout, ARRAYSIZE(terrainLayout));
	pTexturedCubeResourcesBuilder->AddPixelShaderResource(L"TerrainShader.fx", "PS", "ps_4_0");
	pTexturedCubeResourcesBuilder->AddVertexBuffer(vertices, sizeof(TerrainVertex) * cuentaVertex);
	pTexturedCubeResourcesBuilder->AddIndexBuffer(indices, sizeof(UINT) * cuentaIndex);
	pTexturedCubeResourcesBuilder->AddConstantBuffer(sizeof(TerrainConstantBuffer));
	pTexturedCubeResourcesBuilder->AddTexture(L"Textures\\grass.jpg");
	pTexturedCubeResourcesBuilder->AddSampler(D3D11_FILTER_MIN_MAG_MIP_LINEAR, 
		D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, 0, D3D11_FLOAT32_MAX);
	pTexturedCubeResourcesBuilder->Build(pTerrainResources);

	ResourceMgr->AddResources(pTerrainResources, uiOutputId);
}

void InitializeBumpedCubeResources(unsigned int &uiOutputId)
{
	CResources *pTexturedCubeResources = new CResources();
	CResourcesBuilder<BumpedVertex, WORD, BumpedBuffer> *pTexturedCubeResourcesBuilder = new CResourcesBuilder<BumpedVertex, WORD, BumpedBuffer>();

	// Define cómo entrarán
	// los datos al shader
	D3D11_INPUT_ELEMENT_DESC a_d3dLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// Create vertex buffer
	BumpedVertex a_sVertices[] =
	{
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 0.0f, 1.0f, 0.0f ) },

		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },
		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 0.0f, -1.0f, 0.0f ) },

		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( -1.0f, 0.0f, 0.0f ) },

		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 1.0f, 0.0f, 0.0f ) },
			
		{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, -1.0f ) },

		{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
		{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ), XMFLOAT3( 0.0f, 0.0f, 1.0f ) },
	};

	int vertexCounter = 0;
	BumpedVertex *vertexPtr = a_sVertices;

	for(int i = 0; i < ARRAYSIZE(a_sVertices); i++)
	{
		if(vertexCounter < 3)
		{
			XMVECTOR v1 = XMLoadFloat3(&vertexPtr->pos);
			XMVECTOR v2 = XMLoadFloat3(&(vertexPtr + 1)->pos);

			XMStoreFloat3(&vertexPtr->tangent, XMVector3Normalize(v2 - v1));

			vertexCounter++;
		}
		else
		{
			XMVECTOR v1 = XMLoadFloat3(&vertexPtr->pos);
			XMVECTOR v2 = XMLoadFloat3(&(vertexPtr - 1)->pos);

			XMStoreFloat3(&vertexPtr->tangent, XMVector3Normalize(v1 - v2));

			vertexCounter = 0;
		}

		vertexPtr++;
	}

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

	pTexturedCubeResourcesBuilder->AddVertexShaderResource(L"BumpedShader.fx", "VS", "vs_4_0", a_d3dLayout, ARRAYSIZE(a_d3dLayout));
	pTexturedCubeResourcesBuilder->AddPixelShaderResource(L"BumpedShader.fx", "PS", "ps_4_0");
	pTexturedCubeResourcesBuilder->AddVertexBuffer(a_sVertices, sizeof(BumpedVertex) * ARRAYSIZE(a_sVertices));
	pTexturedCubeResourcesBuilder->AddIndexBuffer(a_wIndices, sizeof(WORD) * ARRAYSIZE(a_wIndices));
	pTexturedCubeResourcesBuilder->AddConstantBuffer(sizeof(BumpedBuffer));
	pTexturedCubeResourcesBuilder->AddTexture(L"Textures\\p.gif");
	pTexturedCubeResourcesBuilder->AddSampler(D3D11_FILTER_MIN_MAG_MIP_LINEAR, 
		D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, 0, D3D11_FLOAT32_MAX);
	pTexturedCubeResourcesBuilder->Build(pTexturedCubeResources);

	ResourceMgr->AddResources(pTexturedCubeResources, uiOutputId);
}