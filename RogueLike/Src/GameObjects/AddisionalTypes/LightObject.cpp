#include "LightObject.h"
#include "../GameObject.h"
#include <math.h>
#include "rlgl.h"
#include "raymath.h"
#include "../Game.h"

LightObject::LightObject(float updateTimer)
{
    this->updateTimer = updateTimer;
}

LightObject::~LightObject()
{
    if (lightTexture.id > 0)
        UnloadRenderTexture(lightTexture);
}

void LightObject::update(float deltaTime)
{

    lightTimer += deltaTime;
    if (radius <= 0.0f)
        return;
    if(lightTexture.id<0)
        setRange(radius);
    timer -= deltaTime;
    if (timer > 0.0f)
        return;
    timer = updateTimer;
    GameObject* gm = dynamic_cast<GameObject*>(this);
    if (!gm)
        return;
    Rectangle pos = gm->getPos();
    lightPos = Vector2Add({ pos.x,pos.y }, lightPosDiff);

    valid = createLightFan();
    valid = true;
    generateTexture();
}

void LightObject::drawLight()
{
    if (!valid || radius <= 0.0f)
        return;
    BeginBlendMode(BLEND_CUSTOM);
    rlSetBlendFactors(0xffffffff, 0xffffffff, RL_MAX);
    Texture2D texture = lightTexture.texture;
    float radius = this->radius + (int)(zoom * sin(lightTimer));

    DrawTexturePro(texture, { 0.0f,0.0f,(float)texture.width,(float)-texture.height },
        { lightPos.x - radius, lightPos.y - radius ,radius * 2,radius * 2 }, { 0,0 }, 0, WHITE);
    EndBlendMode();
    //DrawTexturePro(texture, { 0.0f,0.0f,(float)texture.width,(float)-texture.height },
    //   { lightPos.x - radius, lightPos.y - radius ,radius * 2,radius * 2 }, { 0,0 }, 0, {255,0,0,69});
    //DrawCircle(lightPos.x, lightPos.y, radius, RED);

}

void LightObject::setRange(float range)
{
    this->radius = range;
    if (lightTexture.id > 0)
        UnloadRenderTexture(lightTexture);
    if (range > 0)
        lightTexture = LoadRenderTexture((int)(range * 2.0f / zoom), (int)(range * 2 / zoom));
}

void LightObject::generateTexture()
{
    if (!valid)
        return;
    Camera2D camera;
    camera.offset = { radius/zoom,radius/zoom };
    camera.target = lightPos;
    camera.rotation = 0;
    camera.zoom = 1.0f/zoom;
    BeginTextureMode(lightTexture);
    ClearBackground(BLACK);
    BeginMode2D(camera);

    Color end = colorEnd;
    end.a = 0;
    DrawCircleGradient((int)lightPos.x, (int)lightPos.y, radius, colorCenter, end);
    rlSetBlendMode(BLEND_MULTIPLIED);

    for (auto f : lightFan)
    {
        DrawTriangleFan(f.vertices, 4, BLACK);
    }
    EndBlendMode();
    

    EndMode2D();
    EndTextureMode();
}

bool LightObject::createLightFan()
{
    if (radius <= 0.0f)
        return false;
    Rectangle lightBox = { lightPos.x - radius,lightPos.y - radius,radius * 2,radius * 2 };
    std::list<Rectangle> shadowObjects = Game::getShadowsRecs(lightBox);
    lightFan.clear();
    for (auto shadow : shadowObjects)
    {
        //if (CheckCollisionPointRec(lightPos, shadow)) 
        //    return false;

        if (!CheckCollisionRecs(lightBox, shadow)) 
            continue;

        Vector2 sp = { shadow.x, shadow.y };
        Vector2 ep = { shadow.x + shadow.width, shadow.y };

        if (lightPos.y > ep.y) 
            computeShadowVolumeForEdge(sp, ep);
        sp = ep;
        ep.y += shadow.height;
        if (lightPos.x < ep.x) 
            computeShadowVolumeForEdge(sp, ep);
        sp = ep;
        ep.x -= shadow.width;
        if (lightPos.y < ep.y) 
            computeShadowVolumeForEdge(sp, ep);
        sp = ep;
        ep.y -= shadow.height;
        if (lightPos.x > ep.x) 
            computeShadowVolumeForEdge(sp, ep);

        ShadowGeometry sg;
        sg.vertices[0] = { shadow.x, shadow.y };
        sg.vertices[1] = { shadow.x, shadow.y + shadow.height };
        sg.vertices[2] = { shadow.x + shadow.width, shadow.y + shadow.height };
        sg.vertices[3] = { shadow.x + shadow.width, shadow.y };
        lightFan.push_back(sg);
    }

    return true;
}

void LightObject::computeShadowVolumeForEdge(Vector2 sp, Vector2 ep)
{
    float extension = radius * 2;

    Vector2 spVector = Vector2Normalize(Vector2Subtract(sp, lightPos));
    Vector2 spProjection = Vector2Add(sp, Vector2Scale(spVector, extension));

    Vector2 epVector = Vector2Normalize(Vector2Subtract(ep, lightPos));
    Vector2 epProjection = Vector2Add(ep, Vector2Scale(epVector, extension));
    ShadowGeometry sg;
    sg.vertices[0] = sp;
    sg.vertices[1] = ep;
    sg.vertices[2] = epProjection;
    sg.vertices[3] = spProjection;
    lightFan.push_back(sg);
}
