// ## 直すべき致命点（このままだと動かない／壊れる）

// ### 1) `ray` が列ごとにリセットされていない

// `decide_ray_dir()` が `ray->dir` を上書きではなく加算しているので、`x` が増えるたびに方向が累積します。

// * 対応：各列で **player.dir をベースに rayDir を作る**
// * 最低限：`init_ray()` を列ループ内で呼ぶ、または `decide_ray_dir()` に `base_dir` を渡す

// 例（列ごとに作り直す）：

// ```c
// t_vec2 base_dir = game->player.dir;
// ray.dir.x = base_dir.x + plane.pos.x * camera_x;
// ray.dir.y = base_dir.y + plane.pos.y * camera_x;
// ```

// ---

// ### 2) `dda.hit` が初期化されていない

// `step_until_hit()` は `while (dda->hit == 0)` なので、`hit` 未初期化だと未定義動作です。

// * 対応：`init_dda()` で `dda->hit = 0;` と `dda->side = 0;` を初期化

// ---

// ### 3) `dda.side` の型と値が壊れている

// `dda.side` は `char` なのに、`'x'` と `1` が混在しています。さらに `seek_perp_dist()` と `decide_wall_column()` が `side==0` を見ているので整合が取れていません。

// * 対応：`side` は **0/1 の int** にするのが安全（典型）

//   * `0`：x-side（縦壁）
//   * `1`：y-side（横壁）

// 例：

// ```c
// dda->side = 0; // init
// ...
// dda->side = 0; // x側を跨いだ
// ...
// dda->side = 1; // y側を跨いだ
// ```

// ---

// ### 4) `seek_perp_dist()` が未実装

// ここが 0 のままだと `line_height = frame_height / perp_dist;` で落ちます。

// * 対応：DDA後はこれで確定します。

// ```c
// void seek_perp_dist(t_dda *d)
// {
//     if (d->side == 0) d->perp_dist = d->side_dist_x - d->delta_dist_x;
//     else              d->perp_dist = d->side_dist_y - d->delta_dist_y;
//     if (d->perp_dist < 1e-6f) d->perp_dist = 1e-6f;
// }
// ```

// ---

// ### 5) `delta_dist_*` の `ULONG_MAX` は不適切

// `float` に `ULONG_MAX` は雑です。`FLT_MAX` か十分大きい `1e30f` の方が安全です。

// * 対応：`#include <float.h>` して `FLT_MAX` を使う

// ```c
// dda->delta_dist_x = (ray->dir.x == 0) ? FLT_MAX : fabsf(1.0f / ray->dir.x);
// ```

// ---

// ### 6) `decide_ray_dir()` の引数名が誤誘導

// `map_rows` ではなく画面幅 `screen_w` です。いまは `frame.w` を渡しているので動作は近いですが、読み違いの原因になります。

// ---

// ## 次に必要な最低限（単色壁が出るまで）

// ### A) 平面（plane）の設定が固定値なのは暫定としてOK。ただし回転時は dir と一緒に回す

// いま `init_plane(&plane, 0, 0.66f);` は「初期dirが(1,0)前提」の値です。

// * 東向き dir=(1,0) なら plane=(0,0.66) で合います
// * 北向き dir=(0,-1) なら plane=(0.66,0) が合います

// 暫定でもいいですが、最終的には `player` に plane を持たせて回転で一緒に回すのが自然です。

// ### B) `decide_wall_column()` の条件が誤り

// あなたの現在：

// ```c
// if (dda->side == 0) wall_col = pos.y + perp * ray.dir.y;
// else                wall_col = pos.x + perp * ray.dir.x;
// ```

// これは「side==0が縦壁」の前提なら正しいです。
// ただし現状の `side` が `'x'` / `1` なので必ず壊れます。上の **sideを0/1に統一**すれば通ります。

// さらにテクスチャ用なら必ず：

// ```c
// *wall_col -= floor(*wall_col); // [0,1)
// ```

// ---

// ## 安全に進める実装順（明日仕上げに向く順）

// 1. **sideを0/1に統一**、`hit` 初期化、`rayDir` を列ごとに再計算（累積を消す）
// 2. `seek_perp_dist()` 実装
// 3. `draw_to_frame_buffer()` を「単色縦線」で実装

//    * `x`, `draw_start`, `draw_end`, `color` だけでまず出す
// 4. その後に `wall_col -> tex_x/tex_y` を入れてテクスチャに拡張

// ---

// ## raycasting単体テスト（最小）

// MLXを使わずに、**DDAの出力だけ**テストできます。

// * 固定map（小さくて良い）
// * 固定pos/rayDir
// * 期待する `map_x,map_y,side,perp_dist` を assert

// これで「描画が黒い」系のバグ切り分けが速くなります。

// ---

// ## まとめ

// いまの構造（関数分割）は成立します。ですが現状は

// * rayDirの累積
// * hit未初期化
// * sideの型・値の不一致
// * perp_dist未実装

// があるので、そこを直せば「3Dの壁が出る」段階には乗ります。

// もし明日までに確実に進めるなら、あなたの `t_player`（dir/planeの持ち方）と `t_img`（put_pixel）のインターフェースに合わせて、`draw_to_frame_buffer()` の「単色縦線版」をそのまま貼れる形で書き起こします。
