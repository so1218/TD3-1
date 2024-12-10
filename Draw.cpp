#include "Structures.h"
#include "Player.h"

//矩形の描画関数
void DrawQuadWithData(RectangleObject* ro, float srcW, float srcH, int GH, int spriteNumX, int spriteNumY, unsigned int color)
{
    Novice::DrawQuad(
        static_cast<int>(ro->sVertex.LT.x),
        static_cast<int>(ro->sVertex.LT.y),
        static_cast<int>(ro->sVertex.RT.x),
        static_cast<int>(ro->sVertex.RT.y),
        static_cast<int>(ro->sVertex.LB.x),
        static_cast<int>(ro->sVertex.LB.y),
        static_cast<int>(ro->sVertex.RB.x),
        static_cast<int>(ro->sVertex.RB.y),
        int(srcW * spriteNumX), int(srcH * spriteNumY), int(srcW), int(srcH), GH, color);
}


Color HSVtoRGB(float h, float s, float v) {
    float r = 0;
    float g = 0;
    float b = 0;

    int i;
    float f, p, q, t;

    // 色相が360度までの範囲で、彩度と明度は[0, 1]
    if (s == 0) {
        r = g = b = v;
    }
    else {
        h /= 60;  // 色相を0〜6の範囲にスケーリング
        i = (int)h;  // 色相を60度単位で分ける
        f = h - i;   // 小数部分

        p = v * (1 - s);
        q = v * (1 - s * f);
        t = v * (1 - s * (1 - f));

        switch (i) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        }
    }

    // RGBは0〜1の範囲で計算されるので、0〜255の範囲にスケール
    return Color((unsigned int)(r * 255), (unsigned int)(g * 255));
}

// HSVから0xRRGGBBAAのunsigned intカラーコードを生成する関数
unsigned int HSVtoColorCode(float h, float s, float v) {
    // HSVをRGBに変換
    Color color = HSVtoRGB(h, s, v);

    // RGBAで返す 
    return (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}
