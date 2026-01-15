// 必須

// 2次元ベクトル

// 位置 (x, y)、方向 (dx, dy)、速度、加算・スカラー倍

// 「プレイヤー位置 + t * 方向」の形で光線を表現するために使います。

// 三角関数（sin, cos）

// 視線方向の回転、カメラ平面の生成

// 角度→方向ベクトル：(cosθ, sinθ)

// 回転：(x', y') = (x cosα - y sinα, x sinα + y cosα)

// 直線（半直線）とグリッドの交差

// 光線がどの格子線（x一定 / y一定）を次に跨ぐか、という計算

// 実装は「連続的な幾何」よりも「格子上の増分計算（DDA）」として扱うのが普通です。

// 距離と内積の直観（魚眼補正のため）

// 壁までの距離 dist をそのまま使うと魚眼になるので補正が必要です。

// 補正の中身は「視線方向への射影」になり、実装的には

// perpDist = dist * cos(Δangle)
// あるいは

// perpDist = dot(hitPos - playerPos, viewDir)
// のどちらかになります（後者が内積）。

// 比例・相似（投影の基本）

// 壁の高さ lineHeight を 1 / distance に比例させる関係

// 例：lineHeight = screenHeight / perpDist の形に落ちます。

// ほぼ必須（入れておくと破綻しにくい）

// 浮動小数点と誤差

// 0 除算回避、epsilon、境界上（ちょうど格子線上）でのぶれ対策

// “数式”というより「数値計算の扱い方」です。

// 角度の正規化

// 角度を [-π, π) あるいは [0, 2π) に保つ

// 回転し続けても値が壊れないための管理です。

// 床・天井テクスチャ（床キャスト）をやるなら

// 画面y座標から床上の点を逆算する比例関係

// ここも基本は「似た三角形」「距離の比例」です

// モジュール化する際
// 以下は「モジュール化する粒度」に合わせて、**機能（関数）単位**で再リスト化したものです。
// C想定で、`vec2`, `player`, `ray`, `hit`, `camera` などの構造体を前提にしています。

// ---

// ## // 必須

// ## // 2次元ベクトル（vec2）

// * `vec2_add(a, b) -> vec2`
//   位置更新、補助計算で使用。
// * `vec2_sub(a, b) -> vec2`
//   `hitPos - playerPos` を作るために使用。
// * `vec2_scale(v, s) -> vec2`
//   `playerPos + t * dir` の `t * dir` 部分で使用。
// * `vec2_dot(a, b) -> double`
//   魚眼補正を「射影」で行う場合に使用。
// * `vec2_len(v) -> double` / `vec2_len2(v) -> double`
//   距離計算が必要な設計なら使用（DDAでは必須ではないが、デバッグや別用途で便利）。

// ---

// ## // 三角関数（sin, cos）と回転

// * `angle_to_dir(theta) -> vec2`
//   `(cosθ, sinθ)` を返す。初期方向や角度更新後に使用。
// * `rotate_vec(v, alpha) -> vec2`
//   `(x', y') = (x cosα - y sinα, x sinα + y cosα)` を実装。
//   視線方向、カメラ平面の回転に使用。
// * `build_camera_plane(viewDir, fov) -> vec2`
//   カメラ平面ベクトルを作る関数。FOVを扱う設計ならここに閉じ込める。

// ---

// ## // 光線生成（スクリーン列 → ray）

// * `ray_from_column(playerPos, viewDir, camPlane, x, screenW) -> Ray`
//   スクリーンx（列）から `rayDir` を作る。
//   典型は `cameraX = 2*x/screenW - 1` を用いて `rayDir = viewDir + camPlane
// *cameraX`。

// ---

// ## // 直線（半直線）とグリッドの交差（DDA）

// ここがレイキャスティングの中核なので、関数を分けると良いです。

// * `dda_init(playerPos, rayDir) -> DDAState`
//   `mapX, mapY`（セル座標）、`stepX, stepY`、`sideDistX, sideDistY`、`deltaDistX,
//  deltaDistY` を初期化。
// * `dda_step(state) -> void`
//   `sideDistX < sideDistY` で次に跨ぐ格子線を決めて状態更新。
// * `dda_run_until_hit(state, map) -> Hit`
//   壁に当たるまで `dda_step` を繰り返し、ヒット位置情報（ヒットセル、side（縦壁/横壁）など）を返す。

// ---

// ## // 距離（魚眼補正込みの距離）

// * `perp_distance(playerPos, rayDir, hit, ddaState) -> double`
//   DDAの情報（`sideDist`や`map`境界）から「カメラ平面に対して垂直な距離」を出す。
//   方式は2系統あります。

//   **A. cos補正系**

//   * `perpDist = dist * cos(deltaAngle)`
//     角度差を持っている設計ならこれ。

//   **B. 射影（内積）系**

//   * `perpDist = dot(hitPos - playerPos, viewDir)`
//     `hitPos` を復元する設計ならこちら。

//   どちらにするかで、必要な補助関数（角度差 or hitPos計算）が変わります。

// ---

// ## // 比例・相似（投影：距離→壁の高さ）

// * `project_wall_height(screenH, perpDist) -> int lineHeight`
//   `lineHeight = screenH / perpDist` を核にする。
// * `compute_draw_range(screenH, lineHeight) -> (drawStart, drawEnd)`
//   画面に収まるようにクリップする。

// ---

// ## // ほぼ必須（入れておくと破綻しにくい）

// ## // 浮動小数点と誤差（数値ガード）

// * `safe_inv(x, eps) -> double`
//   `1/x` を使う場面で `0` 回避する。
// * `is_near_zero(x, eps) -> bool`
//   `deltaDistX = abs(1/rayDirX)` などの分母に対するガード。
// * `clamp_int(v, lo, hi) -> int`
//   `drawStart/drawEnd` のクリップなどで使用。
// * `apply_epsilon_to_border(pos, eps) -> vec2`（任意）
//   ちょうど格子線上にいるときの「どっちのセル扱い」を安定させる目的。

// ---

// ## // 角度の正規化

// * `wrap_angle_2pi(theta) -> double` または `wrap_angle_pi(theta)
// -> double`
//   角度を `[0, 2π)` または `[-π, π)` に保つ。
// * `update_player_angle(player, delta) -> void`
//   入力に応じて角度更新→正規化までをまとめる。

// ---

// ## // 床・天井テクスチャ（床キャスト）をやるなら

// 床天井は別モジュールに切り出すのが妥当です（壁より式が増えるため）。

// * `floorcast_row_distance(y, screenH, camZ) -> double`
//   画面yから「その行が表す床までの距離」を出す（似た三角形）。
// * `floorcast_world_step(playerPos, leftRayDir, rightRayDir, rowDist,
// screenW)
// ->(worldPos, step)`
//   行内で x を進めるごとの床座標の増分を作る。
// * `floorcast_sample_tex(worldPos) -> (tx, ty)`
//   床座標→テクスチャ座標への変換。

// ---

// ### 実装上のモジュール案（粒度の例）

// * `vec2.c/h`：ベクトル演算
// * `math_angle.c/h`：角度・回転・正規化
// * `camera.c/h`：カメラ平面生成、列→ray生成
// * `dda.c/h`：DDA初期化、step、hit取得
// * `projection.c/h`：距離→描画範囲
// * `floorcast.c/h`：床天井（入れるなら）

// 必要なら、この関数リストに合わせて「最低限の構造体（Ray/DDAState/Hit）」も定義して、依存関係（どのモジュールがどれをincludeするか）まで整理します。
