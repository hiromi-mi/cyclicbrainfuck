# Cyclic Brainfuck

Cyclic Brainfuck は Brainfuck をほんの少し変えただけの難解プログラミング言語です。

## 更新履歴

### Version 2.0.1

* `\n` を命令の一部として扱い予期せぬ命令が実行されていた問題を修正
* `.` コマンドとして `fputc()` のあとに強制的に `flush()` するように

### Version 2

* 命令配置を変更可能に
* 法の変更コマンドを追加

### Version 1

* 初版

## Brainfuck との言語仕様の違い
Cyclic Brainfuck のソースコードは以下の1行あるいは2行からなります。
なお、改行コードは LF を想定しています。
```
コマンド
```
もしくは
```
コマンド
命令配置
```

### コマンド
`s` の初期値は `s = 61` で、ASCII CODE 128 以上の値 `s'` が入力命令であれば、それ以降の命令は `s'` を signed char 型として解釈した上での `s := -s'` を法にして解釈します。(ASCII CODE 128 以上のときは法をとる操作は行なわれず、プログラム実行ステップも増加しません。)
ASCII CODE 127以下のときは 0起点のプログラム実行ステップ `step` ごとに `(入力命令 - '!' - step) mod s + '!'` をbrainfuck命令として解釈します。
命令と無関係の文字は無視され、プログラム実行ステップ `step` が1増加します。

### 命令配置

命令配置は次の2バイト指定子の列となります。命令配置を省略したり、後述する記述を行わなかったものは Brainfuck と同一になります。
初期 step での `CyclicBrainfuck命令` と `対応するBrainfuck命令` を順番に書き並べたものになります。
たとえば、`+-.+A-` とすると、 CyclicBrainfuck での `+` 命令は Brainfuck での `-` 命令に、`.` は `+` に、 `A` は `-` になります。

## 使い方
```
$ make
$ ./cyclicbrainfuck cyclic.cyclicbf
```

## セールスポイント

お楽しみください。

### Brainfuck の `++++++++` は `+*)(&%$#"!`

開始直後にメモリ0 に 8 を加えてみます。
Brainfuck なら `++++++++` と書きます。
一方Cyclic Brainfuck では、ステップ数を数えその分を差し引きます。
```
ステップ数 : Brainfuck 命令: Cyclic Brainfuck 命令
0 : + : +
1 : + : *
2 : + : )
3 : + : (
...
```
`man ascii` を見ながら、ぜひ ASCIIコードと仲良しになってください。
面倒かもしれませんが、ただただ遂行するのみです。

### Brainfuck `,++++++++` は `,*)(&%$#"!]`

今度は入力された値に8 を加えてみます。
Brainfuck で入力するコマンドは `,` なので、それに上のものを加えるだけ...

ではありません。
プログラムのどこかに1命令追加すると、その先の命令は全て1ずらす必要があります。
ずらしてるうちに端の '!' に到達して、さらに戻ると '`' に戻ります。
手作業で煩雑なら、インタプリタを書くといいかもしれません。

### 繰り返し範囲が毎回変化
たとえば 番地0の値を0 にする Brainfuck `[-]` を考えます。
`[,[` なら動くだろうか、と動きを見てみると (番地0上には4が入っています)
```
ステップ : 命令 : 説明
0 : [ : ループ開始
1 : , : 番地0 を3に
2 : [ : ループ継続、',' へ
3 : , : Brainfuck '/' (=','+3) として解釈され無視
4 : [ : Brainfuck 'V' として解釈され無視
ループ内だが終了 (番地0の値は3)
```

ループから外れて3 という値で正常終了します。
Brainfuck のループ`[` と `]` では実現できないような脱出条件が書け、
コードゴルフの夢が広がります。

### `[(60命令)]` 書くと？
簡単に動くプログラムを書きたいときには、`[]` の中を60命令に揃えることをオススメします。
同じループをくりかえしても `+` は `+` 、`-` は `-` です。簡単です。
なお、これは `s` の値を手動で変更しないことを前提としていますが...

### Version 2 での Codegolf の指針
多くのプログラミング言語においてそれぞれの命令がどの文字なのかは見掛け上の意味しかもちません。
例えば、C言語において `+` と `-` の意味を入れかえたとしても、それによりプログラミング言語上の記述量が変化することはありません。

一方、CyclicBrainfuck では多くの命令が変化します。
`[` から `]` の間になるべく少ない命令を書ける状況にすることが Brainfuck にはない特有の最適化の考慮事項です。
`!` になるべく近い ASCII CODE に必要な命令を詰め込んだり、同じ命令を繰り返しASCII CODE に埋め込みループ途中での `]` の複数の挙動を再現できるようにするか、が方針だと考えられます。


## Hello, world!
```
+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!#2[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876546E10/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@BAP<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHJYEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWY+TSRQPONMLKJIHGFEDCBA@?>=<;:987657F210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:98768G3210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?AP<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEGVBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQS%NMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)('&%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:9876543210/.-,+*)(*9%$#"!]\[ZYXWVUTSRQPONMLKJIHGFEDCBDS[
```

対応する Brainfuck ソースコードが書け
```
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.
.>
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
++++++++++++++++++++++++++++++++++++++++++++.>
++++++++++++++++++++++++++++++++.>
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>
+++++++++++++++++++++++++++++++++.>
```

## `cat`

```
>*Y9()8$%"#]![\YZWXUVSTQROPMNKLIJGHEFCDAB?@=>;<9:78563412/0-.+,[D
```
(入力としては 1 から254 までを想定)

## ほかの例

### Esolang Golf Contest #6
[shinh さんによる 55バイト解答](https://https://gist.github.com/shinh/fac3952336776d8dc34433a94474bdad)

こちらは法を9 として `>` が複数の意味を持つ高度なプログラミングが行なわれています.

## Author
[hiromi-mi](https://hiromi-mi.github.io)

このファイルには若干の誇張や曲解が含まれていますが、残念ながらスーパー牛さんパワーはありません。
