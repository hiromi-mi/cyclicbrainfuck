# 2CyclicBrainfuck (未実装)

2Cyclic Brainfuck は Brainfuck をほんの少し変えただけの難解プログラミング言語です。

## Brainfuck との言語仕様の違い
2CyclicBrainfuck のソースコードは以下の2行からなります。
```
コマンド
命令配置
```

初期状態では `s = 61` です。
0起点のプログラム実行ステップ `step` ごとに `(入力命令 - '!' - step) mod s + '!'` をbrainfuck命令として解釈します。
命令と無関係の文字は無視され、プログラム実行ステップ `step` が1増加します。
ASCII CODE 128 以上は signed char 型の `s` にキャストされます。それ以降の命令は `-s` を法としてbrainfuck 命令として解釈します。

命令配置は次の2バイトの指定子の列となります。
`2CyclicBrainfuck命令` と `対応するBrainfuck命令` を順番に書き並べたものになります。
