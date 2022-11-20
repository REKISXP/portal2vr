#pragma once

#include "texture.h"

enum MaterialRenderTargetDepth_t
{
	MATERIAL_RT_DEPTH_SHARED = 0x0,
	MATERIAL_RT_DEPTH_SEPARATE = 0x1,
	MATERIAL_RT_DEPTH_NONE = 0x2,
	MATERIAL_RT_DEPTH_ONLY = 0x3,
};

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30)
};


enum CompiledVtfFlags
{
	// flags from the *.txt config file
	TEXTUREFLAGS_POINTSAMPLE = 0x00000001,
	TEXTUREFLAGS_TRILINEAR = 0x00000002,
	TEXTUREFLAGS_CLAMPS = 0x00000004,
	TEXTUREFLAGS_CLAMPT = 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC = 0x00000010,
	TEXTUREFLAGS_HINT_DXT5 = 0x00000020,
	TEXTUREFLAGS_SRGB = 0x00000040,
	TEXTUREFLAGS_NORMAL = 0x00000080,
	TEXTUREFLAGS_NOMIP = 0x00000100,
	TEXTUREFLAGS_NOLOD = 0x00000200,
	TEXTUREFLAGS_ALL_MIPS = 0x00000400,
	TEXTUREFLAGS_PROCEDURAL = 0x00000800,

	// These are automatically generated by vtex from the texture data.
	TEXTUREFLAGS_ONEBITALPHA = 0x00001000,
	TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000,

	// newer flags from the *.txt config file
	TEXTUREFLAGS_ENVMAP = 0x00004000,
	TEXTUREFLAGS_RENDERTARGET = 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000,
	TEXTUREFLAGS_SINGLECOPY = 0x00040000,

	TEXTUREFLAGS_STAGING_MEMORY = 0x00080000,
	TEXTUREFLAGS_IMMEDIATE_CLEANUP = 0x00100000,
	TEXTUREFLAGS_IGNORE_PICMIP = 0x00200000,
	TEXTUREFLAGS_UNUSED_00400000 = 0x00400000,

	TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000,

	TEXTUREFLAGS_UNUSED_01000000 = 0x01000000,

	TEXTUREFLAGS_CLAMPU = 0x02000000,

	TEXTUREFLAGS_VERTEXTEXTURE = 0x04000000,					// Useable as a vertex texture

	TEXTUREFLAGS_SSBUMP = 0x08000000,

	TEXTUREFLAGS_UNUSED_10000000 = 0x10000000,

	// Clamp to border color on all texture coordinates
	TEXTUREFLAGS_BORDER = 0x20000000,

	TEXTUREFLAGS_UNUSED_40000000 = 0x40000000,
	TEXTUREFLAGS_UNUSED_80000000 = 0x80000000,
};

enum RenderTargetSizeMode_t
{
	RT_SIZE_NO_CHANGE = 0,			// Only allowed for render targets that don't want a depth buffer
	// (because if they have a depth buffer, the render target must be less than or equal to the size of the framebuffer).
	RT_SIZE_DEFAULT = 1,				// Don't play with the specified width and height other than making sure it fits in the framebuffer.
	RT_SIZE_PICMIP = 2,				// Apply picmip to the render target's width and height.
	RT_SIZE_HDR = 3,					// frame_buffer_width / 4
	RT_SIZE_FULL_FRAME_BUFFER = 4,	// Same size as frame buffer, or next lower power of 2 if we can't do that.
	RT_SIZE_OFFSCREEN = 5,			// Target of specified size, don't mess with dimensions
	RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6, // Same size as the frame buffer, rounded up if necessary for systems that can't do non-power of two textures.
	RT_SIZE_REPLAY_SCREENSHOT = 7,	// Rounded down to power of 2, essentially...
	RT_SIZE_LITERAL = 8,			// Use the size passed in. Don't clamp it to the frame buffer size. Really.
	RT_SIZE_LITERAL_PICMIP = 9		// Use the size passed in, don't clamp to the frame buffer size, but do apply picmip restrictions.

};

enum PaintMode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2), // software cursor, if appropriate
};

class IMatRenderContext;
class IMaterial;

class IMaterialSystem
{
public:
	virtual void ConnectEPFPvPKcPiE() = 0; //CMaterialSystem::Connect(void * (*)(char const*,int *))
	virtual void DisconnectEv() = 0; //CMaterialSystem::Disconnect(void)
	virtual void QueryInterfaceEPKc() = 0; //CMaterialSystem::QueryInterface(char const*)
	virtual void InitEv() = 0; //CMaterialSystem::Init(void)
	virtual void ShutdownEv() = 0; //CMaterialSystem::Shutdown(void)
	virtual void InitEPKcP21IMaterialProxyFactoryPFPvS1_PiES7_() = 0; //CMaterialSystem::Init(char const*,IMaterialProxyFactory *,void * (*)(char const*,int *),void * (*)(char const*,int *))
	virtual void SetShaderAPIEPKc() = 0; //CMaterialSystem::SetShaderAPI(char const*)
	virtual void SetAdapterEii() = 0; //CMaterialSystem::SetAdapter(int,int)
	virtual void ModInitEv() = 0; //CMaterialSystem::ModInit(void)
	virtual void ModShutdownEv() = 0; //CMaterialSystem::ModShutdown(void)
	virtual void SetThreadModeE20MaterialThreadMode_ti() = 0; //CMaterialSystem::SetThreadMode(MaterialThreadMode_t,int)
	virtual void GetThreadModeEv() = 0; //CMaterialSystem::GetThreadMode(void)
	virtual void IsRenderThreadSafeEv() = 0; //CMaterialSystem::IsRenderThreadSafe(void)
	virtual void ExecuteQueuedEv() = 0; //CMaterialSystem::ExecuteQueued(void)
	virtual void GetHardwareConfigEPKcPi() = 0; //CMaterialSystem::GetHardwareConfig(char const*,int *)
	virtual void UpdateConfigEb() = 0; //CMaterialSystem::UpdateConfig(bool)
	virtual void OverrideConfigERK23MaterialSystem_Config_tb() = 0; //CMaterialSystem::OverrideConfig(MaterialSystem_Config_t const&,bool)
	virtual void GetCurrentConfigForVideoCardEv() = 0; //CMaterialSystem::GetCurrentConfigForVideoCard(void)
	virtual void GetRecommendedConfigurationInfoEiP9KeyValues() = 0; //CMaterialSystem::GetRecommendedConfigurationInfo(int,KeyValues *)
	virtual void GetDisplayAdapterCountEv() = 0; //CMaterialSystem::GetDisplayAdapterCount(void)
	virtual void GetCurrentAdapterEv() = 0; //CMaterialSystem::GetCurrentAdapter(void)
	virtual void GetDisplayAdapterInfoEiR21MaterialAdapterInfo_t() = 0; //CMaterialSystem::GetDisplayAdapterInfo(int,MaterialAdapterInfo_t &)
	virtual void GetModeCountEi() = 0; //CMaterialSystem::GetModeCount(int)
	virtual void GetModeInfoEiiR19MaterialVideoMode_t() = 0; //CMaterialSystem::GetModeInfo(int,int,MaterialVideoMode_t &)
	virtual void AddModeChangeCallBackEPFvvE() = 0; //CMaterialSystem::AddModeChangeCallBack(void (*)(void))
	virtual void GetDisplayModeER19MaterialVideoMode_t() = 0; //CMaterialSystem::GetDisplayMode(MaterialVideoMode_t &)
	virtual void SetModeEPvRK23MaterialSystem_Config_t() = 0; //CMaterialSystem::SetMode(void *,MaterialSystem_Config_t const&)
	virtual void SupportsMSAAModeEi() = 0; //CMaterialSystem::SupportsMSAAMode(int)
	virtual void GetVideoCardIdentifierEv() = 0; //CMaterialSystem::GetVideoCardIdentifier(void)
	virtual void SpewDriverInfoEv() = 0; //CMaterialSystem::SpewDriverInfo(void)
	virtual void GetBackBufferDimensions(int &, int &) = 0; //CMaterialSystem::GetBackBufferDimensions(int &,int &)
	virtual ImageFormat GetBackBufferFormat() = 0; //CMaterialSystem::GetBackBufferFormat(void)
	virtual void SupportsHDRModeE9HDRType_t() = 0; //CMaterialSystem::SupportsHDRMode(HDRType_t)
	virtual void AddViewEPv() = 0; //CMaterialSystem::AddView(void *)
	virtual void RemoveViewEPv() = 0; //CMaterialSystem::RemoveView(void *)
	virtual void SetViewEPv() = 0; //CMaterialSystem::SetView(void *)
	virtual void BeginFrameEf() = 0; //CMaterialSystem::BeginFrame(float)
	virtual void EndFrameEv() = 0; //CMaterialSystem::EndFrame(void)
	virtual void FlushEb() = 0; //CMaterialSystem::Flush(bool)
	virtual void SwapBuffersEv() = 0; //CMaterialSystem::SwapBuffers(void)
	virtual void EvictManagedResourcesEv() = 0; //CMaterialSystem::EvictManagedResources(void)
	virtual void ReleaseResourcesEv() = 0; //CMaterialSystem::ReleaseResources(void)
	virtual void ReacquireResourcesEv() = 0; //CMaterialSystem::ReacquireResources(void)
	virtual void AddReleaseFuncEPFviE() = 0; //CMaterialSystem::AddReleaseFunc(void (*)(int))
	virtual void RemoveReleaseFuncEPFviE() = 0; //CMaterialSystem::RemoveReleaseFunc(void (*)(int))
	virtual void AddRestoreFuncEPFviE() = 0; //CMaterialSystem::AddRestoreFunc(void (*)(int))
	virtual void RemoveRestoreFuncEPFviE() = 0; //CMaterialSystem::RemoveRestoreFunc(void (*)(int))
	virtual void ResetTempHWMemoryEb() = 0; //CMaterialSystem::ResetTempHWMemory(bool)
	virtual void HandleDeviceLostEv() = 0; //CMaterialSystem::HandleDeviceLost(void)
	virtual void ShaderCountEv() = 0; //CMaterialSystem::ShaderCount(void)
	virtual void GetShadersEiiPP7IShader() = 0; //CMaterialSystem::GetShaders(int,int,IShader **)
	virtual void ShaderFlagCountEv() = 0; //CMaterialSystem::ShaderFlagCount(void)
	virtual void ShaderFlagNameEi() = 0; //CMaterialSystem::ShaderFlagName(int)
	virtual void GetShaderFallbackEPKcPci() = 0; //CMaterialSystem::GetShaderFallback(char const*,char *,int)
	virtual void GetMaterialProxyFactoryEv() = 0; //CMaterialSystem::GetMaterialProxyFactory(void)
	virtual void SetMaterialProxyFactoryEP21IMaterialProxyFactory() = 0; //CMaterialSystem::SetMaterialProxyFactory(IMaterialProxyFactory *)
	virtual void EnableEditorMaterialsEv() = 0; //CMaterialSystem::EnableEditorMaterials(void)
	virtual void EnableGBuffersEv() = 0; //CMaterialSystem::EnableGBuffers(void)
	virtual void SetInStubModeEb() = 0; //CMaterialSystem::SetInStubMode(bool)
	virtual void DebugPrintUsedMaterialsEPKcb() = 0; //CMaterialSystem::DebugPrintUsedMaterials(char const*,bool)
	virtual void DebugPrintUsedTexturesEv() = 0; //CMaterialSystem::DebugPrintUsedTextures(void)
	virtual void ToggleSuppressMaterialEPKc() = 0; //CMaterialSystem::ToggleSuppressMaterial(char const*)
	virtual void ToggleDebugMaterialEPKc() = 0; //CMaterialSystem::ToggleDebugMaterial(char const*)
	virtual void UsingFastClippingEv() = 0; //CMaterialSystem::UsingFastClipping(void)
	virtual void StencilBufferBitsEv() = 0; //CMaterialSystem::StencilBufferBits(void)
	virtual void UncacheAllMaterialsEv() = 0; //CMaterialSystem::UncacheAllMaterials(void)
	virtual void UncacheUnusedMaterialsEb() = 0; //CMaterialSystem::UncacheUnusedMaterials(bool)
	virtual void CacheUsedMaterialsEv() = 0; //CMaterialSystem::CacheUsedMaterials(void)
	virtual void ReloadTexturesEv() = 0; //CMaterialSystem::ReloadTextures(void)
	virtual void ReloadMaterialsEPKc() = 0; //CMaterialSystem::ReloadMaterials(char const*)
	virtual void CreateMaterialEPKcP9KeyValues() = 0; //CMaterialSystem::CreateMaterial(char const*,KeyValues *)
	virtual IMaterial *FindMaterial(char const *pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL) = 0; //CMaterialSystem::FindMaterial(char const*,char const*,bool,char const*)
	virtual void FirstMaterialEv() = 0; //CMaterialSystem::FirstMaterial(void)
	virtual void NextMaterialEt() = 0; //CMaterialSystem::NextMaterial(ushort)
	virtual void InvalidMaterialEv() = 0; //CMaterialSystem::InvalidMaterial(void)
	virtual void GetMaterialEt() = 0; //CMaterialSystem::GetMaterial(ushort)
	virtual void GetNumMaterialsEv() = 0; //CMaterialSystem::GetNumMaterials(void)
	virtual void FindTextureEPKcS1_bi() = 0; //CMaterialSystem::FindTexture(char const*,char const*,bool,int)
	virtual void IsTextureLoadedEPKc() = 0; //CMaterialSystem::IsTextureLoaded(char const*)
	virtual void CreateProceduralTextureEPKcS1_ii11ImageFormati() = 0; //CMaterialSystem::CreateProceduralTexture(char const*,char const*,int,int,ImageFormat,int)
	virtual void BeginRenderTargetAllocation() = 0; //CMaterialSystem::BeginRenderTargetAllocation(void)
	virtual void EndRenderTargetAllocation() = 0; //CMaterialSystem::EndRenderTargetAllocation(void)
	virtual void *CreateRenderTargetTexture(int, int, RenderTargetSizeMode_t, ImageFormat, MaterialRenderTargetDepth_t) = 0; //CMaterialSystem::CreateRenderTargetTexture(int,int,RenderTargetSizeMode_t,ImageFormat,MaterialRenderTargetDepth_t)
	virtual ITexture *CreateNamedRenderTargetTextureEx(const char *pRTName,				// Pass in NULL here for an unnamed render target.
														int w,
														int h,
														RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
														ImageFormat format,
														MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
														unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
														unsigned int renderTargetFlags = 0) = 0; //CMaterialSystem::CreateNamedRenderTargetTextureEx(char const*,int,int,RenderTargetSizeMode_t,ImageFormat,MaterialRenderTargetDepth_t,uint,uint)
	virtual void *CreateNamedRenderTargetTexture(char const *, int, int, RenderTargetSizeMode_t, ImageFormat, MaterialRenderTargetDepth_t, bool, bool) = 0; //CMaterialSystem::CreateNamedRenderTargetTexture(char const*,int,int,RenderTargetSizeMode_t,ImageFormat,MaterialRenderTargetDepth_t,bool,bool)
	virtual ITexture *CreateNamedRenderTargetTextureEx2(const char *pRTName,				// Pass in NULL here for an unnamed render target.
														int w,
														int h,
														RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
														ImageFormat format,
														MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
														unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
														unsigned int renderTargetFlags = 0) = 0; //CMaterialSystem::CreateNamedRenderTargetTextureEx2(char const*,int,int,RenderTargetSizeMode_t,ImageFormat,MaterialRenderTargetDepth_t,uint,uint)
	virtual void BeginLightmapAllocationEv() = 0; //CMaterialSystem::BeginLightmapAllocation(void)
	virtual void EndLightmapAllocationEv() = 0; //CMaterialSystem::EndLightmapAllocation(void)
	virtual void AllocateLightmapEiiPiP9IMaterial() = 0; //CMaterialSystem::AllocateLightmap(int,int,int *,IMaterial *)
	virtual void AllocateWhiteLightmapEP9IMaterial() = 0; //CMaterialSystem::AllocateWhiteLightmap(IMaterial *)
	virtual void UpdateLightmapEiPiS0_PfS1_S1_S1_() = 0; //CMaterialSystem::UpdateLightmap(int,int *,int *,float *,float *,float *,float *)
	virtual void GetNumSortIDsEv() = 0; //CMaterialSystem::GetNumSortIDs(void)
	virtual void GetSortInfoEP25MaterialSystem_SortInfo_t() = 0; //CMaterialSystem::GetSortInfo(MaterialSystem_SortInfo_t *)
	virtual void GetLightmapPageSizeEiPiS0_() = 0; //CMaterialSystem::GetLightmapPageSize(int,int *,int *)
	virtual void ResetMaterialLightmapPageInfoEv() = 0; //CMaterialSystem::ResetMaterialLightmapPageInfo(void)
	virtual void ClearBuffersEbbb() = 0; //CMaterialSystem::ClearBuffers(bool,bool,bool)
	virtual IMatRenderContext *GetRenderContext() = 0; //CMaterialSystem::GetRenderContext(void)
	
	char pad_0004[10932]; //0x0004
	bool isGameRunning; //0x2AB8
}; //Size: 0x2ABC
static_assert(sizeof(IMaterialSystem) == 0x2ABC);

