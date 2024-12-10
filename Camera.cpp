#include "Structures.h"

#include "Camera.h"

//コンストラクタ
Camera::Camera()
	: isShake(false), shakeDuration(20), shakeCounter(0), magnitude(15),
	pos{ 325, 175 }, scale{ 1.0f, 1.0f }, theta(0.0f)
{
}

//矩形の単体シェイク処理
void Camera::Shake()
{
	if (shakeCounter < shakeDuration)
	{
		shakingPos.x = rand() % (magnitude * 2 + 1) - magnitude;
		shakingPos.y = rand() % (magnitude * 2 + 1) - magnitude;

		shakeCounter++;
	}
	else
	{
		shakingPos.x = 0;
		shakingPos.y = 0;
		shakeCounter = 0;
		isShake = false;
	}
}

//========================================================
// カメラ行列の更新
//========================================================

//掛け算行列の関数
Matrix3x3 Camera::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	return
	{
		matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0],
		matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1],
		matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2],
		matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0],
		matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1],
		matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2],
		matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0],
		matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1],
		matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2],
	};
}

//逆行列の関数
Matrix3x3 Camera::InverseMatrix(Matrix3x3 matrix)
{
	Matrix3x3 InverseMatrix;
	float determinant = matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1])
		- matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0])
		+ matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);

	InverseMatrix.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / determinant;
	InverseMatrix.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) / determinant;
	InverseMatrix.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / determinant;
	InverseMatrix.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) / determinant;
	InverseMatrix.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) / determinant;
	InverseMatrix.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / determinant;

	return InverseMatrix;

}

//回転行列の関数
Matrix3x3 Camera::MakeRotateMatrix(float rotateTheta)
{
	Matrix3x3 rotateMatrix;

	rotateMatrix.m[0][0] = cosf(rotateTheta);
	rotateMatrix.m[0][1] = sinf(rotateTheta);
	rotateMatrix.m[0][2] = 0;
	rotateMatrix.m[1][0] = -sinf(rotateTheta);
	rotateMatrix.m[1][1] = cosf(rotateTheta);
	rotateMatrix.m[1][2] = 0;
	rotateMatrix.m[2][0] = 0;
	rotateMatrix.m[2][1] = 0;
	rotateMatrix.m[2][2] = 1;

	return rotateMatrix;
}

//スケーリング行列の関数
Matrix3x3 Camera::MakeScaleMatrix(Vector2 scaling)
{
	Matrix3x3 scaleMatrix;

	scaleMatrix.m[0][0] = scaling.x;
	scaleMatrix.m[0][1] = 0;
	scaleMatrix.m[0][2] = 0;
	scaleMatrix.m[1][0] = 0;
	scaleMatrix.m[1][1] = scaling.y;
	scaleMatrix.m[1][2] = 0;
	scaleMatrix.m[2][0] = 0;
	scaleMatrix.m[2][1] = 0;
	scaleMatrix.m[2][2] = 1;

	return scaleMatrix;
}


//平行移動行列の関数
Matrix3x3 Camera::MakeTranslateMatrix(Vector2 translate)
{
	Matrix3x3 translateMatrix;

	translateMatrix.m[0][0] = 1;
	translateMatrix.m[0][1] = 0;
	translateMatrix.m[0][2] = 0;
	translateMatrix.m[1][0] = 0;
	translateMatrix.m[1][1] = 1;
	translateMatrix.m[1][2] = 0;
	translateMatrix.m[2][0] = translate.x;
	translateMatrix.m[2][1] = translate.y;
	translateMatrix.m[2][2] = 1;

	return translateMatrix;
}
Vector2 Camera::Transform(Vector2 vector, Matrix3x3 matrix)
{
	Vector2 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];


	result.x /= w;
	result.y /= w;
	return result;
}

//アフィン行列の関数
Matrix3x3 Camera::MakeAffineMatrix(Vector2 scaling, float rotate, Vector2 translate)
{
	//拡縮の行列
	Matrix3x3 scaleMatrix = Camera::MakeScaleMatrix(scaling);

	//回転の行列
	Matrix3x3 rotateMatrix = Camera::MakeRotateMatrix(rotate);

	//平行移動の行列
	Matrix3x3 translateMatrix = Camera::MakeTranslateMatrix(translate);

	Matrix3x3 scaleRotateMatrix = Camera::Multiply(scaleMatrix, rotateMatrix);
	Matrix3x3 affineMatrix = Camera::Multiply(scaleRotateMatrix, translateMatrix);

	return affineMatrix;
}


//矩形のワールド行列
Matrix3x3 Camera::MakeRectangleWorldMatrix(const RectangleObject* ro)
{
	return Camera::MakeAffineMatrix(
		ro->scale,
		ro->theta,
		{ ro->wCenterPos.x - Camera::pos.x, ro->wCenterPos.y - Camera::pos.y }
	);
}

//カメラのワールド行列
Matrix3x3 Camera::MakeCameraWorldMatrix()
{
	return Camera::MakeAffineMatrix(Camera::scale, Camera::theta, Camera::pos);
}

//ビュー行列
Matrix3x3 Camera::MakeViewMatrix()
{
	Matrix3x3 CameraWorldMatrix = Camera::MakeCameraWorldMatrix();
	return Camera::InverseMatrix(CameraWorldMatrix);
}

//正射影行列の関数
Matrix3x3 Camera::MakeOrthographicMatrix(float left, float top,
	float right, float bottom)
{
	Matrix3x3 result;

	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0.0f;

	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1.0f;

	return result;
}

//ビューポート行列
Matrix3x3 Camera::MakeViewportMatrix(float left, float top,
	float right, float bottom)
{
	Matrix3x3 result;

	result.m[0][0] = (right - left) / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = -(bottom - top) / 2.0f;
	result.m[1][2] = 0.0f;

	result.m[2][0] = left + (right - left) / 2.0f;
	result.m[2][1] = top + (bottom - top) / 2.0f;
	result.m[2][2] = 1.0f;

	return result;
}

//矩形をカメラ座標に変換

/// <summary>
/// カメラ座標に変換する関数
/// </summary>
/// <param name="ro">RectangleObject構造体</param>
/// <param name="camera">カメラ構造体</param>
void Camera::MakeCameraMatrix(RectangleObject* ro)
{
	// プレイヤーとカメラのワールド行列を作成
	Matrix3x3 playerWorldMatrix = Camera::MakeRectangleWorldMatrix(ro);

	// ビュー行列を逆行列で作成
	Matrix3x3 viewMatrix = Camera::MakeViewMatrix();

	// 正射影行列
	Matrix3x3 orthographic = Camera::MakeOrthographicMatrix(
		-kWindowWidth / 2.0f,
		kWindowHeight / 2.0f,
		kWindowWidth / 2.0f,
		-kWindowHeight / 2.0f
	);

	// ビューポート行列
	Matrix3x3 viewportMatrix = Camera::MakeViewportMatrix(0, 0, kWindowWidth, kWindowHeight);

	// 行列を順番に掛け算して最終的なカメラ行列を作成
	Matrix3x3 cameraMatrix = Camera::Multiply(playerWorldMatrix, viewMatrix);  // ワールド座標 -> ビュー座標
	cameraMatrix = Camera::Multiply(cameraMatrix, orthographic);              // ビュー座標 -> 正規化デバイス座標
	cameraMatrix = Camera::Multiply(cameraMatrix, viewportMatrix);            // 正規化デバイス座標 -> スクリーン座標

	// 矩形の位置を変換
	ro->sVertex.LT = Camera::Transform(ro->wVertex.LT, cameraMatrix);
	ro->sVertex.RT = Camera::Transform(ro->wVertex.RT, cameraMatrix);
	ro->sVertex.LB = Camera::Transform(ro->wVertex.LB, cameraMatrix);
	ro->sVertex.RB = Camera::Transform(ro->wVertex.RB, cameraMatrix);
}

//矩形のカメラのデバッグ用関数
void Camera::DebugCameraMovement(GameManager* gm, RectangleObject* ro)
{
	if (gm->keys[DIK_LEFT]) Camera::pos.x -= 5.0f;
	if (gm->keys[DIK_RIGHT]) Camera::pos.x += 5.0f;
	if (gm->keys[DIK_UP]) Camera::pos.y += 5.0f;
	if (gm->keys[DIK_DOWN]) Camera::pos.y -= 5.0f;

	if (gm->keys[DIK_Q])
	{
		Camera::theta -= 0.05f;
	}
	if (gm->keys[DIK_E])
	{
		Camera::theta += 0.05f;
	}

	if (gm->keys[DIK_Z])
	{
		ro->theta -= 0.05f;
	}
	if (gm->keys[DIK_X])
	{
		ro->theta += 0.05f;
	}

	if (gm->keys[DIK_R])
	{
		Camera::scale.x += 0.05f;
		Camera::scale.y += 0.05f;
	}
	if (gm->keys[DIK_T])
	{
		Camera::scale.x -= 0.05f;
		Camera::scale.y -= 0.05f;
	}

	if (gm->keys[DIK_C])
	{
		ro->scale.x -= 0.05f;
		ro->scale.y -= 0.05f;
	}
	if (gm->keys[DIK_V])
	{
		ro->scale.x += 0.05f;
		ro->scale.y += 0.05f;
	}
}

