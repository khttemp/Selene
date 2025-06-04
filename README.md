# Selene
たぶん、20071101バージョンのSelene

# モデルフォーマット仕様

[【原本】](https://web.archive.org/web/20081229212402/http://selene-lue.halfmoon.jp/index.php?%E3%83%A2%E3%83%87%E3%83%AB%E3%83%95%E3%82%A9%E3%83%BC%E3%83%9E%E3%83%83%E3%83%88%E4%BB%95%E6%A7%98)

 * [最初に](#最初に-)
 * [データ構造](#データ構造-)
 * [基本定義](#基本定義-)
 * [全体構造](#全体構造-)
 * [チャンク解説](#チャンク解説-)
   * [SMF](#smf-)
   * [FRM](#frm-)
     * [OBB(FRM)](#obbfrm-)
   * [ANIS](#anis-)
     * [ANI](#ani-)
   * [MESH](#mesh-)
     * [OBB(MESH)](#obbmesh-)
     * [BONE](#bone-)
     * [V_PC](#v_pc-)
     * [V_N](#v_n-)
     * [V_B](#v_b-)
     * [V_A](#v_a-)
     * [V_UV](#v_uv-)
     * [IDX2](#idx2-)
     * [IDX4](#idx4-)
   * [MTRL](#mtrl-)
     * [TEXC](#texc-)
     * [TEXL](#texl-)
     * [TEXE](#texe-)
     * [TEXS](#texs-)
     * [TEXN](#texn-)
     * [DRAW](#draw-)
     * [ZTES](#ztes-)
     * [ZWRI](#zwri-)
     * [ATES](#ates-)
     * [ABND](#abnd-)
     * [CULL](#cull-)
     * [LGT](#lgt-)
     * [DIFF](#diff-)
     * [EMIS](#emis-)
     * [SPEC](#spec-)
     * [BUMP](#bump-)
   * [C_AT](#c_at-)
   * [C_FC](#c_fc-)
   * [C_VX](#c_vx-)
 * [チャンクの取得方法の例](#チャンクの取得方法の例-)

## 最初に [↑](#モデルフォーマット仕様)

Seleneでは独自のモデルフォーマットを利用しています。

これはエンジン側で複数のモデルの読み込みを対応するとメンテナンスが面倒になるのと、

エンジンでしか使わないパラメーターを埋め込ませるためです。

## データ構造 [↑](#モデルフォーマット仕様)

SMFファイルはチャンクの塊で構成されています。

いわゆるWAVEファイルやLightwave Objectファイルの構造です。

またエンディアンはリトルです。

<br>

データの先頭にはデータの種類とサイズが定義された構造体が配置されています。

<br>

```
struct SMF_CHUNK
{
    long Chunk;          // チャンクID
    long Size;           // チャンクサイズ
};
```

## 基本定義 [↑](#モデルフォーマット仕様)

SMFファイル内で固定されている基本的な定義は以下のようになっています。

```
#define SMF_VERSION_GUID        0x20071101              // バージョン識別子
#define MAX_BONE_COUNT          (40)                    // ボーン数
#define MAX_NAME_SIZE           (64)                    // 名前用サイズ
```

3要素ベクトル構造体

```
struct SMF_VECTOR3
{
    float x;
    float y;
    float z;
};
```

4要素ベクトル構造体

```
struct SMF_VECTOR4
{
    float x;
    float y;
    float z;
    float w;
};
```

マトリックス構造体

```
struct SMF_MATRIX
{
    SMF_VECTOR4 x;
    SMF_VECTOR4 y;
    SMF_VECTOR4 z;
    SMF_VECTOR4 w;
};
```

平面構造体

```
struct SMF_PLANE
{
    SMF_VECTOR3 vNormal;
    float d;
};
```

## 全体構造 [↑](#モデルフォーマット仕様)

```
SMF
FRM
  OBB
ANIS
  ANI
MESH
  OBB
  BONE
  V_PC
  V_N
  V_B
  V_A
  V_UV
  IDX2/IDX4
  MTRL
    TEXC
    TEXL
    TEXE
    TEXS
    TEXN
    DRAW
    ZTES
    ZWRI
    ATES
    ABND
    CULL
    LGT
    DIFF
    EMIS
    SPEC
    BUMP
  C_AT
  C_FC
  C_VX
```

## チャンク解説 [↑](#モデルフォーマット仕様)

### SMF [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_FILEHEAD
{
    unsigned long Guid;            // バージョン識別子(=SMF_VERSION_GUID)
    long MeshCount;                // メッシュの数
    long FrameCount;               // フレームの数
    long AnimationSetCount;        // アニメーションの数
};
```

ファイルの先頭には必ずこのチャンクがあります。

最低限の基本的な情報がここに格納されています。

<br>

### FRM [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_FRAMEDATA
{
    SMF_MATRIX mTransform;               // フレーム用変換行列(アニメーションがない場合のワールド変換に適用)
    char Name[MAX_NAME_SIZE];            // フレームの名前
    long MeshNo;                         // 所持しているメッシュのインデックス（ない場合は-1）
    long ParentFrameNo;                  // 親のフレームのインデックス（ない場合は-1）
};
```

フレーム用のチャンクです。

SMF_FILEHEADのFrameCountメンバの数だけあります。

このチャンクではサブチャンクを持っている場合があるので、

サイズは固定ではありません。

<br>

### OBB(FRM) [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_OBBDATA
{
    SMF_VECTOR3 vCenter;           // 中心座標
    SMF_VECTOR3 vAxis[3];          // ローカルXYZ軸
    float fLength[3];              // XYZ軸の長さ
};
```

フレームによってはバウンディングを持っているものがあります。

このバウンディングはフレームが所持しているコリジョン用のバウンディングです。

<br>

### ANIS [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_ANIMATIONSETDATA
{
    char Name[MAX_NAME_SIZE];      // アニメーションの名前
    long AnimationCount;           // アニメーションデータの数
    long LastTime;                 // アニメーションの最終時間（=長さ）
};
```

アニメーションの用のチャンクです。

SMF_FILEHEADのAnimationSetCountの数だけあります。

このチャンクはアニメーションのデータを定義するサブチャンクを含んでいます。

<br>

### ANI [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_ANIMATIONDATA
{
    long TargetFrame;            // 適用する対象のフレームのインデックス
    long KeyMaxScale;            // 拡大縮小キーの数
    long KeyMaxRotate;           // 回転キーの数
    long KeyMaxTranslate;        // 移動キーの数
};
```

アニメーションデータのチャンクです。

この構造体で定義されている分のデータが続いて格納されています。

構造的には以下のように配置されています。

```
SMF_ANIMATIONDATA
  SMF_ANIMATIONKEY_SCALE      [ SMF_ANIMATIONDATA::KeyMaxScale ]
  SMF_ANIMATIONKEY_ROTATE     [ SMF_ANIMATIONDATA::KeyMaxRotate ]
  SMF_ANIMATIONKEY_TRANSLATE  [ SMF_ANIMATIONDATA::KeyMaxTranslate ]
```

それぞれの構造体は以下のように定義されています。

```
// 拡大縮小用キーフレーム
struct SMF_ANIMATIONKEY_SCALE
{
    long Time;       // 時間
    float x;         // X軸拡大縮小率(1.0=100%)
    float y;         // Y軸拡大縮小率(1.0=100%)
    float z;         // Z軸拡大縮小率(1.0=100%)
};

// 回転用キーフレーム
struct SMF_ANIMATIONKEY_ROTATE
{
    long Time;       // 時間
    float x;         // クォータニオンX成分
    float y;         // クォータニオンY成分
    float z;         // クォータニオンZ成分
    float w;         // クォータニオンW成分
};

// 移動用キーフレーム
struct SMF_ANIMATIONKEY_TRANSLATE
{
    long Time;       // 時間
    float x;         // X軸位置
    float y;         // Y軸位置
    float z;         // Z軸位置
};
```

<br>

### MESH [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_MESHDATA
{
    char Name[MAX_NAME_SIZE];   // メッシュの名前
    long MaterialCount;         // 所持しているマテリアルの数
};
```

メッシュ用のチャンクです。

SMF_FILEHEADのMeshCountメンバの数だけあります。

このチャンクではマテリアルの情報やメッシュのデータのサブチャンクを持っています。

<br>

### OBB(MESH) [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_OBBDATA
{
    SMF_VECTOR3 vCenter;           // 中心座標
    SMF_VECTOR3 vAxis[3];          // ローカルXYZ軸
    float fLength[3];              // XYZ軸の長さ
};
```

ビューカリング用のバウンディングデータです。

Seleneではこのバウンディングを利用してカメラ外のメッシュの描画をスキップします。

<br>

### BONE [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_BONEDATA
{
    SMF_MATRIX mBoneOffset;     // ボーンのローカルオフセット行列（変換前に適用してボーンを正しい姿勢に変換するため）
    long FrameNo;               // 骨の対象となるフレームのインデックス（骨変換用の行列はこのフレームから取ってくる）
};
```

メッシュが持っている骨のデータが格納されています。

骨の数は、「SMF_CHUNK::Size / sizeof(SMF_BONEDATA)」で求めることができます。

<br>

### V_PC [↑](#モデルフォーマット仕様)

データ配置

```
SMF_VECTOR3
unsigned long
```

頂点データ用のチャンクです。

このチャンクでは「頂点の位置」と「頂点の色」が格納されています。

頂点の数は、「SMF_CHUNK::Size / (sizeof(SMF_VECTOR3)+sizeof(unsigned long))」で求めることができます。

このチャンクはメッシュには必ず含まれていて、ここで求めた頂点数はその他全ての頂点データチャンクで一致しています。

<br>

### V_N [↑](#モデルフォーマット仕様)

データ配置

```
SMF_VECTOR3
```

頂点データ用のチャンクです。

このチャンクでは「頂点の法線」が格納されています。

ライティングに利用されますが、ライティングを行わないモデルでも含まれます。

<br>

### V_B [↑](#モデルフォーマット仕様)

データ配置

```
SMF_VECTOR3
```

頂点データ用のチャンクです。

このチャンクでは「頂点の接線」が格納されています。

法線バンプマッピングで利用され、テクスチャが張られていないモデルやライティングを行わないメッシュには含まれません。

<br>

### V_A [↑](#モデルフォーマット仕様)

データ配置

```
float
unsigned char [ 4 ]
```

頂点データ用のチャンクです。

このチャンクでは「頂点の骨インデックス」と「頂点の骨重み」が格納されています。

ボーンアニメーションで利用され、ボーンアニメーションを行わないメッシュには含まれません。

<br>

### V_UV [↑](#モデルフォーマット仕様)

データ配置

```
float [ 2 ]
float [ 2 ]
```

頂点データ用のチャンクです。

このチャンクでは「頂点のテクスチャUV」と「頂点のライトマップ用テクスチャUV」が格納されています。

テクスチャマッピングで利用され、テクスチャが張られていないメッシュには含まれません。

<br>

### IDX2 [↑](#モデルフォーマット仕様)

データ配置

```
unsigned short
```

頂点インデックス用のチャンクです。

頂点数が65535以下の場合はこの16BITインデックスが利用されます。

インデックス3つで1つのポリゴンを定義しています。

インデックスの数は「SMF_CHUNK::Size / sizeof(unsigned short)」で求めることができ、 「インデックスの数 / 3」がポリゴン数になります。

<br>

### IDX4 [↑](#モデルフォーマット仕様)

データ配置

```
unsigned long
```

頂点インデックス用のチャンクです。

頂点数が65536以上の場合はこの32BITインデックスが利用されます。

インデックス3つで1つのポリゴンを定義しています。

インデックスの数は「SMF_CHUNK::Size / sizeof(unsigned long)」で求めることができ、 「インデックスの数 / 3」がポリゴン数になります。

<br>

### MTRL [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_MATERIAL
{
    char Name[MAX_NAME_SIZE];   // マテリアル名
    long PolygonStart;          // ポリゴン開始位置（x3＝Index）
    long PolygonCount;          // ポリゴン数
    long VertexStart;           // 頂点開始位置
    long VertexCount;           // 頂点数
};
```

メッシュのマテリアルに関する情報が格納されています。

マテリアルはメッシュの描画に関するパラメーターを保持しています。

<br>

### TEXC [↑](#モデルフォーマット仕様)

データ構造

```
char [ MAX_NAME_SIZE ]
```

テクスチャ名チャンク。

メッシュに貼られている通常のテクスチャのファイル名です。

<br>

### TEXL [↑](#モデルフォーマット仕様)

データ構造

```
char [ MAX_NAME_SIZE ]
```

テクスチャ名チャンク。

メッシュに貼られているライトマップテクスチャのテクスチャのファイル名です。

<br>

### TEXE [↑](#モデルフォーマット仕様)

データ構造

```
char [ MAX_NAME_SIZE ]
```

テクスチャ名チャンク。

メッシュに貼られているキューブ環境マップのテクスチャのファイル名です。

このテクスチャはキューブマップ形式のDDSです。

<br>

### TEXS [↑](#モデルフォーマット仕様)

データ構造

```
char [ MAX_NAME_SIZE ]
```

テクスチャ名チャンク。

メッシュに貼られているスペキュラー用のテクスチャのファイル名です。

<br>

### TEXN [↑](#モデルフォーマット仕様)

データ構造

```
char [ MAX_NAME_SIZE ]
```

テクスチャ名チャンク。

メッシュに貼られている法線マップ用のテクスチャのファイル名です。

<br>

### DRAW [↑](#モデルフォーマット仕様)

データ構造

```
unsigned long
```

マテリアルの描画属性が格納されています。

描画属性は以下のいずれかになります。

```
enum eSMFDrawType
{
    SMF_DRAW_NORMAL,
    SMF_DRAW_BLEND,
    SMF_DRAW_ADD,
    SMF_DRAW_ADD_NOALPHA,
    SMF_DRAW_SUB,
    SMF_DRAW_SUB_NOALPHA,
    SMF_DRAW_MULTIPLE,
};
```

<br>

### ZTES [↑](#モデルフォーマット仕様)

データ構造

```
unsigned long
```

Zテストを行うかどうかのフラグが0,1で格納されています。

<br>

### ZWRI [↑](#モデルフォーマット仕様)

データ構造

```
unsigned long
```

Z書き込みを行うかどうかのフラグが0,1で格納されています。

<br>

### ATES [↑](#モデルフォーマット仕様)

データ構造

```
unsigned long
```

アルファテストを行うかどうかのフラグが0,1で格納されています。

<br>

### ABND [↑](#モデルフォーマット仕様)

データ構造

```
unsigned long
```

アルファテストを行う場合の閾値が格納されています。

ここで指定した値以下のアルファの場合はピクセルの描画カットされます。

<br>

### CULL [↑](#モデルフォーマット仕様)

データ構造

```
unsigned long
```

背面カリングを行うかどうかのフラグが0,1で格納されています。

Seleneでは左手座標系なので時計回りが表面になります。

<br>

### LGT [↑](#モデルフォーマット仕様)

データ構造

```
unsigned long
```

ライティングを行うかどうかのフラグが0,1で格納されています。

<br>

### DIFF [↑](#モデルフォーマット仕様)

データ構造

```
SMF_VECTOR4
```

拡散反射の色が格納されています。

<br>

### EMIS [↑](#モデルフォーマット仕様)

データ構造

```
SMF_VECTOR3
```

自己発光の色が格納されています。

<br>

### SPEC [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_SPECULAR
{
    SMF_VECTOR3 vSpecular;    // スペキュラーの色
    float fRefractive;        // 反射率（大きいほど強い反射）
    float fRoughly;           // 荒さ（大きいほどソフトな反射）
};
```

スペキュラーライティングを行う場合にこのチャンクが存在します。

<br>

### BUMP [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_BUMPMAP
{
     float fParallaxDepth;   // 視差マップ用の視差
};
```

法線バンプマッピングを行う場合にこのチャンクが存在します。

<br>

### C_AT [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_COLLISION_ATTRIBUTE
{
    long Start;         // 面の開始位置
    long Count;         // 面の数
    long Attribute;     // 面の属性
};
```

コリジョン用データの属性を定義するためのチャンクです。

<br>

### C_FC [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_COLLISION_FACE
{
    long Attribute;     // 面の属性
    long Index[3];      // 面を構成する頂点のインデックス
    SMF_PLANE Plane;    // 面データ
};
```

コリジョン用の面データを定義するためのチャンクです。

<br>

### C_VX [↑](#モデルフォーマット仕様)

使用構造体

```
struct SMF_COLLISIONVERTEX
{
    SMF_VECTOR3 Position;    // 頂点の位置
    unsigned long Color;     // 頂点の色
    SMF_VECTOR3 Normal;      // 頂点の法線
};
```

コリジョン用の頂点データを定義するためのチャンクです。

## チャンクの取得方法の例 [↑](#モデルフォーマット仕様)

```
 unsigned long Size;
 unsigned char *pData = pSrc;
 while ( Pos < Size )
 {
   // チャンク取得
   SMF_CHUNK *pChunk = (SMF_CHUNK*)pData;
   pData += sizeof(SMF_CHUNK);
   Pos += sizeof(SMF_CHUNK);

   // チャンク解析
   switch ( pChunk->Chunk )
   {
   case 'SMF':  //------------------------------------ ファイルヘッダ
     if ( !Load_SMF( pData, pChunk->Size ) )
     {
       delete [] pSrc;
       return false;
     }
     break;
   case 'FRM':  //------------------------------------ フレーム
     Load_FRM( pData, pChunk->Size );
     break;
   case 'ANIS': //------------------------------------ アニメーションセット
     Load_ANIS( pData, pChunk->Size );
     break;
   case 'MESH': //------------------------------------ メッシュ
     Load_MESH( pData, pChunk->Size );
     break;
   }

   // チャンクサイズ分進める
   pData += pChunk->Size;
   Pos += pChunk->Size;
 }
```