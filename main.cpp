#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "LE2A_12_ホリ_ソウヘイ_タイトル";
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct Matrix4x4
{
	float m[4][4];
};

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label)
{
    Novice::ScreenPrintf(x, y, "%s", label);
    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f", matrix.m[row][column]);
        }
    }
}


// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; ++i) 
	{
		for (int j = 0; j < 4; ++j) 
		{
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k)
			{
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m)
{
    Matrix4x4 result{};
    float inv[16], det;
    const float* src = &m.m[0][0]; 

    inv[0] = src[5] * src[10] * src[15] -
        src[5] * src[11] * src[14] -
        src[9] * src[6] * src[15] +
        src[9] * src[7] * src[14] +
        src[13] * src[6] * src[11] -
        src[13] * src[7] * src[10];

    inv[4] = -src[4] * src[10] * src[15] +
        src[4] * src[11] * src[14] +
        src[8] * src[6] * src[15] -
        src[8] * src[7] * src[14] -
        src[12] * src[6] * src[11] +
        src[12] * src[7] * src[10];

    inv[8] = src[4] * src[9] * src[15] -
        src[4] * src[11] * src[13] -
        src[8] * src[5] * src[15] +
        src[8] * src[7] * src[13] +
        src[12] * src[5] * src[11] -
        src[12] * src[7] * src[9];

    inv[12] = -src[4] * src[9] * src[14] +
        src[4] * src[10] * src[13] +
        src[8] * src[5] * src[14] -
        src[8] * src[6] * src[13] -
        src[12] * src[5] * src[10] +
        src[12] * src[6] * src[9];

    inv[1] = -src[1] * src[10] * src[15] +
        src[1] * src[11] * src[14] +
        src[9] * src[2] * src[15] -
        src[9] * src[3] * src[14] -
        src[13] * src[2] * src[11] +
        src[13] * src[3] * src[10];

    inv[5] = src[0] * src[10] * src[15] -
        src[0] * src[11] * src[14] -
        src[8] * src[2] * src[15] +
        src[8] * src[3] * src[14] +
        src[12] * src[2] * src[11] -
        src[12] * src[3] * src[10];

    inv[9] = -src[0] * src[9] * src[15] +
        src[0] * src[11] * src[13] +
        src[8] * src[1] * src[15] -
        src[8] * src[3] * src[13] -
        src[12] * src[1] * src[11] +
        src[12] * src[3] * src[9];

    inv[13] = src[0] * src[9] * src[14] -
        src[0] * src[10] * src[13] -
        src[8] * src[1] * src[14] +
        src[8] * src[2] * src[13] +
        src[12] * src[1] * src[10] -
        src[12] * src[2] * src[9];

    inv[2] = src[1] * src[6] * src[15] -
        src[1] * src[7] * src[14] -
        src[5] * src[2] * src[15] +
        src[5] * src[3] * src[14] +
        src[13] * src[2] * src[7] -
        src[13] * src[3] * src[6];

    inv[6] = -src[0] * src[6] * src[15] +
        src[0] * src[7] * src[14] +
        src[4] * src[2] * src[15] -
        src[4] * src[3] * src[14] -
        src[12] * src[2] * src[7] +
        src[12] * src[3] * src[6];

    inv[10] = src[0] * src[5] * src[15] -
        src[0] * src[7] * src[13] -
        src[4] * src[1] * src[15] +
        src[4] * src[3] * src[13] +
        src[12] * src[1] * src[7] -
        src[12] * src[3] * src[5];

    inv[14] = -src[0] * src[5] * src[14] +
        src[0] * src[6] * src[13] +
        src[4] * src[1] * src[14] -
        src[4] * src[2] * src[13] -
        src[12] * src[1] * src[6] +
        src[12] * src[2] * src[5];

    inv[3] = -src[1] * src[6] * src[11] +
        src[1] * src[7] * src[10] +
        src[5] * src[2] * src[11] -
        src[5] * src[3] * src[10] -
        src[9] * src[2] * src[7] +
        src[9] * src[3] * src[6];

    inv[7] = src[0] * src[6] * src[11] -
        src[0] * src[7] * src[10] -
        src[4] * src[2] * src[11] +
        src[4] * src[3] * src[10] +
        src[8] * src[2] * src[7] -
        src[8] * src[3] * src[6];

    inv[11] = -src[0] * src[5] * src[11] +
        src[0] * src[7] * src[9] +
        src[4] * src[1] * src[11] -
        src[4] * src[3] * src[9] -
        src[8] * src[1] * src[7] +
        src[8] * src[3] * src[5];

    inv[15] = src[0] * src[5] * src[10] -
        src[0] * src[6] * src[9] -
        src[4] * src[1] * src[10] +
        src[4] * src[2] * src[9] +
        src[8] * src[1] * src[6] -
        src[8] * src[2] * src[5];

    det = src[0] * inv[0] + src[1] * inv[4] + src[2] * inv[8] + src[3] * inv[12];

    det = 1.0f / det;

    Matrix4x4 resultMatrix;
    for (int i = 0; i < 16; ++i)
    {
        ((float*)resultMatrix.m)[i] = inv[i] * det;
    }

    return resultMatrix;
}

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m)
{
    Matrix4x4 result{};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.m[i][j] = m.m[j][i];  // 行と列を反転
        }
    }
    return result;
}

// 単位行列の作成
Matrix4x4 MakeIdentity4x4()
{
    Matrix4x4 m = {};

    for (int i = 0; i < 4; ++i)
    {
        m.m[i][i] = 1.0f;
    }

    return m;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

    Matrix4x4 m1 = { 3.2f,0.7f,9.6f,4.4f,
                     5.5f,1.3f,7.0f,2.1f,
                     6.9f,8.0f,2.6f,1.0f,
                     0.5f,7.2f,5.1f,3.3f };

    Matrix4x4 m2 = { 4.1f,6.5f,3.3f,2.2f,
                     8.8f,0.6f,9.9f,7.7f,
                     1.1f,5.5f,6.6f,0.0f,
                     3.3f,9.9f,8.8f,2.2f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

        Matrix4x4 resultAdd = Add(m1, m2);
        Matrix4x4 resultSubtract = Subtract(m1, m2);
        Matrix4x4 resultMultiply = Multiply(m1, m2);
        Matrix4x4 inverseM1 = Inverse(m1);
        Matrix4x4 inverseM2 = Inverse(m2);
        Matrix4x4 transposeM1 = Transpose(m1);
        Matrix4x4 transposeM2 = Transpose(m2);
        Matrix4x4 identity = MakeIdentity4x4();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

        MatrixScreenPrintf(0, 0, resultAdd, "Add");
        MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
        MatrixScreenPrintf(0, kRowHeight * 10, resultMultiply, "Multiply");
        MatrixScreenPrintf(0, kRowHeight * 15, inverseM1, "inverseM1");
        MatrixScreenPrintf(0, kRowHeight * 20, inverseM2, "inverseM2");
        MatrixScreenPrintf(kColumnWidth * 5, 0, transposeM1, "transposeM1");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, transposeM2, "transposeM2");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 10, identity, "identity");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
