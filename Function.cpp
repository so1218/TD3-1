#include "Structures.h"

//ブレンドモードの更新処理
void UpdateBlendMode(BlendModeFunc* blendMode)
{

    switch (blendMode->mode)
    {
    case blendMode->None:

        Novice::SetBlendMode(kBlendModeNone);
        break;

    case blendMode->Normal:

        Novice::SetBlendMode(kBlendModeNormal);
        break;

    case blendMode->Add:

        Novice::SetBlendMode(kBlendModeAdd);
        break;

    case blendMode->Subtract:

        Novice::SetBlendMode(kBlendModeSubtract);
        break;

    case blendMode->Multiply:

        Novice::SetBlendMode(kBlendModeMultiply);
        break;

    case blendMode->Screen:

        Novice::SetBlendMode(kBlendModeScreen);
        break;

    case blendMode->Exclusion:

        Novice::SetBlendMode(kBlendModeExclusion);
        break;

    default:

        Novice::SetBlendMode(kBlendModeNone);
        break;

    }

}

// ブレンドモードのリセット処理
void ResetBlendMode()
{
    Novice::SetBlendMode(kBlendModeNormal);
}