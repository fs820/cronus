//--------------------------------------------
//
// レンダラーインターフェース [renderer.h]
// Author: Fuma Sato
//
//--------------------------------------------
#pragma once
#include "graphics_types.h" // Vertex3D

class Renderer;
class Window;

namespace gui
{
    void init(const Window& window, const Renderer& renderer);
}

class RendererImpl;
class TextureManager;
class Scene;
struct TextureData;

//----------------------------
// レンダラー (外部インターフェース)
//----------------------------
class Renderer
{
public:
    Renderer();
    ~Renderer();

    void init(HWND handle, long width, long height);
    void uninit();
    bool render(const Scene& scene);
    void beginShadow(Matrix lightView, Matrix lightProj);
    void endShadow();
    void beginGeometry(Matrix cameraView, Matrix cameraProj);
    void endGeometry();
    void beginDecal(Matrix cameraView, Matrix cameraProj);
    void endDecal();
    void beginForward(Matrix cameraView, Matrix cameraProj);
    void endForward();
    void beginUI(bool isUIOnly = false);
    void endUI();
    void present();

    bool uploadTextures(const TextureManager& textureManager, unsigned int maxThread, std::function<bool(std::string_view, int, int)> progressCallback = {});

    MeshHandle createMesh(unsigned int stride, const void* vertices, size_t verticesCount, const void* indices, size_t indicesCount);
    bool setMesh(const MeshHandle& handle);
    bool setTexture(const TextureHandle& handle);
    bool setTransformWorld(const Matrix& matrix);
    bool setTransformView(const Matrix& matrix);
    bool setTransformProjection(const Matrix& matrix);
    bool setCameraPosition(const Vector3& cameraPos);
    bool setMaterial(const Material& material);
    bool setLight(std::span<const LightData> lights, const Color& ambient);
    bool setFog(const FogData& fog);
    bool setBoneTransforms(std::span<const Matrix> boneTransforms);
    void setOutlineData(Color color, float width);
    bool drawMesh(VertexShaderType vertexShaderType, const MeshHandle& handle);
    bool drawIndexedPrimitive(VertexShaderType vertexShaderType, int indexCount, unsigned int startIndexLocation, unsigned int baseVertexLocation);
    void drawDecal(Matrix transform, const MeshHandle& handle, Color color);
    void drawLightingPass();
    void drawPostProcessPass(PostProcessShaderMask mask, ToneMappingType type);
    void drawString(std::string_view string, Vector2 pos = { 0,0 }, Color color = Color::White(), float angle = 0.0f, Vector2 scale = { 1,1 });

    void setShadowMode();
    void setGeometryMode();
    void setDecalMode();
    void setForwardMode();
    void setUIMode();
    void setOutlineMode();
    void setSkyMode();
    void setBlendMode(BlendMode blendMode);
    void setRasMode(RasMode rasMode);
    void setDepthMode(DepthMode depthMode);
    void setSampMode(SampMode sampMode);
    void setScissorRect(int left, int top, int right, int bottom);

    void onResize(int width, int height);

    HWND getRegisteredHWND() const;
    void getScreenSizeMagnification(Vector2& magnification) const;
    void getViewportSize(Vector2& size) const;

private:
    // ↓ friend Gui
    friend void gui::init(const Window& window, const Renderer& renderer);
    ID3D11Device* getDevice() const;
    ID3D11DeviceContext* getContext() const;
    // ↑
    
    std::unique_ptr<RendererImpl> m_pImpl;
};
