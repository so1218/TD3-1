#include "Structures.h"
#include "Matrix.h"

//矩形の単体シェイク処理
void RectangleShakeCamera(RectangleObject* ro) 
{
    if (ro->camera.shakeCounter < ro->camera.shakeDuration)
    {
        ro->camera.randCamera.x = rand() % (ro->camera.magnitude * 2 + 1) - ro->camera.magnitude;
        ro->camera.randCamera.y = rand() % (ro->camera.magnitude * 2 + 1) - ro->camera.magnitude;
   
		ro->camera.shakeCounter++;
        
    }
    else 
    {
        // シェイク終了後にカメラを元の位置に戻す
        ro->camera.randCamera.x = 0;
        ro->camera.randCamera.y = 0;
        ro->camera.shakeCounter = 0; // カウンターをリセット
        
		ro->camera.isShake = false;
    }
}

//========================================================
// カメラ行列の更新
//========================================================

//プレイヤーのワールド行列
Matrix3x3 MakePlayerWorldMatrix(const RectangleObject* ro, const Camera& camera)
{
	return MakeAffineMatrix(
		ro->scale,
		ro->theta,
		{ ro->centerPos.x - camera.pos.x, ro->centerPos.y - camera.pos.y }
	);
}

//カメラのワールド行列
Matrix3x3 MakeCameraWorldMatrix(const Camera& camera)
{
	return MakeAffineMatrix(camera.scale, camera.theta, camera.pos);
}

//ビュー行列
Matrix3x3 MakeViewMatrix(const Camera& camera)
{
	Matrix3x3 CameraWorldMatrix = MakeCameraWorldMatrix(camera);
	return InverseMatrix(CameraWorldMatrix);
}

//正射影行列
Matrix3x3 MakeOrthographicMatrix()
{
	return MakeOrthographicMatrix(
		-kWindowWidth / 2.0f,
		kWindowHeight / 2.0f,
		kWindowWidth / 2.0f,
		-kWindowHeight / 2.0f
	);
}

//ビューポート行列
Matrix3x3 MakeViewportMatrix()
{
	return MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight);
}

//矩形をカメラ座標に変換
void MakeCameraMatrix(RectangleObject* ro, const Camera& camera)
{
	// プレイヤーとカメラのワールド行列を作成
	Matrix3x3 playerWorldMatrix = MakePlayerWorldMatrix(ro, camera);

	// ビュー行列を逆行列で作成
	Matrix3x3 viewMatrix = MakeViewMatrix(camera);

	// 正射影行列
	Matrix3x3 orthographic = MakeOrthographicMatrix();

	// ビューポート行列
	Matrix3x3 viewportMatrix = MakeViewportMatrix();

	// 行列を順番に掛け算して最終的なカメラ行列を作成
	Matrix3x3 cameraMatrix = Multiply(playerWorldMatrix, viewMatrix);  // ワールド座標 -> ビュー座標
	cameraMatrix = Multiply(cameraMatrix, orthographic);              // ビュー座標 -> 正規化デバイス座標
	cameraMatrix = Multiply(cameraMatrix, viewportMatrix);            // 正規化デバイス座標 -> スクリーン座標

	// 矩形の位置を変換
	ro->sVertex.LT = Transform(ro->wVertex.LT, cameraMatrix);
	ro->sVertex.RT = Transform(ro->wVertex.RT, cameraMatrix);
	ro->sVertex.LB = Transform(ro->wVertex.LB, cameraMatrix);
	ro->sVertex.RB = Transform(ro->wVertex.RB, cameraMatrix);

}

//矩形のカメラのデバッグ用関数
void DebugCameraRectangle(GameManager* gm, RectangleObject* ro)
{
	if (gm->keys[DIK_LEFT])
	{
		ro->camera.pos.x -= 5.0f;
	};
	if (gm->keys[DIK_RIGHT])
	{
		ro->camera.pos.x += 5.0f;
	}
	if (gm->keys[DIK_UP])
	{
		ro->camera.pos.y += 5.0f;
	}
	if (gm->keys[DIK_DOWN])
	{
		ro->camera.pos.y -= 5.0f;
	}

	if (gm->keys[DIK_Q])
	{
		ro->camera.theta -= 0.05f;
	}
	if (gm->keys[DIK_E])
	{
		ro->camera.theta += 0.05f;
	}

	if (gm->keys[DIK_R])
	{
		ro->theta -= 0.05f;
	}
	if (gm->keys[DIK_T])
	{
		ro->theta += 0.05f;
	}

	if (gm->keys[DIK_Y])
	{
		ro->scale.x -= 0.05f;
		ro->scale.y -= 0.05f;
	}
	if (gm->keys[DIK_U])
	{
		ro->scale.x += 0.05f;
		ro->scale.y += 0.05f;
	}

	if (gm->keys[DIK_Z]) {
		ro->camera.scale.x -= 0.05f;
		ro->camera.scale.y -= 0.05f;
	}
	if (gm->keys[DIK_X]) {
		ro->camera.scale.x += 0.05f;
		ro->camera.scale.y += 0.05f;
	}
}