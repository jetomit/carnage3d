#pragma once

#include "GameDefs.h"
#include "TrimeshBuffer.h"
#include "Sprite2D.h"

class RenderView;

// defines renderer class for 2d sprites
class SpriteBatch final: public cxx::noncopyable
{
public:
    // init/deinit internal resources of sprite batch
    bool Initialize();
    void Deinit();

    // render all batched sprites
    void Flush(RenderView* renderview);

    // discard all batched sprites
    void Clear();

    // add sprite to batch but does not draw it immediately
    // @param sourceSprite: Source sprite data
    void DrawSprite(const Sprite2D& sourceSprite);

private:
    void SortSpritesList();
    void GenerateSpritesBatches();
    void RenderSpritesBatches(RenderView* renderview);

private:
    // single batch of drawing sprites
    struct DrawSpriteBatch
    {
        unsigned int mFirstVertex;
        unsigned int mFirstIndex;
        unsigned int mVertexCount;
        unsigned int mIndexCount;
        GpuTexture2D* mSpriteTexture;
    };
    // all sprites stored as is until they needs to be flushed
    std::vector<Sprite2D> mSpritesList;

    // draw data buffers
    std::vector<SpriteVertex3D> mDrawVertices;
    std::vector<DrawIndex> mDrawIndices;

    std::list<DrawSpriteBatch> mBatchesList;
    TrimeshBuffer mTrimeshBuffer;
};